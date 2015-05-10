/**
 * @file    AxonStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_AXON_STATS__
#define __NSOL_AXON_STATS__

#include "../Axon.h"
#include "NeuriteStats.h"

namespace nsol
{

  /** \class AxonStats
   *  \brief This class allows to compute stats for axons
   *
   *  Using this class instead of Axon when constructing the
   *  hierarchy allows to call the method stats from base Axon
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/neuriteStats.cpp
   */
  class AxonStats
    : public Axon
    , public virtual NeuriteStats
  {

  public:

    NSOL_API
    AxonStats( void )
      : Neurite( Neurite::AXON )
    {
    }


    // NSOL_API
    // virtual AxonNeuriteStats * stats( void )
    // {
    //   return this;
    // }

    /**
     * Returns object as AxonStats
     * @return pointer to AxonStats object
     */
    // NSOL_API
    // virtual NeuriteStats * stats( void )
    // {
    //   return this;
    // }

  }; // class AxonStats

} // namespace nsol

#endif // __NSOL_AXON_STATS__
