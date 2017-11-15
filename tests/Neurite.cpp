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

BOOST_AUTO_TEST_CASE( neurite_constructor )
{

  BOOST_CHECK( true );

  Neurite* neurite = new Neurite( );

  BOOST_CHECK_EQUAL( neurite->neuriteType( ), 0 );
  BOOST_CHECK( !neurite->hasMorphology( ));
  BOOST_CHECK( !neurite->morphology( ));
  BOOST_CHECK( !neurite->firstSection( ));
  BOOST_CHECK_EQUAL( neurite->numBranches( ), 0 );
  BOOST_CHECK_EQUAL( neurite->numBifurcations( ), 0 );
}


BOOST_AUTO_TEST_CASE( neurite_type )
{
  {
    std::ostringstream out;
    out << Neurite::DENDRITE;
    BOOST_CHECK_EQUAL( out.str( ), "DENDRITE" );
  }
  {
    std::ostringstream out;
    out << Neurite::AXON;
    BOOST_CHECK_EQUAL( out.str( ), "AXON" );
  }
  {
    std::ostringstream out;
    out << Neurite::TNeuriteType( -100 );
    BOOST_CHECK_EQUAL( out.str( ), "UNDEFINED" );
  }
}

BOOST_AUTO_TEST_CASE( neurite_clone )
{

  NeuronMorphologySection section;
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float radius = 1.0f;
  NodePtr node;
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
  NeuronMorphologySection section1 =
    *( dynamic_cast< NeuronMorphologySectionPtr >( section.clone( )));
  section1.parent( &section );

  Neurite* neurite = new Neurite( );
  section.neurite( neurite );
  section1.neurite( neurite );
  neurite->firstSection( &section );
  Neurite* neurite1 = neurite->clone( );

  Sections originalSecs = neurite->sections( );
  Sections cloneSecs = neurite1->sections( );
  for ( unsigned int i = 0; i < originalSecs.size( ); i++ )
  {
    Nodes originalNodes = originalSecs[i]->nodes( );
    Nodes cloneNodes = cloneSecs[i]->nodes( );
    for ( unsigned int j = 0; j < originalNodes.size( ); j++ )
    {
      BOOST_CHECK( originalNodes[j] != cloneNodes[j] );
      BOOST_CHECK( *originalNodes[j] == *cloneNodes[j] );
    }
  }

}

BOOST_AUTO_TEST_CASE( neurite_operators )
{

  NeuronMorphologySection section;
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float radius = 1.0f;
  NodePtr node;
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
  NeuronMorphologySection section1 =
    *( dynamic_cast< NeuronMorphologySectionPtr >( section.clone( )));
  section1.parent( &section );
  NeuronMorphologySection section2 =
    *( dynamic_cast< NeuronMorphologySectionPtr >( section.clone( )));

  Neurite* neurite = new Neurite( );
  section.neurite( neurite );
  section1.neurite( neurite );
  section2.neurite( neurite );
  neurite->firstSection( &section );

  Neurite* neurite1 = neurite->clone( );

  section2.parent( &section1 );

  BOOST_CHECK( *neurite == *neurite );
  BOOST_CHECK( *neurite1 == *neurite1 );
  BOOST_CHECK( *neurite != *neurite1 );
}

BOOST_AUTO_TEST_CASE( neurite_stats)
{
  Neurite* neurite = new Neurite( );
  BOOST_CHECK( neurite->stats( ) == nullptr );
}
