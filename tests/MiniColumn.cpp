/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"


//using namespace nsol;



void CheckNullMorphologicalValues( nsol::MiniColumnPtr /* mc */ )
{

  // BOOST_CHECK_EQUAL( mc->meanSomaVolume( ), 0 );
  // BOOST_CHECK_EQUAL( mc->meanSomaSurface( ), 0.0f );
  // BOOST_CHECK_EQUAL( mc->meanDendriteVolume( ), 0.0f );
  // BOOST_CHECK_EQUAL( mc->meanDendriteSurface( ), 0.0f );
  // BOOST_CHECK_EQUAL( mc->maxSomaVolume( ), 0.0f );
  // BOOST_CHECK_EQUAL( mc->maxSomaSurface( ), 0.0f );
  // BOOST_CHECK_EQUAL( mc->maxDendriteVolume( ), 0.0f );
  // BOOST_CHECK_EQUAL( mc->maxDendriteSurface( ), 0.0f );


}

void CheckNoNeurons( nsol::MiniColumnPtr mc )
{
  BOOST_CHECK_EQUAL( mc->numberOfNeurons(), 0 );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( false ), 0 );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( true, nsol::Neuron::PYRAMIDAL ),
		     0 );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( false, nsol::Neuron::PYRAMIDAL ),
		     0 );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( true, nsol::Neuron::INTERNEURON ),
		     0 );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( false, nsol::Neuron::INTERNEURON ),
		     0 );
}




BOOST_AUTO_TEST_CASE( emptyMiniColumn )
{

  // Create minicolumn
  nsol::MiniColumnPtr mc ( new nsol::MiniColumn );

  // Check id equal to 0
  #define MINICOL_ID 115
  BOOST_CHECK_EQUAL( mc->id( ), 0 );
  mc->id( ) = MINICOL_ID;
  BOOST_CHECK_EQUAL( mc->id( ), MINICOL_ID );

  // Check morphological values are computed
  // to 0 without errors
  CheckNullMorphologicalValues( mc );
  CheckNoNeurons( mc );

  // Free dynamic memory
  NSOL_DELETE_PTR( mc )

}


BOOST_AUTO_TEST_CASE( addNeuron)
{
  // Create a minicolumn
  nsol::MiniColumnPtr mc ( new nsol::MiniColumn );

  // Create a neuron
  nsol::NeuronPtr n (
    new nsol::Neuron ( new nsol::NeuronMorphology ( new nsol::Soma )));

  // Add the neuron to the minicol
  mc->addNeuron( n );

  // Check if added ok
  BOOST_CHECK_EQUAL( mc->neurons( ).size( ), 1);
  BOOST_CHECK_EQUAL( mc->neurons( ).size( ), mc->numberOfNeurons( ));

  // Check morphological values are still computed
  // to 0 without errors
  CheckNullMorphologicalValues( mc );

  // Free dynamic memory
  NSOL_DELETE_PTR( mc )

}


BOOST_AUTO_TEST_CASE( removeNeuron)
{

  // Create a minicolumn
  nsol::MiniColumnPtr mc ( new nsol::MiniColumn );

  // Create two neurons
  nsol::NeuronPtr n1 (
    new nsol::Neuron ( new nsol::NeuronMorphology( new nsol::Soma )));
  nsol::NeuronPtr n2 (
    new nsol::Neuron ( new nsol::NeuronMorphology( new nsol::Soma )));

  // Add one of them to the column
  mc->addNeuron( n1 );

  // Try to remove the one not added
  BOOST_CHECK_EQUAL( mc->removeNeuron( n2 ), false );
  BOOST_CHECK_EQUAL( mc->neurons( ).size( ), 1);
  BOOST_CHECK_EQUAL( mc->neurons( ).size( ), mc->numberOfNeurons( ));

  // Remove the one added
  BOOST_CHECK_EQUAL( mc->removeNeuron( n1 ), true );
  BOOST_CHECK_EQUAL( mc->neurons( ).size( ), 0);
  BOOST_CHECK_EQUAL( mc->neurons( ).size( ), mc->numberOfNeurons( ));

  // Check morphological values are still computed
  // to 0 without errors
  CheckNullMorphologicalValues( mc );
  CheckNoNeurons( mc );

  // Free dynamic memory
  NSOL_DELETE_PTR( mc )
  NSOL_DELETE_PTR( n1 );
  NSOL_DELETE_PTR( n2 );


}


BOOST_AUTO_TEST_CASE( clearNeurons )
{
  // Create a minicolumn
  nsol::MiniColumnPtr mc ( new nsol::MiniColumn );

  #define NUM_NEURONS 100

  // Create and add some neurons
  for ( int i = 0; i < NUM_NEURONS; i++ )
    mc->addNeuron(
      nsol::NeuronPtr(
        new nsol::Neuron( new nsol::NeuronMorphology( new nsol::Soma ))));

  // Clear neurons
  mc->clearNeurons( );

  BOOST_CHECK_EQUAL( mc->neurons( ).size( ), 0);
  BOOST_CHECK_EQUAL( mc->neurons( ).size( ), mc->numberOfNeurons( ));

  // Check morphological values are still computed
  // to 0 without errors
  CheckNullMorphologicalValues( mc );
  CheckNoNeurons( mc );

  // Free dymanic memory used
  for ( auto neuronIt = mc->neurons( ).begin( );
	neuronIt != mc->neurons( ).end( ); neuronIt++ )
    NSOL_DELETE_PTR( ( * neuronIt ));

  NSOL_DELETE_PTR( mc )

}



