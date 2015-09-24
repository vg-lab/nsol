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



BOOST_AUTO_TEST_CASE( section_stats_getStat)
{
	// Create a section
	SectionStats* sectionStats = new SectionStats();

	#define NUM_NODES  20

	// Check value of stat of a section without nodes
	BOOST_CHECK_EQUAL(sectionStats->getStat(SectionStats::SURFACE, TOTAL), 0.0f);

	// Check value of the stats of a section with one node
	NodePtr firstNode (new Node );
	sectionStats->firstNode( firstNode );
	float statValue0 = sectionStats->getStat(SectionStats::SURFACE, TOTAL);

	BOOST_CHECK_EQUAL( statValue0 , 0.0f);

	// Check value of the stats of a section with two nodes
	NodePtr lastNode (new Node );
	sectionStats->addNode( lastNode );
	float statValue1 = sectionStats->getStat(SectionStats::SURFACE, TOTAL);

	BOOST_CHECK( statValue1 != 0.0f );
	BOOST_CHECK( statValue1 > statValue0 );

	// Check value of the stats of a section with more than two nodes
	for ( int i = 0; i < NUM_NODES; i++ )
	    sectionStats->addNode( nsol::NodePtr( new nsol::Node ));

	float statValue2 = sectionStats->getStat(SectionStats::SURFACE, TOTAL);

	BOOST_CHECK( statValue2 != 0.0f );
	BOOST_CHECK( statValue2 > statValue0 );
	BOOST_CHECK( statValue2 > statValue1 );

	// Check with other types of aggregation
	float value3 = sectionStats->getStat(SectionStats::SURFACE, STD_DEV);
	float value4 = sectionStats->getStat(SectionStats::SURFACE, VARIANCE);
	BOOST_CHECK_EQUAL( value3, sqrt(value4) );

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

