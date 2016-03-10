 /**
 * @brief
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#ifndef __NSOL_BRAIN_READER__
#define __NSOL_BRAIN_READER__

#include "../Stats/ColumnStats.h"
#include "../Stats/MiniColumnStats.h"
#include "../Neuron.h"
#include "../Stats/NodeCached.h"
#include "../Stats/SectionCachedStats.h"
#include "../Stats/DendriteCachedStats.h"
#include "../Stats/AxonCachedStats.h"
#include "../Stats/NeuronMorphologyCachedStats.h"

#include "../NsolTypes.h"

#include <brion/brion.h>

#include <string>

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

    NEURONMORPHOLOGY*
    loadMorphology( brion::Morphology* brionMorphology_,
                    bool reposition_ = true );

    NEURONMORPHOLOGY*
    loadMorphology( const brion::URI& uri_,
                    bool reposition_ = true );

    NEURONMORPHOLOGY*
    loadMorphology( const std::string& path_,
                    bool reposition_ = true );

    NEURON*
    loadNeuron(
      const std::string& path_,
      const unsigned int gid_,
      const unsigned int layer_ = 0,
      const Matrix4_4f transform_ = Matrix4_4f::IDENTITY,
      const Neuron::TMorphologicalType morphologicalType_ = Neuron::PYRAMIDAL,
      const Neuron::TFunctionalType functionalType_ = Neuron::EXCITATORY,
      bool reposition_ = true );

    void
    loadFromBlueconfig( Columns& columns_,
                        const brion::BlueConfig& blueConfig_,
                        const std::string& targetLabel_ = std::string( "" ));

    void
    loadFromBlueConfig( Columns& columns_,
                        NeuronsMap& neurons_,
                        const std::string& blueConfig_,
                        const std::string& targetLabel = std::string( "" ));

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
  NEURONMORPHOLOGY*
  BrionReaderTemplated< BRION_READER_TEMPLATE_CLASS_NAMES >::loadMorphology(
    brion::Morphology* brionMorpho_,
    bool reposition_ )
  {
    NEURONMORPHOLOGY* nsolMorpho = new NEURONMORPHOLOGY( );

    brion::Vector4fsPtr points = brionMorpho_->readPoints(
      brion::MORPHOLOGY_UNDEFINED );
    brion::Vector2isPtr sections = brionMorpho_->readSections(
      brion::MORPHOLOGY_UNDEFINED );
    brion::SectionTypesPtr sectionTypes = brionMorpho_->readSectionTypes( );

    SOMA* soma = new SOMA;

    std::vector< SECTION* > nsolSections( sections->size( ));

    for ( unsigned int sectId = 0; sectId < sections->size(); sectId++ )
    {
      int fatherSectId = (*sections)[sectId].y( );
      brion::SectionType sectType = (*sectionTypes)[sectId];
      brion::SectionType fatherSectType = (*sectionTypes)[fatherSectId];

      int startNode = (*sections)[sectId].x( );
      int endNode = sectId == sections->size( ) - 1 ?
        points->size( ) : (*sections)[sectId+1].x( );

      NODE* nsolNode = nullptr;
      SECTION* nsolSection = nullptr;
      SECTION* nsolFatherSection = nullptr;
      NeuritePtr nsolNeurite = nullptr;

      if ( sectType == brion::SectionType::SECTION_SOMA )
      {
        for ( int i = startNode; i < endNode; i++ )
        {
          brion::Vector4f point = (*points)[i];
          nsolNode = new NODE( Vec3f( point.x( ), point.y( ), point.z( )), i,
                               point.w( ) / 2.0f );
          soma->addNode( nsolNode );
        }
        nsolSections[sectId] = nullptr;
      }
      else
      {
        nsolSection = new SECTION( );
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
        }
        else
        {
          nsolFatherSection = nsolSections[fatherSectId];
          nsolNeurite = nsolFatherSection->neurite( );
          nsolSection->parent( nsolFatherSection );
          nsolFatherSection->addChild( nsolSection );
          startNode++;
        }
        nsolSection->neurite( nsolNeurite );

        for ( int i = startNode; i < endNode; i++ )
        {
          brion::Vector4f point = (*points)[i];
          nsolNode = new NODE( Vec3f( point.x( ), point.y( ), point.z( )), i,
                               point.w( ) / 2.0f );
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
  NEURONMORPHOLOGY*
  BrionReaderTemplated< BRION_READER_TEMPLATE_CLASS_NAMES >::loadMorphology(
    const brion::URI& uri_,
    bool reposition_ )
  {
    brion::Morphology* brionMorpho = new brion::Morphology(
      uri_.getPath( ));

    NEURONMORPHOLOGY* nsolMorpho = loadMorphology( brionMorpho, reposition_ );
    delete brionMorpho;
    return nsolMorpho;
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  NEURONMORPHOLOGY*
  BrionReaderTemplated< BRION_READER_TEMPLATE_CLASS_NAMES >::loadMorphology(
    const std::string& path_,
    bool reposition_ )
  {
    return loadMorphology( brion::URI( path_ ), reposition_ );
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  NEURON*
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
    NEURONMORPHOLOGY* neuronMorphology = loadMorphology( path_, reposition_ );
    NEURON* neuron = new NEURON( neuronMorphology, layer_, gid_, transform_,
                                 nullptr, morphologicalType_, functionalType_ );

    return neuron;
  }

  template < BRION_READER_TEMPLATE_CLASSES >
  void
  BrionReaderTemplated
  < BRION_READER_TEMPLATE_CLASS_NAMES >::loadFromBlueconfig(
    Columns& columns_,
    const brion::BlueConfig& blueConfig_,
    const std::string& target_   )
  {
    brion::Circuit circuit( blueConfig_.getCircuitSource( ));
    brion::GIDSet gidSet = blueConfig_.parseTarget( target_ );

    uint32_t attributes = brion::NEURON_POSITION_X |
      brion::NEURON_POSITION_Y | brion::NEURON_POSITION_Z |
      brion::NEURON_ROTATION | brion::NEURON_LAYER |
      brion::NEURON_MINICOLUMN_GID | brion::NEURON_COLUMN_GID |
      brion::NEURON_METYPE ;
    const brion::NeuronMatrix& data = circuit.get( gidSet, attributes );

    std::vector< unsigned int > neuronIds( gidSet.begin( ), gidSet.end( ));

    for ( unsigned int i = 0; i < gidSet.size( ); i++ )
    {
      unsigned short layer =( dynamic_cast< unsigned short >( data[i][4] ));
      unsigned int gid = neuronIds[i];
      Matrix4_4f transform = Matrix4_4f::IDENTITY;

      transform.rotate_y( dynamic_cast< float >( data[i][3] ) * (M_PI*1280.0f));
      Vec3f translationVec( dynamic_cast< float >( data[i][0] ),
                               dynamic_cast< float >( data[i][1] ),
                            dynamic_cast< float >( data[i][2] ));
      transform.set_translation( translationVec );

      unsigned int miniColumnId = dynamic_cast< unsigned int >( data[i][5] );
      unsigned int columnId = dynamic_cast< unsigned int >( data[i][6] );
      brion::NeuronClass type = dynamic_cast< brion::NeuronClass >( data[i][7] );

      std::cout << "*****************" << std::endl;
      std::cout << "Gid: " << gid << std::endl;
      std::cout << "Layer: " << layer << std::endl;
      std::cout << "Transform matrix: " << transform << std::endl;
      std::cout << "MiniColumn: " << miniColumnId << std::endl;
      std::cout << "Column: " << columnId << std::endl;
      std::cout << "Type: " << type << std::endl;

      // MiniColumnPtr miniColumn;
      // TMorphologicalType morphologicalType;
      // TFunctionalType functionalType;

      // NEURON* neuron = new NEURON( nullptr, layer, gid, transform, miniColumn,
      //                              morphologicalType, functionalType );
    }
  }
}

#endif // __NSOL_BRION_READER__
