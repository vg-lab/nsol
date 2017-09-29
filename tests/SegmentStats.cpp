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
   SegmentStats* segmentStat = new SegmentStats( );

   // Aggregation STD_DEV & VARIANCE
   const NodePtr begin_node( new Node );
   const NodePtr end_node( new Node );
   float result = segmentStat->getStat( SegmentStats::SURFACE, nullptr,
                                        nullptr );
   float result1 = segmentStat->getStat( SegmentStats::VOLUME, nullptr,
                                        nullptr );
   float result2 = segmentStat->getStat( SegmentStats::LENGTH, begin_node,
                                         end_node );
   float result3 = segmentStat->getStat( SegmentStats::RADIUS, begin_node,
                                         end_node );

   BOOST_CHECK(( result == result1 ) && ( result1 == result2 ) &&
               ( result2 == result3 ));
   BOOST_CHECK_EQUAL( result, 0.0f );

   // Free dymanic memory used
   NSOL_DELETE_PTR( segmentStat );
}
