/*
 * @brief   Test for class nsol::ObjectWithProperties
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

BOOST_AUTO_TEST_CASE( test_object_with_properties )
{
  nsol::Object o;
  BOOST_CHECK( o.properties( ) ==  nullptr );

  nsol::ObjectWithProperties owp1;
  nsol::ObjectPtr owp2 = new nsol::ObjectWithProperties;

#ifdef NSOL_WITH_FIRES

  BOOST_CHECK_EQUAL( owp1.properties( ), &owp1 );
  BOOST_CHECK_EQUAL( owp2->properties( ), owp2 );

  owp2->properties( )->registerFeature( "label", 3 );
  BOOST_CHECK_EQUAL(
    owp2->properties( )->getFeature( "label" ).value< int >( ), 3 );

#else
  BOOST_CHECK( owp1.properties( ) == 0 );
  BOOST_CHECK( owp2->properties( ) == 0 );
#endif

}


BOOST_AUTO_TEST_CASE( test_create_object_with_properties )
{
  nsol::ObjectWithProperties owp1;

#ifdef NSOL_WITH_FIRES

  nsol::ObjectPtr o2 = new nsol::Object;
  nsol::ObjectPtr o3 = o2->create( );

  nsol::ObjectPtr owp4 = new nsol::ObjectWithProperties;
  nsol::ObjectPtr owp5 = owp4->create( );

  nsol::ObjectWithPropertiesPtr owp6 =
    dynamic_cast< nsol::ObjectWithPropertiesPtr >( owp1.create( ));

  BOOST_CHECK( o2->properties( ) == 0 );
  BOOST_CHECK( o3->properties( ) == 0 );
  BOOST_CHECK( owp4->properties( ) != 0 );
  BOOST_CHECK( owp5->properties( ) != 0 );
  BOOST_CHECK( owp6->properties( ) != 0 );


  delete o2;
  delete o3;
  delete owp4;
  delete owp5;
  delete owp6;

#endif

}



BOOST_AUTO_TEST_CASE( test_node_with_properties )
{

  class Node : public nsol::Node, public nsol::ObjectWithProperties
  {
  };

  Node node;

#ifdef NSOL_WITH_FIRES

  BOOST_CHECK_EQUAL( node.properties( ), &node );

  node.properties( )->registerFeature( "label", 3.5f );
  BOOST_CHECK(
    node.properties( )->getFeature( "label" ).value< float >( ) ==
    3.5f );

  node.properties( )->registerFeature( "label2", std::string( "hello" ));
  BOOST_CHECK(
    node.properties( )->getFeature( "label2" ).value< std::string >( ) ==
    std::string( "hello" ));


#else

  BOOST_CHECK( node.properties( ) == nullptr );

#endif



}
