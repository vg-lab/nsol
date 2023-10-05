/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 *          Cristian Rodriguez <cristian.rodriguez@urjc.es>
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
#include <testData.h>

using namespace nsol;

BOOST_AUTO_TEST_CASE( neuronMorphology_constructor )
{
  {
    NeuronMorphology neuronMorphology;
    BOOST_CHECK( neuronMorphology.soma() == nullptr );
    BOOST_CHECK_EQUAL( neuronMorphology.neurites( ).size( ), 0 );
    BOOST_CHECK_EQUAL( neuronMorphology.parentNeurons( ).size( ), 0 );
  }
  {
    NeuronMorphology const neuronMorphology( nullptr );
    BOOST_CHECK_EQUAL( neuronMorphology.neurites( ).size( ), 0 );
    BOOST_CHECK_EQUAL( neuronMorphology.parentNeurons( ).size( ), 0 );
  }
}

BOOST_AUTO_TEST_CASE( neuronMorphology_clone )
{
  NeuronMorphologyPtr neuronMorphology;
#ifdef NSOL_USE_BRION
  BrionReader brionReader;
  neuronMorphology = brionReader.loadMorphology( NSOL_EXAMPLE_NEURON_SWC );
#else
  SwcReader swcReader;
  neuronMorphology = swcReader.readMorphology( NSOL_EXAMPLE_NEURON_SWC );
#endif

  NeuronMorphologyPtr neuronMorphology1 = neuronMorphology->clone( );

  BOOST_CHECK( *neuronMorphology->soma( ) != *neuronMorphology1->soma( ));
}

BOOST_AUTO_TEST_CASE( neuronMorphology_operators )
{
  NeuronMorphologyPtr neuronMorphology1;
  NeuronMorphologyPtr neuronMorphology2;

#ifdef NSOL_USE_BRION
  BrionReader brionReader;
  neuronMorphology1 = brionReader.loadMorphology( NSOL_EXAMPLE_NEURON_SWC );
  neuronMorphology2 = brionReader.loadMorphology( NSOL_MINI_SWC );
#else
  SwcReader swcReader;
  neuronMorphology1 = swcReader.readMorphology( NSOL_EXAMPLE_NEURON_SWC );
  neuronMorphology2 = swcReader.readMorphology( NSOL_MINI_SWC );
#endif

  BOOST_CHECK( neuronMorphology1 == neuronMorphology1 );

  BOOST_CHECK( *neuronMorphology1 == *neuronMorphology1 );
  BOOST_CHECK( *neuronMorphology2 != *neuronMorphology1 );

  BOOST_CHECK( neuronMorphology2 == neuronMorphology2 );
  BOOST_CHECK( neuronMorphology1 != neuronMorphology2 );
}

void checkMorphology( NeuronMorphologyPtr neuronMorphology )
{
  auto basalDendrites = neuronMorphology->basalDendrites( );
  auto apicalDendrites = neuronMorphology->apicalDendrites( );

  size_t numNeurites = neuronMorphology->neurites( ).size( );
  size_t numDendrites = neuronMorphology->dendrites( )->size( );
  size_t numBasals = basalDendrites->size( );
  size_t numApicals = apicalDendrites->size( );

  BOOST_CHECK_EQUAL( numNeurites, 3 );
  BOOST_CHECK_EQUAL( numDendrites, 2 );
  BOOST_CHECK_EQUAL( numBasals + numApicals, numDendrites);
  BOOST_CHECK_EQUAL( numBasals, 1 );
  BOOST_CHECK_EQUAL( numApicals, 1 );

  BOOST_CHECK( neuronMorphology->apicalDendrite( ) != nullptr );
  BOOST_CHECK( neuronMorphology->axons( )->empty() != true );
  BOOST_CHECK_EQUAL( neuronMorphology, neuronMorphology );
  BOOST_CHECK_EQUAL( neuronMorphology->parentNeurons( ).size( ), 0 );

  Neurites neurites = neuronMorphology->neurites( );
  unsigned int numSomaNodes =
    static_cast<unsigned int>(neuronMorphology->soma( )->nodes().size( ));
  unsigned int numBranches = 0;
  unsigned int numBifurcations = 0;
  unsigned int numNeuritesNodes = 0;

  for ( auto neurite: neurites )
  {
    numBranches += neurite->numBranches( );
    numBifurcations += neurite->numBifurcations( );
    for ( auto section: neurite->sections( ) )
    {
      numNeuritesNodes += static_cast<unsigned int>(section->nodes( ).size( ));
    }
  }

  BOOST_CHECK_EQUAL( numNeurites, 3 );
  BOOST_CHECK_EQUAL( numSomaNodes, 3 );
  BOOST_CHECK_EQUAL( numBranches, 30 );
  BOOST_CHECK_EQUAL( numBifurcations, 60 );

  //TODO: this value includes repeated nodes
  BOOST_CHECK_EQUAL( numNeuritesNodes, 208 );

}

BOOST_AUTO_TEST_CASE( neuronMorphology_dentrites )
{
  NeuronMorphologyPtr neuronMorphology;

#ifdef NSOL_USE_BRION
  //TODO: this test fails
  // BrionReader brionReader;
  // neuronMorphology = brionReader.loadMorphology( NSOL_EXAMPLE_NEURON_SWC );
  // checkMorphology( neuronMorphology );
#endif

  SwcReader swcReader;
  neuronMorphology = swcReader.readMorphology( NSOL_EXAMPLE_NEURON_SWC );
  checkMorphology( neuronMorphology );

  const NeuronMorphologyPtr neuronMorphology2 = new NeuronMorphology( );
  BOOST_CHECK( neuronMorphology2->apicalDendrite( ) == nullptr );
  BOOST_CHECK( neuronMorphology2->axons( )->empty() == true );
  BOOST_CHECK_EQUAL( neuronMorphology2->neurites( ).size( ), 0 );
}

BOOST_AUTO_TEST_CASE( neuronmorphology_stats)
{
  NeuronMorphology nm;
  BOOST_CHECK( nm.stats( ) == nullptr );

  NeuronMorphologyStats neuronMorphologyStats;
  BOOST_CHECK( neuronMorphologyStats.stats( ) == &neuronMorphologyStats );
}
