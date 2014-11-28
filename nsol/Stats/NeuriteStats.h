/**
 * @file    NeuriteStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
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
   * Example: @include examples/stats.cpp
   */
  class NeuriteStats : public virtual Neurite
  {

  public:

    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      BIFURCATIONS,
      NEURITE_NUM_STATS
    } TNeuriteStat;


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

    NSOL_API
    virtual float getStat( TNeuriteStat stat,
                           TAggregation agg = TAggregation::TOTAL ) const;


    /**
     * Computes volume of the neurite
     * @return volume of neurite
     */
    // NSOL_API
    // virtual float volume( void ) const;

    // /**
    //  * Computes surface of the neurite
    //  * @return surface of neurite
    //  */
    // NSOL_API
    // virtual float surface( void ) const;

    // /**
    //  * Computes length of the neurite
    //  * @return length of neurite
    //  */
    // NSOL_API
    // virtual float length( void ) const;

    // /**
    //  * Computes the number of bifurcations
    //  * @return number of bifurcations
    //  */
    // NSOL_API
    // virtual unsigned int bifurcations( void ) const;


  }; // class NeuriteStats

} // namespace nsol

#endif // __NSOL_NEURITE_STATS__
