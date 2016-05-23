/**
 * @file    Simplifier.cpp
 * @brief   Test for class nsol::Simplifier
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

#include <iostream>

using namespace nsol;

BOOST_AUTO_TEST_CASE( simplifier_constructor )
{
  {
    Simplifier* simplifier0 = Simplifier::Instance( );
    Simplifier* simplifier1 = Simplifier::Instance( );

    BOOST_CHECK_EQUAL( simplifier0, simplifier1 );
  }
}

BOOST_AUTO_TEST_CASE( simplifier_simplify )
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

    NeuronMorphologyPtr morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = originalNeurites.size( );
    unsigned int originalNumSomaNodes = morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += section->nodes( ).size( );
      }
    }

    morpho1 =
      Simplifier::Instance( )->simplify( morpho0, Simplifier::DELETE_ALL );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = resultNeurites.size( );
    unsigned int resultNumSomaNodes = morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += section->nodes( ).size( );
      }
    }

    BOOST_CHECK_EQUAL( morpho0, morpho1 );
    BOOST_CHECK_EQUAL( originalNumNeurites, resultNumNeurites );
    BOOST_CHECK_EQUAL( originalNumSomaNodes, resultNumSomaNodes );
    BOOST_CHECK_EQUAL( originalNumBranches, resultNumBranches );
    BOOST_CHECK_EQUAL( originalNumBifurcations, resultNumBifurcations );
    BOOST_CHECK( originalNumNeuritesNodes != resultNumNeuritesNodes );
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

    NeuronMorphologyPtr morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = originalNeurites.size( );
    unsigned int originalNumSomaNodes = morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += section->nodes( ).size( );
      }
    }

    morpho1 =
      Simplifier::Instance( )->simplify( morpho0, Simplifier::DELETE_ALL, 0.0,
                                         true );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = resultNeurites.size( );
    unsigned int resultNumSomaNodes = morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += section->nodes( ).size( );
      }
    }

    BOOST_CHECK( morpho0 != morpho1 );
    BOOST_CHECK_EQUAL( originalNumNeurites, resultNumNeurites );
    BOOST_CHECK_EQUAL( originalNumSomaNodes, resultNumSomaNodes );
    BOOST_CHECK_EQUAL( originalNumBranches, resultNumBranches );
    BOOST_CHECK_EQUAL( originalNumBifurcations, resultNumBifurcations );
    BOOST_CHECK( originalNumNeuritesNodes != resultNumNeuritesNodes );
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

    NeuronMorphologyPtr morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = originalNeurites.size( );
    unsigned int originalNumSomaNodes = morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += section->nodes( ).size( );
      }
    }
    morpho1 =
      Simplifier::Instance( )->simplify( morpho0, Simplifier::DIST_NODES, 5 );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = resultNeurites.size( );
    unsigned int resultNumSomaNodes = morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += section->nodes( ).size( );
      }
    }

    BOOST_CHECK_EQUAL( morpho0, morpho1 );
    BOOST_CHECK_EQUAL( originalNumNeurites, resultNumNeurites );
    BOOST_CHECK_EQUAL( originalNumSomaNodes, resultNumSomaNodes );
    BOOST_CHECK_EQUAL( originalNumBranches, resultNumBranches );
    BOOST_CHECK_EQUAL( originalNumBifurcations, resultNumBifurcations );
    BOOST_CHECK( originalNumNeuritesNodes != resultNumNeuritesNodes );
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

    NeuronMorphologyPtr morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = originalNeurites.size( );
    unsigned int originalNumSomaNodes = morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += section->nodes( ).size( );
      }
    }
    morpho1 =
      Simplifier::Instance( )->simplify( morpho0, Simplifier::DIST_NODES, 5.0f,
                                         true );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = resultNeurites.size( );
    unsigned int resultNumSomaNodes = morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += section->nodes( ).size( );
      }
    }

    BOOST_CHECK( morpho0 != morpho1 );
    BOOST_CHECK_EQUAL( originalNumNeurites, resultNumNeurites );
    BOOST_CHECK_EQUAL( originalNumSomaNodes, resultNumSomaNodes );
    BOOST_CHECK_EQUAL( originalNumBranches, resultNumBranches );
    BOOST_CHECK_EQUAL( originalNumBifurcations, resultNumBifurcations );
    BOOST_CHECK( originalNumNeuritesNodes != resultNumNeuritesNodes );
  }
}
