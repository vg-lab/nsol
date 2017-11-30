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

#include <nsol/nsol.h>

// std.
#include <assert.h>
#include <iostream>

using namespace nsol;
using namespace std;

int main(int argc, char *argv[])
{
  if ( argc < 2 )
  {
    std::cerr << "Usage: bin/nsolEspINAXMLReader espina_xml_file" << std::endl;
    return -1;
  }

  EspINAXMLReader reader;

  std::string espinaXMLFile( argv[1] );

  cout << "Reading file: " << espinaXMLFile << endl;

  NeuronPtr neuron = reader.readNeuron( espinaXMLFile );

  if( !neuron )
  {
    std::cerr << "Unable to create a neuron from the XML." << std::endl;
    return -1;
  }

  NeuronMorphologyPtr neuronMorphology =
    neuron->morphology( );

  if( !neuronMorphology )
  {
    std::cerr << "Unable to create a morphology for the neuron." << std::endl;
    return -1;
  }

  //! Currently, EspINA skeletons are n-ary trees.
  //! This could change in the future (graphs).
  Neurites neurites = neuronMorphology->neurites();

  //! Currently, an EspINA skeleton represents a single neurite.
  int j = 0;
  NSOL_FOREACH( neurite, neurites )
  {
    cout << "Neurite " << j++ << endl;

    int numSections = 0;
    int numNodes = 1;
    std::stack< SectionPtr > sectionStack;
    sectionStack.push( (*neurite)->firstSection( ) );

    while( ! sectionStack.empty( ) )
    {
      NeuronMorphologySectionPtr section =
        dynamic_cast< NeuronMorphologySectionPtr >( sectionStack.top( ) );
      sectionStack.pop( );
      numSections ++;

      if( section->firstNode( ) )
        numNodes += ( unsigned int ) section->nodes( ).size( ) - 1;

      cout << "  Section. Number of nodes: "
           << section->nodes( ).size( ) << endl;
      cout << "    First node: " << section->firstNode( )->id( )
           << " End node: " << section->lastNode( )->id( ) << endl;

      if( section->children( ).size( ) > 0 )
        NSOL_FOREACH( sec, section->children( ) )
        {
    	  NeuronMorphologySectionPtr childSection =
    	    dynamic_cast< NeuronMorphologySectionPtr >( *sec );
          if( section->lastNode( )->id( ) != childSection->firstNode( )->id( ) )
            cout << "Inconsistency between nodes "
				 << section->lastNode( )->id( ) << " and "
				 << childSection->firstNode( )->id( ) << endl;
          sectionStack.push( *sec );
        }
    }
    cout << "Number of sections " << numSections << endl;
    cout << "Number of nodes " << numNodes << endl;
  }

  //! Cleaning NeuronPtr.
  delete neuron;
}
