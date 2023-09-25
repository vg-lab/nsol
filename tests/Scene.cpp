/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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

void checkScene( const DataSet& ds )
{
  BOOST_CHECK_EQUAL( ds.columns( ).size( ), 2 );
  BOOST_CHECK_EQUAL( ds.columns( )[0]->miniColumns( ).size( ), 2 );
  BOOST_CHECK_EQUAL( ds.columns( )[1]->miniColumns( ).size( ), 1 );

  BOOST_CHECK_EQUAL( ds.neurons( ).size( ), 4 );

  for ( const auto& neuron : ds.neurons( ))
  {
    BOOST_CHECK( neuron.second->morphology( ) != nullptr );
  }

  auto neurons = ds.neurons( );

  BOOST_CHECK( neurons[0]->layer( ) == 2 );
  BOOST_CHECK( neurons[1]->layer( ) == 3 );
  BOOST_CHECK( neurons[2]->layer( ) == 1 );
  BOOST_CHECK( neurons[3]->layer( ) == 1 );

  BOOST_CHECK( neurons[0]->morphologicalType( ) == Neuron::UNDEFINED );
  BOOST_CHECK( neurons[1]->morphologicalType( ) == Neuron::INTERNEURON );
  BOOST_CHECK( neurons[2]->morphologicalType( ) == Neuron::PYRAMIDAL );
  BOOST_CHECK( neurons[3]->morphologicalType( ) == Neuron::PYRAMIDAL );

  BOOST_CHECK( neurons[0]->functionalType( ) ==
               Neuron::UNDEFINED_FUNCTIONAL_TYPE );
  BOOST_CHECK( neurons[1]->functionalType( ) == Neuron::INHIBITORY );
  BOOST_CHECK( neurons[2]->functionalType( ) == Neuron::EXCITATORY );
  BOOST_CHECK( neurons[3]->functionalType( ) == Neuron::EXCITATORY );


  BOOST_CHECK( neurons[0]->morphology( ) == neurons[1]->morphology( ));
  BOOST_CHECK( neurons[2]->morphology( ) == neurons[3]->morphology( ));

  Matrix4_4f m0;
  m0 << 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f;
  BOOST_CHECK( neurons[0]->transform( ) == m0 );

  Matrix4_4f m1;
  m1 << 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 40.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f;
  BOOST_CHECK( neurons[1]->transform( ) == m1 );

  Matrix4_4f m2;
  m2 << 1.0f, 0.0f, 0.0f, 20.0f,
        0.0f, 1.0f, 0.0f, 20.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f;
  BOOST_CHECK( neurons[2]->transform( ) == m2 );

  Matrix4_4f m3;
  m3 << 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 30.0f,
        0.0f, 0.0f, 0.0f, 1.0f;
  BOOST_CHECK( neurons[3]->transform( ) == m3 );

}

BOOST_AUTO_TEST_CASE( load_scene )
{

  DataSet ds;

  ds.loadXmlScene( NSOL_XML_SCENE_TEST_DATA );
  checkScene( ds );
  ds.close( );

  BOOST_CHECK_EQUAL( ds.columns( ).size( ), 0 );
  BOOST_CHECK_EQUAL( ds.neurons( ).size( ), 0 );

  BOOST_CHECK_EQUAL( ds.circuit( ).synapses( ).empty( ), true );

  DataSet const ds2;

  BOOST_CHECK_EQUAL( ds2.circuit( ).synapses( ).empty( ), true );
}

BOOST_AUTO_TEST_CASE( write_scene )
{

#define NSOL_SCENE_TEST_OUT "____nsol_scene_test_out.xml"

  DataSet ds;

  ds.loadXmlScene( NSOL_XML_SCENE_TEST_DATA );
  ds.writeXmlScene( NSOL_SCENE_TEST_OUT );
  ds.close( );

  BOOST_CHECK_EQUAL( ds.columns( ).size( ), 0 );
  BOOST_CHECK_EQUAL( ds.neurons( ).size( ), 0 );

  ds.loadXmlScene( NSOL_SCENE_TEST_OUT );
  checkScene( ds );
}

class TestDataSetLoader : public DataSet
{
public:
  bool hasMorphologies( void )
  {
    return !_morphologies.empty( );
  }
  bool hasNeurons( void )
  {
    return !_neurons.empty( );
  }
};

BOOST_AUTO_TEST_CASE( unload_scene )
{
  TestDataSetLoader tl;
  tl.loadXmlScene( NSOL_XML_SCENE_TEST_DATA );
  checkScene( tl );
  tl.close( );

  tl.unloadMorphologies( );

  BOOST_CHECK( !tl.hasMorphologies( ) );
  BOOST_CHECK( !tl.hasNeurons( ) );
}
