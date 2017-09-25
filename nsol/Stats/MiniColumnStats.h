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
#ifndef __NSOL_MINICOLUMN_STATS__
#define __NSOL_MINICOLUMN_STATS__

#include "../MiniColumn.h"

namespace nsol
{

  /** \class MiniColumnStats
   *  \brief This class allows to compute stats for sections
   *
   *  Using this class instead of MiniColumn when constructing the
   *  hierarchy allows to call the method stats from base MiniColumn
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/miniColumnStats.cpp
   */
  class MiniColumnStats
    : public MiniColumn
  {

  public:

    typedef enum
    {
      // Volume
      DENDRITIC_VOLUME = 0,
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
      // This last one allows to know the number of stats
      MINI_COLUMN_NUM_STATS
    } TMiniColumnStat;

    NSOL_API
    MiniColumnStats( const ColumnPtr column = nullptr,
                     const unsigned short id = 0 );


    NSOL_API
    float getStat( TMiniColumnStat stat,
                   TAggregation agg = /*TAggregation::*/TOTAL ) const;


    /**
     * Returns object as MiniColumnStats
     * @return pointer to MiniColumnStats object
     */
    NSOL_API
    virtual MiniColumnStats * stats( void );

    // NSOL_API
    // virtual float dendriticVolume( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float axonVolume( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float neuriticVolume( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float somaVolume( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float volume( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float dendriticSurface( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float axonSurface( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float neuriticSurface( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float somaSurface( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float surface( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float dendriticLength( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float axonLength( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual float neuriticLength( TAggregation op = TOTAL ) const;

    // NSOL_API
    // virtual unsigned int dendriticBifurcations( TAggregation op = TOTAL )
    //   const;

    // NSOL_API
    // virtual unsigned int axonBifurcations( TAggregation op = TOTAL )
    //   const;

    // NSOL_API
    // virtual unsigned int neuriticBifurcations( TAggregation op = TOTAL )
    //   const;

  }; // class MiniColumnStats

} // namespace nsol

#endif // __NSOL_COLUMN_STATS__
