/*
 * Copyright (c) 2014-2017 GMRV/URJC.
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

/*
 * Example to show how to use stats and cached stats
 */

#include <nsol/nsol.h>

void computeMiniColumnStats( nsol::MiniColumnPtr column );

void printMiniColumnStats( nsol::MiniColumnPtr column );


#ifndef NSOL_USE_BBPSDK

int main ( int /* argc */, char ** /* argv */ )
{
  std::cout << "BBPSDK support not built-in" << std::endl;

  return 0;
}
#else

int main ( int argc, char ** argv )
{
  std::cout << std::endl;

  if ( argc < 2 )
  {
    std::cerr << "Error. Usage: " << argv[0]
              << " blue_config_input_file" << std::endl;
    return -1;
  }

  nsol::BBPSDKReaderStats readerWithStats;
  nsol::Columns columnsWithStats;
  nsol::NeuronsMap neuronsWithStats;
  readerWithStats.readFromBlueConfig( columnsWithStats, neuronsWithStats,
                                      argv[1] );

  nsol::MiniColumnPtr miniColumnWithStats =
    columnsWithStats[0]->miniColumns( )[0];

  // columnsWithStats[0]->miniColumns( )[0]->stats()->dendriticSurface();
  // return 0;

  nsol::BBPSDKReaderCachedStats readerWithCachedStats;
  nsol::Columns columnsWithCachedStats;
  nsol::NeuronsMap neuronsWithCachedStats;
  readerWithCachedStats.readFromBlueConfig( columnsWithCachedStats,
                                            neuronsWithCachedStats, argv[1] );

  nsol::MiniColumnPtr miniColumnWithCachedStats =
    columnsWithCachedStats[0]->miniColumns( )[0];

  NSOL_CHECK_THROW( miniColumnWithStats->stats( ),
                    "no stats in minicolumn" );
  NSOL_CHECK_THROW( miniColumnWithCachedStats->stats( ),
                    "no stats in minicolumn" );

  std::cout << "Number of neurons: "
            << miniColumnWithStats->neurons().size() << std::endl;

  std::cout << std::endl;


  for ( unsigned int layer = 0 ; layer < 7; layer++ )
  {
    std::cout << layer << " pyr: " <<
      miniColumnWithStats->numberOfNeurons( false,
                                            nsol::Neuron::PYRAMIDAL,
                                            layer )
              <<  " inter: " <<
      miniColumnWithStats->numberOfNeurons( false,
                                            nsol::Neuron::INTERNEURON,
                                            layer )
              << std::endl;
  }



  return 0;

  struct timeval startTime, endTime;
  long totalTime;

#define START_TIME  gettimeofday(&startTime, NULL);
#define END_TIME                                               \
  gettimeofday(&endTime, NULL);                                \
  totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L; \
  totalTime += (endTime.tv_usec - startTime.tv_usec);          \
  std::cout << "\tElapsed time: "                              \
            << (totalTime/1000L) / 1000.0f                     \
            << std::endl << std::endl;

  std::cout << "Non-cached stats" << std::endl;
  START_TIME;
  printMiniColumnStats( miniColumnWithStats );
  END_TIME;

  START_TIME;
  printMiniColumnStats( miniColumnWithCachedStats );
  END_TIME;

  START_TIME;
  printMiniColumnStats( miniColumnWithCachedStats );
  END_TIME;

  return 0;

}


void computeMiniColumnStats( nsol::MiniColumnPtr miniColumn )
{

  NSOL_DEBUG_CHECK( miniColumn , "miniColumn is null" );
  NSOL_DEBUG_CHECK( miniColumn->stats( ) , "no stats" );

  miniColumn->stats( )->getStat( nsol::MiniColumnStats::DENDRITIC_VOLUME );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::AXON_VOLUME );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::NEURITIC_VOLUME );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::SOMA_VOLUME );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::VOLUME );

  // Surface
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::DENDRITIC_SURFACE );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::AXON_SURFACE );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::NEURITIC_SURFACE );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::SOMA_SURFACE );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::SURFACE );

  // Length
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::DENDRITIC_LENGTH );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::AXON_LENGTH );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::NEURITIC_LENGTH
    );
  // Bifurcations
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::DENDRITIC_BIFURCATIONS );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::AXON_BIFURCATIONS );
  miniColumn->stats( )->getStat( nsol::MiniColumnStats::NEURITIC_BIFURCATIONS );



  // miniColumn->stats( )->dendriticSurface( );
  // miniColumn->stats( )->axonSurface( );
  // miniColumn->stats( )->neuriticSurface( );
  // miniColumn->stats( )->surface( );
  // miniColumn->stats( )->dendriticVolume( );
  // miniColumn->stats( )->axonVolume( );
  // miniColumn->stats( )->neuriticVolume( );
  // miniColumn->stats( )->volume( );
  // miniColumn->stats( )->dendriticLength( );
  // miniColumn->stats( )->axonLength( );
  // miniColumn->stats( )->neuriticLength( );
  // miniColumn->stats( )->dendriticBifurcations( );
  // miniColumn->stats( )->axonBifurcations( );
  // miniColumn->stats( )->neuriticBifurcations( );

}

