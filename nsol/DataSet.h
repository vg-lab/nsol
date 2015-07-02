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
                         const int bbpDataTypes = bbp::MICROCIRCUIT |
                         bbp::AFFERENT_SYNAPSES |
                         bbp::EFFERENT_SYNAPSES,
                         const std::string& targetLabel = std::string( "" ))
    {
      BBPSDKReaderTemplated< NODE, SEGMENT, SECTION, DENDRITE, AXON,
                             SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                             COLUMN > reader;
      auto columnsMap = reader.readFromBlueConfig( blueconfig,
                                                   bbpDataTypes,
                                                   targetLabel );

      NSOL_FOREACH( column, columnsMap )
        _columns.push_back( column->second );

    }
#endif

    void close( void );

    Columns& columns( void );

  protected:

    Columns _columns;

  }; // class DataSet

} // namespace nsol

#endif // __NSOL_DATASET__
