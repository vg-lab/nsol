/*
 * Example to show how to use stats and cached stats
 */

#include <nsol/nsol.h>



void computeNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology );

void printNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology );


int main ( int argc, char ** argv )
{
  std::cout << std::endl;

  if ( argc < 2 )
  {
    std::cerr << "Error. Usage: " << argv[0]
              << " swc_input_file" << std::endl;
    return -1;
  }

  std::cout << "Reading neuron with stats" << std::endl;
  nsol::SwcReaderStats readerWithStats;
  nsol::NeuronPtr neuronWithStats = readerWithStats.readNeuron( argv[1] );

  std::cout << "Reading neuron with cached stats" << std::endl;
  nsol::SwcReaderCachedStats readerWithCachedStats;
  nsol::NeuronPtr neuronWithCachedStats =
    readerWithCachedStats.readNeuron( argv[1] );

  if ( ! neuronWithStats || ! neuronWithCachedStats )
  {
    std::cerr << "Could not read neurons" << std::endl;
    return -1;
  }

  std::cout << std::endl;

  std::cout << "Non-cached stats" << std::endl;
  printNeuronMorphologyStats( neuronWithStats->morphology( ));

  std::cout << "Cached stats" << std::endl;
  printNeuronMorphologyStats( neuronWithCachedStats->morphology( ));


  struct timeval startTime, endTime;
  long totalTime;

  gettimeofday(&startTime, NULL);
  for ( int i = 0; i < 1000; i++ )
    computeNeuronMorphologyStats( neuronWithStats->morphology( ));
  gettimeofday(&endTime, NULL);

  totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
  totalTime += (endTime.tv_usec - startTime.tv_usec);

  std::cout << "Compute non-cached stats 1000 times. Time elapsed: "
            << (totalTime/1000L) / 1000.0f << std::endl;

  gettimeofday(&startTime, NULL);
  for ( int i = 0; i < 1000; i++ )
    computeNeuronMorphologyStats( neuronWithCachedStats->morphology( ));
  gettimeofday(&endTime, NULL);

  totalTime =  (endTime.tv_sec - startTime.tv_sec) * 1000000L;
  totalTime += (endTime.tv_usec - startTime.tv_usec);

  std::cout << "Compute cached stats 1000 times. Time elapsed: "
            << (totalTime/1000L) / 1000.0f << std::endl;

  std::cout << std::endl;


  return 0;


}


void computeNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology )
{

  NSOL_DEBUG_CHECK( morphology , "morphology is null" );
  NSOL_DEBUG_CHECK( morphology->stats( ) , "no stats" );

  morphology->stats( )->dendriticSurface( );
  morphology->stats( )->axonSurface( );
  morphology->stats( )->neuriticSurface( );
  morphology->stats( )->surface( );
  morphology->stats( )->dendriticVolume( );
  morphology->stats( )->axonVolume( );
  morphology->stats( )->neuriticVolume( );
  morphology->stats( )->volume( );
  morphology->stats( )->dendriticLength( );
  morphology->stats( )->axonLength( );
  morphology->stats( )->neuriticLength( );
  morphology->stats( )->dendriticBifurcations( );
  morphology->stats( )->axonBifurcations( );
  morphology->stats( )->neuriticBifurcations( );
}

void printNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology )
{

  NSOL_DEBUG_CHECK( morphology , "morphology is null" );
  NSOL_DEBUG_CHECK( morphology->stats( ) , "no stats" );

  std::cout << "\tDendritic surface:\t"
            << morphology->stats( )->dendriticSurface( )
            << std::endl;

  std::cout << "\tAxon surface:\t\t"
            << morphology->stats( )->axonSurface( )
            << std::endl;

  std::cout << "\tNeuritic surface:\t"
            << morphology->stats( )->neuriticSurface( )
            << std::endl;

  std::cout << "\tNeuron surface:\t\t"
            << morphology->stats( )->surface( )
            << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic volume:\t"
            << morphology->stats( )->dendriticVolume( )
            << std::endl;

  std::cout << "\tAxon volume:\t\t"
            << morphology->stats( )->axonVolume( )
            << std::endl;

  std::cout << "\tNeuritic volume:\t"
            << morphology->stats( )->neuriticVolume( )
            << std::endl;

  std::cout << "\tNeuron volume:\t\t"
            << morphology->stats( )->volume( )
            << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic length:\t"
            << morphology->stats( )->dendriticLength( )
            << std::endl;

  std::cout << "\tAxon length:\t\t"
            << morphology->stats( )->axonLength( )
            << std::endl;

  std::cout << "\tNeuritic length:\t"
            << morphology->stats( )->neuriticLength( )
            << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic bifurcations:\t"
            << morphology->stats( )->dendriticBifurcations( )
            << std::endl;

  std::cout << "\tAxon bifurcations:\t"
            << morphology->stats( )->axonBifurcations( )
            << std::endl;

  std::cout << "\tNeuritic bifurcations:\t"
            << morphology->stats( )->neuriticBifurcations( )
            << std::endl;

  std::cout << std::endl;

}