#define COMPUTE_AND_PRINT2( __MSG__, __METHOD__ )                        \
  std::cout << __MSG__                                                  \
  << miniColumn->stats( )->__METHOD__( nsol::TAggregation::TOTAL )      \
  << std::endl;                                                         \


#define COMPUTE_AND_PRINT( __MSG__, _S_ )                               \
  std::cout << __MSG__                                                  \
  << miniColumn->stats( )->getStat( _S_, nsol::TAggregation::TOTAL )    \
  << "\tmin: "                                                          \
  << miniColumn->stats( )->getStat( _S_, nsol::TAggregation::MIN )      \
  << "\tmax: "                                                          \
  << miniColumn->stats( )->getStat( _S_, nsol::TAggregation::MAX )      \
    << "\tmean: "                                                       \
  << miniColumn->stats( )->getStat( _S_, nsol::TAggregation::MEAN )     \
  << "\tvariance: "                                                     \
  << miniColumn->stats( )->getStat( _S_, nsol::TAggregation::VARIANCE ) \
  << "\tstd dev.: "                                                     \
  << miniColumn->stats( )->getStat( _S_, nsol::TAggregation::STD_DEV )  \
  << std::endl;                                                         \


void printMiniColumnStats( nsol::MiniColumnPtr miniColumn )
{

  NSOL_DEBUG_CHECK( miniColumn , "miniColumn is null" );
  NSOL_DEBUG_CHECK( miniColumn->stats( ) , "no stats" );

  COMPUTE_AND_PRINT( "\tDendritic surface:\t",
                     nsol::MiniColumnStats::DENDRITIC_SURFACE );
  COMPUTE_AND_PRINT( "\tAxon surface:\t\t",
                     nsol::MiniColumnStats::AXON_SURFACE );
  COMPUTE_AND_PRINT( "\tNeuritic surface:\t",
                     nsol::MiniColumnStats::NEURITIC_SURFACE );
  COMPUTE_AND_PRINT( "\tSoma surface:\t\t",
                     nsol::MiniColumnStats::SOMA_SURFACE );
  COMPUTE_AND_PRINT( "\tMiniColumn surface:\t",
                     nsol::MiniColumnStats::SURFACE );

  std::cout << std::endl;

  COMPUTE_AND_PRINT( "\tDendritic volume:\t",
                     nsol::MiniColumnStats::DENDRITIC_SURFACE );
  COMPUTE_AND_PRINT( "\tAxon volume:\t\t",
                     nsol::MiniColumnStats::AXON_VOLUME );
  COMPUTE_AND_PRINT( "\tNeuritic volume:\t",
                     nsol::MiniColumnStats::NEURITIC_VOLUME );
  COMPUTE_AND_PRINT( "\tSoma volume:\t\t",
                     nsol::MiniColumnStats::SOMA_VOLUME );
  COMPUTE_AND_PRINT( "\tMiniColumn volume:\t",
                     nsol::MiniColumnStats::VOLUME );

  std::cout << std::endl;

  COMPUTE_AND_PRINT( "\tDendritic length:\t",
                     nsol::MiniColumnStats::DENDRITIC_LENGTH );
  COMPUTE_AND_PRINT( "\tAxon length:\t\t",
                     nsol::MiniColumnStats::AXON_LENGTH );
  COMPUTE_AND_PRINT( "\tNeuritic length:\t",
                     nsol::MiniColumnStats::NEURITIC_LENGTH );

  std::cout << std::endl;

  COMPUTE_AND_PRINT( "\tDendritic bifurcations:\t",
                     nsol::MiniColumnStats::DENDRITIC_BIFURCATIONS );
  COMPUTE_AND_PRINT( "\tAxon bifurcations:\t",
                     nsol::MiniColumnStats::AXON_BIFURCATIONS );
  COMPUTE_AND_PRINT( "\tNeuritic bifurcations:\t",
                     nsol::MiniColumnStats::NEURITIC_BIFURCATIONS );

  std::cout << std::endl;

}

#endif // NSOL_USE_BBPSDK
