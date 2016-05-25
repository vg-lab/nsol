/**
 * @file    BrionReader.cpp
 * @brief   Test for class nsol::BrionReaderTemplated
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

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

    NeuronMorphologyPtr morphology = br.loadMorphology( "ExampleNeuron.swc" );

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

    // std::cout << "Number of neurites: " << numNeurites << std::endl;
    // std::cout << "Number of soma nodes: " << numSomaNodes << std::endl;
    // std::cout << "Number of branches: " << numBranches << std::endl;
    // std::cout << "Number of bifurcations: " << numBifurcations << std::endl;
    // std::cout << "Number of neurites nodes: " << numNeuritesNodes << std::endl;

    BOOST_CHECK_EQUAL( numNeurites, 6 );
    BOOST_CHECK_EQUAL( numSomaNodes, 1 );
    BOOST_CHECK_EQUAL( numBranches, 80 );
    BOOST_CHECK_EQUAL( numBifurcations, 160 );
    BOOST_CHECK_EQUAL( numNeuritesNodes, 515 );
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

    NeuronPtr neuron = br.loadNeuron( "ExampleNeuron.swc", 0 );

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

    NeuronPtr neuron = br.loadNeuron( "ExampleNeuron.swc", 1, 1,
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
