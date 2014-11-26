/*
 * Example to show how to use stats and cached stats
 */

#include <nsol/nsol.h>

void computeMiniColumnStats( nsol::MiniColumnPtr column );

void printMiniColumnStats( nsol::MiniColumnPtr column );



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
  std::map<unsigned int, nsol::ColumnPtr> columnsWithStats =
    readerWithStats.readExperiment( argv[1] );

  nsol::MiniColumnPtr miniColumnWithStats =
    columnsWithStats[0]->miniColumns( )[0];

  nsol::BBPSDKReaderCachedStats readerWithCachedStats;
  std::map<unsigned int, nsol::ColumnPtr> columnsWithCachedStats =
    readerWithCachedStats.readExperiment( argv[1] );

  nsol::MiniColumnPtr miniColumnWithCachedStats =
    columnsWithCachedStats[0]->miniColumns( )[0];

  NSOL_CHECK_THROW( miniColumnWithStats->stats( ), "no stats in column" );
  NSOL_CHECK_THROW( miniColumnWithCachedStats->stats( ),
                    "no stats in column" );

  std::cout << std::endl;

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

  miniColumn->stats( )->dendriticSurface( );
  miniColumn->stats( )->axonSurface( );
  miniColumn->stats( )->neuriticSurface( );
  miniColumn->stats( )->surface( );
  miniColumn->stats( )->dendriticVolume( );
  miniColumn->stats( )->axonVolume( );
  miniColumn->stats( )->neuriticVolume( );
  miniColumn->stats( )->volume( );
  miniColumn->stats( )->dendriticLength( );
  miniColumn->stats( )->axonLength( );
  miniColumn->stats( )->neuriticLength( );
  miniColumn->stats( )->dendriticBifurcations( );
  miniColumn->stats( )->axonBifurcations( );
  miniColumn->stats( )->neuriticBifurcations( );
}


#define COMPUTE_AND_PRINT( __MSG__, __METHOD__ )                        \
  std::cout << __MSG__                                                  \
  << miniColumn->stats( )->__METHOD__( nsol::TAggregation::TOTAL )      \
  << "\tmean: "                                                         \
  << miniColumn->stats( )->__METHOD__( nsol::TAggregation::MEAN )       \
  << "\tvariance: "                                                     \
  << miniColumn->stats( )->__METHOD__( nsol::TAggregation::VARIANCE )   \
  << "\tstd dev.: "                                                      \
  << miniColumn->stats( )->__METHOD__( nsol::TAggregation::STD_DEV )    \
  << std::endl;                                                         \


void printMiniColumnStats( nsol::MiniColumnPtr miniColumn )
{

  NSOL_DEBUG_CHECK( miniColumn , "miniColumn is null" );
  NSOL_DEBUG_CHECK( miniColumn->stats( ) , "no stats" );

  COMPUTE_AND_PRINT( "\tDendritic surface:\t", dendriticSurface );
  COMPUTE_AND_PRINT( "\tAxon surface:\t\t", axonSurface );
  COMPUTE_AND_PRINT( "\tNeuritic surface:\t", neuriticSurface );
  COMPUTE_AND_PRINT( "\tSoma surface:\t\t", somaSurface );
  COMPUTE_AND_PRINT( "\tMiniColumn surface:\t", surface );

  std::cout << std::endl;

  COMPUTE_AND_PRINT( "\tDendritic volume:\t", dendriticVolume );
  COMPUTE_AND_PRINT( "\tAxon volume:\t\t", axonVolume );
  COMPUTE_AND_PRINT( "\tNeuritic volume:\t", neuriticVolume );
  COMPUTE_AND_PRINT( "\tSoma volume:\t\t", somaVolume );
  COMPUTE_AND_PRINT( "\tMiniColumn volume:\t", volume );

  std::cout << std::endl;

  COMPUTE_AND_PRINT( "\tDendritic length:\t", dendriticLength );
  COMPUTE_AND_PRINT( "\tAxon length:\t\t", axonLength );
  COMPUTE_AND_PRINT( "\tNeuritic length:\t", neuriticLength );

  std::cout << std::endl;

  COMPUTE_AND_PRINT( "\tDendritic bifurcations:\t",dendriticBifurcations );
  COMPUTE_AND_PRINT( "\tAxon bifurcations:\t", axonBifurcations );
  COMPUTE_AND_PRINT( "\tNeuritic bifurcations:\t", neuriticBifurcations );

  std::cout << std::endl;

}
