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
#include <cassert>

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
            std::vector<std::string> NEURON_DATASETS = { "network/neurons/neuron_id", "network/neurons/position", "network/neurons/rotation", "network/neurons/morphology" };
            std::vector<std::string> SYNAPSE_DATASETS = { "meta/simulation_origo", "meta/voxel_size", "network/synapses" };

            auto _file = std::make_unique<H5::H5File>(hdf5SceneFile, 0);
            const std::string _data = dataRepository;

            auto checkKeys = [&_file](const std::vector<std::string>& keys) {
                for (const auto& key : keys) {
                    if (H5Lexists(_file->getLocId(), key.c_str(), H5P_DEFAULT) < 0) {
                        return false;
                    }
                }

                return true;
            };

            // Snudda doesnt define a column or minicolum, but NeuroScheme requires it.
            auto column = new nsol::ColumnStats(0);
            columns.emplace_back(column);

            auto minicolumn = new nsol::MiniColumnStats(column, 0);
            column->addMiniColumn(minicolumn);

            // TODO: Snudda doesnt define a type, create defaults. Not correct, has types somewhere
            const auto morphologicalType = nsol::Neuron::PYRAMIDAL;
            const auto functionalType = nsol::Neuron::INHIBITORY;
            std::vector<uint32_t> ids;

            if (checkKeys(NEURON_DATASETS)) {
                auto idsDS = _file->openDataSet("network/neurons/neuron_id");
                auto positionDS = _file->openDataSet("network/neurons/position");
                auto rotationDS = _file->openDataSet("network/neurons/rotation");

                // NOTE: read dims of ids separately, as the buffer could be truncated due to
                // "faked" dataset with less ids for faster delevelopment iteration.
                hsize_t dims[2];
                idsDS.getSpace().getSimpleExtentDims(dims);
                ids.resize(dims[0]);

                positionDS.getSpace().getSimpleExtentDims(dims);
                std::vector<std::array<double, 3>> position(dims[0]);
                std::vector<std::array<double, 9>> rotation(dims[0]);

                idsDS.read(ids.data(), H5::PredType::INTEL_I32);
                idsDS.close();

                positionDS.read(position.data(), H5::PredType::IEEE_F64LE);
                positionDS.close();

                rotationDS.read(rotation.data(), H5::PredType::IEEE_F64LE);
                rotationDS.close();

                for (size_t i = 0; i < ids.size(); ++i) {
                    nsol::Vec3f pos(position[i][0], position[i][1], position[i][2]);

                    Eigen::Matrix4f model = Eigen::Matrix4f::Zero();
                    for (size_t c = 0; c < 3; ++c) {
                        for (size_t r = 0; r < 3; ++r) {
                            model(r, c) = static_cast<float>(rotation[i][c + r * 3]);
                        }
                    }

                    pos *= TO_MICROMETERS;
                    model(0, 3) = pos[0];
                    model(1, 3) = pos[1];
                    model(2, 3) = pos[2];
                    model(3, 3) = 1.0f;

                    auto neuron =
                        new nsol::Neuron(nullptr, 0, ids[i], model, minicolumn, morphologicalType, functionalType);

                    if (neuronsMap.addNeuron(neuron)) {
                        minicolumn->addNeuron(neuron);
                    }
                }

                // Morphologies
                static const std::string SNUDDA_PREFIX = "$SNUDDA_DATA";

                auto morphologiesDS = _file->openDataSet("network/neurons/morphology");
                auto stringType = morphologiesDS.getStrType();

                morphologiesDS.getSpace().getSimpleExtentDims(dims);

                std::vector<char*> cStringArray(dims[0], nullptr);
                H5::DataSpace dataspace = morphologiesDS.getSpace();
                morphologiesDS.read(cStringArray.data(), stringType, dataspace);

                std::map<std::string, nsol::NeuronMorphologyPtr> morphMap;

                SnuddaSwcReader reader;
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

                    auto morphology = reader.readMorphology(finalFilename, false);
                    if (!morphology) {
                        Log::log(std::string("nsol warning (SnuddaReader): morphology ") + finalFilename +
                                     std::string(" could not be read"),
                                 LOG_LEVEL_WARNING);
                        std::cout << "morphology not found: " << finalFilename << std::endl;
                        continue;
                    }

                    morphologies[name] = morphology;
                    morphMap.emplace(std::to_string(id), morphology);
                    neuron->morphology(morphology);
                    morphology->addParentNeuron(neuron);
                }
                morphologiesDS.close();
            }

            // Synapses
            if (checkKeys(SYNAPSE_DATASETS)) {
                hsize_t dims[2];
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
                    if (synapse->source_cell_id < ids.size() && synapse->dest_cell_id < ids.size()) {
                        Vec3f synapsePos{static_cast<float>(synapse->voxel_x), static_cast<float>(synapse->voxel_y),
                                         static_cast<float>(synapse->voxel_z)};

                        synapsePos = (synapsePos * voxel_size * TO_MICROMETERS) + origoPos;

                        auto synPtr = new MorphologySynapse();
                        synPtr->preSynapticNeuron(synapse->source_cell_id);
                        synPtr->postSynapticNeuron(synapse->dest_cell_id);
                        synPtr->preSynapticSurfacePosition(synapsePos);
                        synPtr->postSynapticSurfacePosition(synapsePos);

                        circuit.addSynapse(synPtr);
                    }

                    i += 13;
                }

                delete[] buffer;
            }
        }
    };
} // namespace nsol

#endif
