/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
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

