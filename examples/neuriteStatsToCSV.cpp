/**
 * @file    neuriteStatsToCSV.h
 * @brief
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include <nsol/nsol.h>

#include <stdio.h>

void ComputeAndPrint( nsol::NeuronPtr n,
                      const char* fileName,
                      const char* neuronId )
{
  /*
  std::string neuronType = "";
  if (n->morphologicalType() == nsol::Neuron::TMorphologicalType::INTERNEURON)
  {
    neuronType = "interneurona";
  } else if (n->morphologicalType() ==
             nsol::Neuron::TMorphologicalType::PYRAMIDAL)
  {
    neuronType = "piramidal";
  } else {
    neuronType = "sintipo";
  }*/

  FILE* fp;

  fp = fopen(fileName, "w+");

  std::stringstream first_line_stream;
  first_line_stream << neuronId << ";"
                    << "longitud;grosor;volumen;num_bifurcaciones\n";

  std::string first_line_string =
      first_line_stream.str();

  const char* first_line =
      first_line_string.c_str();

  fputs(first_line, fp);

  unsigned int i = 1;

  for ( auto it = n->morphology( )->neurites( ).begin( );
        it != n->morphology( )->neurites( ).end( ); it++ )
  {

    std::cout << "\tDendrite " << i << " type: "
              <<  ( * it )->neuriteType( ) << " ";

    if ( ( * it )->neuriteType( ) == nsol::Neurite::DENDRITE )
      std::cout << NSOL_DYNAMIC_CAST( nsol::Dendrite, ( * it ))
        ->dendriteType( );

    if ( ( * it )->stats( ))
    {

      std::cout << " length: ";
      std::cout << " " << ( * it )->stats( )->getStat(
        nsol::NeuriteStats::LENGTH ) << " ";

      std::cout << " surface: ";
      std::cout << " " << ( * it )->stats( )->getStat(
        nsol::NeuriteStats::SURFACE ) << " ";

      std::cout << " volume: ";
      std::cout << " " << ( * it )->stats( )->getStat(
      nsol::NeuriteStats::VOLUME ) << " ";

      std::cout << " number of bifurcations: ";
      std::cout << " " << ( * it )->stats( )->getStat(
      nsol::NeuriteStats::BIFURCATIONS ) << " ";

      std::stringstream current_line_stream;
      current_line_stream
        << "dendrita_" << i << ";"
        << ( * it )->stats( )->getStat(nsol::NeuriteStats::LENGTH ) << ";"
        << ( * it )->stats( )->getStat(nsol::NeuriteStats::SURFACE ) << ";"
        << ( * it )->stats( )->getStat(nsol::NeuriteStats::VOLUME ) << ";"
        << ( * it )->stats( )->getStat(nsol::NeuriteStats::BIFURCATIONS )
        << "\n";

      std::string current_line_string =
          current_line_stream.str();

      const char* current_line =
          current_line_string.c_str();

      fputs(current_line, fp);

      /*
       * Volume per section.
       */

//      nsol::Sections sections = ( * it )->sections( );
//      std::cout << "[ ";
//      for ( auto sectionsIt = sections.begin( );
//            sectionsIt != sections.end( ); sectionsIt++ )
//      {
//        //Change this line
//        std::cout << ( * sectionsIt )->stats( )->getStat(
//            nsol::SectionStats::/*TSectionStat::*/VOLUME ) << " ";
//      }
//      std::cout << "]";

    } /* if_stats */
    else
      std::cout << "No stats available";
    std::cout << std::endl;
    i++;
  }/* for_neurites */

  fclose(fp);

}

void PrintCachedState( nsol::NeuronPtr n )
{

  unsigned int i = 0;

  NSOL_CONST_FOREACH( it, n->morphology( )->neurites( ))
  {
    std::cout << "\tDendrite " << i++ << " type: "
              <<  ( * it )->neuriteType( ) << " ";

    if ( ( * it )->neuriteType( ) == nsol::Neurite::DENDRITE )
      std::cout << NSOL_DYNAMIC_CAST( nsol::Dendrite, ( * it ))
        ->dendriteType( );



    if ( ( * it )->stats( ))
    {
      nsol::Cached<> * cached =
        NSOL_DYNAMIC_CAST( nsol::Cached<>, ( * it )->stats( ));

      if ( cached )

        std::cout << " length: ";
        std::cout << ( !cached->dirty( nsol::NeuriteCachedStats::LENGTH )
                       ? "C" : "D" );

        std::cout << " surface: ";
        std::cout << ( !cached->dirty( nsol::NeuriteCachedStats::SURFACE )
                       ? "C" : "D" );

        std::cout << " volume: ";
        std::cout << ( !cached->dirty( nsol::NeuriteCachedStats::VOLUME )
                       ? "C" : "D" );

        std::cout << " number of bifurcations: ";
        std::cout << ( !cached->dirty( nsol::NeuriteCachedStats::BIFURCATIONS )
                       ? "C" : "D" );

//      nsol::Sections sections = ( * it )->sections( );
//      std::cout << " [ ";
//      for ( auto sectionsIt = sections.begin( );
//            sectionsIt != sections.end( ); sectionsIt++ )
//      {
//        cached =
//          NSOL_DYNAMIC_CAST( nsol::Cached<>, ( * sectionsIt )->stats( ));
//
//        if ( cached )
//          std::cout  <<
//            ( ! cached->dirty( nsol::SectionCachedStats::VOLUME )
//              ? "C " : "D " );
//      }
//      std::cout << "]";

    } /* if_stats */
    else
      std::cout << "No stats available";

    std::cout << std::endl;
  }

}

int main ( int argc, char ** argv )
{
  std::cout << std::endl;

  if ( argc < 4 )
  {
    std::cerr << "Error. Usage: " << argv[0]
              << " swc_input_file csv_output_file neuron_external_id"
              << std::endl;
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

  PrintCachedState( neuronWithCachedStats );
  std::cout << std::endl;

  ComputeAndPrint( neuronWithCachedStats, argv[2], argv[3]);
  std::cout << std::endl;

  PrintCachedState( neuronWithCachedStats );
  std::cout << std::endl;

  {
    nsol::SectionPtr sectionWithCachedStats =
      neuronWithCachedStats->morphology( )->neurites()[0]->firstSection( );

    NSOL_CHECK_THROW( sectionWithCachedStats, "No stats available" );
  }
  {
    nsol::SectionPtr sectionWithCachedStats =
      neuronWithCachedStats->morphology( )->neurites()[1]->firstSection( );
    NSOL_CHECK_THROW( sectionWithCachedStats, "No stats available" );
  }

  /*
  PrintCachedState( neuronWithCachedStats );
  std::cout << std::endl;

  ComputeAndPrint( neuronWithCachedStats );
  std::cout << std::endl;

  PrintCachedState( neuronWithCachedStats );
  std::cout << std::endl;
  */

  return 0;

}
