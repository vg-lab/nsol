/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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

#define POINT Vec3f( 1.2f, 2.3f, 3.4f )
#define ID 1
#define RADIUS 5.6f

BOOST_AUTO_TEST_CASE( node_constructor )
{
  {
    Node node;
    BOOST_CHECK_EQUAL( node.point( ), Vec3f( 0.0f, 0.0f, 0.0f ));
    BOOST_CHECK_EQUAL( node.id( ), 0 );
    BOOST_CHECK_EQUAL( node.radius( ), 0.0f );
  }
  {
    Node node( POINT );
    BOOST_CHECK_EQUAL( node.point( ), POINT );
    BOOST_CHECK_EQUAL( node.id( ), 0 );
    BOOST_CHECK_EQUAL( node.radius( ), 0.0f );
  }
  {
    Node node( POINT, ID );
    BOOST_CHECK_EQUAL( node.point( ), POINT );
    BOOST_CHECK_EQUAL( node.id( ), ID );
    BOOST_CHECK_EQUAL( node.radius( ), 0.0f );
  }
  {
    Node node( POINT, ID, RADIUS );
    BOOST_CHECK_EQUAL( node.point( ), POINT );
    BOOST_CHECK_EQUAL( node.id( ), ID );
    BOOST_CHECK_EQUAL( node.radius( ), RADIUS );
  }
}


BOOST_AUTO_TEST_CASE( node_getters_setters )
{

  Node node;

  node.point( POINT );
  BOOST_CHECK_EQUAL( node.point( ), POINT );

  node.id( ) = ID;
  BOOST_CHECK_EQUAL( node.id( ), ID );

  node.radius( RADIUS );
  BOOST_CHECK_EQUAL( node.radius( ), RADIUS );

}

BOOST_AUTO_TEST_CASE( node_clone )
{

  Node node( POINT, ID, RADIUS );
  NodePtr cloneNode = node.clone( );

  BOOST_CHECK( &node != cloneNode );
  BOOST_CHECK_EQUAL( cloneNode->point( ), POINT );
  BOOST_CHECK_EQUAL( cloneNode->id( ), ID );
  BOOST_CHECK_EQUAL( cloneNode->radius( ), RADIUS );

}

BOOST_AUTO_TEST_CASE( node_operators )
{

  Node node1;
  Node node2( POINT, ID, RADIUS );
  Node node3( POINT, ID, RADIUS );

  BOOST_CHECK( node1 == node1 );
  BOOST_CHECK( node2 == node2 );
  BOOST_CHECK( node2 == node3 );

  BOOST_CHECK( node1 != node2 );
  BOOST_CHECK( node1 != node3 );

  node3 = node1;
  BOOST_CHECK( node1 == node3 );

  node1 = node2;
  BOOST_CHECK( node1 == node2 );
  BOOST_CHECK( node1 != node3 );

}


BOOST_AUTO_TEST_CASE( node_parent_segments )
{

  // TODO

}
