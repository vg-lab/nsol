/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
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
#ifndef __NSOL_NEURON_MORPHOLOGY_STATS__
#define __NSOL_NEURON_MORPHOLOGY_STATS__

#include "../NeuronMorphology.h"

namespace nsol
{

  /** \class NeuronMorphologyStats
   *  \brief This class allows to compute stats for sections
   *
   *  Using this class instead of NeuronMorphology when constructing the
   *  hierarchy allows to call the method stats from base NeuronMorphology
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/neuronStats.cpp
   */
  class NeuronMorphologyStats
    : public NeuronMorphology
  {

  public:

    typedef enum
    {
      // Volume
      DENDRITIC_VOLUME,
      AXON_VOLUME,
      NEURITIC_VOLUME,
      SOMA_VOLUME,
      VOLUME,
      // Surface
      DENDRITIC_SURFACE,
      AXON_SURFACE,
      NEURITIC_SURFACE,
      SOMA_SURFACE,
      SURFACE,
      // Length
      DENDRITIC_LENGTH,
      AXON_LENGTH,
      NEURITIC_LENGTH,
      // Bifurcations
      DENDRITIC_BIFURCATIONS,
      AXON_BIFURCATIONS,
      NEURITIC_BIFURCATIONS,
      NEURON_MORPHOLOGY_NUM_STATS
    } TNeuronMorphologyStat;


    NSOL_API
    NeuronMorphologyStats( void )
      : NeuronMorphology( )
    {
    }

    NSOL_API
    NeuronMorphologyStats( SomaPtr soma_ )
      : NeuronMorphology( soma_ )
    {
    }

    /**
     * Returns object as NeuronMorphologyStats
     * @return pointer to NeuronMorphologyStats object
     */
    NSOL_API
    virtual NeuronMorphologyStats * stats( void );

    NSOL_API
    virtual float getStat( TNeuronMorphologyStat stat,
                           TAggregation agg = /*TAggregation::*/TOTAL ) const;


  }; // class NeuronMorphologyStats

} // namespace nsol

#endif // __NSOL_NEURON_MORPHOLOGY_STATS__
