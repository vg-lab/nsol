/**
 * @file    Node.cpp
 * @brief   Test for class nsol::Node
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
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
