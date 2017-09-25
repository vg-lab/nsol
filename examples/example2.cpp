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
using namespace std;

int main ( void )
{

  ColumnPtr c ( new Column );
  c->id( ) = 0;

  std::cout << "Testing empty column" << std::endl;
  // assert( c->meanSomaVolume( ) == 0 );
  // assert( c->meanSomaSurface( ) == 0.0f );
  // assert( c->meanDendriteVolume( ) == 0.0f );
  // assert( c->meanDendriteSurface( ) == 0.0f );
  // assert( c->maxSomaVolume( ) == 0.0f );
  // assert( c->maxSomaSurface( ) == 0.0f );
  // assert( c->maxDendriteVolume( ) == 0.0f );
  // assert( c->maxDendriteSurface( ) == 0.0f );
  assert( c->numberOfNeurons() == 0 );
  assert( c->numberOfNeurons( false ) == 0 );
  assert( c->numberOfNeurons( true, Neuron::PYRAMIDAL ) == 0 );
  assert( c->numberOfNeurons( false, Neuron::PYRAMIDAL ) == 0 );
  assert( c->numberOfNeurons( true, Neuron::INTERNEURON ) == 0 );
  assert( c->numberOfNeurons( false, Neuron::INTERNEURON ) == 0 );


  std::cout << "Add mini column" << std::endl;
  MiniColumnPtr mc ( new MiniColumn ( c, 1 ));
  assert( mc->id( ) == 1 );
  assert( mc->column( )  == c );

  mc->id( ) = 0;
  assert( mc->id( ) == 0 );

  c->addMiniColumn( mc );

  assert( c->miniColumns( ).size( ) == 1);
  assert( c->miniColumns( ).size( ) == c->numberOfMiniColumns( ));

  // assert( c->meanSomaVolume( ) == 0 );
  // assert( c->meanSomaSurface( ) == 0.0f );
  // assert( c->meanDendriteVolume( ) == 0.0f );
  // assert( c->meanDendriteSurface( ) == 0.0f );
  // assert( c->maxSomaVolume( ) == 0.0f );
  // assert( c->maxSomaSurface( ) == 0.0f );
  // assert( c->maxDendriteVolume( ) == 0.0f );
  // assert( c->maxDendriteSurface( ) == 0.0f );
  assert( c->numberOfNeurons() == 0 );
  assert( c->numberOfNeurons( false ) == 0 );
  assert( c->numberOfNeurons( true, Neuron::PYRAMIDAL ) == 0 );
  assert( c->numberOfNeurons( false, Neuron::PYRAMIDAL ) == 0 );
  assert( c->numberOfNeurons( true, Neuron::INTERNEURON ) == 0 );
  assert( c->numberOfNeurons( false, Neuron::INTERNEURON ) == 0 );

  {
    MiniColumnPtr mc2 ( new MiniColumn );

    // needed in release mode to avoid warning 
    ((void)( mc2 ));

    assert( c->removeMiniColumn( mc2 ) == false );
    assert( c->miniColumns( ).size( ) == 1);
    assert( c->miniColumns( ).size( ) == c->numberOfMiniColumns( ));
  }

  assert( c->removeMiniColumn( mc ) == true );
  assert( c->miniColumns( ).size( ) == 0);
  assert( c->miniColumns( ).size( ) == c->numberOfMiniColumns( ));


#define NUM_MINICOLS 20
#define NUM_NEURONS_PYR_PER_LAYER 10
#define NUM_NEURONS_INT_PER_LAYER 8
  unsigned int gid = 0;
  for ( unsigned short i = 0 ; i < NUM_MINICOLS ; i++ )
  {
    c->addMiniColumn( MiniColumnPtr( new MiniColumn ( c, i )));
  }

  MiniColumns miniCols = c->miniColumns( );

  for ( MiniColumns::iterator mcIt = miniCols.begin( );
        mcIt != miniCols.end( ); ++mcIt )
  {
    for ( unsigned short l = 1 ; l < 7 ; l++ )
    {
      for ( unsigned short j = 0 ; j < NUM_NEURONS_PYR_PER_LAYER ; j++ )
      {
        ( *mcIt )->addNeuron(
          NeuronPtr( new Neuron(
            new nsol::NeuronMorphology( new nsol::Soma ),
            l, gid++,
            Matrix4_4fIdentity,
            *mcIt, Neuron::PYRAMIDAL )));
      }
      for ( unsigned short j = 0 ; j < NUM_NEURONS_INT_PER_LAYER ; j++ )
      {
        ( *mcIt )->addNeuron(
          NeuronPtr( new Neuron(
                       nsol::NeuronMorphologyPtr (
                         new nsol::NeuronMorphology( new nsol::Soma )),
                       l, gid++,
                       Matrix4_4fIdentity,
                       *mcIt, Neuron::INTERNEURON )));
      }
    }
  }

  assert( c->numberOfNeurons( ) == gid );
  assert( c->numberOfNeurons( ) ==
          NUM_MINICOLS * 6 * ( NUM_NEURONS_PYR_PER_LAYER +
                               NUM_NEURONS_INT_PER_LAYER ) );
  assert( c->numberOfNeurons( false, Neuron::PYRAMIDAL ) ==
          NUM_MINICOLS * 6 * NUM_NEURONS_PYR_PER_LAYER );
  assert( c->numberOfNeurons( false, Neuron::INTERNEURON ) ==
          NUM_MINICOLS * 6 * NUM_NEURONS_INT_PER_LAYER );
  assert( c->numberOfNeurons( false, Neuron::PYRAMIDAL, 2 ) ==
          NUM_MINICOLS * NUM_NEURONS_PYR_PER_LAYER );
  assert( c->numberOfNeurons( false, Neuron::INTERNEURON , 2 ) ==
          NUM_MINICOLS * NUM_NEURONS_INT_PER_LAYER );


  // assert( c->meanSomaVolume( ) == 0 );
  // assert( c->meanSomaSurface( ) == 0.0f );
  // assert( c->meanDendriteVolume( ) == 0.0f );
  // assert( c->meanDendriteSurface( ) == 0.0f );
  // assert( c->maxSomaVolume( ) == 0.0f );
  // assert( c->maxSomaSurface( ) == 0.0f );
  // assert( c->maxDendriteVolume( ) == 0.0f );
  // assert( c->maxDendriteSurface( ) == 0.0f );


}
