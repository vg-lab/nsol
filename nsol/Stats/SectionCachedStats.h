/**
 * @file    SectionCachedStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SECTION_CACHED_STATS__
#define __NSOL_SECTION_CACHED_STATS__

#include <nsol/api.h>

#include "Cached.h"
#include "SectionStats.h"

namespace nsol
{


  /** \class SectionCachedStats
   *  \brief This class allows to cache the stats for sections
   *
   *  Using this class instead of Section or SectionStats when constructing
   *  the hierarchy allows to call the method stats from base Section
   *  class and get the corresponding volume, surface and length. If the cached
   *  value is dirty then the actual computation process is done. In case is
   *  clean the cached value is returned directly.
   *
   *  Example: @include examples/stats.cpp
   */
  class SectionCachedStats
    : public SectionStats
    , public Cached<>
  {


  public:

    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      MEAN_RADIUS,
      SECTION_NUM_CACHED_VALUES
    } TSectionCachedValues;

    NSOL_API
    SectionCachedStats( void );

    NSOL_API
    virtual ~SectionCachedStats( void );

    NSOL_API
    virtual void setAndPropagateDirty( unsigned int id );

    NSOL_API
    virtual void setAndPropagateDirty( void );

    NSOL_API
    virtual SegmentPtr addSegment( SegmentPtr segment = nullptr );

    NSOL_API
    virtual void firstSegment( SegmentPtr firstSegment_ );

    NSOL_API
    virtual void lastSegment( SegmentPtr lastSegment_ );

    NSOL_API
    virtual float volume( void ) const;

    NSOL_API
    virtual float surface( void ) const;

    NSOL_API
    virtual float length( void ) const;


  }; // class SectionCachedStats

} // namespace nsol

#endif // __NSOL_SECTION_CACHED_STATS__
