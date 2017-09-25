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

BOOST_AUTO_TEST_CASE( section_constructor )
{

  Section section;
  BOOST_CHECK( !section.neurite( ));
  BOOST_CHECK( !section.parent( ));
  BOOST_CHECK_EQUAL( section.nodes( ).size( ), 0 );

}

BOOST_AUTO_TEST_CASE( section_clone )
{
  // Construction of section and clone section
  Section section;
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
  SectionPtr cloneSection = section.clone( );
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

BOOST_AUTO_TEST_CASE( section_operators )
{
    // Construction of section and clone section
  Section section;
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
  SectionPtr section1 = section.clone( );
  SectionPtr section2 = section.clone( );
  section1->firstNode( node );
  section2->firstNode( node );

  section1->firstNode( )->point( ).x( ) = 1000.0f;
  section2->addNode( node );

  // Tests
  BOOST_CHECK( section == section );
  BOOST_CHECK( *section1 == *section1 );
  BOOST_CHECK( *section2 == *section2 );

  BOOST_CHECK( section != *section1 );
  BOOST_CHECK( section != *section2 );
  BOOST_CHECK( *section1 != *section2 );

}
