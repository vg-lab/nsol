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
    virtual void setAndPropagateDirty( void );

    NSOL_API
    virtual SegmentPtr addSegment( SegmentPtr segment = nullptr );

    NSOL_API
    virtual void firstSegment( SegmentPtr firstSegment_ );

    NSOL_API
    virtual void lastSegment( SegmentPtr lastSegment_ );

    NSOL_API
    virtual float volume( void );


  }; // class SectionCachedStats

} // namespace nsol

#endif // __NSOL_SECTION_CACHED_STATS__
