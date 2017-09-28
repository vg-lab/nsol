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

BOOST_AUTO_TEST_CASE( columnStats_constructors )
{
    ColumnStats columnStats;
    BOOST_CHECK_EQUAL( columnStats.id( ), 0 );

    ColumnStats columnStats1( 2 );
    BOOST_CHECK_EQUAL( columnStats1.id( ), 2 );
}

BOOST_AUTO_TEST_CASE( columnStats_getStat )
{
    ColumnStats columnStats;
    ColumnStats::TColumnStat stat = ColumnStats::DENDRITIC_VOLUME;

    // Aggregation STD_DEV & VARIANCE
    float result1  = columnStats.getStat( stat, STD_DEV, STD_DEV );
    float result2 = sqrt( columnStats.getStat( stat, VARIANCE ));

    BOOST_CHECK_EQUAL( result1, result2 );

    // Aggregation MIN & MAX
//    float result3 = columnStats.getStat( stat, MIN );
//    float result4 = columnStats.getStat( stat, MAX );

//    BOOST_CHECK( result3 < result4 );
//    BOOST_CHECK_EQUAL( result3, std::min( result3, result4 ));
//    BOOST_CHECK_EQUAL( result4, std::max( result3, result4 ));

    // Aggregation MEAN & TOTAL
    MiniColumns minicolumns = columnStats.miniColumns( );

    float result5 = columnStats.getStat( stat, MEAN );
    float result6 = columnStats.getStat( stat, TOTAL );
    float result7 = minicolumns.size( ) == 0? 0.0f : result6 /
                                             float( minicolumns.size( ));
    BOOST_CHECK_EQUAL( result5, result7 );
}

BOOST_AUTO_TEST_CASE( columnStats_stats )
{
   ColumnStats* columnStats = new ColumnStats( 2 );

   ColumnStats* columnStats1 = columnStats->stats( );

   BOOST_CHECK_EQUAL( columnStats, columnStats1 );
   BOOST_CHECK_EQUAL( columnStats1->id( ), 2 );
   BOOST_CHECK_EQUAL( columnStats->id( ), columnStats1->id( ) );

   // Free dymanic memory used
   NSOL_DELETE_PTR( columnStats );
}
