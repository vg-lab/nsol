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

  float SegmentStats::getStat( TSegmentStat stat ) const
  {
    switch ( stat )
    {
    case SURFACE:
    return ( _begin && _end) ?
      float( M_2PI) * _end->radius( ) *
      ( _begin->point( ) - _end->point( )).length( ) :
      0.0f;
      break;

    case VOLUME:
    return ( _begin && _end) ?
      float( M_PI) *
      ( _begin->point( ) - _end->point( )).length( ) *
      _end->radius( ) *
      _end->radius( ) : 0.0f;
      break;

    case LENGTH:
    return ( _begin && _end) ?
      ( _begin->point( ) - _end->point( )).length( ) : 0.0f;
      break;

    default:
      NSOL_THROW( "stat not implemented for SegmentStats" );
    }
    return 0.0f;
  }

  // float SegmentStats::volume( void ) const
  // {
  //   return ( _begin && _end) ?
  //     float( M_PI) *
  //     ( _begin->point( ) - _end->point( )).length( ) *
  //     _end->radius( ) *
  //     _end->radius( ) : 0.0f;
  // }

  // float SegmentStats::surface( void ) const
  // {
  //   return ( _begin && _end) ?
  //     float( M_2PI) * _end->radius( ) *
  //     ( _begin->point( ) - _end->point( )).length( ) :
  //     0.0f;
  // }

  // float SegmentStats::length( void ) const
  // {
  //   return ( _begin && _end) ?
  //     ( _begin->point( ) - _end->point( )).length( ) : 0.0f;
  // }



}
