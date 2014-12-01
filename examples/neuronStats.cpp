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

  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::DENDRITIC_VOLUME );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::AXON_VOLUME );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::NEURITIC_VOLUME );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::SOMA_VOLUME );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::VOLUME );

  // Surface
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::DENDRITIC_SURFACE );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::AXON_SURFACE );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::NEURITIC_SURFACE );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::SOMA_SURFACE );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::SURFACE );

  // Length
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::DENDRITIC_LENGTH );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::AXON_LENGTH );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::NEURITIC_LENGTH
    );
  // Bifurcations
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::AXON_BIFURCATIONS );
  morphology->stats( )->getStat(
    nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS );


  // morphology->stats( )->dendriticSurface( );
  // morphology->stats( )->axonSurface( );
  // morphology->stats( )->neuriticSurface( );
  // morphology->stats( )->surface( );
  // morphology->stats( )->dendriticVolume( );
  // morphology->stats( )->axonVolume( );
  // morphology->stats( )->neuriticVolume( );
  // morphology->stats( )->volume( );
  // morphology->stats( )->dendriticLength( );
  // morphology->stats( )->axonLength( );
  // morphology->stats( )->neuriticLength( );
  // morphology->stats( )->dendriticBifurcations( );
  // morphology->stats( )->axonBifurcations( );
  // morphology->stats( )->neuriticBifurcations( );
}

void printNeuronMorphologyStats( nsol::NeuronMorphologyPtr morphology )
{

  NSOL_DEBUG_CHECK( morphology , "morphology is null" );
  NSOL_DEBUG_CHECK( morphology->stats( ) , "no stats" );

  #define NMS morphology->stats( )

  std::cout << "\tDendritic surface:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_SURFACE )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_SURFACE,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_SURFACE,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_SURFACE,
                             nsol::TAggregation::STD_DEV ) << " "
            << std::endl;

  std::cout << "\tAxon surface:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_SURFACE )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_SURFACE,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_SURFACE,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_SURFACE,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << "\tNeuritic surface:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_SURFACE )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_SURFACE,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_SURFACE,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_SURFACE,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << "\tSurface:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::SURFACE )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::SURFACE,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::SURFACE,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::SURFACE,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic volume:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_VOLUME )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_VOLUME,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_VOLUME,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_VOLUME,
                             nsol::TAggregation::STD_DEV ) << " "
            << std::endl;

  std::cout << "\tAxon volume:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_VOLUME )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_VOLUME,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_VOLUME,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_VOLUME,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << "\tNeuritic volume:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_VOLUME )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_VOLUME,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_VOLUME,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_VOLUME,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << "\tVolume:\t\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::VOLUME )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::VOLUME,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::VOLUME,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::VOLUME,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic length:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_LENGTH )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_LENGTH,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_LENGTH,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::DENDRITIC_LENGTH,
                             nsol::TAggregation::STD_DEV ) << " "
            << std::endl;

  std::cout << "\tAxon length:\t\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_LENGTH )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_LENGTH,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_LENGTH,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_LENGTH,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << "\tNeuritic length:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_LENGTH )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_LENGTH,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_LENGTH,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_LENGTH,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << std::endl;

  std::cout << "\tDendritic bifurcations:\t"
            << NMS->getStat(
              nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS )
            << " "
            << NMS->getStat(
              nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS,
              nsol::TAggregation::MEAN ) << " "
            << NMS->getStat(
              nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS,
              nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat(
              nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS,
              nsol::TAggregation::STD_DEV ) << " "
            << std::endl;

  std::cout << "\tAxon bifurcations:\t"
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_BIFURCATIONS )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_BIFURCATIONS,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_BIFURCATIONS,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::AXON_BIFURCATIONS,
                             nsol::TAggregation::STD_DEV ) << " "
             << std::endl;

  std::cout << "\tNeuritic bifurcations:\t"
            << NMS->getStat(
              nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS )
            << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS,
                             nsol::TAggregation::MEAN ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS,
                             nsol::TAggregation::VARIANCE ) << " "
            << NMS->getStat( nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS,
                             nsol::TAggregation::STD_DEV ) << " "
            << std::endl;

  std::cout << std::endl;

}
