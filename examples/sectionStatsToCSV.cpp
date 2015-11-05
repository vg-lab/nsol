/**
 * @file    sectionStatsToCSV.h
 * @brief
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
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

  if ( argc < 4 )
  {
    std::cerr << "Error. Usage: " << argv[0]
              << " swc_input_file csv_output_file"
              << " dendrite_external id" << std::endl;
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
  (( section->dirty(nsol::SectionCachedStats::SURFACE) ) ?      \
   "Dirty" : "Clean" )


  std::cout << std::endl;

  std::cout << "Surface of the first section of the first neurite "
            << std::endl;

  std::cout << "\tNon cached section: "
            << sectionWithStats->stats( )->getStat(
	         nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
	         nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
	         nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << std::endl;

  // Next code shows how to force dirty on a specific cached value
  sectionCached->setDirty( nsol::SectionCachedStats::SURFACE );

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
                 nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << std::endl;

  // Next code shows how to force dirty on all cached values
  sectionCached->setAndPropagateDirty( );

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << std::endl;

  // Now lets pretend to change something on a segment an see if it propagates
  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << std::endl;

  // Now changind the radius of a node should dirty segment and section
  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::SectionStats::/*TSectionStat::*/SURFACE ) << std::endl;

  std::cout << std::endl;


  int j = 0;
  NSOL_FOREACH( neurite, neuronWithCachedStats->morphology( )->neurites( ))
  {
    //Generating CSV only for one neurite.

    FILE* fp;

    fp = fopen(argv[2], "w+");

    const char* dendrite_external_id = argv[3];

    std::stringstream first_line_stream;
    first_line_stream
      << dendrite_external_id << ";"
      << "longitud;grosor;volumen;ramas_hijas\n";

    std::string first_line_string =
        first_line_stream.str();

    const char* first_line =
        first_line_string.c_str();

    fputs(first_line, fp);

    std::cout << "Neurite " << j << std::endl;

    std::map<nsol::SectionPtr, int> sectionPtrToId;

    int sectionTempId = 0;
    const nsol::Sections& sec = (*neurite)->sections();
    //Do not use name "section" for first parameter.
    NSOL_FOREACH( sect, sec )
    {
      sectionPtrToId.insert(
          std::pair<nsol::SectionPtr,int>
          ((*sect), sectionTempId) );
      sectionTempId++;
    }

    std::stack< nsol::SectionPtr > sSP;

    nsol::SectionPtr section = (*neurite)->firstSection( );

    sSP.push( section );

    int k = 0;
    while( !sSP.empty( ))
    {
      section = sSP.top( );
      sSP.pop( );

      std::cout << "  Section " << k << std::endl;
      std::cout << "    Surface " << section->stats( )->getStat(
          nsol::SectionStats::SURFACE ) << std::endl;
      std::cout << "    Volumne " << section->stats( )->getStat(
          nsol::SectionStats::VOLUME ) << std::endl;
      std::cout << "    Length " << section->stats( )->getStat(
          nsol::SectionStats::LENGTH ) << std::endl;

      std::stringstream current_line_stream;
      current_line_stream
        << sectionPtrToId[section] << ";"
        << section->stats( )->getStat( nsol::SectionStats::LENGTH ) << ";"
        << section->stats( )->getStat( nsol::SectionStats::SURFACE ) << ";"
        << section->stats( )->getStat( nsol::SectionStats::VOLUME ) << ";";

      if ( section->children( ).size( ) > 0 )
      {
        NSOL_FOREACH( sec, section->children( ))
        {
          sSP.push( *sec );
          current_line_stream << sectionPtrToId[(*sec)] << " ";
        }
      }

      current_line_stream << "\n";

      std::string current_line_string =
        current_line_stream.str();

      const char* current_line =
        current_line_string.c_str();

      fputs(current_line, fp);

      k ++;
    }

    fclose(fp);

    j ++;
  } /* for_neurites */

  return 0;

}
