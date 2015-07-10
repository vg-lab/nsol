/**
 * @file    DataSet.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_DATASET__
#define __NSOL_DATASET__

#include <nsol/api.h>
#include "NsolTypes.h"
#include "Neuron.h"
#include "Container/Columns.h"
#include "Reader/BBPSDKReader.h"
#include "Reader/SwcReader.h"

#ifdef NSOL_WITH_QT5CORE
#include <QXmlStreamReader>
#include <QFile>
#endif


namespace nsol
{

  class DataSet
  {
  public:
    DataSet( void );

#ifdef NSOL_WITH_BBPSDK

    template < class NODE = Node,
               class SEGMENT = Segment,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void openBlueConfig( const std::string& blueconfig,
                         const int loadFlags = MORPHOLOGY,
                         const std::string& targetLabel = std::string( "" ))
    {
      BBPSDKReaderTemplated< NODE, SEGMENT, SECTION, DENDRITE, AXON,
                             SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                             COLUMN > reader;
      reader.readFromBlueConfig( _columns,
                                 blueconfig,
                                 loadFlags,
                                 targetLabel );

      // NSOL_FOREACH( column, columnsMap )
      //   _columns.push_back( column->second );

    }
#endif

    NSOL_API
    void close( void );

    NSOL_API
    Columns& columns( void );

    template < class NODE = Node,
               class SEGMENT = Segment,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void addNeuron( const std::string& swc, const unsigned int gid_,
        const unsigned int columnId_ = 0, const unsigned int miniColumnId_ = 0,
        const unsigned int layer_ = 0,
        const Matrix4_4f transform_ = Matrix4_4f::IDENTITY,
        const Neuron::TNeuronType type_ = Neuron::PYRAMIDAL )
    {
      SwcReaderTemplated< NODE, SEGMENT, SECTION, DENDRITE, AXON, SOMA,
          NEURONMORPHOLOGY, NEURON > swcReader;
      NeuronMorphologyPtr neuronMorphology = swcReader.readFile( swc );

      if( neuronMorphology )
      {

        COLUMN* column = nullptr;
        NSOL_FOREACH( col, _columns )
        {
          if (( *col )->id( ) == columnId_ )
          {
            column = *col;
          }
        }
        if( !column )
        {
          column = new COLUMN( columnId_ );
          _columns.push_back( column );
        }

        MINICOLUMN* miniColumn = nullptr;
        NSOL_FOREACH( miniCol, column->miniColumns() )
        {
          if(( *miniCol )->id( ) == miniColumnId_ )
          {
            miniColumn = *miniCol;
          }
        }
        if( !miniColumn )
        {
          miniColumn = new MINICOLUMN( column );
          column->addMiniColumn( miniColumn );
        }

        NEURON* neuron = new NEURON( neuronMorphology, layer_, gid_, transform_,
                    nullptr, type_ );
        neuron->miniColumn( miniColumn );
        miniColumn->addNeuron( neuron );
      }
    }


    NSOL_API
    void loadScene( const std::string& xmlSceneFile );

  protected:

    Columns _columns;

  }; // class DataSet

} // namespace nsol

#endif // __NSOL_DATASET__