BOOST_AUTO_TEST_CASE( operators )
{

  // Create a minicolumn
  nsol::MiniColumnPtr mc ( new nsol::MiniColumn );

  // Compare empty columns
  nsol::MiniColumnPtr mc2( new nsol::MiniColumn( ));
  BOOST_CHECK_EQUAL( *mc == *mc2, true );
  BOOST_CHECK_EQUAL( *mc != *mc2, false );

  // Change id and compare
  mc2->id( ) = 10;
  BOOST_CHECK_EQUAL( *mc == *mc2, false );
  BOOST_CHECK_EQUAL( *mc != *mc2, true );

  // Assignment operator
  nsol::MiniColumn mc3 = *mc2 ;
  BOOST_CHECK_EQUAL( mc3 == *mc2, true );
  BOOST_CHECK_EQUAL( mc3 != *mc2, false );

  // Add neurons and test if equal
  *mc2 = *mc;
  BOOST_CHECK_EQUAL( *mc == *mc2, true );
  BOOST_CHECK_EQUAL( *mc != *mc2, false );

  for ( int i = 0 ; i < NUM_NEURONS ; i++ )
  {
    mc->addNeuron(
      nsol::NeuronPtr( new nsol::Neuron(
                         new nsol::NeuronMorphology( new nsol::Soma ))));
  }

  BOOST_CHECK_EQUAL( *mc == *mc2, false );
  BOOST_CHECK_EQUAL( *mc != *mc2, true );

  // Test assignment op with minicols
  *mc2 = *mc;
  BOOST_CHECK_EQUAL( *mc == *mc2, true );
  BOOST_CHECK_EQUAL( *mc != *mc2, false );


  // Test copy constructor
  nsol::MiniColumn mc4( mc3 );
  BOOST_CHECK_EQUAL( *mc == mc4, false );
  BOOST_CHECK_EQUAL( *mc != mc4, true );

  nsol::MiniColumn mc5( *mc );
  BOOST_CHECK_EQUAL( *mc == mc5, true );
  BOOST_CHECK_EQUAL( *mc != mc5, false );

  // Free dymanic memory used
  for ( auto neuronIt = mc->neurons( ).begin( );
	neuronIt != mc->neurons( ).end( ); neuronIt++ )
    NSOL_DELETE_PTR( ( * neuronIt ));

  NSOL_DELETE_PTR( mc )
  NSOL_DELETE_PTR( mc2 )




}


BOOST_AUTO_TEST_CASE( numberOfNeurons )
{

#define NUM_NEURONS_PYR_PER_LAYER 10
#define NUM_NEURONS_INT_PER_LAYER 8

  // Create a minicolumn
  nsol::MiniColumnPtr mc ( new nsol::MiniColumn );

  unsigned int gid = 0;

  for ( int l = 1 ; l < 7 ; l++ )
  {
    for ( int j = 0 ; j < NUM_NEURONS_PYR_PER_LAYER ; j++ )
    {
      mc->addNeuron(
        nsol::NeuronPtr(
          new nsol::Neuron(
            new nsol::NeuronMorphology( new nsol::Soma ),
            l, gid++,
            nsol::Matrix4_4fIdentity,
            mc, nsol::Neuron::PYRAMIDAL )));
    }
    for ( int j = 0 ; j < NUM_NEURONS_INT_PER_LAYER ; j++ )
    {
      mc->addNeuron(
        nsol::NeuronPtr(
          new nsol::Neuron(
            new nsol::NeuronMorphology( new nsol::Soma ),
            l, gid++,
            nsol::Matrix4_4fIdentity,
            mc, nsol::Neuron::INTERNEURON )));
    }
  }


  BOOST_CHECK_EQUAL( mc->numberOfNeurons( ), gid );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( ),
	     6 * ( NUM_NEURONS_PYR_PER_LAYER +
		   NUM_NEURONS_INT_PER_LAYER ) );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( false, nsol::Neuron::PYRAMIDAL ),
	     6 * NUM_NEURONS_PYR_PER_LAYER );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( false, nsol::Neuron::INTERNEURON ),
	     6 * NUM_NEURONS_INT_PER_LAYER );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( false, nsol::Neuron::PYRAMIDAL, 2 ),
	     NUM_NEURONS_PYR_PER_LAYER );
  BOOST_CHECK_EQUAL( mc->numberOfNeurons( false, nsol::Neuron::INTERNEURON ,
       2 ), NUM_NEURONS_INT_PER_LAYER );

  // Check morphological values are still computed
  // to 0 without errors
  CheckNullMorphologicalValues( mc );

  // Free dymanic memory used
  for ( auto neuronIt = mc->neurons( ).begin( );
	neuronIt != mc->neurons( ).end( ); neuronIt++ )
    NSOL_DELETE_PTR( ( * neuronIt ));

  NSOL_DELETE_PTR( mc )


}


BOOST_AUTO_TEST_CASE( minicolumn_stats)
{
  nsol::MiniColumnPtr mc ( new nsol::MiniColumn );
  BOOST_CHECK( mc->stats( ) == nullptr );
}