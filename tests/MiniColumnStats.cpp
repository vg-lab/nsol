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
}

BOOST_AUTO_TEST_CASE( miniColumnStats_getStat )
{
   // 1- With empty data
   ColumnPtr column( new Column( 1 ));

   MiniColumnStats* minicolumnStats( new MiniColumnStats( column, 2 ));
   MiniColumnStats* minicolumnStats1( new MiniColumnStats( column, 3 ));

   MiniColumnStats::TMiniColumnStat stat = MiniColumnStats::DENDRITIC_VOLUME;

   // Aggregation STD_DEV & VARIANCE
   float surface  = minicolumnStats->getStat( stat, STD_DEV );
   float volume = sqrt( minicolumnStats->getStat( stat, VARIANCE ));

   float length  = minicolumnStats1->getStat( stat, STD_DEV );
   float radius = sqrt( minicolumnStats1->getStat( stat, VARIANCE ));

   BOOST_CHECK_EQUAL( surface, volume );
   BOOST_CHECK_EQUAL( surface, length );
   BOOST_CHECK_EQUAL( volume,radius );

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

   Columns columns = dataSet.columns();

   if( columns.size() > 0 )
   {
      ColumnPtr column1 = columns.at(0);

      if( column1->miniColumns().size() >= 2 )
      {
         MiniColumnPtr miniColumn1 = column1->miniColumns().at(0);
         MiniColumnPtr miniColumn2 = column1->miniColumns().at(1);

         MiniColumnStats* miniColumnStats2 = miniColumn1->stats();
         MiniColumnStats* miniColumnStats3 = miniColumn2->stats();

         BOOST_CHECK( miniColumnStats2 != nullptr );
         BOOST_CHECK_EQUAL( miniColumnStats2->id( ), 0 );

         BOOST_CHECK( miniColumnStats3 != nullptr );
         BOOST_CHECK_EQUAL( miniColumnStats3->id( ), 1 );

         // Aggregation VARIANCE
         if( !miniColumnStats2->neurons( ).empty( ) )
         {
            MiniColumnStats::TMiniColumnStat stat1 = MiniColumnStats::SOMA_VOLUME;
            NeuronMorphologyStats::TNeuronMorphologyStat nStat =
                            NeuronMorphologyStats::TNeuronMorphologyStat( stat1 );

            float value = 0;
            float mean = miniColumnStats2->getStat( stat1, MEAN );

            NSOL_CONST_FOREACH( neuron, miniColumn2->neurons() )
            {
               NeuronMorphologyPtr morphology = ( * neuron )->morphology( );

               float tmpValue = morphology->stats( )->getStat( nStat );
               value += ( mean - tmpValue ) * ( mean - tmpValue );
            }

            float varianceResult = ( miniColumn2->neurons().size( ) == 0 ? 0.0f :
                                 value / float( miniColumn2->neurons().size( )));

            float varianceResult1 = miniColumnStats2->getStat( stat1, VARIANCE);

            BOOST_CHECK_EQUAL( varianceResult, varianceResult1 );
         }

         // MiniColumn Stats 1
         float maxVarianceNeuriteSurface1 = miniColumnStats2->getStat(
                                       MiniColumnStats::NEURITIC_SURFACE, MAX );
         float minVarianceNeuriteSurface1 = miniColumnStats2->getStat(
                                       MiniColumnStats::NEURITIC_SURFACE, MIN );

         float maxVolumeNeurite1 = miniColumnStats2->getStat(
                                        MiniColumnStats::NEURITIC_VOLUME, MAX );
         float maxSurfaceNeurite1 = miniColumnStats2->getStat(
                                       MiniColumnStats::NEURITIC_SURFACE, MAX );

         float minVolumeNeurite1 = miniColumnStats2->getStat(
                                        MiniColumnStats::NEURITIC_VOLUME, MIN );
         float minSurfaceNeurite1 = miniColumnStats2->getStat(
                                           MiniColumnStats::NEURITIC_SURFACE, MIN );
         // MiniColumn Stats 2
         float maxVarianceNeuriteSurface2 = miniColumnStats3->getStat(
                                       MiniColumnStats::NEURITIC_SURFACE, MAX );
         float minVarianceNeuriteSurface2 = miniColumnStats3->getStat(
                                       MiniColumnStats::NEURITIC_SURFACE, MIN );

         float maxVolumeNeurite2 = miniColumnStats3->getStat(
                                        MiniColumnStats::NEURITIC_VOLUME, MAX );
         float maxSurfaceNeurite2 = miniColumnStats3->getStat(
                                       MiniColumnStats::NEURITIC_SURFACE, MAX );

         float minVolumeNeurite2 = miniColumnStats3->getStat(
                                        MiniColumnStats::NEURITIC_VOLUME, MIN );
         float minSurfaceNeurite2 = miniColumnStats3->getStat(
                                           MiniColumnStats::NEURITIC_SURFACE, MIN );

         // MiniColumn Stats 1 same morphology than MiniColumn Stats 2
         BOOST_CHECK( maxVarianceNeuriteSurface1 > maxVarianceNeuriteSurface2 );
         BOOST_CHECK( minVarianceNeuriteSurface1 < minVarianceNeuriteSurface2 );
         BOOST_CHECK( maxVolumeNeurite1 > maxVolumeNeurite2 );
         BOOST_CHECK( maxSurfaceNeurite1 > maxSurfaceNeurite2 );
         BOOST_CHECK( minVolumeNeurite1 < minVolumeNeurite2 );
         BOOST_CHECK( minSurfaceNeurite1 < minSurfaceNeurite2 );

         // Free dymanic memory used
         NSOL_DELETE_PTR( miniColumnStats2 );
         NSOL_DELETE_PTR( miniColumnStats3 );

      }
   }

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
