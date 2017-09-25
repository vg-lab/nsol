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
#ifndef __NSOL_AXON_CACHED_STATS__
#define __NSOL_AXON_CACHED_STATS__

#include "AxonStats.h"
#include "NeuriteCachedStats.h"

namespace nsol
{

  /** \class AxonCachedStats
   *  \brief This class allows to compute stats for axons
   *
   *  Using this class instead of Axon when constructing the
   *  hierarchy allows to call the method stats from base Axon
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/neuriteStats.cpp
   */
  class AxonCachedStats
    : public AxonStats
    , public NeuriteCachedStats
  {

  public:

    NSOL_API
    AxonCachedStats( void );


    // NSOL_API
    // virtual AxonNeuriteStats * stats( void )
    // {
    //   return this;
    // }

    /**
     * Returns object as AxonCachedStats
     * @return pointer to AxonCachedStats object
     */
    // NSOL_API
    // virtual NeuriteStats * stats( void )
    // {
    //   return this;
    // }

  }; // class AxonCachedStats

} // namespace nsol

#endif // __NSOL_AXON_STATS__
