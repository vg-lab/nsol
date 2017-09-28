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

BOOST_AUTO_TEST_CASE( miniColumnStats_constructors )
{
   MiniColumnStats minicolumnStats;
   BOOST_CHECK_EQUAL( minicolumnStats.id( ), 0 );
   BOOST_CHECK( minicolumnStats.column( ) == nullptr );

   ColumnPtr column( new Column( 3 ));

   MiniColumnStats* minicolumnStats1( new MiniColumnStats( column, 2 ));
   BOOST_CHECK_EQUAL( minicolumnStats1->id( ), 2 );
   BOOST_CHECK( minicolumnStats1->column( ) != nullptr );
   BOOST_CHECK_EQUAL( minicolumnStats1->column( )->id( ), 3 );
   column->addMiniColumn( minicolumnStats1 );
   BOOST_CHECK_EQUAL( column->miniColumns( ).size( ), 1 );

   // Free dymanic memory used
   NSOL_DELETE_PTR( minicolumnStats1 );
   NSOL_DELETE_PTR( column );
}

BOOST_AUTO_TEST_CASE( miniColumnStats_getStat )
{
   ColumnPtr column( new Column( 1 ));

   MiniColumnStats* minicolumnStats( new MiniColumnStats( column, 2 ));
   MiniColumnStats* minicolumnStats1( new MiniColumnStats( column, 3 ));

   MiniColumnStats::TMiniColumnStat stat = MiniColumnStats::DENDRITIC_VOLUME;

   // Aggregation STD_DEV & VARIANCE
   float result  = minicolumnStats->getStat( stat, STD_DEV );
   float result1 = sqrt( minicolumnStats->getStat( stat, VARIANCE ));

   float result2  = minicolumnStats1->getStat( stat, STD_DEV );
   float result3 = sqrt( minicolumnStats1->getStat( stat, VARIANCE ));

   BOOST_CHECK_EQUAL( result, result1 );
   BOOST_CHECK_EQUAL( result, result2 );
   BOOST_CHECK_EQUAL( result1,result3 );

   // Aggregation MEAN & TOTAL
   Neurons neurons = minicolumnStats->neurons();

   float result4 = minicolumnStats->getStat( stat, MEAN );
   float result5 = minicolumnStats->getStat( stat, TOTAL );
   float result6 = neurons.size( ) == 0? 0.0f : result5 / float( neurons.size( ));

   BOOST_CHECK_EQUAL( result4, result6 );

   Neurons neurons1 = minicolumnStats1->neurons();

   float result7 = minicolumnStats1->getStat( stat, MEAN );
   float result8 = minicolumnStats1->getStat( stat, TOTAL );
   float result9 = neurons1.size( ) == 0? 0.0f : result8 / float( neurons1.size( ));

   BOOST_CHECK_EQUAL( result4, result7 );
   BOOST_CHECK_EQUAL( result5, result8 );
   BOOST_CHECK_EQUAL( result4, result9 );

   float result10 = minicolumnStats->getStat( stat, MEAN );
   BOOST_CHECK_EQUAL( result4, result10 );
   BOOST_CHECK_EQUAL( result7, result10 );

   // Free dymanic memory used
   NSOL_DELETE_PTR( minicolumnStats );
   NSOL_DELETE_PTR( minicolumnStats1 );
   NSOL_DELETE_PTR( column );
}

BOOST_AUTO_TEST_CASE( miniColumnStats_stats )
{
    ColumnPtr column( new Column( 3 ));

   MiniColumnStats* minicolumnStats = new MiniColumnStats( column, 2 );

   MiniColumnStats* minicolumnStats1 = minicolumnStats->stats( );

   BOOST_CHECK_EQUAL( minicolumnStats, minicolumnStats1 );
   BOOST_CHECK_EQUAL( minicolumnStats1->id( ), 2 );
   BOOST_CHECK_EQUAL( minicolumnStats->id( ), minicolumnStats1->id( ));

   // Free dymanic memory used
   NSOL_DELETE_PTR( minicolumnStats );
}
