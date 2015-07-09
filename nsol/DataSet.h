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
#include "Container/Columns.h"
#include "Reader/BBPSDKReader.h"
#include "Reader/SwcReader.h"

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
    NSOL_API
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
               class NEURON = Neuron >
    NSOL_API
    void addNeuron( const std::string& swc, unsigned int columnId_,
        unsigned int miniColumnId_/*,
        Matrix4_4f transform_, unsigned int gid_
        unsigned int layer_*/ )
    {
      SwcReaderTemplated< NODE, SEGMENT, SECTION, DENDRITE, AXON, SOMA,
          NEURONMORPHOLOGY, NEURON > swcReader;
      NeuronPtr neuron = swcReader.readNeuron( swc );

      /*
       * neuron->gid( gid_ );
       * neuron->layer( layer_ );
       * neuron->transform( transform_ );
       *
       */

      if ( _columns.size( ) <= columnId_ )
      {
        for ( unsigned int i = _columns.size() ; i < columnId_ + 1; i++ )
        {
          _columns.push_back( new Column( ));
        }
      }

      MiniColumns miniColumns = _columns[ columnId_ ]->miniColumns( );
      if ( miniColumns.size( ) <= miniColumnId_ )
      {
        for ( unsigned int i = miniColumns.size() ; i < miniColumnId_ + 1; i++ )
        {
          miniColumns.push_back( new MiniColumn( ));
        }
      }

      miniColumns[ miniColumnId_ ]->addNeuron( neuron );
    }

  protected:

    Columns _columns;

  }; // class DataSet

} // namespace nsol

#endif // __NSOL_DATASET__
