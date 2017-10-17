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
#include <testData.h>

using namespace nsol;

#ifdef NSOL_USE_BRION
BOOST_AUTO_TEST_CASE( brionReader_loaders )
{
  {
    BrionReaderTemplated<
      Node,
      Section,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron,
      MiniColumn,
      Column> br;

    NeuronMorphologyPtr morphology = br.loadMorphology( NSOL_EXAMPLE_NEURON_SWC );

    Neurites neurites = morphology->neurites( );
    unsigned int numNeurites = neurites.size( );
    unsigned int numSomaNodes = morphology->soma( )->nodes().size( );
    unsigned int numBranches = 0;
    unsigned int numBifurcations = 0;
    unsigned int numNeuritesNodes = 0;

    for ( auto neurite: neurites )
    {
      numBranches += neurite->numBranches( );
      numBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        numNeuritesNodes += section->nodes( ).size( );
      }
    }

    BOOST_CHECK_EQUAL( numNeurites, 3 );
    BOOST_CHECK_EQUAL( numSomaNodes, 3 );
    BOOST_CHECK_EQUAL( numBranches, 30 );
    BOOST_CHECK_EQUAL( numBifurcations, 60 );
    //TODO: check this value. Seems to be wrong
    BOOST_CHECK_EQUAL( numNeuritesNodes, 211 );
  }
  {
    BrionReaderTemplated<
      Node,
      Section,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron,
      MiniColumn,
      Column> br;

    NeuronPtr neuron = br.loadNeuron( NSOL_EXAMPLE_NEURON_SWC, 0 );

    BOOST_CHECK_EQUAL( neuron->gid( ), 0 );
    BOOST_CHECK_EQUAL( neuron->layer( ), 0 );
    BOOST_CHECK_EQUAL( neuron->transform( ), Matrix4_4fIdentity );
    BOOST_CHECK_EQUAL( neuron->morphologicalType( ), Neuron::PYRAMIDAL );
    BOOST_CHECK_EQUAL( neuron->functionalType( ), Neuron::EXCITATORY );
  }
  {
    BrionReaderTemplated<
      Node,
      Section,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron,
      MiniColumn,
      Column> br;

    NeuronPtr neuron = br.loadNeuron( NSOL_EXAMPLE_NEURON_SWC, 1, 1,
                                      Matrix4_4fIdentity,
                                      Neuron::INTERNEURON,
                                      Neuron::INHIBITORY );

    BOOST_CHECK_EQUAL( neuron->gid( ), 1 );
    BOOST_CHECK_EQUAL( neuron->layer( ), 1 );
    BOOST_CHECK_EQUAL( neuron->transform( ), Matrix4_4fIdentity );
    BOOST_CHECK_EQUAL( neuron->morphologicalType( ), Neuron::INTERNEURON );
    BOOST_CHECK_EQUAL( neuron->functionalType( ), Neuron::INHIBITORY );
  }
}
#else

BOOST_AUTO_TEST_CASE( brionReader_loaders )
{
}

#endif // NSOL_USE_BRION
