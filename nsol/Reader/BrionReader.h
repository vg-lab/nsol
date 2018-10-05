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
#include "../Stats/NeuronMorphologySectionCachedStats.h"
#include "../Stats/DendriteCachedStats.h"
#include "../Stats/AxonCachedStats.h"
#include "../Stats/NeuronMorphologyCachedStats.h"
#include "../Container/Synapses.h"

#include "../NsolTypes.h"

#include <brain/brain.h>
#include <brion/brion.h>

#include <string>

#include <boost/filesystem.hpp>
#include <vmmlib/vmmlib.h>

namespace nsol
{

#define BRION_READER_TEMPLATE_CLASSES            \
  class NODE,                                         \
    class NEURONMORPHOLOGYSECTION,                    \
    class DENDRITE,                                   \
    class AXON,                                       \
    class SOMA,                                       \
    class NEURONMORPHOLOGY,                           \
    class NEURON,                                     \
    class MINICOLUMN,                                 \
    class COLUMN

#define BRION_READER_TEMPLATE_CLASS_NAMES        \
  NODE,                                               \
    NEURONMORPHOLOGYSECTION,                          \
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
      const std::string& target_,
      bool loadMorphologicalData = false );

  protected:

    Vec3f _calculatePosition( const Vec3fs& sectionNodes, unsigned int segmentID,
                              float distance );

  }; // BrionReaderTemplated

  typedef BrionReaderTemplated<
    Node,
    NeuronMorphologySection,
    Dendrite,
    Axon,
    Soma,
    NeuronMorphology,
    Neuron,
    MiniColumn,
    Column > BrionReader;

   typedef BrionReaderTemplated<
     Node,
     NeuronMorphologySectionStats,
     DendriteStats,
     AxonStats,
     SomaStats,
     NeuronMorphologyStats,
     Neuron,
     MiniColumnStats,
     ColumnStats > BrionReaderStats;

   typedef BrionReaderTemplated<
     NodeCached,
     NeuronMorphologySectionCachedStats,
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

    //Id of each node as loaded from file
    unsigned int nodeId = 1;

    SOMA* soma = new SOMA;

    std::vector< NEURONMORPHOLOGYSECTION* > nsolSections( sections.size( ));

    for ( unsigned int sectId = 0; sectId < sections.size(); sectId++ )
    {
      int fatherSectId = sections[sectId].y( );
      brion::SectionType sectType = sectionTypes[sectId];
      brion::SectionType fatherSectType = sectionTypes[fatherSectId];

      int startNode = sections[sectId].x( );
      int endNode = sectId == sections.size( ) - 1 ?
        points.size( ) : sections[sectId+1].x( );

      NODE* nsolNode = nullptr;
      NEURONMORPHOLOGYSECTION* nsolSection = nullptr;
      NEURONMORPHOLOGYSECTION* nsolFatherSection = nullptr;
      NeuritePtr nsolNeurite = nullptr;

      if ( sectType == brion::SectionType::SECTION_SOMA )
      {
        for ( int i = startNode; i < endNode; i++ )
        {
          brion::Vector4f point = points[i];
          nsolNode = new NODE( Vec3f( point.x( ), point.y( ), point.z( )),
                               nodeId++, point.w( ) / 2.0f );
          soma->addNode( nsolNode );
        }
        nsolSections[sectId] = nullptr;
      }
      else
      {
        nsolSection = new NEURONMORPHOLOGYSECTION( );
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
          nsolNode = new NODE( Vec3f( point.x( ), point.y( ), point.z( )),
                               nodeId++, point.w( ) / 2.0f );
          nsolSection->addNode( nsolNode );
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
  Vec3f
  BrionReaderTemplated< BRION_READER_TEMPLATE_CLASS_NAMES >::_calculatePosition(
      const Vec3fs& sectionNodes, unsigned int segmentID, float distance )
  {
    Vec3f result;

    auto start = sectionNodes[ segmentID ];
    auto end = sectionNodes[ segmentID + 1 ];

    Vec3f direction = ( end - start );

    direction.normalize( );

    result = start + direction * distance;

    return result;
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

    std::string circuitPath = blueConfig_.getCircuitSource( ).getPath( );
    auto fileExt = boost::filesystem::extension( circuitPath );
    if (( fileExt.compare( ".mvd" ) == 0 ) |
        ( fileExt.compare( ".mvd2" ) == 0 ))
    {
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
        float yRotation = boost::lexical_cast< float >( data[i][7] );
        if ( std::isnan( yRotation ))
          yRotation = 0.0f;
        yRotation *= (toRadians);
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
    else if ( fileExt.compare( ".mvd3" ) == 0 )
    {
      ColumnPtr column = new COLUMN( 1 );
      MiniColumnPtr minicolumn = new MINICOLUMN( column, 1 );
      column->addMiniColumn( minicolumn );

      brain::Circuit circuit( blueConfig_ );
      brion::GIDSet gidSet = blueConfig_.parseTarget( target_ );
      auto transforms = circuit.getTransforms( gidSet );

      std::vector< unsigned int > neuronIds( gidSet.begin( ), gidSet.end( ));

      for ( unsigned int i = 0; i < gidSet.size( ); i++ )
      {
        auto layer = 1;
        unsigned int gid = neuronIds[i];
        Matrix4_4f transform = Matrix4_4f::Identity( );
        if (  i < transforms.size( ))
          for ( unsigned int j = 0; j < 4; j++ )
            for ( unsigned int k = 0; k < 4; k++)
              transform( j, k ) = transforms[i]( j, k );
        auto morphoType =  Neuron::UNDEFINED;
        auto functionalType = Neuron::UNDEFINED_FUNCTIONAL_TYPE;

        Neuron* neuron = new NEURON( nullptr, layer, gid, transform, minicolumn,
                                     morphoType, functionalType );
        minicolumn->addNeuron( neuron );
        neurons_[ gid ] = neuron;
      }
    }
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  void
  BrionReaderTemplated
  < BRION_READER_TEMPLATE_CLASS_NAMES >::loadBlueConfigConnectivity(
    NeuronsMap& neurons_,
    Circuit& circuit_,
    const brion::BlueConfig& blueConfig_,
    const std::string& target_,
    bool loadMorphologicalData )
  {
    circuit_.clear();

    brain::Circuit brainCircuit( blueConfig_);
    brion::GIDSet gidSetBrain = brainCircuit.getGIDs( target_ );

    // Load brain synapses with only attributes to avoid crash.
    const brain::Synapses& brainSynapses =
        brainCircuit.getAfferentSynapses( gidSetBrain,
                                          brain::SynapsePrefetch::attributes );

    std::vector< MorphologySynapsePtr > synapseVector( brainSynapses.size( ),
                                                       nullptr );

    typedef std::unordered_map< unsigned int,
        NeuronMorphologySectionPtr > TGidSectionMap;

    std::unordered_map< unsigned int, TGidSectionMap > neuronSectionMap;

    // Load neuron gid to neuron pointer and section id to section pointer maps
    for( auto neuron : neurons_ )
    {

      TGidSectionMap neuronSections;
      auto morphology = neuron.second->morphology( );
      for( auto neurite : morphology->neurites( ))
      {
        for( auto section : neurite->sections( ))
        {
          auto mSection = dynamic_cast< NeuronMorphologySectionPtr >( section );

          neuronSections.insert( std::make_pair( mSection->id( ), mSection ));

        }
      }

      neuronSectionMap.insert( std::make_pair( neuron.first, neuronSections ));
    }

    bool computePositions = false;
    if( loadMorphologicalData )
    {

      // Test if position files are present
      try
      {
        auto brainSynapse = brainSynapses[ 0 ];
        brainSynapse.getPresynapticSurfacePosition( );
      }
      catch( ... )
      {
        Log::log( "Computing positions...", LOG_LEVEL_VERBOSE );
        computePositions = true;
      }
    }

#ifdef NSOL_USE_OPENMP
    #pragma omp parallel for
#endif
    for( unsigned int i = 0; i < brainSynapses.size( ); ++i )
    {
      auto brainSynapse = brainSynapses[ i ];

      unsigned int gidPre = brainSynapse.getPresynapticGID( );
      unsigned int gidPost = brainSynapse.getPostsynapticGID( );

      auto neuronPre = neurons_.find( gidPre );
      auto neuronPost = neurons_.find( gidPost );

      // DISCARD INCOMPLETE AND INVALID SYNAPSES
      // Check if both neurons have been loaded from given BlueConfig target
      if (( neuronPre  == neurons_.end( )) ||
          ( neuronPost == neurons_.end( )))
      {
        continue;
      }
      // Check if both sections exist
      unsigned int sectionIdPre = brainSynapse.getPresynapticSectionID( );
      unsigned int sectionIdPost = brainSynapse.getPostsynapticSectionID( );

      // Check presynaptic section exists
      auto neuronSectionsPre = neuronSectionMap.find( gidPre );
      auto neuronSectionsPost = neuronSectionMap.find( gidPost );
      auto sectionPre = neuronSectionsPre->second.find( sectionIdPre );
      auto sectionPost = neuronSectionsPost->second.find( sectionIdPost );

      if(( sectionIdPre != 0 &&
          sectionPre == neuronSectionsPre->second.end( )) ||
          ( sectionIdPost != 0 &&
            sectionPost == neuronSectionsPost->second.end( )))
      {
        continue;
      }

      // Check if both segment IDs are in range considering section nodes
      unsigned int segmentIdxPre = brainSynapse.getPresynapticSegmentID( );
      unsigned int segmentIdxPost = brainSynapse.getPostsynapticSegmentID( );

      if( loadMorphologicalData )
      {
        if( sectionPre->second->nodes( ).empty( ) ||
            segmentIdxPre >= sectionPre->second->nodes( ).size( ) - 1 ||
            ( sectionIdPost != 0 &&
            ( sectionPost->second->nodes( ).empty( ) ||
              segmentIdxPost >= sectionPost->second->nodes( ).size( ) - 1 )))
          continue;
      }

      MorphologySynapsePtr afferentSynapse = new MorphologySynapse( );

      afferentSynapse->preSynapticNeuron( neuronPre->second->gid( ));
      afferentSynapse->postSynapticNeuron( neuronPost->second->gid( ));

      afferentSynapse->weight( 0.0f );

      if( loadMorphologicalData )
      {

        Vec3f positionPre;
        Vec3f positionPost;

        if( !computePositions )
        {
          // Set positionsPre
          auto posPre = brainSynapse.getPresynapticSurfacePosition( );
          auto posPost = brainSynapse.getPostsynapticSurfacePosition( );

          positionPre = Vec3f( posPre.x( ), posPre.y( ), posPre.z( ));
          positionPost = Vec3f( posPost.x( ), posPost.y( ), posPost.z( ));

        }
        else
        {

          positionPre =
              _calculatePosition( sectionPre->second->nodes( ).positions( ),
                                  segmentIdxPre,
                                  brainSynapse.getPresynapticDistance( ));

          // if section id equals zero, synapse is assigned to soma
          if( sectionIdPost == 0 )
          {
            auto soma = neuronPost->second->morphology( )->soma( );

            Vec3fs nodes;
            nodes.reserve( 2 );
            nodes.emplace_back( soma->center( ));
            nodes.emplace_back( positionPre );

            positionPost = _calculatePosition( nodes, 0, soma->maxRadius( ));
          }
          // dendritic synapse
          else
          {
            positionPost =
                _calculatePosition( sectionPost->second->nodes( ).positions( ),
                                    segmentIdxPost,
                                    brainSynapse.getPostsynapticDistance( ));
          }

          auto transform = neuronPre->second->transform( );
          Vec4f aux = Vec4f( positionPre.x( ), positionPre.y( ), positionPre.z( ), 1);

          positionPre = ( transform * aux ).block< 3, 1 >( 0, 0 );

          transform = neuronPost->second->transform( );
          aux = Vec4f( positionPost.x( ), positionPost.y( ), positionPost.z( ), 1);

          positionPost = ( transform * aux ).block< 3, 1 >( 0, 0 );

        }

        afferentSynapse->preSynapticSurfacePosition( positionPre );
        afferentSynapse->preSynapticSection( sectionPre->second );

        afferentSynapse->postSynapticSurfacePosition( positionPost );

        afferentSynapse->postSynapticSection(
            ( sectionIdPost == 0 ) ? nullptr : sectionPost->second );

      }

      afferentSynapse->gid( i + 1 );

#ifndef NSOL_USE_OPENMP
      circuit_.addSynapse( afferentSynapse );
#else
      synapseVector[ i ] = afferentSynapse;
#endif
    } // for each synapse

#ifdef NSOL_USE_OPENMP
    circuit_.addSynapses( synapseVector );
#endif

    std::cout << "Loaded " << circuit_.numberOfSynapses( ) << " synapses." << std::endl;
  }


}

#endif // __NSOL_BRION_READER__
#endif // NSOL_USE_BRION
