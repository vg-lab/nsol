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

#include <assert.h>

#include <iostream>

#include <stack>

using namespace nsol;
using namespace std;

int main(int argc, char *argv[])
{

  AscReader r;
  SwcWriter w;

  if ( argc < 2 )
  {
    std::cerr << "Error: asc file parameter needed." << std::endl;
    return -1;
  }

  cout << "Reading file " << argv[1] << endl;
  string filename;

  cout << "Filename SWC to export: ";
  cin >> filename;

  NeuronMorphologyPtr n = r.readMorphology(argv[1]);

  if (!n)
    return -1;

  w.writeMorphology(filename, n);

  Neurites neurites = n->neurites();

  int j = 0;
  NSOL_FOREACH( neurite, neurites )
  {
    std::cout << "  Neurite " << j << endl;;
    j++;

    int numSections = 0;
    int numNodes = 1;
    std::stack< SectionPtr > sPS;
    sPS.push( (*neurite)->firstSection( ));


    while( ! sPS.empty( ))
    {
      NeuronMorphologySectionPtr section =
          dynamic_cast< NeuronMorphologySectionPtr >( sPS.top( ));
      sPS.pop( );
      numSections ++;

      if ( section->firstNode( ))
        numNodes += ( unsigned int ) section->nodes( ).size(  ) - 1;

      cout << "    Section-> number of nodes: "
           << section->nodes( ).size( ) << endl;
      cout << "      First Node: " << section->firstNode( )->id( )
           << " End Node: " << section->lastNode( )->id( ) << endl;

      if (section->children( ).size( ) > 0 )
        NSOL_FOREACH( sec, section->children( ))
      {
        if( section->lastNode( ) !=
            dynamic_cast< NeuronMorphologySectionPtr >( *sec )->firstNode( ))
          cout << "Incoherent node connections found" << endl;
        sPS.push( *sec );
      }
    }
    cout << " Number of sections " << numSections;
    cout << " number of nodes " << numNodes << endl;
  }


  delete n;
}
