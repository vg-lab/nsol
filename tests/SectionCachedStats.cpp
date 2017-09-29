/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
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

BOOST_AUTO_TEST_CASE( sectionCachedStats_constructor )
{
   SectionCachedStats* sectionCachedStats = new SectionCachedStats( );

   BOOST_CHECK_EQUAL( sectionCachedStats->id( ), 0 );
   BOOST_CHECK( sectionCachedStats->stats( ) != nullptr );

   // Free dymanic memory used
   NSOL_DELETE_PTR( sectionCachedStats );

}

BOOST_AUTO_TEST_CASE( sectionCachedStats_getStat )
{
   SectionCachedStats* sectionCachedStats = new SectionCachedStats( );

   BOOST_CHECK_EQUAL( sectionCachedStats->getStat( SectionStats::SURFACE ), 0.0f );

   sectionCachedStats->setAndPropagateDirty( );

   BOOST_CHECK_EQUAL( sectionCachedStats->dirty( 1 ), true );
   BOOST_CHECK_EQUAL( sectionCachedStats->getStat( SectionStats::SURFACE ), 0.0f );

   // Free dymanic memory used
   NSOL_DELETE_PTR( sectionCachedStats );
}

BOOST_AUTO_TEST_CASE( sectionCachedStats_setAndPropagateDirty )
{
   SectionCachedStats* sectionCachedStats = new SectionCachedStats( );

   BOOST_CHECK_EQUAL( sectionCachedStats->dirty( 1 ), true );

   sectionCachedStats->setAndPropagateDirty( 1 );

   NodePtr node( new Node );
   NodePtr node1( new Node );
   sectionCachedStats->addNode( node );
   sectionCachedStats->firstNode( node1 );

   BOOST_CHECK_EQUAL( sectionCachedStats->dirty( 2 ), true );

   // Free dymanic memory used
   NSOL_DELETE_PTR( sectionCachedStats );

}


