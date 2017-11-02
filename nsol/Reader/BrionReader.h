/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
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
#ifdef NSOL_USE_BRION

#ifndef __NSOL_BRAIN_READER__
#define __NSOL_BRAIN_READER__

#include "../Stats/ColumnStats.h"
#include "../Stats/MiniColumnStats.h"
#include "../Neuron.h"
#include "../Synapse.h"
#include "../Stats/NodeCached.h"
#include "../Stats/SectionCachedStats.h"
#include "../Stats/DendriteCachedStats.h"
#include "../Stats/AxonCachedStats.h"
#include "../Stats/NeuronMorphologyCachedStats.h"
#include "../Container/Synapses.h"

#include "../NsolTypes.h"

#include <brain/brain.h>
#include <brion/brion.h>

#include <string>
#include <vmmlib/vmmlib.h>

namespace nsol
{

#define BRION_READER_TEMPLATE_CLASSES            \
  class NODE,                                         \
    class SECTION,                                    \
    class DENDRITE,                                   \
    class AXON,                                       \
    class SOMA,                                       \
    class NEURONMORPHOLOGY,                           \
    class NEURON,                                     \
    class MINICOLUMN,                                 \
    class COLUMN

#define BRION_READER_TEMPLATE_CLASS_NAMES        \
  NODE,                                               \
    SECTION,                                          \
    DENDRITE,                                         \
    AXON,                                             \
    SOMA,                                             \
    NEURONMORPHOLOGY,                                 \
    NEURON,                                           \
    MINICOLUMN,                                       \
    COLUMN

  template < BRION_READER_TEMPLATE_CLASSES >
  class BrionReaderTemplated
  {

  public:

    NeuronMorphologyPtr
    loadMorphology( brion::Morphology* brionMorphology_,
                    bool reposition_ = true );

    NeuronMorphologyPtr
    loadMorphology( const brion::URI& uri_,
                    bool reposition_ = true );

    NeuronMorphologyPtr
    loadMorphology( const std::string& path_,
                    bool reposition_ = true );

    NeuronPtr
    loadNeuron(
      const std::string& path_,
      const unsigned int gid_,
      const unsigned int layer_ = 0,
      const Matrix4_4f transform_ = Matrix4_4fIdentity,
      const Neuron::TMorphologicalType morphologicalType_ = Neuron::PYRAMIDAL,
      const Neuron::TFunctionalType functionalType_ = Neuron::EXCITATORY,
      bool reposition_ = false );

    void
    loadBlueConfigHierarchy(
      Columns& columns_,
      NeuronsMap& neurons_,
      const brion::BlueConfig& blueConfig_,
      const std::string& targetLabel = std::string( "" ));

    void
    loadBlueConfigConnectivity(
      NeuronsMap& neurons_,
      Circuit& circuit_,
      const brion::BlueConfig& blueConfig_,
      const std::string& target_ );


  }; // BrionReaderTemplated

  typedef BrionReaderTemplated<
    Node,
    Section,
    Dendrite,
    Axon,
    Soma,
    NeuronMorphology,
    Neuron,
    MiniColumn,
    Column > BrionReader;

   typedef BrionReaderTemplated<
     Node,
     SectionStats,
     DendriteStats,
     AxonStats,
     SomaStats,
     NeuronMorphologyStats,
     Neuron,
     MiniColumnStats,
     ColumnStats > BrionReaderStats;

   typedef BrionReaderTemplated<
     NodeCached,
     SectionCachedStats,
     DendriteCachedStats,
     AxonCachedStats,
     SomaStats,
     NeuronMorphologyCachedStats,
     Neuron,
     MiniColumnStats,
     ColumnStats > BrionReaderCachedStats;


