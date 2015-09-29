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

		begin->radius( 0.0f );
		end->radius( 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 1.44568324f );
	}
	// Check with values for the begin node (radius and point)
	{
		begin->point( POINT );
		begin->radius( RADIUS );

		end->point(Vec3f(0.0f, 0.0f, 0.0f));
		end->radius(0.0f);

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 4.27668095f );
	}
	// Check with values for the point of beginNode and radius for endNode
	{
		begin->point( POINT );
		end->radius( RADIUS2 );

		end->point(Vec3f(0.0f, 0.0f, 0.0f));
		begin->radius(0.0f);

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 112.858948f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 237.003784f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 4.27668095f );
	}
	// Check with values for the point of endNode and radius for beginNode
	{
		end->point( POINT2 );
		begin->radius( RADIUS );

		begin->point(Vec3f(0.0f, 0.0f, 0.0f));
		end->radius(0.0f);

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 0.0f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 3.11448216f );
	}
	// Check with values for the point of endNode and radius for endNode
	{
		end->point( POINT2 );
		end->radius( RADIUS2 );

		begin->point(Vec3f(0.0f, 0.0f, 0.0f));
		begin->radius(0.0f);

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												SURFACE, begin, end), 82.1892471f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												VOLUME, begin, end), 172.597412f );

		BOOST_CHECK_EQUAL(SegmentStats::getStat(SegmentStats::/*TSegmentStat::*/
												LENGTH, begin, end), 3.11448216f );
	}

	// Free dynamic memory used
	NSOL_DELETE_PTR( begin );
	NSOL_DELETE_PTR( end );

}

// EOF
