/**
 * @file    SegmentStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "../error.h"
#include "SegmentStats.h"

namespace nsol
{

  SegmentStats * SegmentStats::stats( void )
  {
    return this;
  }

  float SegmentStats::getStat(TSegmentStat stat,
                              const NodePtr begin,
                              const NodePtr end)
  {
    switch ( stat )
    {
    case SURFACE:
      return ( begin && end) ?
        float( M_2PI ) * end->radius( ) *
        ( begin->point( ) - end->point( )).length( ) :
        0.0f;
      break;

    case VOLUME:
      return ( begin && end) ?
        float( M_PI ) *
        ( begin->point( ) - end->point( )).length( ) *
        end->radius( ) * end->radius( ) : 0.0f;
      break;

    case LENGTH:
      return ( begin && end) ?
        ( begin->point( ) - end->point( )).length( ) : 0.0f;
      break;

    case RADIUS:
      return ( begin && end) ?
        ( begin->radius() + end->radius() ) * 0.5f : 0.0f;
      break;

    default:
      NSOL_THROW( "stat not implemented for SegmentStats" );
    }
    return 0.0f;
  } // class SegmentStats

} // namespace nsol

