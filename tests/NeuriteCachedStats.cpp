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

BOOST_AUTO_TEST_CASE( neuriteCachedStats_constructors )
{
   NeuriteCachedStats* neuritecached = new NeuriteCachedStats( );
   BOOST_CHECK_EQUAL( neuritecached->neuriteType( ), Neurite::DENDRITE );
   BOOST_CHECK_EQUAL( neuritecached->dirty( 1 ), true );
}

BOOST_AUTO_TEST_CASE( neuriteCachedStats_firstSection )
{
   SectionPtr section( new Section );

   NeuriteCachedStats* neuritecached = new NeuriteCachedStats( );
   neuritecached->firstSection( section );

   Sections sections = neuritecached->sections( );
   BOOST_CHECK_EQUAL( sections.at(0)->id( ), section->id( ));
   BOOST_CHECK_EQUAL( sections.at(0)->id( ), 0 );

   SectionPtr section1( new Section );
   section1->id( 1 );

   neuritecached->firstSection( section1 );

   Sections sections1 = neuritecached->sections( );

   BOOST_CHECK_EQUAL( sections1.at( 0 )->id( ), section1->id( ));
   BOOST_CHECK_EQUAL( sections1.at( 0 )->id( ), 1 );

   // Free dymanic memory used
   NSOL_DELETE_PTR( section );
   NSOL_DELETE_PTR( section1 );
}

BOOST_AUTO_TEST_CASE( neuriteCachedStats_getStat )
{
  NeuriteStats* neuriteStats = new NeuriteStats( );
  NeuriteCachedStats* neuritecached = new NeuriteCachedStats( );

  NeuriteStats::TNeuriteStat stat = NeuriteStats::SURFACE;

  float result  = neuriteStats->getStat( stat );
  float result1 = neuritecached->getStat( stat );

  BOOST_CHECK_EQUAL( result, result1 );

  BOOST_CHECK_EQUAL( neuritecached->dirty( stat ), false );

  NeuriteStats::TNeuriteStat stat1 = NeuriteStats::SURFACE;
  TAggregation agg = MEAN;

  float result2 = neuriteStats->getStat( stat1, agg );
  float result3 = neuritecached->getStat( stat1, agg );

  BOOST_CHECK_EQUAL( result2, result3 );

}

BOOST_AUTO_TEST_CASE( neuriteCachedStats_setAndPropagateDirty )
{
   NeuriteCachedStats* neuritecached = new NeuriteCachedStats( );
   neuritecached->setAndPropagateDirty( 1 );

   BOOST_CHECK_EQUAL( neuritecached->dirty( 1 ), true );

   NeuriteCachedStats* neuritecached1 = new NeuriteCachedStats( );
   neuritecached1->setAndPropagateDirty( );

   BOOST_CHECK_EQUAL( neuritecached->dirty( 0 ), true );
}
