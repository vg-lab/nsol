/**
 * @file    Soma.cpp
 * @brief   Test for class nsol::Soma
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

#define CENTER Vec3f( 0.0f, 0.0f, 0.0f )
#define MAX_RADIUS 0.0f
#define MEAN_RADIUS 0.0f

BOOST_AUTO_TEST_CASE( soma_constructor )
{

  Soma soma;

  BOOST_CHECK_EQUAL( soma.nodes( ).size( ), 0 );
  BOOST_CHECK_EQUAL( soma.center( ), CENTER );
  BOOST_CHECK_EQUAL( soma.maxRadius( ), MAX_RADIUS );
  BOOST_CHECK_EQUAL( soma.meanRadius( ), MEAN_RADIUS );

}

BOOST_AUTO_TEST_CASE( soma_methods )
{

  Soma soma;
  soma.addNode( new Node( Vec3f( 0, 0, 0), 0, 1 ));
  soma.addNode( new Node( Vec3f( 2, 0, 0), 1, 1 ));

  BOOST_CHECK_EQUAL( soma.nodes( ).size( ), 2 );
  BOOST_CHECK_EQUAL( soma.center( ), Vec3f( 1, 0, 0 ));
  BOOST_CHECK_EQUAL( soma.maxRadius( ), 1.0f );
  BOOST_CHECK_EQUAL( soma.meanRadius( ), 1.0f );
}

BOOST_AUTO_TEST_CASE( soma_clone )
{

  Soma soma1;
  soma1.addNode( new Node( Vec3f( 0, 0, 0), 0, 1 ));
  soma1.addNode( new Node( Vec3f( 2, 0, 0), 1, 1 ));
  SomaPtr soma2 = soma1.clone( );

  BOOST_CHECK_EQUAL( soma1.nodes( ).size( ), soma2->nodes( ).size( ));
  for ( unsigned int i = 0; i < soma1.nodes( ).size( ); i++ )
  {
    BOOST_CHECK_EQUAL( soma1.nodes( )[i], soma2->nodes( )[i]);
  }
  BOOST_CHECK_EQUAL( soma1.center( ), soma2->center( ));
  BOOST_CHECK_EQUAL( soma1.maxRadius( ), soma2->maxRadius( ));
  BOOST_CHECK_EQUAL( soma1.meanRadius( ), soma2->meanRadius( ));
}

BOOST_AUTO_TEST_CASE( soma_operators )
{
  Soma soma1;
  soma1.addNode( new Node( Vec3f( 0, 0, 0), 0, 1 ));
  soma1.addNode( new Node( Vec3f( 2, 0, 0), 1, 1 ));
  Soma soma2 = *(soma1.clone( ));
  soma2.nodes( )[0]->point( ).x( ) = 8;
  Soma soma3 = *(soma1.clone( ));
  soma3.addNode( new Node( Vec3f( 4, 0, 0), 2, 1 ));

  BOOST_CHECK( soma1 == soma1 );
  BOOST_CHECK( soma2 == soma2 );
  BOOST_CHECK( soma3 == soma3 );

  BOOST_CHECK( soma1 != soma2 );
  BOOST_CHECK( soma1 != soma3 );
  BOOST_CHECK( soma2 != soma3 );
}
