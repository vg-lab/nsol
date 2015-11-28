/*
 * Example to show how to use stats and cached stats
 */

#include <nsol/nsol.h>
#include <stack>


int main ( int argc, char ** argv )
{


  // nsol::NeuritePtr n1 = new nsol::Axon;
  // nsol::NeuritePtr n2 = new nsol::AxonStats;

  // std::cout << n1->neuriteType( ) << " " << n1->stats( ) << std::endl;
  // std::cout << n2->neuriteType( ) << " " << n2->stats( )->surface( ) << std::endl;

  // return 0;


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

  // Will get the base class to force cache operations
  nsol::SectionCachedStats * sectionCached =
    dynamic_cast< nsol::SectionCachedStats * >
    ( sectionWithCachedStats->stats( ));
  NSOL_CHECK_THROW( sectionCached, "non cached section" );


#define PRINT_SURFACE_DIRTY_STATE( section )                    \
  (( section->dirty(nsol::SectionCachedStats::RADIUS) ) ?      \
   "Dirty" : "Clean" )


  std::cout << std::endl;

  std::cout << "Accumulated radius of the first section of the first neurite "
            << std::endl;

  std::cout << "\tNon cached section: "
            << sectionWithStats->stats( )->getStat(
           nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
           nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
           nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << std::endl;

  // Next code shows how to force dirty on a specific cached value
  sectionCached->setDirty( nsol::SectionCachedStats::RADIUS );

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
                 nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << std::endl;

  // Next code shows how to force dirty on all cached values
  sectionCached->setAndPropagateDirty( );

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << std::endl;

  // Now lets pretend to change something on a segment an see if it propagates
  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << std::endl;

  // Now changind the radius of a node should dirty segment and section
  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/RADIUS ) << std::endl;

  std::cout << std::endl;


  int j = 0;
  NSOL_FOREACH( neurite, neuronWithCachedStats->morphology( )->neurites( ))
  {
    std::cout << "Neurite " << j << std::endl;

    std::stack< nsol::SectionPtr > sSP;

    nsol::SectionPtr section = (*neurite)->firstSection( );

    sSP.push( section );

    int k = 0;
    while( !sSP.empty( ))
    {
      section = sSP.top( );
      sSP.pop( );

      std::cout << "  Section " << k << std::endl;
      std::cout << "    Radius " << section->stats( )->getStat(
          nsol::SectionStats::RADIUS, nsol::TAggregation::MEAN ) << std::endl;
      std::cout << "    Volume " << section->stats( )->getStat(
                nsol::SectionStats::VOLUME ) << std::endl;
      std::cout << "    Surface " << section->stats( )->getStat(
                nsol::SectionStats::SURFACE ) << std::endl;
      std::cout << "    Length " << section->stats( )->getStat(
                nsol::SectionStats::LENGTH ) << std::endl;

      if ( section->children( ).size( ) > 0 )
      {
        NSOL_FOREACH( sec, section->children( ))
        {
          sSP.push( *sec );
        }
      }
      k ++;
    }

    j ++;
  }

  return 0;

}