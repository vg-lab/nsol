/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
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

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( segmentStats_stats )
{
   SegmentStats* segmentStat = new SegmentStats();

   BOOST_CHECK_EQUAL( segmentStat->stats() != nullptr, true );

   // Free dymanic memory used
   NSOL_DELETE_PTR( segmentStat );

}

BOOST_AUTO_TEST_CASE( segmentStats_getStat )
{
   {
      SegmentStats* segmentStat = new SegmentStats( );

      // Aggregation STD_DEV & VARIANCE
      const NodePtr beginNode( new Node );
      const NodePtr endNode( new Node );
      float surface = segmentStat->getStat( SegmentStats::SURFACE, nullptr,
                                           nullptr );
      float volume = segmentStat->getStat( SegmentStats::VOLUME, nullptr,
                                           nullptr );
      float length = segmentStat->getStat( SegmentStats::LENGTH, beginNode,
                                            endNode );
      float radius = segmentStat->getStat( SegmentStats::RADIUS, beginNode,
                                            endNode );

      BOOST_CHECK(( surface == volume ) && ( volume == length ) &&
                  ( length == radius ));
      BOOST_CHECK_EQUAL( surface, 0.0f );

      // Free dymanic memory used
      NSOL_DELETE_PTR( segmentStat );
   }
   {
      SegmentStats* segmentStat1 = new SegmentStats( );
      const NodePtr beginNode( new Node );
      const NodePtr endNode( new Node );

      beginNode->point( Vec3f(1.0f, 1.0f, 1.0f));
      endNode->point( Vec3f(2.0f, 3.0f, 5.0f ));

      beginNode->radius( 10.f );
      endNode->radius( 5.0f );

      float segmentLength = (beginNode->point( ) - endNode->point( )).norm( );
      float radiusDifference = beginNode->radius() - endNode->radius();
      float generatrix = sqrt( segmentLength*segmentLength +
                                 radiusDifference*radiusDifference );

      float surface = ( M_PI ) * ( beginNode->radius() + endNode->radius() )
                       * generatrix;

      float volume = segmentStat1->getStat( SegmentStats::SURFACE, beginNode,
                                               endNode );

      BOOST_CHECK_EQUAL( surface, volume );

      float length = (M_PI_3) * (beginNode->point( ) - endNode->point( ))
              .norm( ) * ( beginNode->radius() * beginNode->radius() +
              endNode->radius()*endNode->radius() +
              2.0f*beginNode->radius()*endNode->radius() );

      float radius = segmentStat1->getStat( SegmentStats::VOLUME, beginNode,
                                             endNode );


      BOOST_CHECK_EQUAL( length, radius );

      // Free dymanic memory used
      NSOL_DELETE_PTR( segmentStat1 );

   }
}
