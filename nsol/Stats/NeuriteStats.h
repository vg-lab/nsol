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
#ifndef __NSOL_NEURITE_STATS__
#define __NSOL_NEURITE_STATS__

#include "../Neurite.h"

namespace nsol
{

  /** \class NeuriteStats
   *  \brief This class allows to compute stats for neurites
   *
   *  Using this class instead of Neurite when constructing the
   *  hierarchy allows to call the method stats from base Neurite
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/neuriteStats.cpp
   */
  class NeuriteStats : public virtual Neurite
  {

  public:

    //! Enumeration of the stats that can be computed for Neurite
    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      BIFURCATIONS,
      // This should remain the last item
      NEURITE_NUM_STATS
    } TNeuriteStat;


    /**
     * Default constructor
     */
    NSOL_API
    NeuriteStats( TNeuriteType neuriteType = DENDRITE );

    /**
     * Returns object as NeuriteStats
     * @return pointer to NeuriteStats object
     */
    NSOL_API
    virtual NeuriteStats * stats( void )
    {
      return this;
    }

    /**
     * Computes the stat given
     * @param stat stat to compute
     * @param agg aggregation used
     * @return stat value using the aggregation given
     */
    NSOL_API
    virtual float getStat( TNeuriteStat stat,
                           TAggregation agg = /*TAggregation::*/TOTAL ) const;



  }; // class NeuriteStats

} // namespace nsol

#endif // __NSOL_NEURITE_STATS__