  template < BRION_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  BrionReaderTemplated< BRION_READER_TEMPLATE_CLASS_NAMES >::loadMorphology(
    brion::Morphology* brionMorpho_,
    bool reposition_ )
  {
    NeuronMorphologyPtr nsolMorpho = new NEURONMORPHOLOGY( );

    const auto& points = brionMorpho_->getPoints( );
    const auto& sections = brionMorpho_->getSections( );
    const auto& sectionTypes = brionMorpho_->getSectionTypes( );

    SOMA* soma = new SOMA;

    std::vector< SECTION* > nsolSections( sections.size( ));

    for ( unsigned int sectId = 0; sectId < sections.size(); sectId++ )
    {
      int fatherSectId = sections[sectId].y( );
      brion::SectionType sectType = sectionTypes[sectId];
      brion::SectionType fatherSectType = sectionTypes[fatherSectId];

      int startNode = sections[sectId].x( );
      int endNode = sectId == sections.size( ) - 1 ?
        points.size( ) : sections[sectId+1].x( );

      NODE* nsolNode = nullptr;
      SECTION* nsolSection = nullptr;
      SECTION* nsolFatherSection = nullptr;
      NeuritePtr nsolNeurite = nullptr;

      if ( sectType == brion::SectionType::SECTION_SOMA )
      {
        for ( int i = startNode; i < endNode; i++ )
        {
          brion::Vector4f point = points[i];
          nsolNode = new NODE( Vec3f( point.x( ), point.y( ), point.z( )), i,
                               point.w( ) / 2.0f );
          soma->addNode( nsolNode );
        }
        nsolSections[sectId] = nullptr;
      }
      else
      {
        nsolSection = new SECTION( );
        nsolSection->id( sectId );
        nsolSections[sectId] = nsolSection;
        if ( sectType != fatherSectType )
        {
          switch( sectType )
          {
          case brion::SectionType::SECTION_AXON:
            nsolNeurite = new AXON( );
            break;
          case brion::SectionType::SECTION_APICAL_DENDRITE:
            nsolNeurite = new DENDRITE( Dendrite::APICAL );
            break;
          case brion::SectionType::SECTION_DENDRITE:
            nsolNeurite = new DENDRITE( Dendrite::BASAL );
            break;
          default:
            nsolNeurite = new DENDRITE( Dendrite::BASAL );
            break;
          }
          nsolMorpho->addNeurite( nsolNeurite );
          nsolNeurite->firstSection( nsolSection );
          if ( soma->nodes( ).size( ) > 1 )
            ++startNode;
        }
        else
        {
          nsolFatherSection = nsolSections[fatherSectId];
          nsolNeurite = nsolFatherSection->neurite( );
          nsolSection->parent( nsolFatherSection );
          nsolFatherSection->addChild( nsolSection );
          ++startNode;
        }
        nsolSection->neurite( nsolNeurite );

        for ( int i = startNode; i < endNode; i++ )
        {
          brion::Vector4f point = points[i];
          nsolNode = new NODE( Vec3f( point.x( ), point.y( ), point.z( )), i,
                               point.w( ) / 2.0f );
          nsolSection->addNode( nsolNode );
        }
      }
    }

    unsigned int nodeId = 1;

    for( auto node: soma->nodes( ))
    {
      node->id( ) = nodeId;
      nodeId ++;
    }

    for( auto neurite: nsolMorpho->neurites( ))
    {
      neurite->firstSection( )->firstNode( )->id( ) = nodeId;
      nodeId++;
      for( auto section: neurite->sections( ))
      {
        auto nodes = section->nodes( );
        for ( unsigned int i = 1; i < nodes.size( ); i++ )
        {
          nodes[i]->id( ) = nodeId;
          nodeId ++;
        }
      }
    }

    nsolMorpho->soma( soma );

    if ( reposition_ )
    {
      Vec3f center = soma->center( );

      for ( auto node: soma->nodes( ))
        node->point( node->point( ) - center );

      soma->center( Vec3f( 0.0f, 0.0f, 0.0f ));

      for ( auto neurite: nsolMorpho->neurites( ))
      {
        Node* firstNode = neurite->firstSection( )->firstNode(  );
        firstNode->point( firstNode->point( ) - center );
        for ( auto section: neurite->sections( ))
        {
          for ( auto node: section->nodes( ))
          {
            if ( node == firstNode )
              continue;
            node->point( node->point( ) - center );
          }
        }
      }
    }
    return nsolMorpho;
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  BrionReaderTemplated< BRION_READER_TEMPLATE_CLASS_NAMES >::loadMorphology(
    const brion::URI& uri_,
    bool reposition_ )
  {
    brion::Morphology* brionMorpho = new brion::Morphology(
      servus::URI( uri_.getPath( )));

    NeuronMorphologyPtr nsolMorpho = loadMorphology( brionMorpho, reposition_ );
    delete brionMorpho;
    return nsolMorpho;
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  BrionReaderTemplated< BRION_READER_TEMPLATE_CLASS_NAMES >::loadMorphology(
    const std::string& path_,
    bool reposition_ )
  {
    return loadMorphology( brion::URI( path_ ), reposition_ );
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  NeuronPtr
  BrionReaderTemplated
  < BRION_READER_TEMPLATE_CLASS_NAMES >::loadNeuron(
    const std::string& path_,
    const unsigned int gid_,
    const unsigned int layer_,
    const Matrix4_4f transform_,
    const nsol::Neuron::TMorphologicalType morphologicalType_,
    const nsol::Neuron::TFunctionalType functionalType_,
    bool reposition_ )
  {
    NeuronMorphologyPtr neuronMorphology = loadMorphology( path_, reposition_ );
    NeuronPtr neuron = new NEURON( neuronMorphology, layer_, gid_, transform_,
                                 nullptr, morphologicalType_, functionalType_ );

    return neuron;
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  void
  BrionReaderTemplated
  < BRION_READER_TEMPLATE_CLASS_NAMES >::loadBlueConfigHierarchy(
    Columns& columns_,
    NeuronsMap& neurons_,
    const brion::BlueConfig& blueConfig_,
    const std::string& target_ )
  {
    columns_.clear( );
    neurons_.clear( );

    brion::Circuit circuit( blueConfig_.getCircuitSource( ));
    brion::GIDSet gidSet = blueConfig_.parseTarget( target_ );

    uint32_t attributes =
      brion::NEURON_COLUMN_GID | brion::NEURON_MINICOLUMN_GID |
      brion::NEURON_LAYER | brion::NEURON_MTYPE | brion::NEURON_POSITION_X |
      brion::NEURON_POSITION_Y | brion::NEURON_POSITION_Z |
      brion::NEURON_ROTATION;

    brion::Strings functionTypes =
      circuit.getTypes( brion::NEURONCLASS_FUNCTION_CLASS );
    brion::Strings morphologyTypes =
      circuit.getTypes( brion::NEURONCLASS_MORPHOLOGY_CLASS );

    const brion::NeuronMatrix& data = circuit.get( gidSet, attributes );

    std::vector< unsigned int > neuronIds( gidSet.begin( ), gidSet.end( ));

    float toRadians = (M_PI/180.f);

    for ( unsigned int i = 0; i < gidSet.size( ); i++ )
    {
      unsigned int gid = neuronIds[i];
      Matrix4_4f transform = Matrix4_4fIdentity;

      float yRotation =
                      boost::lexical_cast< float >( data[i][7] ) * (toRadians);
      transform( 0, 0 ) = cos( yRotation );
      transform( 0, 2 ) = sin( yRotation );
      transform( 2, 0 ) = -sin( yRotation );
      transform( 2, 2 ) = cos( yRotation );

      Vec3f translationVec( boost::lexical_cast< float >( data[i][4] ),
                            boost::lexical_cast< float >( data[i][5] ),
                            boost::lexical_cast< float >( data[i][6] ));
      transform( 0, 3 ) = translationVec.x( );
      transform( 1, 3 ) = translationVec.y( );
      transform( 2, 3 ) = translationVec.z( );

      unsigned short layer = ( boost::lexical_cast< uint16_t >( data[i][2] )
                               + 1 );

      unsigned int miniColumnId = boost::lexical_cast< uint16_t >( data[i][1] );
      unsigned int columnId = boost::lexical_cast< uint16_t >( data[i][0] );
      std::string mType =
        morphologyTypes[ boost::lexical_cast< uint16_t >( data[i][3] )];
      std::string eType =
        functionTypes[ boost::lexical_cast< uint16_t >( data[i][3] )];

      Neuron::TMorphologicalType morphoType = Neuron::UNDEFINED;
      Neuron::TFunctionalType functionalType =
        Neuron::UNDEFINED_FUNCTIONAL_TYPE;

      if( mType == "PYR" )
        morphoType = Neuron::PYRAMIDAL;
      else if( mType == "INT" )
        morphoType = Neuron::INTERNEURON;

      if( eType == "EXC" )
        functionalType = Neuron::EXCITATORY;
      else if( eType == "INH" )
        functionalType = Neuron::INHIBITORY;

      // std::cout << "*****************" << std::endl;
      // std::cout << "Gid: " << gid << std::endl;
      // std::cout << "Layer: " << layer << std::endl;
      // std::cout << "Transform matrix:\n " << transform << std::endl;
      // std::cout << "MiniColumn: " << miniColumnId << std::endl;
      // std::cout << "Column: " << columnId << std::endl;
      // std::cout << "Morphology type: " << morphoType << std::endl;
      // std::cout << "Electric type: " << functionalType << std::endl;

      MiniColumnPtr miniColumn = nullptr;
      ColumnPtr column = nullptr;

      for ( auto col: columns_ )
      {
        if ( col->id( ) == columnId )
        {
          column = col;
          break;
        }
      }

      if ( !column )
      {
        column = new COLUMN( columnId );
        columns_.push_back( column );
      }


      for( auto miniCol: column->miniColumns( ))
      {
        if ( miniCol->id( ) == miniColumnId )
        {
          miniColumn = miniCol;
          break;
        }
      }

      if( !miniColumn )
      {
        miniColumn = new MINICOLUMN( column, miniColumnId );
        column->addMiniColumn( miniColumn );
      }

      Neuron* neuron = new NEURON( nullptr, layer, gid, transform, miniColumn,
                                   morphoType, functionalType );
      miniColumn->addNeuron( neuron );
      neurons_[ gid ] = neuron;
    }
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  void
  BrionReaderTemplated
  < BRION_READER_TEMPLATE_CLASS_NAMES >::loadBlueConfigConnectivity(
    NeuronsMap& neurons_,
    Circuit& circuit_,
    const brion::BlueConfig& blueConfig_,
    const std::string& target_ )
  {
    circuit_.clear();

    brain::Circuit brainCircuit( blueConfig_);
    brion::GIDSet gidSetBrain = brainCircuit.getGIDs( target_ );

    const brain::Synapses& brainSynapses = brainCircuit.
                                           getAfferentSynapses( gidSetBrain,
                                              brain::SynapsePrefetch::all );

    // number of efferent synapses it is the same that afferent synapses
    for( brain::Synapses::const_iterator it = brainSynapses.begin();
                                           it != brainSynapses.end(); ++it)
    {
      const brain::Synapse& brainSynapse = (*it);

      MorphologySynapsePtr afferent_synapse = MorphologySynapsePtr(
                                                     new MorphologySynapse( ));

      std::unordered_map< unsigned int, NeuronPtr >::iterator nitPre = neurons_
                                         .find(brainSynapse.getPresynapticGID());
      std::unordered_map< unsigned int, NeuronPtr >::iterator nitPost = neurons_
                                         .find(brainSynapse.getPostsynapticGID());

      if (( nitPre  == neurons_.end( ))||
          ( nitPost == neurons_.end( )))
          break;

      afferent_synapse->preSynapticNeuron( nitPre->second->gid( ));
      afferent_synapse->postSynapticNeuron( nitPost->second->gid( ));

      afferent_synapse->weight( 0.0f );

      circuit_.addSynapse( afferent_synapse );

    }
  }

}

#endif // __NSOL_BRION_READER__
#endif // NSOL_USE_BRION
