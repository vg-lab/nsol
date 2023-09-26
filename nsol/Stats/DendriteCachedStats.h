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
#ifndef __NSOL_DENDRITE_CACHED_STATS__
#define __NSOL_DENDRITE_CACHED_STATS__

#include "DendriteStats.h"
#include "NeuriteCachedStats.h"

namespace nsol
{

  /** \class DendriteCachedStats
   *  \brief This class allows to compute stats for dendrites
   *
   *  Using this class instead of Dendrite when constructing the
   *  hierarchy allows to call the method stats from base Dendrite
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/neuriteStats.cpp
   */
  class DendriteCachedStats
    : public DendriteStats
    , public NeuriteCachedStats
  {

  public:

    NSOL_API
    DendriteCachedStats ( TDendriteType dendriteType_ = BASAL );
    
    NSOL_API
    virtual NeuriteStats * stats( void )
    {
      return this;
    }

    // /**
    //  * Returns object as DendriteCachedStats
    //  * @return pointer to DendriteCachedStats object
    //  */
    // NSOL_API
    // virtual NeuriteStats * stats( void )
    // {
    //   return this;
    // }

  }; // class DendriteCachedStats

} // namespace nsol

#endif // __NSOL_DENDRITE_CACHED_STATS__
