/**
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_FACTORY__
#define __NSOL_FACTORY__

#include <nsol/nsol.h>

namespace nsol
{

#define FACTORY_TEMPLATE_CLASSES                 \
    class NODE,                                  \
    class SECTION,                               \
    class DENDRITE,                              \
    class AXON,                                  \
    class SOMA,                                  \
    class NEURONMORPHOLOGY,                      \
    class NEURON,                                \
    class MINICOLUMN,                            \
    class COLUMN

#define FACTORY_TEMPLATE_CLASS_NAMES            \
    NODE,                                       \
    SECTION,                                    \
    DENDRITE,                                   \
    AXON,                                       \
    SOMA,                                       \
    NEURONMORPHOLOGY,                           \
    NEURON,                                     \
    MINICOLUMN,                                 \
    COLUMN

  namespace generic
  {
    template < FACTORY_TEMPLATE_CLASSES >
    class Factory
    {

    public:

      static NeuronPtr newNeuron( bool createMorphology = true )
      {
        if ( createMorphology )
          return NeuronPtr (
            new NEURON( new NEURONMORPHOLOGY( new SOMA )));
        else
          return NeuronPtr ( new NEURON );
      }


      static NeuronMorphologyPtr newNeuronMorphology( void )
      {
        return new NEURONMORPHOLOGY( new SOMA );
      }

    };
  } // namespace generic

  typedef generic::Factory< Node,
                            Section,
                            Dendrite,
                            Axon,
                            Soma,
                            NeuronMorphology,
                            Neuron,
                            MiniColumn,
                            Column > Factory;

//  typedef generic::Factory< Node,
//                            SegmentStats,
//                            SectionStats,
//                            DendriteStats,
//                            AxonStats,
//                            SomaStats,
//                            NeuronMorphologyStats,
//                            Neuron,
//                            MiniColumnStats,
//                            ColumnStats > FactoryStats;
//
//  typedef generic::Factory< NodeCached,
//                            SegmentCachedStats,
//                            SectionCachedStats,
//                            DendriteCachedStats,
//                            AxonCachedStats,
//                            SomaStats,
//                            NeuronMorphologyCachedStats,
//                            Neuron,
//                            MiniColumnStats,
//                            ColumnStats > FactoryCachedStats;



} // namespace nsol

#endif // __NSOL_FACTORY__
