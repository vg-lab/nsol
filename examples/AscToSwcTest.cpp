/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Iago Calvo Lista
 *          Fernando Lucas Pérez
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

#include <nsol/nsol.h>

#include <iostream>

#include <stack>

using namespace nsol;

enum
{
  ASC_READER_ERROR_INCORRECT_MORPHOLOGY = -1,
  ASC_READER_ERROR_INCORRECT_PARAMETERS = -2
};



int main(int argc, char *argv[])
{

  AscReader ascReader;
  SwcWriter swcWriter;
  std::string importFilename,exportFilename;

  if ( argc == 1 )
  {
    std::cout << "ASC filename to import: ";
    std::cin >> importFilename;
    std::cout << "SWC filename to export: ";
    std::cin >> exportFilename;
  }
  else if ( argc == 2 )
  {
    std::cout << "SWC filename to export: ";
    std::cin >> exportFilename;
    importFilename = argv[1];
  }
  else if ( argc == 3 )
  {
    importFilename = argv[1];
    exportFilename = argv[2];
  }
  else
  {
    std::cerr << "Incorrect use of nsolAscToSwcTest: [importFilename] [exportFilename]." << std::endl;
    return ASC_READER_ERROR_INCORRECT_PARAMETERS;
  }
  std::cout << "Reading from ASC file: " << importFilename << std::endl;

  NeuronMorphologyPtr neuronMorphology = ascReader.readMorphology( importFilename );

  if ( !neuronMorphology ) {
    std::cerr << "Error: neuronMorphology not recognised." << std::endl;
    return ASC_READER_ERROR_INCORRECT_MORPHOLOGY;
  }


  std::cout << "Exporting to SWC file: " << exportFilename << std::endl;

  swcWriter.writeMorphology( exportFilename, neuronMorphology );

  Neurites neurites = neuronMorphology->neurites( );

  int neuriteNumber = 0;
  for ( const auto& neurite : neurites )
  {
    std::cout << "  Neurite " << neuriteNumber << std::endl;;
    neuriteNumber++;

    int numSections = 0;
    int numNodes = 1;
    std::stack< SectionPtr > sectionStack;
    sectionStack.push( neurite->firstSection( ) );


    while( ! sectionStack.empty( ) )
    {
      NeuronMorphologySectionPtr section =
          dynamic_cast< NeuronMorphologySectionPtr >( sectionStack.top( ) );
      sectionStack.pop( );
      ++numSections;

      if ( section->firstNode( ) )
        numNodes += ( unsigned int ) section->nodes( ).size( ) - 1;

      std::cout << "    Section-> number of nodes: "
                << section->nodes( ).size( ) << std::endl;
      std::cout << "      First Node: " << section->firstNode( )->id( )
                << " End Node: " << section->lastNode( )->id( ) << std::endl;

      if ( !section->children( ).empty( ) )
        for( auto&  sec : section->children( ) )
        {
          if( section->lastNode( ) !=
              dynamic_cast< NeuronMorphologySectionPtr >
              ( sec )->firstNode( ) )
            std::cout << "Node Incoherence." << std::endl;
          sectionStack.push( sec );
        }
    }
    std::cout << " Number of sections " << numSections;
    std::cout << " number of nodes " << numNodes << std::endl;
  }


  delete neuronMorphology;
}
