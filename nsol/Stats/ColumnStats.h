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
#ifndef __NSOL_COLUMN_STATS__
#define __NSOL_COLUMN_STATS__

#include "../Column.h"

namespace nsol
{

  /** \class ColumnStats
   *  \brief This class allows to compute stats for sections
   *
   *  Using this class instead of Column when constructing the
   *  hierarchy allows to call the method stats from base Column
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/miniColumnStats.cpp
   */
  class ColumnStats
    : public Column
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
      COLUMN_NUM_STATS
    } TColumnStat;

    NSOL_API
    ColumnStats( const unsigned short id = 0 );


    NSOL_API
    float getStat( TColumnStat stat,
                   TAggregation miniColAgg = /*TAggregation::*/TOTAL,
                   TAggregation neuronAgg = /*TAggregation::*/TOTAL ) const;

    /**
     * Returns object as ColumnStats
     * @return pointer to ColumnStats object
     */
    NSOL_API
    virtual ColumnStats * stats( void );

  }; // class ColumnStats

} // namespace nsol

#endif // __NSOL_COLUMN_STATS__
