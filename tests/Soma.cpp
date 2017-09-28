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

#include <cmath>

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
  BOOST_CHECK_EQUAL( soma.minRadius( ), 0.0f );
  BOOST_CHECK_EQUAL( soma.meanRadius( ), MEAN_RADIUS );


  soma.center( CENTER );
  BOOST_CHECK_EQUAL( soma.center( ), CENTER );

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
    BOOST_CHECK( *(soma1.nodes( )[i]) == *(soma2->nodes( )[i]) );
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

BOOST_AUTO_TEST_CASE( soma_stats)
{
  Soma s;
  BOOST_CHECK_EQUAL( s.stats( ) == nullptr, true );
}
