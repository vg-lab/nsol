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
#ifndef __NSOL_DENDRITE_STATS__
#define __NSOL_DENDRITE_STATS__

#include "../Dendrite.h"
#include "NeuriteStats.h"

namespace nsol
{

  /** \class DendriteStats
   *  \brief This class allows to compute stats for dendrites
   *
   *  Using this class instead of Dendrite when constructing the
   *  hierarchy allows to call the method stats from base Dendrite
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/neuriteStats.cpp
   */
  class DendriteStats
    : public Dendrite
    , public virtual NeuriteStats
  //    , public DendriteStats
  {

  public:

    NSOL_API
    DendriteStats ( TDendriteType dendriteType_ = BASAL );
    
    // NSOL_API
    // virtual NeuriteStats * stats( void )
    // {
    //   return this;
    // }

    // /**
    //  * Returns object as DendriteStats
    //  * @return pointer to DendriteStats object
    //  */
    // NSOL_API
    // virtual NeuriteStats * stats( void )
    // {
    //   return this;
    // }

  }; // class DendriteStats

} // namespace nsol

#endif // __NSOL_DENDRITE_STATS__
