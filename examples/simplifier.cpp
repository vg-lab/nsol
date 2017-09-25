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

using namespace nsol;

void printMorpho( NeuronMorphologyPtr morpho )
{
  for ( auto neurite: morpho->neurites( ))
  {
    std::cout << "****Neurite****" << std::endl;
    for ( auto section: neurite->sections( ))
    {
      std::cout << "Section********" << std::endl;
      for ( auto node: section->nodes( ))
      {
        std::cout << "Node: " << node->id( ) << std::endl;
        std::cout << "      " <<  node->point( ) << std::endl;
      }
    }
  }
}

int main( int argc, char* argv[ ])
{
  if( argc < 2 )
  {
    std::cerr << "Error: swc/hdf5 file parameters needed" << std::endl;
    return -1;
  }

  NeuronMorphologyPtr morpho;

#ifdef NSOL_USE_BRION
  BrionReader r;
  morpho = r.loadMorphology( std::string( argv[1]) );
#else
  SwcReader r;
  morpho = r.readMorphology( std::string(argv[1]) );
#endif

  printMorpho( morpho );

  std::cout << "Simplificada" << std::endl;

  morpho = Simplifier::Instance( )->simplify( morpho, Simplifier::DIST_NODES, 5, true );

  printMorpho( morpho );
}
