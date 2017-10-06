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
#include <testData.h>

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
    // 1- With empty data
   ColumnStats columnStats;
   ColumnStats::TColumnStat stat = ColumnStats::DENDRITIC_VOLUME;

   // Aggregation STD_DEV & VARIANCE
   float volume  = columnStats.getStat( stat, STD_DEV, STD_DEV );
   float length = sqrt( columnStats.getStat( stat, VARIANCE ));

   BOOST_CHECK_EQUAL( volume, length );

   // Aggregation MIN & MAX
   float radius = columnStats.getStat( ColumnStats::DENDRITIC_BIFURCATIONS, MIN );
   float result4 = columnStats.getStat( ColumnStats::SOMA_SURFACE, MAX );

   BOOST_CHECK_EQUAL( radius != result4, true );

   // Aggregation MEAN & TOTAL
   MiniColumns minicolumns = columnStats.miniColumns( );

   float result5 = columnStats.getStat( stat, MEAN );
   float result6 = columnStats.getStat( stat, TOTAL );
   float result7 = minicolumns.size( ) == 0? 0.0f : result6 /
                                            float( minicolumns.size( ));
   BOOST_CHECK_EQUAL( result5, result7 );

   MiniColumnPtr miniColumn( new MiniColumn );
   columnStats.addMiniColumn( miniColumn );

   BOOST_CHECK_EQUAL( columnStats.miniColumns( ).size( ), 1 );

   // 2- With data loaded
   DataSet dataSet;

#ifdef NSOL_USE_QT5CORE
   dataSet.loadXmlScene<
     nsol::NodeCached,
     nsol::SectionCachedStats,
     nsol::DendriteCachedStats,
     nsol::AxonCachedStats,
     nsol::SomaStats,
     nsol::NeuronMorphologyCachedStats,
     nsol::Neuron,
     nsol::MiniColumnStats,
     nsol::ColumnStats >( NSOL_XML_SCENE_TEST2_DATA );
#else
   std::cerr << "No QT5 support built-in" << std::endl;
   return 0;
#endif

   Columns columns = dataSet.columns( );

   if( columns.size( ) > 0 )
   {
      ColumnPtr column = columns.at( 0 );
      ColumnStats* columnStats1 = column->stats( );

      // Aggregation VARIANCE
      if( !column->miniColumns().empty() )
      {
         ColumnStats::TColumnStat stat1 = ColumnStats::SOMA_VOLUME;
         MiniColumnStats::TMiniColumnStat nStat = MiniColumnStats::TMiniColumnStat( stat1 );
         TAggregation neuronAgg = MAX;

         float value = 0.f;
         float mean = columnStats1->getStat( stat1, MEAN );

         NSOL_CONST_FOREACH( miniCol, columnStats1->miniColumns( ))
         {
            float tmpValue = ( * miniCol )->stats( )->getStat( nStat, neuronAgg );
            value += ( mean - tmpValue ) * ( mean - tmpValue );
         }
         float variance_result = ( columnStats1->miniColumns( ).size( ) == 0 ? 0.0f :
                                value / float( columnStats1->miniColumns( ).size( )));

         float variance_result1 = columnStats1->getStat( stat1, VARIANCE, neuronAgg );

         BOOST_CHECK_EQUAL( variance_result, variance_result1 );
      }

      BOOST_CHECK_EQUAL( columnStats1->id( ), 0 );

      float maxVarianceNeuriteSurface = columnStats1->getStat(
                                 ColumnStats::NEURITIC_SURFACE, VARIANCE, MAX );
      float minVarianceNeuriteSurface = columnStats1->getStat(
                                 ColumnStats::NEURITIC_SURFACE, VARIANCE, MIN );

      float maxVolumeNeurite = columnStats1->getStat( ColumnStats::NEURITIC_VOLUME,
                                                 MAX, MAX );
      float maxSurfaceNeurite = columnStats1->getStat( ColumnStats::NEURITIC_SURFACE,
                                                 MAX, MAX );

      float minVolumeNeurite = columnStats1->getStat( ColumnStats::NEURITIC_VOLUME,
                                                  MIN, MIN );
      float minSurfaceNeurite = columnStats1->getStat( ColumnStats::NEURITIC_SURFACE,
                                                  MIN, MIN );

      BOOST_CHECK_EQUAL( minVarianceNeuriteSurface,
                         std::numeric_limits<double>::infinity( ));

      BOOST_CHECK_EQUAL( maxVolumeNeurite, minVolumeNeurite );
      BOOST_CHECK_EQUAL( maxSurfaceNeurite, minSurfaceNeurite );

      float maxVarianceSomaSurface = columnStats1->getStat(
                                     ColumnStats::SOMA_SURFACE, VARIANCE, MAX );
      float minVarianceSomaSurface = columnStats1->getStat(
                                     ColumnStats::SOMA_SURFACE, VARIANCE, MIN );

      float maxVolumeSoma = columnStats1->getStat( ColumnStats::SOMA_VOLUME,
                                                  MAX, MAX );
      float maxSurfaceSoma = columnStats1->getStat( ColumnStats::SOMA_SURFACE,
                                                  MAX, MAX );

      float minVolumeSoma = columnStats1->getStat( ColumnStats::SOMA_VOLUME,
                                                  MIN, MIN );
      float minSurfaceSoma = columnStats1->getStat( ColumnStats::SOMA_SURFACE,
                                                  MIN, MIN );

      BOOST_CHECK_EQUAL( minVarianceSomaSurface, std::numeric_limits<double>::infinity( ));

      BOOST_CHECK_EQUAL( maxVolumeSoma, minVolumeSoma );
      BOOST_CHECK_EQUAL( maxSurfaceSoma, minSurfaceSoma );

      BOOST_CHECK_EQUAL( minVarianceNeuriteSurface, minVarianceSomaSurface);

      BOOST_CHECK( maxVarianceNeuriteSurface > maxVarianceSomaSurface );

      // Free dymanic memory used
      NSOL_DELETE_PTR( columnStats1 );

   }

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
