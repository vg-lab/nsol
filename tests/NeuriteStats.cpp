/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Cristian Rodríguez <cristian.rodriguez@urjc.es>
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


BOOST_AUTO_TEST_CASE( neuritestats_constructor )
{
  NodeCached node;
  BOOST_CHECK_EQUAL( static_cast<Node>( node ).id( ), 0 );

  node.radius( 5.0f );
  BOOST_CHECK_EQUAL( static_cast<Node>( node ).radius( ), 5.0f );

  node.point( Vec3f( 0.0f, 1.0f, 0.0f ) );
  BOOST_CHECK( static_cast<Node>( node ).point( ) == Vec3f( 0.0f, 1.0f, 0.0f ) );

  node.setAndPropagateDirty( 0 );
  BOOST_CHECK( node.dirty( 0 ) );
  node.setAndPropagateDirty( );

  NeuriteStats* neuriteStats = new NeuriteStats();

  BOOST_CHECK_EQUAL( neuriteStats->stats() != nullptr, true );
}

BOOST_AUTO_TEST_CASE( neuritestats_getStat )
{
   NeuriteStats* neuriteStats = new NeuriteStats();

   float surface = neuriteStats->getStat( NeuriteStats::SURFACE, MEAN );
   BOOST_CHECK_EQUAL( surface, 0.0f );
}

