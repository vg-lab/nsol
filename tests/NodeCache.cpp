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


BOOST_AUTO_TEST_CASE( nodecache_constructor )
{
  NeuriteStats* neuriteStats = new NeuriteStats( );

  BOOST_CHECK( neuriteStats->stats( ) == neuriteStats );

  BOOST_CHECK( neuriteStats->getStat( NeuriteStats::SURFACE, TAggregation::STD_DEV ) == 0.0f );
  BOOST_CHECK( neuriteStats->getStat( NeuriteStats::SURFACE, TAggregation::MIN ) == 0.0f );
  BOOST_CHECK( neuriteStats->getStat( NeuriteStats::SURFACE, TAggregation::MAX ) == 0.0f );
  BOOST_CHECK( neuriteStats->getStat( NeuriteStats::SURFACE, TAggregation::VARIANCE ) == 0.0f );
}