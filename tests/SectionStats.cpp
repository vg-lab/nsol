/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
 *          Cristian Rodríguez <cristian.rodriguez@urjc.es>
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


BOOST_AUTO_TEST_CASE( sectionStats_stats )
{
   SectionStats* sectionStat = new SectionStats();

   BOOST_CHECK_EQUAL(sectionStat->id(), 0);
   BOOST_CHECK_EQUAL( sectionStat->stats() != nullptr, true );

   // Free dymanic memory used
   NSOL_DELETE_PTR( sectionStat );
}

BOOST_AUTO_TEST_CASE( sectionStats_getStat )
{
   SectionStats* sectionStats = new SectionStats();

   // Aggregation STD_DEV & VARIANCE
   float result  = sectionStats->getStat( SectionStats::SURFACE,
                                          STD_DEV );
   float result1 = sectionStats->getStat( SectionStats::SURFACE,
                                          VARIANCE );
   BOOST_CHECK_EQUAL( result, result1 );

   // Aggregation MEAN & TOTAL
   float result2 = sectionStats->getStat( SectionStats::VOLUME, MEAN );
   float result3 = sectionStats->getStat( SectionStats::VOLUME, TOTAL );

   BOOST_CHECK( result2 == result3 );

   BOOST_CHECK( sectionStats->getStat( SectionStats::SURFACE,
                                          MIN ) == 0.0f );
   BOOST_CHECK( sectionStats->getStat( SectionStats::SURFACE,
                                          MAX ) == 0.0f );
   BOOST_CHECK( sectionStats->getStat( SectionStats::RADIUS,
                                           MEAN ) == 0.0f );

   // Free dymanic memory used
   NSOL_DELETE_PTR( sectionStats );
}
