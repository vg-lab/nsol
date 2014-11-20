/**
 * @file    SegmentStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SEGMENT_STATS__
#define __NSOL_SEGMENT_STATS__

#include "../Segment.h"

namespace nsol
{

  class SegmentStats : public Segment
  {

  public:

    NSOL_API
    SegmentStats * stats( void );

    NSOL_API
    virtual float volume( void ) const;

    NSOL_API
    virtual float surface( void ) const;

    NSOL_API
    virtual float length( void ) const;


  }; // class SegmentStats


} // namespace nsol

#endif // __NSOL_SEGMENT_STATS__
