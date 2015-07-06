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

    //! Stats that can be computed for Segment
    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      SEGMENT_NUM_STATS
    } TSegmentStat;


    NSOL_API
    SegmentStats * stats( void );

    NSOL_API
    virtual float getStat( TSegmentStat stat ) const;


  }; // class SegmentStats


} // namespace nsol

#endif // __NSOL_SEGMENT_STATS__
