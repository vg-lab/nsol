/**
 * @file    SegmentCachedStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SEGMENT_CACHED_STATS__
#define __NSOL_SEGMENT_CACHED_STATS__

#include <nsol/api.h>

#include "Cached.h"
#include "SegmentStats.h"

namespace nsol
{


  class SegmentCachedStats
    : public SegmentStats
    , public Cached<>
  {

  public:

    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      MEAN_RADIUS,
      SEGMENT_NUM_CACHED_VALUES
    } TSegmentCachedValues;

    NSOL_API
    SegmentCachedStats( void );

    NSOL_API
    virtual ~SegmentCachedStats( void );

    NSOL_API
    virtual void setAndPropagateDirty( unsigned int id );

    NSOL_API
    virtual void setAndPropagateDirty( void );

    NSOL_API
    virtual void begin( NodePtr begin_ );

    NSOL_API
    void end( NodePtr end_ );

    NSOL_API
    virtual float volume( void ) const;

    NSOL_API
    virtual float surface( void ) const;

    NSOL_API
    virtual float length( void ) const;

  }; // class SegmentCachedStats

} // namespace nsol

#endif // __NSOL_SEGMENT_CACHED_STATS__
