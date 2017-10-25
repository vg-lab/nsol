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

BOOST_AUTO_TEST_CASE( neuron_morphology_section_constructor )
{

  NeuronMorphologySection section;
  BOOST_CHECK( !section.neurite( ));
  BOOST_CHECK( !section.parent( ));
  BOOST_CHECK_EQUAL( section.nodes( ).size( ), 0 );

  BOOST_CHECK_EQUAL( section.id( ), 0 );

  const unsigned int newId  = 1;
  section.id( newId );
  BOOST_CHECK_EQUAL( section.id( ), newId );

  BOOST_CHECK_EQUAL( section.children( ).size( ), 0 );

  NeuronMorphologySection const section2;
  BOOST_CHECK_EQUAL( section2.children( ).size( ), 0 );

  BOOST_CHECK( section.firstNode( ) == nullptr );
  BOOST_CHECK( section.lastNode( ) == nullptr );

}

BOOST_AUTO_TEST_CASE( neuron_morphology_section_clone )
{
  // Construction of neuron morphology section and clone neuron
  // morphology section
  NeuronMorphologySection section;
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float radius = 1.0f;
  NodePtr node, cloneNode;
  for( unsigned int i = 0; i < 10; i++ )
  {
    node = new Node( Vec3f( x, y, z ), i+1, radius );
    section.addNode( node );
    x += 0.1f;
    y += 0.1f;
    z += 0.1f;
    radius += 0.1f;
  }
  node = new Node( Vec3f( x, y, z ), 0, radius );
  section.firstNode( node );
  NeuronMorphologySectionPtr cloneSection =
    dynamic_cast< NeuronMorphologySectionPtr >( section.clone( ));
  cloneSection->firstNode( node );

  // Tests
  BOOST_CHECK_EQUAL( section.nodes( ).size( ), cloneSection->nodes( ).size( ));
  for ( unsigned int i = 1; i < section.nodes( ).size( ); i++ )
  {
    node = section.nodes( )[i];
    cloneNode = cloneSection->nodes( )[i];

    BOOST_CHECK( node != cloneNode );
    BOOST_CHECK( *node == *cloneNode );
  }
}

BOOST_AUTO_TEST_CASE( neuron_morphology_section_stats)
{
  NeuronMorphologySection s;
  BOOST_CHECK( s.stats( ) == nullptr );

  NeuronMorphologySectionStats ss;
  BOOST_CHECK( ss.stats( ) == &ss );
}
