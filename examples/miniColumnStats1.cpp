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


#include <nsol/nsol.h>
#include <../tests/testData.h>


using namespace nsol;

int main (  )
{
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
   return -1;
#endif

   Columns columns = dataSet.columns( );

   std::cout << "Num Columns = "<< columns.size( ) << std::endl;

   if( columns.size( ) == 0 )
   {
      std::cerr << "Columns data is empty" << std::endl;
      return -1;
   }

   for( ColumnPtr col : columns )
   {
      MiniColumnPtr miniColumn1 = col->miniColumns( ).at( 0 );
      MiniColumnPtr minicolumn2 = col->miniColumns( ).at( 1 );

      MiniColumnStats* miniColumnStats1 = miniColumn1->stats( );
      MiniColumnStats* miniColumnStats2 = minicolumn2->stats( );

      // MiniColumn Stats 1
      float maxVarianceNeuriteSurface1 = miniColumnStats1->getStat(
                                      MiniColumnStats::NEURITIC_SURFACE, MAX );
      float minVarianceNeuriteSurface1 = miniColumnStats1->getStat(
                                      MiniColumnStats::NEURITIC_SURFACE, MIN );

      float maxVolumeNeurite1 = miniColumnStats1->getStat(
                                       MiniColumnStats::NEURITIC_VOLUME, MAX );
      float maxSurfaceNeurite1 = miniColumnStats1->getStat(
                                      MiniColumnStats::NEURITIC_SURFACE, MAX );

      float minVolumeNeurite1 = miniColumnStats1->getStat(
                                       MiniColumnStats::NEURITIC_VOLUME, MIN );
      float minSurfaceNeurite1 = miniColumnStats1->getStat(
                                          MiniColumnStats::NEURITIC_SURFACE, MIN );

      std::cout << miniColumnStats1->id() << ") MiniColumn" << std::endl;

      std::cout << "Neuritic Surface - Maximun Variance = "
                  << maxVarianceNeuriteSurface1 << std::endl;
      std::cout << "Neuritic Surface - Minimun Variance = "
                  << minVarianceNeuriteSurface1 << std::endl;

      std::cout << "Neuritic  Volume - Maximun = "
                  << maxVolumeNeurite1 << std::endl;
      std::cout << "Neuritic Surface - Maximun = "
                  << maxSurfaceNeurite1 << std::endl;

      std::cout << "Neuritic  Volume - Minimun = "
                  << minVolumeNeurite1 << std::endl;
      std::cout << "Neuritic Surface - Minimun = "
                  << minSurfaceNeurite1 << std::endl;

      std::cout << std::endl;

      // MiniColumn Stats 2
      float maxVarianceNeuriteSurface2 = miniColumnStats2->getStat(
                                      MiniColumnStats::NEURITIC_SURFACE, MAX );
      float minVarianceNeuriteSurface2 = miniColumnStats2->getStat(
                                      MiniColumnStats::NEURITIC_SURFACE, MIN );

      float maxVolumeNeurite2 = miniColumnStats2->getStat(
                                       MiniColumnStats::NEURITIC_VOLUME, MAX );
      float maxSurfaceNeurite2 = miniColumnStats2->getStat(
                                      MiniColumnStats::NEURITIC_SURFACE, MAX );

      float minVolumeNeurite2 = miniColumnStats2->getStat(
                                       MiniColumnStats::NEURITIC_VOLUME, MIN );
      float minSurfaceNeurite2 = miniColumnStats2->getStat(
                                          MiniColumnStats::NEURITIC_SURFACE, MIN );

      std::cout << miniColumnStats2->id() << ") MiniColumn" << std::endl;

      std::cout << "Neuritic Surface - Maximun Variance = "
                  << maxVarianceNeuriteSurface2 << std::endl;
      std::cout << "Neuritic Surface - Minimun Variance = "
                  << minVarianceNeuriteSurface2 << std::endl;

      std::cout << "Neuritic  Volume - Maximun = "
                  << maxVolumeNeurite2 << std::endl;
      std::cout << "Neuritic Surface - Maximun = "
                  << maxSurfaceNeurite2 << std::endl;

      std::cout << "Neuritic  Volume - Minimun = "
                  << minVolumeNeurite2 << std::endl;
      std::cout << "Neuritic Surface - Minimun = "
                  << minSurfaceNeurite2 << std::endl;


      std::cout << std::endl;

   }

   return 0;

}
