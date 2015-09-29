/**
 * @file    SectionStats.cpp
 * @brief   Test for class nsol::SectionStats
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

BOOST_AUTO_TEST_CASE( section_stats_getStat)
{
	// Create a section
	SectionStats* sectionStats = new SectionStats();

	#define NUM_NODES  20

	// Check value of stat of a section without nodes
	BOOST_CHECK_EQUAL(sectionStats->getStat(SectionStats::SURFACE, TOTAL), 0.0f);

	// Check value of the stats of a section with one node
	NodePtr firstNode (new Node( POINT, ID, RADIUS ));
	sectionStats->firstNode( firstNode );
	float statValue0 = sectionStats->getStat(SectionStats::SURFACE, TOTAL);

	BOOST_CHECK_EQUAL( statValue0 , 0.0f);

	// Check value of the stats of a section with two nodes
	NodePtr lastNode (new Node( POINT2, ID2, RADIUS2 ) );
	sectionStats->addNode( lastNode );
	float statValue1 = sectionStats->getStat(SectionStats::SURFACE, TOTAL);

	BOOST_CHECK( statValue1 != 0.0f );
	BOOST_CHECK( statValue1 > statValue0 );

	// Check value of the stats of a section with more than two nodes
	Vec3f p   = POINT2+0.1f;
	int   id  = ID2+1;
	float r   = RADIUS2+0.1f;
	for ( int i = 0; i < NUM_NODES; i++ )
	{
	    sectionStats->addNode( nsol::NodePtr( new nsol::Node( p, id, r) ));
	    p += 0.1f; id++; r +=0.1f;
	}

	float statValue2 = sectionStats->getStat(SectionStats::SURFACE, TOTAL);

	BOOST_CHECK( statValue2 != 0.0f );
	BOOST_CHECK( statValue2 > statValue0 );
	BOOST_CHECK( statValue2 > statValue1 );

	// Check with other types of aggregation
	float value3 = sectionStats->getStat(SectionStats::SURFACE, STD_DEV);
	float value4 = sectionStats->getStat(SectionStats::SURFACE, VARIANCE);
	BOOST_CHECK_EQUAL( value3, ((float)sqrt(value4)) );

	float min = sectionStats->getStat(SectionStats::SURFACE, MIN);
	float max = sectionStats->getStat(SectionStats::SURFACE, MAX);
	BOOST_CHECK( max > min );

	 // Free dynamic memory used
	  for ( auto nodeIt = sectionStats->middleNodes( ).begin( );
			  nodeIt != sectionStats->middleNodes( ).end( ); nodeIt++ )
		NSOL_DELETE_PTR( ( * nodeIt ));

	  NSOL_DELETE_PTR( firstNode );
	  NSOL_DELETE_PTR( sectionStats->lastNode() );
	  NSOL_DELETE_PTR( sectionStats );
}

// EOF

