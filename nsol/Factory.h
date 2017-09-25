/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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
