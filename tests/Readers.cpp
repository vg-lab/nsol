/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
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
      NeuronMorphologySection,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron,
      MiniColumn,
      Column> br;

    NeuronMorphologyPtr morphology =
      br.loadMorphology( NSOL_EXAMPLE_NEURON_SWC );

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
    BOOST_CHECK_EQUAL( numNeuritesNodes, 208 );
  }
  {
    BrionReaderTemplated<
      Node,
      NeuronMorphologySection,
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
      NeuronMorphologySection,
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

BOOST_AUTO_TEST_CASE( swcReader_loaders )
{
  {
    SwcReaderTemplated<
      Node,
      NeuronMorphologySection,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron > sr;

    NeuronMorphologyPtr morphology =
      sr.readMorphology( NSOL_EXAMPLE_NEURON_SWC );

    Neurites neurites = morphology->neurites( );
    unsigned int numNeurites = ( unsigned int )neurites.size( );
    unsigned int numSomaNodes =
      ( unsigned int )morphology->soma( )->nodes().size( );
    unsigned int numBranches = 0;
    unsigned int numBifurcations = 0;
    unsigned int numNeuritesNodes = 0;

    for ( auto neurite: neurites )
    {
      numBranches += neurite->numBranches( );
      numBifurcations += neurite->numBifurcations( );
      for ( auto section: neurite->sections( ) )
      {
        numNeuritesNodes += ( unsigned int )section->nodes( ).size( );
      }
    }

    BOOST_CHECK_EQUAL( numNeurites, 3 );
    BOOST_CHECK_EQUAL( numSomaNodes, 3 );
    BOOST_CHECK_EQUAL( numBranches, 30 );
    BOOST_CHECK_EQUAL( numBifurcations, 60 );
    BOOST_CHECK_EQUAL( numNeuritesNodes, 208 );
  }
  {
    SwcReaderTemplated<
      Node,
      NeuronMorphologySection,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron > sr;

    NeuronPtr neuron = sr.readNeuron( NSOL_EXAMPLE_NEURON_SWC );

    BOOST_CHECK_EQUAL( neuron->gid( ), 0 );
    BOOST_CHECK_EQUAL( neuron->layer( ), 0 );
    BOOST_CHECK_EQUAL( neuron->transform( ), Matrix4_4fIdentity );
    BOOST_CHECK_EQUAL( neuron->morphologicalType( ), Neuron::UNDEFINED );
    BOOST_CHECK_EQUAL( neuron->functionalType( ),
                       Neuron::UNDEFINED_FUNCTIONAL_TYPE );
  }
}

void checkEquivalentNeuronMorphologies( NeuronMorphologyPtr morpho0,
                                        NeuronMorphologyPtr morpho1 )
{
  unsigned int numNeurites0 = ( unsigned int )morpho0->neurites( ).size( );
  unsigned int numSomaNodes0 =
    ( unsigned int )morpho0->soma( )->nodes().size( );
  unsigned int numBranches0 = 0;
  unsigned int numBifurcations0 = 0;
  unsigned int numNeuritesNodes0 = 0;

  unsigned int numNeurites1 = ( unsigned int )morpho1->neurites( ).size( );
  unsigned int numSomaNodes1 =
    ( unsigned int )morpho1->soma( )->nodes().size( );
  unsigned int numBranches1 = 0;
  unsigned int numBifurcations1 = 0;
  unsigned int numNeuritesNodes1 = 0;

  for ( auto neurite: morpho0->neurites( ))
  {
    numBranches0 += neurite->numBranches( );
    numBifurcations0 += neurite->numBifurcations( );
    for ( auto section: neurite->sections( ) )
    {
      numNeuritesNodes0 += ( unsigned int )section->nodes( ).size( );
    }
  }

  for ( auto neurite: morpho1->neurites( ))
  {
    numBranches1 += neurite->numBranches( );
    numBifurcations1 += neurite->numBifurcations( );
    for ( auto section: neurite->sections( ) )
    {
      numNeuritesNodes1 += ( unsigned int )section->nodes( ).size( );
    }
  }

  BOOST_CHECK( morpho0 != morpho1 );
  BOOST_CHECK_EQUAL( numNeurites0, numNeurites1 );
  BOOST_CHECK_EQUAL( numSomaNodes0, numSomaNodes1 );
  BOOST_CHECK_EQUAL( numBranches0, numBranches1 );
  BOOST_CHECK_EQUAL( numBifurcations0, numBifurcations1 );
  BOOST_CHECK_EQUAL( numNeuritesNodes0, numNeuritesNodes1 );

}

#ifdef NSOL_USE_BRION
BOOST_AUTO_TEST_CASE( morphology_loaders_comparison )
{
  {
    SwcReaderTemplated<
      Node,
      NeuronMorphologySection,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron > sr;

    NeuronMorphologyPtr swcMorphology =
      sr.readMorphology( NSOL_EXAMPLE_NEURON_SWC, false );

    BrionReaderTemplated<
      Node,
      NeuronMorphologySection,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron,
      MiniColumn,
      Column> br;

    NeuronMorphologyPtr brionMorphology =
      br.loadMorphology( NSOL_EXAMPLE_NEURON_SWC, false );

    checkEquivalentNeuronMorphologies( swcMorphology, brionMorphology );
  }
  {
    SwcReaderTemplated<
      Node,
      NeuronMorphologySection,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron > sr;

    NeuronMorphologyPtr swcMorphology =
      sr.readMorphology( NSOL_EXAMPLE_NEURON_SWC, true );

    BrionReaderTemplated<
      Node,
      NeuronMorphologySection,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron,
      MiniColumn,
      Column> br;

    NeuronMorphologyPtr brionMorphology =
      br.loadMorphology( NSOL_EXAMPLE_NEURON_SWC, true );

    checkEquivalentNeuronMorphologies( swcMorphology, brionMorphology );
  }
}
#else
BOOST_AUTO_TEST_CASE( morphology_loaders_comparison )
{
  // Empty test
}
#endif

BOOST_AUTO_TEST_CASE( vectors_morphology_loaders)
{
  std::vector< float > points;
  std::vector< unsigned int > segments;

  Eigen::Vector4f point;
  point = Eigen::Vector4f( 0.0f, 0.0f, 0.0f, 1.0f ); // 0
  points.insert( points.end( ), &point.data( )[0], &point.data( )[4]);
  point = Eigen::Vector4f( 2.0f, 0.0f, 0.0f, 1.0f ); // 1
  points.insert( points.end( ), &point.data( )[0], &point.data( )[4]);
  point = Eigen::Vector4f( 4.0f, 0.0f, 0.0f, 1.0f ); // 2
  points.insert( points.end( ), &point.data( )[0], &point.data( )[4]);
  segments.push_back( 0 ); segments.push_back( 1 );
  segments.push_back( 1 ); segments.push_back( 2 );

  point = Eigen::Vector4f( 6.0f, 0.0f, 0.0f, 1.0f ); // 3
  points.insert( points.end( ), &point.data( )[0], &point.data( )[4]);
  point = Eigen::Vector4f( 8.0f, 0.0f, 0.0f, 1.0f ); // 4
  points.insert( points.end( ), &point.data( )[0], &point.data( )[4]);
  segments.push_back( 2 ); segments.push_back( 3 );
  segments.push_back( 3 ); segments.push_back( 4 );

  point = Eigen::Vector4f( 4.0f, 2.0f, 0.0f, 1.0f ); // 5
  points.insert( points.end( ), &point.data( )[0], &point.data( )[4]);
  point = Eigen::Vector4f( 4.0f, 4.0f, 0.0f, 1.0f ); // 6
  points.insert( points.end( ), &point.data( )[0], &point.data( )[4]);
  segments.push_back( 2 ); segments.push_back( 5 );
  segments.push_back( 5 ); segments.push_back( 6 );

  VectorsReader vr;
  MorphologyPtr morpho = vr.loadMorphology( points, segments );

  BOOST_CHECK_EQUAL( morpho->sections( ).size( ), 1 );
  BOOST_CHECK_EQUAL( morpho->sections( )[0]->nodes( ).size( ), 3 );
  BOOST_CHECK_EQUAL( morpho->sections( )[0]->forwardNeighbors( ).size( ), 2 );
}
