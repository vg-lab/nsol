/**
 * @file    DendriteCachedStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
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
   * Example: @include examples/stats.cpp
   */
  class DendriteCachedStats
    : public DendriteStats
    , public NeuriteCachedStats
  {

  public:

    NSOL_API
    DendriteCachedStats ( TDendriteType dendriteType_ = BASAL )
      : DendriteStats( dendriteType_ )
    {
    }

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
