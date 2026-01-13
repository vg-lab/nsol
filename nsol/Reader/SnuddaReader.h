/*
 * Copyright (c) 2014-2025 GMRV/URJC.
 *
 * Authors: Felix de las Pozas <felix.delaspozas@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#ifndef __NSOL__SNUDDA_SCENE_READER__
#define __NSOL__SNUDDA_SCENE_READER__

// Nsol
#include "../NsolTypes.h"
#include "../Stats/ColumnStats.h"
#include "../Stats/MiniColumnStats.h"
#include "../Neuron.h"
#include "../Synapse.h"
#include "../Column.h"
#include "../Circuit.h"
#include "../MorphologySynapse.h"
#include "../Stats/NodeCached.h"
#include "../Stats/NeuronMorphologySectionCachedStats.h"
#include "../Stats/DendriteCachedStats.h"
#include "../Stats/AxonCachedStats.h"
#include "../Stats/NeuronMorphologyCachedStats.h"
#include "../Container/Synapses.h"
#include "SnuddaSwcReader.h"

// HDF5
#include <H5Cpp.h>

// C++
#include <map>
#include <stack>
#include <tuple>
#include <thread>

constexpr int TO_MICROMETERS = 1000000;

namespace nsol
{
    class SnuddaSceneReader
    {
      public:
        // Structure of synapse information in the network file.
        struct [[gnu::packed]] synapseData
        {
            uint32_t source_cell_id;        // source neuron
            uint32_t dest_cell_id;          // destination neuron
            uint32_t voxel_x;               // x voxel coordinate
            uint32_t voxel_y;               // y volxe coordinate
            uint32_t voxel_z;               // z voxel coordinate
            uint32_t hyper_voxel_id;        // ??
            uint32_t channel_model_id;      // ??
            uint32_t source_axon_soma_dist; // (not SI scaled 1e6, micrometers),
            uint32_t dest_dend_soma_dist;   // (not SI scalled 1e6, micrometers)
            uint32_t dest_seg_id;           // destination section? segment?
            uint32_t dest_seg_x;            // (int 0 - 1000, SONATA wants float 0.0-1.0)
            uint32_t conductance;           // (int, not SI scaled 1e12, in pS)
            uint32_t parameterID;           // ??
        };

        static void loadSnudda(const std::string& hdf5SceneFile, const std::string& dataRepository, Columns& columns,
                               Circuit& circuit, NeuronsMap& neuronsMap,
                               std::map<std::string, NeuronMorphologyPtr>& morphologies)
        {
            auto _file = std::make_unique<H5::H5File>(hdf5SceneFile, 0);
            const std::string _data = dataRepository + "/data";

            // Snudda doesnt define a column or minicolum, but NeuroScheme requires it.
            auto column = new nsol::ColumnStats(0);
            columns.emplace_back(column);

            auto minicolumn = new nsol::MiniColumnStats(column, 0);
            column->addMiniColumn(minicolumn);

            // TODO: Snudda doesnt define a type, create defaults. Not correct, has types somewhere
            const auto morphologicalType = nsol::Neuron::PYRAMIDAL;
            const auto functionalType = nsol::Neuron::INHIBITORY;

            // Neurons
            auto idsDS = _file->openDataSet("network/neurons/neuron_id");
            auto positionDS = _file->openDataSet("network/neurons/position");
            auto rotationDS = _file->openDataSet("network/neurons/rotation");

            hsize_t dims[2];
            idsDS.getSpace().getSimpleExtentDims(dims);

            std::vector<uint32_t> ids(dims[0]);
            std::vector<std::array<double, 3>> position(dims[0]);
            std::vector<std::array<double, 9>> rotation(dims[0]);

            idsDS.read(ids.data(), H5::PredType::INTEL_I32);
            positionDS.read(position.data(), H5::PredType::IEEE_F64LE);
            rotationDS.read(rotation.data(), H5::PredType::IEEE_F64LE);

            for (size_t i = 0; i < ids.size(); ++i) {
                nsol::Vec3f pos(position[i][0], position[i][1], position[i][2]);

                Eigen::Matrix4f model;
                for (size_t c = 0; c < 3; ++c) {
                    for (size_t r = 0; r < 3; ++r) {
                        model(c, r) = static_cast<float>(rotation[i][c + r * 3]);
                    }
                }

                pos *= TO_MICROMETERS;
                model(0, 3) = pos[0];
                model(1, 3) = pos[1];
                model(2, 3) = pos[2];
                model(3, 3) = 1.0f;
                
                auto neuron = new nsol::Neuron(nullptr, 0, ids[i], model, minicolumn, morphologicalType, functionalType);

                if (neuronsMap.addNeuron(neuron)) {
                    minicolumn->addNeuron(neuron);
                }
            }

            idsDS.close();
            positionDS.close();
            rotationDS.close();

            // Morphologies
            static const std::string SNUDDA_PREFIX = "$SNUDDA_DATA";

            auto morphologiesDS = _file->openDataSet("network/neurons/morphology");
            auto stringType = morphologiesDS.getStrType();

            morphologiesDS.getSpace().getSimpleExtentDims(dims);

            std::vector<char*> cStringArray(dims[0], nullptr);
            H5::DataSpace dataspace = morphologiesDS.getSpace();
            morphologiesDS.read(cStringArray.data(), stringType, dataspace);

            std::map<std::string, nsol::NeuronMorphologyPtr> morphMap;

            SnuddaSwcReaderStats reader;
            for (const auto& pair : neuronsMap) {
                const auto id = pair.first;
                const auto neuron = pair.second;
                const auto name = std::string(cStringArray[id]);

                if (morphologies.count(name) > 0) {
                    auto morphology = morphologies[name];
                    morphMap.emplace(std::to_string(id), morphology);
                    neuron->morphology(morphology);
                    morphology->addParentNeuron(neuron);
                    continue;
                }

                std::string finalFilename = name;
                finalFilename.replace(0, SNUDDA_PREFIX.length(), _data);

                auto morphology = reader.readMorphology(finalFilename);
                if (!morphology) {
                    Log::log(std::string("nsol warning (SnuddaReader): morphology ") + finalFilename +
                                 std::string(" could not be read"), LOG_LEVEL_WARNING);
                    continue;
                }

                morphologies[name] = morphology;
                morphMap.emplace(std::to_string(id), morphology);
                neuron->morphology(morphology);
                morphology->addParentNeuron(neuron);
            }
            morphologiesDS.close();

            // Synapses
            auto origoDS = _file->openDataSet("meta/simulation_origo");
            Eigen::Vector3d origoPosInt;
            origoDS.read(origoPosInt.data(), H5::PredType::IEEE_F64LE, origoDS.getSpace());
            origoDS.close();

            Vec3f origoPos = Vec3f{static_cast<float>(origoPosInt[0]), static_cast<float>(origoPosInt[1]),
                                     static_cast<float>(origoPosInt[2])};

            origoPos *= TO_MICROMETERS;

            auto vox_sizeDS = _file->openDataSet("meta/voxel_size");
            double voxel_size;
            vox_sizeDS.read(&voxel_size, H5::PredType::IEEE_F64LE, vox_sizeDS.getSpace());
            vox_sizeDS.close();

            auto synapsesDS = _file->openDataSet("network/synapses");
            synapsesDS.getSpace().getSimpleExtentDims(dims);

            auto buffer = new int32_t[dims[0] * dims[1]];
            synapsesDS.read(buffer, H5::PredType::INTEL_I32, synapsesDS.getSpace());
            synapsesDS.close();

            for (size_t i = 0; i < dims[0] * dims[1];) {
                const auto synapse = reinterpret_cast<struct synapseData*>(&buffer[i]);

                Vec3f synapsePos{static_cast<float>(synapse->voxel_x), static_cast<float>(synapse->voxel_y),
                                 static_cast<float>(synapse->voxel_z)};

                synapsePos = (synapsePos * voxel_size) + origoPos;
                    
                auto synPtr = new MorphologySynapse();
                synPtr->preSynapticNeuron(synapse->source_cell_id);
                synPtr->postSynapticNeuron(synapse->dest_cell_id);

                // auto preData = computeSynapticSectionAndDistance(neuronsMap[synapse->source_cell_id], synapsePos);
                // synPtr->preSynapticSection(std::get<0>(preData));
                // auto postData = computeSynapticSectionAndDistance(neuronsMap[synapse->dest_cell_id], synapsePos);
                // synPtr->postSynapticSection(std::get<0>(postData));

                // synPtr->weight(synapse->conductance); // look python source
                // synPtr->preSynapticSurfacePosition(std::get<2>(preData));
                // synPtr->postSynapticSurfacePosition(std::get<2>(postData));

                synPtr->preSynapticSurfacePosition(synapsePos);
                synPtr->postSynapticSurfacePosition(synapsePos);

                circuit.addSynapse(synPtr);

                i += 13;
            }

            delete[] buffer;
        }

      private:
      // HERE BE DRAGONS...
//         static std::tuple<NeuronMorphologySectionPtr, float, Vec3f> computeSynapticSectionAndDistance(const NeuronPtr neuron, const Vec3f &synapsePos)
//         {
//             auto point_segment_distance = [](const Vec3f& p, const Vec3f& a, const Vec3f& b) {
//                 Vec3f ab = b - a;
//                 Vec3f ap = p - a;

//                 // Calculate the projection factor
//                 const auto dot_product = ap.dot(ab);
//                 const auto squared_norm = ab.squaredNorm();

//                 // Handle the case where the segment is a point
//                 if (squared_norm == 0.0) {
//                     return std::tuple<float, float, Vec3f>(0, 0, p);
//                 }

//                 const auto projection_factor = dot_product / squared_norm;

//                 // Clamp the projection factor to the range [0, 1]
//                 const auto t = std::max(0.f, std::min(1.f, projection_factor));

//                 // Calculate the closest point on the segment
//                 Vec3f closest_point = a + t * ab;

//                 // Calculate the distance
//                 return std::tuple<float, float, Vec3f>((p - closest_point).norm(), t, closest_point);
//             };

//             auto transformPoint = [](const Matrix4_4f& t, const Vec3f& v) {
//                 Vec4f temp(v[0], v[1], v[2], 1.f);
//                 const Vec3f transformed = (t * temp).head<3>();
//                 return transformed;
//             };

//             const auto morphology = neuron->morphology();
//             const auto model = neuron->transform();
//             const auto synapseLocal = transformPoint(model.inverse(), synapsePos);

//             assert(!morphology->sections().empty());

//             float minDistance = std::numeric_limits<float>::max();
//             NeuronMorphologySectionPtr sectionId = nullptr;
//             double sectionXDist = 0.f;
//             Vec3f sectionPoint;

//             for(auto neurite: morphology->neurites())
//             {
//                 if(neurite->neuriteType() == nsol::Neurite::TNeuriteType::AXON)
//                     continue;

//                 std::stack<NeuronMorphologySectionPtr> stack;
//                 stack.emplace(neurite->firstSection());

//                 while (!stack.empty()) {
//                     auto section = stack.top();
//                     stack.pop();

//                     double length = 0.;
//                     bool found = false;
// #ifdef LINEAR_SECTION_COMPUTATION
//                     const auto fNode = section->firstNode();
//                     const auto lNode = section->lastNode() ? section->lastNode() : section->nodes().back();
//                     length = (lNode->point() - fNode->point()).norm();
//                     const std::tuple<float, float, Vec3f> dist =  point_segment_distance(synapseLocalPos, fNode->point(), lNode->point());

//                     if (std::get<0>(dist) < minDistance) {
//                         minDistance = std::get<0>(dist);
//                         sectionId = section;
//                         sectionXDist = length * std::get<1>(dist);
//                         sectionPoint = std::get<2>(dist);
//                         found = true;
//                     }
// #else
//                     for (size_t i = 0; i < section->nodes().size() - 1; ++i) {
//                         auto pA = section->nodes()[i]->point();
//                         auto pB = section->nodes()[i+1]->point();
//                         const auto segmentLength = (pB - pA).norm();
//                         assert(segmentLength > 0.f);
//                         const std::tuple<float, float, Vec3f> dist =
//                             point_segment_distance(synapseLocal, pA, pB);

//                         if (std::get<0>(dist) < minDistance) {
//                             minDistance = std::get<0>(dist);
//                             sectionId = section;
//                             sectionXDist = length + (segmentLength * std::get<1>(dist));
//                             sectionPoint = std::get<2>(dist);
//                             found = true;
//                         }

//                         length += segmentLength;
//                     }

//                     if (found) {
//                         sectionXDist /= length;
//                     }
// #endif
//                     assert(0. <= sectionXDist && sectionXDist <= 1.);

//                     for (auto next : section->children()) {
//                         auto sectionPtr = dynamic_cast<NeuronMorphologySectionPtr>(next);
//                         if (sectionPtr) {
//                             stack.emplace(sectionPtr);
//                         }
//                     }
//                 }
//             }

//             const Vec3f transformedPoint = transformPoint(model, sectionPoint);
//             return {sectionId, sectionXDist, transformedPoint};
//         }
    };
} // namespace nsol

#endif
