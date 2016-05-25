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
    {
      if( !(begin && end) )
      {
        return 0.0f;
      }
      //Lateral area of a truncated cone.
      float segmentLength =
        (begin->point( ) - end->point( )).norm( );
      float radiusDifference =
        begin->radius() - end->radius();
      float generatrix =
        sqrt( segmentLength*segmentLength +
              radiusDifference*radiusDifference );
      return ( M_PI ) *
        ( begin->radius() + end->radius() ) * generatrix;
      break;
    }
    case VOLUME:
    {
      if( !(begin && end) )
      {
        return 0.0f;
      }
      //Volume of a truncated cone.
      return (M_PI_3) *
        (begin->point( ) - end->point( )).norm( ) *
        ( begin->radius()*begin->radius() +
          end->radius()*end->radius() +
          2.0f*begin->radius()*end->radius() );
      break;
    }
    case LENGTH:
    {
      return (begin && end) ?
        (begin->point( ) - end->point( )).norm( ) : 0.0f;
      break;
    }
    case RADIUS:
    {
      return (begin && end) ?
        (begin->radius() + end->radius()) * 0.5f : 0.0f;
      break;
    }
    default:
      NSOL_THROW( "stat not implemented for SegmentStats" );
    }
    return 0.0f;
  } // class SegmentStats

} // namespace nsol

