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


void ComputeAndPrintSurface( nsol::NeuronPtr n )
{

  unsigned int i = 0;

  for ( auto it = n->morphology( )->neurites( ).begin( );
        it != n->morphology( )->neurites( ).end( ); it++ )
  {
    std::cout << "\tDendrite " << i++ << " type: "
              <<  ( * it )->neuriteType( ) << " ";

    if ( ( * it )->neuriteType( ) == nsol::Neurite::DENDRITE )
      std::cout << NSOL_DYNAMIC_CAST( nsol::Dendrite, ( * it ))
        ->dendriteType( );

    std::cout << " surface: ";

    if ( ( * it )->stats( ))
    {
      // nsol::Cached<> * cached =
      //   NSOL_DYNAMIC_CAST( nsol::Cached<>, ( * it )->stats( ));

      // if ( cached )
      //   std::cout << ( !cached->dirty( nsol::NeuriteCachedStats::SURFACE )
      //                  ? "Clean" : "Dirty" );

      std::cout << " " << ( * it )->stats( )->getStat(
        nsol::NeuriteStats::SURFACE ) << " ";

      // if ( cached )
      //   std::cout << ( !cached->dirty( nsol::NeuriteCachedStats::SURFACE )
      //                  ? "Clean" : "Dirty" );

      // std::cout << ", " << ( * it )->stats( )->surface( ) << " ";

      // if ( cached )
      //   std::cout  <<
      //     ( ! cached->dirty( nsol::NeuriteCachedStats::SURFACE )
      //       ? "Clean" : "Dirty" );

      nsol::Sections sections = ( * it )->sections( );
      std::cout << "[ ";
      for ( auto sectionsIt = sections.begin( );
            sectionsIt != sections.end( ); sectionsIt++ )
      {
        // cached =
        //   NSOL_DYNAMIC_CAST( nsol::Cached<>, ( * sectionsIt )->stats( ));

        // if ( cached )
        //   std::cout  <<
        //     ( ! cached->dirty( nsol::SectionCachedStats::SURFACE )
        //       ? "Clean, " : "Dirty, " );

//        std::cout << ( * sectionsIt )->stats( )->surface( ) << " ";
        std::cout << ( * sectionsIt )->stats( )->getStat(
	  nsol::SectionStats::/*TSectionStat::*/SURFACE ) << " ";
      }
//      delete sections;

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

  NSOL_CONST_FOREACH( it, n->morphology( )->neurites( ))
  {
    std::cout << "\tDendrite " << i++ << " type: "
              <<  ( * it )->neuriteType( ) << " ";

    if ( ( * it )->neuriteType( ) == nsol::Neurite::DENDRITE )
      std::cout << NSOL_DYNAMIC_CAST( nsol::Dendrite, ( * it ))
        ->dendriteType( );

    std::cout << " surface: ";

    if ( ( * it )->stats( ))
    {
      nsol::Cached<> * cached =
        NSOL_DYNAMIC_CAST( nsol::Cached<>, ( * it )->stats( ));

      if ( cached )
        std::cout << ( !cached->dirty( nsol::NeuriteCachedStats::SURFACE )
                       ? "C" : "D" );

      nsol::Sections sections = ( * it )->sections( );
      std::cout << " [ ";
      for ( auto sectionsIt = sections.begin( );
            sectionsIt != sections.end( ); sectionsIt++ )
      {
        cached =
          NSOL_DYNAMIC_CAST( nsol::Cached<>, ( * sectionsIt )->stats( ));

        if ( cached )
          std::cout  <<
            ( ! cached->dirty( nsol::SectionCachedStats::SURFACE )
              ? "C " : "D " );
      }
//      delete sections;

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

  // ComputeAndPrintSurface( neuron );
  // std::cout << std::endl;

  // ComputeAndPrintSurface( neuronWithStats );
  // std::cout << std::endl;

  PrintCachedSurfaceState( neuronWithCachedStats );
  std::cout << std::endl;

  ComputeAndPrintSurface( neuronWithCachedStats );
  std::cout << std::endl;

  PrintCachedSurfaceState( neuronWithCachedStats );
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

  PrintCachedSurfaceState( neuronWithCachedStats );
  std::cout << std::endl;

  ComputeAndPrintSurface( neuronWithCachedStats );
  std::cout << std::endl;

  PrintCachedSurfaceState( neuronWithCachedStats );
  std::cout << std::endl;

  return 0;


}
