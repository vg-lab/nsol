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

using namespace nsol;

void usageMessage( char* programName )
{
  std::cerr << std::endl
            << "Usage: "
            << programName << "\t"
            << "( -bc file_name [ -target target_name ] | " << std::endl
            << "\t\t\t\t  -swc swc_file | -xml scene_file ) " << std::endl
            << "\t\t\t\t  [ -o output_file_name ] " << std::endl
            << std::endl << std::endl;
  exit(-1);
}


bool atLeastTwo( bool a, bool b, bool c )
{
  return a ^ b ? c : a;
}


int main ( int argc, char ** argv )
{

  std::string blueConfig;
  std::string swcFile;
  std::string sceneFile;
  std::string target = std::string( "" );
  std::string outFile;

  for( int i = 1; i < argc; i++ )
  {
    if( std::strcmp( argv[ i ], "-bc" ) == 0 )
    {
      if( ++i < argc )
      {
        blueConfig = std::string( argv[ i ]);
      }
      else
        usageMessage( argv[0] );

    }
    if( std::strcmp( argv[ i ], "-swc" ) == 0 )
    {
      if( ++i < argc )
      {
        swcFile = std::string( argv[ i ]);
      }
      else
        usageMessage( argv[0] );

    }
    if( std::strcmp( argv[ i ], "-xml" ) == 0 )
    {
      if( ++i < argc )
      {
        sceneFile = std::string( argv[ i ] );
      }
      else
        usageMessage( argv[0] );
    }
    if( std::strcmp( argv[ i ], "-target" ) == 0 )
    {
      if( ++i < argc )
      {
        target = std::string( argv[ i ] );
      }
      else
        usageMessage( argv[0] );
    }
    if( std::strcmp( argv[ i ], "-o" ) == 0 )
    {
      if( ++i < argc )
      {
        outFile = std::string( argv[ i ] );
      }
      else
        usageMessage( argv[0] );
    }
  }

  if ( atLeastTwo( !blueConfig.empty( ),
                   !swcFile.empty( ),
                   !sceneFile.empty( )))
  {
    std::cerr << std::endl << "Error: -swc, -xml and -bc options are exclusive"
              << std::endl;
    usageMessage( argv[0] );
  }

  if ( blueConfig.empty( ) & swcFile.empty( ) & sceneFile.empty( ))
  {
    std::cerr << std::endl << "Error: no -swc, -xml and -bc options selected"
              << std::endl;
    usageMessage( argv[0] );
  }

  std::ostream* outStream = &std::cout;
  std::ofstream* outFileStream;

  if ( !outFile.empty( ))
  {
    outFileStream = new std::ofstream( outFile );
    outStream = outFileStream;
  }


  nsol::DataSet dataSet;

  if( !blueConfig.empty( ))
  {
#ifdef NSOL_USE_BRION
    dataSet.loadBlueConfigHierarchy<
      nsol::Node,
      nsol::NeuronMorphologySectionStats,
      nsol::DendriteStats,
      nsol::AxonStats,
      nsol::SomaStats,
      nsol::NeuronMorphologyCachedStats,
      nsol::Neuron,
      nsol::MiniColumnStats,
      nsol::ColumnStats >( blueConfig, target );
    dataSet.loadAllMorphologies( );

#else
    std::cerr << "No Brion support built-in" << std::endl;
    return -1;
#endif
  }
  else if( !swcFile.empty( ))
  {

    dataSet.loadCorticalNeuronFromFile<
      nsol::NodeCached,
      nsol::NeuronMorphologySectionCachedStats,
      nsol::DendriteCachedStats,
      nsol::AxonCachedStats,
      nsol::SomaStats,
      nsol::NeuronMorphologyCachedStats,
      nsol::Neuron,
      nsol::MiniColumn,
      nsol::Column >( swcFile, 0 );
  }
  else if ( !sceneFile.empty( ))
  {
#ifdef NSOL_USE_QT5CORE
    dataSet.loadXmlScene<
      nsol::NodeCached,
      nsol::NeuronMorphologySectionCachedStats,
      nsol::DendriteCachedStats,
      nsol::AxonCachedStats,
      nsol::SomaStats,
      nsol::NeuronMorphologyCachedStats,
      nsol::Neuron,
      nsol::MiniColumnStats,
      nsol::ColumnStats >( sceneFile );
#else
    std::cerr << "No QT5 support built-in" << std::endl;
    return -1;
#endif
  }

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

    ( *outStream ) << columnStat->id() << ") Column" << std::endl;
    ( *outStream ) << "Neuritic Surface - Maximun Variance = "<< maxVariance << std::endl;
    ( *outStream ) << "Neuritic Surface - Minimun Variance = "<< minVariance << std::endl;

    ( *outStream ) << "Neuritic  Volume - Maximun = "<< maxVolume << std::endl;
    ( *outStream ) << "Neuritic Surface - Maximun = "<< maxSurface << std::endl;

    ( *outStream ) << "Neuritic  Volume - Minimun = "<< minVolume << std::endl;
    ( *outStream ) << "Neuritic Surface - Minimun = "<< minSurface << std::endl;


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

    ( *outStream )
      << "Soma Surface - Maximun Variance = "<< maxVarianceSoma
      << std::endl;
    ( *outStream ) << "Soma Surface - Minimun Variance = "<< minVarianceSoma
                   << std::endl;

    ( *outStream ) << "Soma  Volume - Maximun = "<< maxVolumeSoma << std::endl;
    ( *outStream ) << "Soma Surface - Maximun = "<< maxSurfaceSoma << std::endl;
    ( *outStream ) << "Soma  Volume - Minimun = "<< minVolumeSoma << std::endl;
    ( *outStream ) << "Soma Surface - Minimun = "<< minSurfaceSoma << std::endl;

    ( *outStream ) << std::endl;

  }

  return 0;

}
