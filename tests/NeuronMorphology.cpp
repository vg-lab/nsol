/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
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
  neuronMorphology = brionReader.loadMorphology( "ExampleNeuron.swc" );
#else
  SwcReader swcReader;
  neuronMorphology = swcReader.readMorphology( "ExampleNeuron.swc" );
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
  neuronMorphology1 = brionReader.loadMorphology( "ExampleNeuron.swc" );
  neuronMorphology2 = brionReader.loadMorphology( "mini.swc" );
#else
  SwcReader swcReader;
  neuronMorphology1 = swcReader.readMorphology( "ExampleNeuron.swc" );
  neuronMorphology2 = swcReader.readMorphology( "mini.swc" );
#endif

  BOOST_CHECK( neuronMorphology1 == neuronMorphology1 );

  BOOST_CHECK( *neuronMorphology1 == *neuronMorphology1 );
  BOOST_CHECK( *neuronMorphology2 != *neuronMorphology1 );

  BOOST_CHECK( neuronMorphology2 == neuronMorphology2 );
  BOOST_CHECK( neuronMorphology1 != neuronMorphology2 );
}


BOOST_AUTO_TEST_CASE( neuronMorphology_dentrites )
{
  NeuronMorphologyPtr neuronMorphology;

#ifdef NSOL_USE_BRION
  BrionReader brionReader;
  neuronMorphology = brionReader.loadMorphology( "ExampleNeuron.swc" );
#else
  SwcReader swcReader;
  neuronMorphology = swcReader.readMorphology( "ExampleNeuron.swc" );
#endif

  auto basalDendrites = neuronMorphology->basalDendrites( );
  auto apicalDendrites = neuronMorphology->apicalDendrites( );

  size_t num_neurites = neuronMorphology->neurites( ).size( );
  size_t num_dendrites = neuronMorphology->dendrites( )->size( );
  size_t num_basals = basalDendrites->size( );
  size_t num_apicals = apicalDendrites->size( );

  BOOST_CHECK_EQUAL( num_neurites, 6);
  BOOST_CHECK_EQUAL( num_dendrites, 5);
  BOOST_CHECK_EQUAL( num_basals + num_apicals, num_dendrites);
  BOOST_CHECK_EQUAL( num_basals, 4);
  BOOST_CHECK_EQUAL( num_apicals, 1);

  BOOST_CHECK( neuronMorphology->apicalDendrite( ) != nullptr );
  BOOST_CHECK( neuronMorphology->axon( ) != nullptr );

  BOOST_CHECK_EQUAL( neuronMorphology, neuronMorphology );

  BOOST_CHECK_EQUAL( neuronMorphology->parentNeurons( ).size( ), 0 );



  const NeuronMorphologyPtr neuronMorphology2 = new NeuronMorphology( );
  BOOST_CHECK( neuronMorphology2->apicalDendrite( ) == nullptr );
  BOOST_CHECK( neuronMorphology2->axon( ) == nullptr );
  BOOST_CHECK_EQUAL( neuronMorphology2->neurites( ).size( ), 0 );
}


BOOST_AUTO_TEST_CASE( neuronmorphology_stats)
{
  NeuronMorphology nm;
  BOOST_CHECK( nm.stats( ) == nullptr );
}
