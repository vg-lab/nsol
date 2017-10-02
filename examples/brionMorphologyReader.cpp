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

#include <nsol/nsol.h>
#include <iostream>

int main( int argc, char* argv[ ] )
{
  nsol::BrionReader r;

  if( argc < 2 )
  {
    std::cerr << "Error: morphology input file parameter needed" << std::endl;
    return -1;
  }

  std::cout << "Reading file " << argv[1] << std::endl;

  nsol::NeuronPtr neuron = r.loadNeuron( std::string( argv[1] ), 1 );

  if( !neuron->morphology( ))
  {
    std::cerr << "Error: morphology not loaded " << std::endl;
    return -1;
  }

  std::cout << "Soma center: " << neuron->morphology( )->soma( )->center( )
            << std::endl;
  std::cout << "Soma nodes: " << neuron->morphology( )->soma( )->
    nodes( ).size( ) << std::endl;
  std::cout << "Soma max radius: " << neuron->morphology( )->soma( )->
    maxRadius( ) << std::endl;

  std::cout << "Num neurites: " << neuron->morphology( )->neurites( ).size( )
            << std::endl;

  unsigned int neuriteId = 0;
  for( const auto& neurite: neuron->morphology( )->neurites( ))
  {
    std::cout << "\n**Neurite " << neuriteId << std::endl;
    neuriteId++;
    unsigned int sectionId = 0;
    for( const auto& section: neurite->sections( ))
    {
      std::cout << "\n****Section " << sectionId << std::endl;
      sectionId++;
      for ( auto node: section->nodes( ))
      {
        std::cout << "******Node " << node->id( ) << "Position: "
                  << node->point( ).x( ) << " " << node->point( ).y( )
                  << " " << node->point( ).z( ) << std::endl;
      }
    }
  }

  return 0;
}
