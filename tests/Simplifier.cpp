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
    NeuronMorphologyPtr morpho0;

#ifdef NSOL_USE_BRION
    BrionReader br;
    morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
#else
    SwcReader swcr;
    morpho0 = swcr.readMorphology( "ExampleNeuron.swc" );
#endif

    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = (unsigned int)originalNeurites.size( );
    unsigned int originalNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
      }
    }

    morpho1 =
      Simplifier::Instance( )->simplify( morpho0, Simplifier::DELETE_ALL );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = (unsigned int)resultNeurites.size( );
    unsigned int resultNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
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
    NeuronMorphologyPtr morpho0;

#ifdef NSOL_USE_BRION
    BrionReader br;
    morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
#else
    SwcReader swcr;
    morpho0 = swcr.readMorphology( "ExampleNeuron.swc" );
#endif

    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = (unsigned int)originalNeurites.size( );
    unsigned int originalNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
      }
    }

    morpho1 =
      Simplifier::Instance( )->simplify( morpho0, Simplifier::DELETE_ALL, 0.0,
                                         true );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = (unsigned int)resultNeurites.size( );
    unsigned int resultNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
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
    NeuronMorphologyPtr morpho0;

#ifdef NSOL_USE_BRION
    BrionReader br;
    morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
#else
    SwcReader swcr;
    morpho0 = swcr.readMorphology( "ExampleNeuron.swc" );
#endif

    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = (unsigned int)originalNeurites.size( );
    unsigned int originalNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
      }
    }
    morpho1 =
      Simplifier::Instance( )->simplify( morpho0, Simplifier::DIST_NODES, 5 );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = (unsigned int)resultNeurites.size( );
    unsigned int resultNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
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
    NeuronMorphologyPtr morpho0;

#ifdef NSOL_USE_BRION
    BrionReader br;
    morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
#else
    SwcReader swcr;
    morpho0 = swcr.readMorphology( "ExampleNeuron.swc" );
#endif

    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = (unsigned int)originalNeurites.size( );
    unsigned int originalNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
      }
    }
    morpho1 =
      Simplifier::Instance( )->simplify( morpho0, Simplifier::DIST_NODES, 5.0f,
                                         true );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = (unsigned int)resultNeurites.size( );
    unsigned int resultNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
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

BOOST_AUTO_TEST_CASE( cutout )
{
  {
    NeuronMorphologyPtr morpho0;

#ifdef NSOL_USE_BRION
    BrionReaderTemplated<
      ImportanceNode,
      Section,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron,
      MiniColumn,
      Column
      > br;
    morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
#else
    SwcReaderTemplated<
      ImportanceNode,
      Section,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron
      > swcr;
    morpho0 = swcr.readMorphology( "ExampleNeuron.swc" );
#endif

    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = (unsigned int)originalNeurites.size( );
    unsigned int originalNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
      }
    }
    morpho1 =
      Simplifier::Instance( )->cutout( morpho0 );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = (unsigned int)resultNeurites.size( );
    unsigned int resultNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
      }
    }

    BOOST_CHECK_EQUAL( morpho0, morpho1 );
    BOOST_CHECK( originalNumNeurites != resultNumNeurites );
    BOOST_CHECK_EQUAL( originalNumSomaNodes, resultNumSomaNodes );
    BOOST_CHECK( originalNumBranches != resultNumBranches );
    BOOST_CHECK( originalNumBifurcations != resultNumBifurcations );
    BOOST_CHECK( originalNumNeuritesNodes != resultNumNeuritesNodes );
  }

  {
    NeuronMorphologyPtr morpho0;

#ifdef NSOL_USE_BRION
    BrionReaderTemplated<
      ImportanceNode,
      Section,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron,
      MiniColumn,
      Column
      > br;
    morpho0 = br.loadMorphology( "ExampleNeuron.swc" );
#else
    SwcReaderTemplated<
      ImportanceNode,
      Section,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron
      > swcr;
    morpho0 = swcr.readMorphology( "ExampleNeuron.swc" );
#endif

    NeuronMorphologyPtr morpho1;
    Neurites originalNeurites = morpho0->neurites( );
    unsigned int originalNumNeurites = (unsigned int)originalNeurites.size( );
    unsigned int originalNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int originalNumBranches = 0;
    unsigned int originalNumBifurcations = 0;
    unsigned int originalNumNeuritesNodes = 0;

    for ( auto neurite: originalNeurites )
    {
      originalNumBranches += neurite->numBranches( );
      originalNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        originalNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
      }
    }
    morpho1 =
      Simplifier::Instance( )->cutout( morpho0, true );

    Neurites resultNeurites = morpho1->neurites( );
    unsigned int resultNumNeurites = (unsigned int)resultNeurites.size( );
    unsigned int resultNumSomaNodes =
      (unsigned int)morpho0->soma( )->nodes().size( );
    unsigned int resultNumBranches = 0;
    unsigned int resultNumBifurcations = 0;
    unsigned int resultNumNeuritesNodes = 0;

    for ( auto neurite: resultNeurites )
    {
      resultNumBranches += neurite->numBranches( );
      resultNumBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        resultNumNeuritesNodes += (unsigned int)section->nodes( ).size( );
      }
    }

    BOOST_CHECK( morpho0 != morpho1 );
    BOOST_CHECK( originalNumNeurites != resultNumNeurites );
    BOOST_CHECK_EQUAL( originalNumSomaNodes, resultNumSomaNodes );
    BOOST_CHECK( originalNumBranches != resultNumBranches );
    BOOST_CHECK( originalNumBifurcations != resultNumBifurcations );
    BOOST_CHECK( originalNumNeuritesNodes != resultNumNeuritesNodes );
  }
}
