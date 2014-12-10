/**
 * @file    AxonCachedStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
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
    AxonCachedStats( void )
      : Neurite( Neurite::AXON )
    {
      // std::cout << "AxonCachedStats constructor " <<  _neuriteType
      //           << " " << Neurite::AXON << std::endl;
    }


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
