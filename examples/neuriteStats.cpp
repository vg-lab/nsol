/*
 * Example to show how to use stats and cached stats for neurites
 */

#include <nsol/nsol.h>


void ComputeAndPrintSurface( nsol::NeuronPtr n )
{

  unsigned int i = 0;

  for ( const auto& neurite : n->morphology( )->neurites( ))
  {
    std::cout << "\tDendrite " << i++ << " type: "
              <<  neurite->neuriteType( ) << " ";

    if ( neurite->neuriteType( ) == nsol::Neurite::DENDRITE )
      std::cout << NSOL_DYNAMIC_CAST( nsol::Dendrite, neurite )->dendriteType( );

    std::cout << " surface: ";

    if ( neurite->stats( ))
    {
      std::cout << " " << neurite->stats( )->getStat(
        nsol::NeuriteStats::SURFACE ) << " ";

      const nsol::Sections& sections = neurite->sections( );
      std::cout << "[ ";
      for ( const auto& section : sections )
      {
        std::cout << section->stats( )->getStat(
          nsol::SectionStats::/*TSectionStat::*/SURFACE ) << " ";
      }

      std::cout << "]";
    }
    else
      std::cout << "No stats available";

    std::cout << std::endl;
  }

}


void PrintCachedSurfaceState( nsol::NeuronPtr n )
{

  unsigned int i = 0;

  for ( const auto& neurite : n->morphology( )->neurites( ))
  {
    std::cout << "\tDendrite " << i++ << " type: "
              <<  neurite->neuriteType( ) << " ";

    if ( neurite->neuriteType( ) == nsol::Neurite::DENDRITE )
      std::cout << NSOL_DYNAMIC_CAST( nsol::Dendrite, ( neurite ))
        ->dendriteType( );

    std::cout << " surface: ";

    if ( neurite->stats( ))
    {
      nsol::Cached<> * cached =
        NSOL_DYNAMIC_CAST( nsol::Cached<>, neurite->stats( ));

      if ( cached )
        std::cout << ( !cached->dirty( nsol::NeuriteCachedStats::SURFACE )
                       ? "C" : "D" );

      nsol::Sections sections = neurite->sections( );
      std::cout << " [ ";
      for ( const auto& section : sections )
      {
        cached =
          NSOL_DYNAMIC_CAST( nsol::Cached<>, section->stats( ));

        if ( cached )
          std::cout  <<
            ( ! cached->dirty( nsol::SectionCachedStats::SURFACE )
              ? "C " : "D " );
      }
      std::cout << "]";
    }
    else
      std::cout << "No stats available";

    std::cout << std::endl;
  }

}



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
  nsol::SwcReaderCachedStats readerWithCachedStats;
  nsol::NeuronPtr neuronWithCachedStats =
    readerWithCachedStats.readNeuron( argv[1] );

  if ( ! neuron || ! neuronWithStats || ! neuronWithCachedStats )
  {
    std::cerr << "Could not read neurons" << std::endl;
    return -1;
  }

  std::cout << std::endl;

  std::cout << "Compute and print neuron stats when not available" << std::endl;
  ComputeAndPrintSurface( neuron );
  std::cout << std::endl;

  std::cout << "Compute and print neuron stats when not cacheable" << std::endl;
  ComputeAndPrintSurface( neuronWithStats );
  std::cout << std::endl;

  std::cout << "Print cached stats" << std::endl;
  PrintCachedSurfaceState( neuronWithCachedStats );
  std::cout << std::endl;

  std::cout << "Compute and print cacheable stats" << std::endl;
  ComputeAndPrintSurface( neuronWithCachedStats );
  std::cout << std::endl;

  std::cout << "Print cached stats" << std::endl;
  PrintCachedSurfaceState( neuronWithCachedStats );
  std::cout << std::endl;

  PrintCachedSurfaceState( neuronWithCachedStats );
  std::cout << std::endl;

  ComputeAndPrintSurface( neuronWithCachedStats );
  std::cout << std::endl;

  PrintCachedSurfaceState( neuronWithCachedStats );
  std::cout << std::endl;

  return 0;


}
