/*
 * Example to show how to use stats
 */

#include <nsol/nsol.h>


typedef nsol::SwcReaderTemplated< nsol::Node,
                                  nsol::SegmentStats,
                                  nsol::SectionCachedStats,
                                  nsol::NeuronMorphology,
                                  nsol::Neuron >
  SwcReaderCachedStats;

int main ( int argc, char ** argv )
{

  std::cout << std::endl;

  if ( argc < 2 )
  {
    std::cerr << "Error. Usage: " << argv[0]
              << " swc_input_file" << std::endl;
    return -1;
  }

  std::cout << "Reading neuron without stats" << std::endl;
  nsol::SwcReader readerWithoutStats;
  nsol::NeuronPtr neuron = readerWithoutStats.readNeuron( argv[1] );

  std::cout << "Reading neuron with stats" << std::endl;
  nsol::SwcReaderStats readerWithStats;
  nsol::NeuronPtr neuronWithStats = readerWithStats.readNeuron( argv[1] );

  std::cout << "Reading neuron with cached stats" << std::endl;
  SwcReaderCachedStats readerWithCachedStats;
  nsol::NeuronPtr neuronWithCachedStats =
    readerWithCachedStats.readNeuron( argv[1] );

  if ( ! neuron || ! neuronWithStats || ! neuronWithCachedStats )
  {
    std::cerr << "Could not read neurons" << std::endl;
    return -1;
  }

  nsol::SectionPtr section =
    neuron->morphology( )->neurites( )[0]->firstSection( );

  nsol::SectionPtr sectionWithStats =
    neuronWithStats->morphology( )->neurites()[0]->firstSection( );

  nsol::SectionPtr sectionWithCachedStats =
    neuronWithCachedStats->morphology( )->neurites()[0]->firstSection( );


  if ( ! section || ! sectionWithStats || ! sectionWithCachedStats )
  {
    std::cerr << "Could not get sections of first neurite" << std::endl;
    return -1;
  }

  std::cout << std::endl;


  // Section without stats should return nullptr when asking for its stats
  NSOL_CHECK_THROW ( section->stats( ) == nullptr, "stats not null" );

  // Section without stats should return SectionStats pointer
  NSOL_CHECK_THROW ( sectionWithStats->stats( ) != nullptr, "stats null" );


  std::cout << std::endl;

  std::cout << "Surface of the first section of the first neurite "
            << std::endl;

  std::cout << "\tNon cached section: "
            << sectionWithStats->stats( )->surface( ) << std::endl;

  std::cout << "\tCached section dirty: "
            << sectionWithCachedStats->stats( )->surface( ) << std::endl;

  std::cout << "\tCached section clean: "
            << sectionWithCachedStats->stats( )->surface( ) << std::endl;

  // Next code shows how to force dirty on a specific cached value

  nsol::SectionCachedStats * sectionCached =
    dynamic_cast< nsol::SectionCachedStats * >
    ( sectionWithCachedStats->stats( ));
  NSOL_CHECK_THROW( sectionCached, "non cached section" );

  sectionCached->setDirty( nsol::SectionCachedStats::SURFACE );

  std::cout << "\tCached section dirty: "
            << sectionWithCachedStats->stats( )->surface( ) << std::endl;

  std::cout << "\tCached section clean: "
            << sectionWithCachedStats->stats( )->surface( ) << std::endl;


  // Next code shows how to force dirty on all cached values
  sectionCached->setDirty( );

  std::cout << "\tCached section dirty: "
            << sectionWithCachedStats->stats( )->surface( ) << std::endl;

  std::cout << "\tCached section clean: "
            << sectionWithCachedStats->stats( )->surface( ) << std::endl;

  std::cout << std::endl;


  return 0;

}
