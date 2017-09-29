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

BOOST_AUTO_TEST_CASE( somaStats_constructor)
{
   SomaStats* somaStats = new SomaStats( );
   BOOST_CHECK_EQUAL( somaStats->center(), Vec3f(0.0f, 0.0f, 0.0f) );
   BOOST_CHECK_EQUAL( somaStats->maxRadius( ), 0.0f );
   BOOST_CHECK_EQUAL( somaStats->minRadius( ), 0.0f );
   BOOST_CHECK_EQUAL( somaStats->meanRadius( ), 0.0f );

   // Free dymanic memory used
   NSOL_DELETE_PTR( somaStats );

}

BOOST_AUTO_TEST_CASE( somaStats_getStat )
{
   SomaStats* somaStats = new SomaStats( );

   float result_surface = somaStats->getStat( SomaStats::SURFACE );
   float result_volume = somaStats->getStat( SomaStats::VOLUME );

   BOOST_CHECK_EQUAL( somaStats->center(), Vec3f(0.0f, 0.0f, 0.0f) );
   BOOST_CHECK_EQUAL( result_surface, 0.0f );
   BOOST_CHECK_EQUAL( result_volume, 0.0f );

   BOOST_CHECK( somaStats->stats( ) != nullptr );

   // Free dymanic memory used
   NSOL_DELETE_PTR( somaStats );

}

