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
	NodePtr begin = new Node();
	NodePtr end = new Node();

	// Check with radius and points by default
	BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
											SURFACE, begin, end), 0.0f );

	BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
											VOLUME, begin, end), 0.0f );

	BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
											LENGTH, begin, end), 0.0f );

	// Check with values for the radius
	{
		begin->radius( RADIUS );
		end->radius( RADIUS2 );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 0.0f );
	}
	// Check with values for the points
	{
		begin->point( POINT );
		end->point( POINT2 );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 1.445f );
	}
	// Check with values for the begin node (radius and point)
	{
		begin->point( POINT );
		begin->radius( RADIUS );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 4.28f );
	}
	// Check with values for the point of beginNode and radius for endNode
	{
		begin->point( POINT );
		end->radius( RADIUS2 );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 112.889f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 237.067f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 4.28f );
	}
	// Check with values for the point of endNode and radius for beginNode
	{
		end->point( POINT2 );
		begin->radius( RADIUS );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 3.114f );
	}
	// Check with values for the point of endNode and radius for endNode
	{
		end->point( POINT2 );
		end->radius( RADIUS );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 128.95f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 82.13f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 3.114f );
	}

}

// EOF
