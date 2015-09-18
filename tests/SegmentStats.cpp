/**
 * @file    SegmentStats.cpp
 * @brief   Test for class nsol::SegmentStats
 * @author  Raquel Jarillo <r.jarillo@alumnos.urjc.es>
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

#define POINT2 Vec3f( 1.5f, 1.3f, 2.4f )
#define ID2 2
#define RADIUS2 4.2f

BOOST_AUTO_TEST_CASE( segment_stats_getStat)
{
	NodePtr begin;
	NodePtr end;

	BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
											SURFACE, begin, end), 0.0f );

	BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
											VOLUME, begin, end), 0.0f );

	BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
											LENGTH, begin, end), 0.0f );

	{
		begin.radius( RADIUS )
		end.radius( RADIUS2 );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 0.0f );
	}
	{
		begin.point( POINT );
		end.point( POINT2 );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 1.445f );
	}
	{
		begin.point( POINT );
		begin.radius( RADIUS );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 4.38f );
	}
	{
		begin.point( POINT );
		end.radius( RADIUS2 );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 181,37f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 242,60f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 4.38f );
	}
	{
		end.point( POINT2 );
		begin.radius( RADIUS );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 4.38f );
	}

}


