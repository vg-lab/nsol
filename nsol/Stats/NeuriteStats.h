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
   * Example: @include examples/neuriteStats.cpp
   */
  class NeuriteStats : public virtual Neurite
  {

  public:

    //! Enumeration of the stats that can be computed for Neurite
    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      BIFURCATIONS,
      // This should remain the last item
      NEURITE_NUM_STATS
    } TNeuriteStat;


    /**
     * Default constructor
     */
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

    /**
     * Computes the stat given
     * @param stat stat to compute
     * @param agg aggregation used
     * @return stat value using the aggregation given
     */
    NSOL_API
    virtual float getStat( TNeuriteStat stat,
                           TAggregation agg = /*TAggregation::*/TOTAL ) const;



  }; // class NeuriteStats

} // namespace nsol

#endif // __NSOL_NEURITE_STATS__
