/**
 * @brief Test for class nsol::NodeWithProperties
 * @author Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
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

#define DEFAULT_POINT Vec3f( 0.0f, 0.0f, 0.0f )
#define DEFAULT_ID 0
#define DEFAULT_RADIUS 0.0f

BOOST_AUTO_TEST_CASE( nodeWithProperties_constructor )
{
  {
    NodeWithProperties node;

    BOOST_CHECK_EQUAL( node.point( ), DEFAULT_POINT );
    BOOST_CHECK_EQUAL( node.id( ), DEFAULT_ID );
    BOOST_CHECK_EQUAL( node.radius( ), DEFAULT_RADIUS );
  }
  {
    Node node( POINT );
    BOOST_CHECK_EQUAL( node.point( ), POINT );
    BOOST_CHECK_EQUAL( node.id( ), DEFAULT_ID );
    BOOST_CHECK_EQUAL( node.radius( ), DEFAULT_RADIUS );
  }
  {
    Node node( POINT, ID );
    BOOST_CHECK_EQUAL( node.point( ), POINT );
    BOOST_CHECK_EQUAL( node.id( ), ID );
    BOOST_CHECK_EQUAL( node.radius( ), DEFAULT_RADIUS );
  }
  {
    Node node( POINT, ID, RADIUS );
    BOOST_CHECK_EQUAL( node.point( ), POINT );
    BOOST_CHECK_EQUAL( node.id( ), ID );
    BOOST_CHECK_EQUAL( node.radius( ), RADIUS );
  }
}

BOOST_AUTO_TEST_CASE( nodeWithProperties_getters_setters )
{
  NodeWithProperties node;

  node.point( POINT );
  BOOST_CHECK_EQUAL( node.point( ), POINT );

  node.id( ) = ID;
  BOOST_CHECK_EQUAL( node.id( ), ID );

  node.radius( RADIUS );
  BOOST_CHECK_EQUAL( node.radius( ), RADIUS );
}

BOOST_AUTO_TEST_CASE( nodeWithProperties_properties )
{
  NodeWithProperties node;

#ifdef NSOL_WITH_FIRES

  BOOST_CHECK_EQUAL( node.properties( ), &node );

  node.properties()->registerFeature( "label", 3.5f );
  BOOST_CHECK(
      node.properties( )->getFeature( "label" ).value< float >( ) == 3.5f );

  node.properties( )->registerFeature( "label2", std::string( "hello" ));
    BOOST_CHECK(
      node.properties( )->getFeature( "label2" ).value< std::string >( ) ==
      std::string( "hello" ));

  std::cout << "Checked" << std::endl;
#else

  BOOST_CHECK( node.properites( ) == nullptr );


#endif
}

BOOST_AUTO_TEST_CASE( nodeWithProperties_create_clone )
{
  NodeWithProperties node1( POINT, ID, RADIUS );
#ifdef NSOL_WITH_FIRES

  node1.properties( )->registerFeature( "label", 3.5f );
  node1.properties( )->registerFeature( "label2", std::string( "hello" ));

#endif
  NodeWithPropertiesPtr node2 = node1.create( );

  BOOST_CHECK_EQUAL( node2->point( ), DEFAULT_POINT );
  BOOST_CHECK_EQUAL( node2->id( ), DEFAULT_ID );
  BOOST_CHECK_EQUAL( node2->radius( ), DEFAULT_RADIUS );

  NodeWithPropertiesPtr node3 = node1.clone( );

  BOOST_CHECK_EQUAL( node3->point( ), POINT );
  BOOST_CHECK_EQUAL( node3->id( ), ID );
  BOOST_CHECK_EQUAL( node3->radius( ), RADIUS );

#ifdef NSOL_WITH_FIRES

  BOOST_CHECK(
      node3->properties( )->getFeature( "label" ).value< float >( ) == 3.5f );
  BOOST_CHECK(
      node3->properties( )->getFeature( "label2" ).value< std::string >( )
        == "hello" );

#endif

  delete node2;
  delete node3;
}


