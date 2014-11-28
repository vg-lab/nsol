/**
 * @file    NeuriteCachedStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NEURITE_CACHED_STATS__
#define __NSOL_NEURITE_CACHED_STATS__

#include <nsol/api.h>

#include "Cached.h"
#include "NeuriteStats.h"

namespace nsol
{

  /** \class NeuriteCachedStats
   *  \brief This class allows to cache the stats for neurites
   *
   *  Using this class instead of Neurite or NeuriteStats when constructing
   *  the hierarchy allows to call the method stats from base Neurite
   *  class and get the corresponding volume, surface and length. If the
   *  cached value is dirty then the actual computation process is done.
   *  In case is clean the cached value is returned directly.
   *
   *  Example: @include examples/stats.cpp
   */
  class NeuriteCachedStats
    : public virtual NeuriteStats
    , public Cached<>
  {


  public:

    // //! Stats that can be cached for NeuriteStats
    // typedef enum
    // {
    //   SURFACE = 0,
    //   VOLUME,
    //   LENGTH,
    //   BIFURCATIONS,
    //   NEURITE_NUM_CACHED_VALUES
    // } TNeuriteCachedValues;

    /**
     * Default constructor
     */
    NSOL_API
    NeuriteCachedStats( void );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~NeuriteCachedStats( void );

    /**
     * Set dirty a cached stat and propagates dirty to parent neurite
     * @param id identifier of the property to set dirty. It also propagates
     * dirty state to parent neurite. id value has to be one from
     * TNeuriteCachedValues (checked only on debug compiling).
     */
    NSOL_API
    virtual void setAndPropagateDirty( unsigned int id );

    /**
     * Set dirty all cached stats and propagates dirty to parent neurite
     */
    NSOL_API
    virtual void setAndPropagateDirty( void );

    /**
     * Set dirty all cached stats and propagates dirty to parent neurite
     */
    NSOL_API
    virtual void firstSection( SectionPtr section );

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



  }; // class NeuriteCachedStats

} // namespace nsol

#endif // __NSOL_NEURITE_CACHED_STATS__
