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
#include <examples/exampleData.h>


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

   if( columns.size() == 0 )
   {
      std::cerr << "Columns data is empty" << std::endl;
      return -1;
   }

   for( ColumnPtr col : columns )
   {
      ColumnStats* columnStat = col->stats();

      float maxVolume = columnStat->getStat( ColumnStats::NEURITIC_VOLUME,
                                                    MAX, MAX );
      float maxSurface = columnStat->getStat( ColumnStats::NEURITIC_SURFACE,
                                                    MAX, MAX );

      float minVolume = columnStat->getStat( ColumnStats::NEURITIC_VOLUME,
                                                    MIN, MIN );
      float minSurface = columnStat->getStat( ColumnStats::NEURITIC_SURFACE,
                                                    MIN, MIN );

      float maxVariance = columnStat->getStat( ColumnStats::NEURITIC_SURFACE,
                                                    VARIANCE, MAX );
      float minVariance = columnStat->getStat( ColumnStats::NEURITIC_SURFACE,
                                                    VARIANCE, MIN );

      std::cout << columnStat->id() << ") Column" << std::endl;
      std::cout << "Neuritic Surface - Maximun Variance = "<< maxVariance << std::endl;
      std::cout << "Neuritic Surface - Minimun Variance = "<< minVariance << std::endl;

      std::cout << "Neuritic  Volume - Maximun = "<< maxVolume << std::endl;
      std::cout << "Neuritic Surface - Maximun = "<< maxSurface << std::endl;

      std::cout << "Neuritic  Volume - Minimun = "<< minVolume << std::endl;
      std::cout << "Neuritic Surface - Minimun = "<< minSurface << std::endl;


      float maxVolumeSoma = columnStat->getStat( ColumnStats::SOMA_VOLUME,
                                                    MAX, MAX );
      float maxSurfaceSoma = columnStat->getStat( ColumnStats::SOMA_SURFACE,
                                                    MAX, MAX );

      float minVolumeSoma = columnStat->getStat( ColumnStats::SOMA_VOLUME,
                                                    MIN, MIN );
      float minSurfaceSoma = columnStat->getStat( ColumnStats::SOMA_SURFACE,
                                                    MIN, MIN );

      float maxVarianceSoma = columnStat->getStat( ColumnStats::SOMA_SURFACE,
                                                    VARIANCE, MAX );
      float minVarianceSoma = columnStat->getStat( ColumnStats::SOMA_SURFACE,
                                                    VARIANCE, MIN );

      std::cout << "Soma Surface - Maximun Variance = "<< maxVarianceSoma
                  << std::endl;
      std::cout << "Soma Surface - Minimun Variance = "<< minVarianceSoma
                  << std::endl;

      std::cout << "Soma  Volume - Maximun = "<< maxVolumeSoma << std::endl;
      std::cout << "Soma Surface - Maximun = "<< maxSurfaceSoma << std::endl;
      std::cout << "Soma  Volume - Minimun = "<< minVolumeSoma << std::endl;
      std::cout << "Soma Surface - Minimun = "<< minSurfaceSoma << std::endl;

      std::cout << std::endl;

   }

   return 0;

}
