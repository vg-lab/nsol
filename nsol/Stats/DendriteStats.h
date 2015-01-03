/**
 * @file    DendriteStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
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
    DendriteStats ( TDendriteType dendriteType_ = BASAL )
      : Dendrite( dendriteType_ )
    {
    }

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
