/**
 * @file    SectionCachedStats.cpp
 * @brief   Test for class nsol::SectionCachedStats
 * @author  Raquel Jarillo <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;


  typedef enum
  {
    TEST_CACHED_PROPERTY1 = 0,
    TEST_CACHED_PROPERTY2,
    TEST_CACHED_PROPERTY3
  } TCachedValues;

BOOST_AUTO_TEST_CASE( section_set_and_propagate_dirty )
{

	// Create a section
	SectionCachedStats* section = new SectionCachedStats( );

	// Cache a value for TEST_CACHED_PROPERTY1
	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY1 ), true);

	section->cacheValue( TEST_CACHED_PROPERTY1, 3.4f );
	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY1 ), false);

	section->setAndPropagateDirty ( TEST_CACHED_PROPERTY1 );
	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY1 ), true);

	// Propagate changes to parent neurite of this section with id
	NeuriteCachedStats* neurite ( new NeuriteCachedStats );
	section->neurite( neurite );

	neurite->cacheValue( TEST_CACHED_PROPERTY1, 3.4f );
	section->cacheValue( TEST_CACHED_PROPERTY1, 3.4f );

	section->setAndPropagateDirty ( TEST_CACHED_PROPERTY1 );
	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY1 ), true);
	BOOST_CHECK_EQUAL( neurite->Cached::dirty( TEST_CACHED_PROPERTY1 ), true);

	// Free dynamic memory used
	NSOL_DELETE_PTR( neurite );
	NSOL_DELETE_PTR( section );
}


BOOST_AUTO_TEST_CASE( section_add_nodes)
{
	// Create a section
	SectionCachedStats* section = new SectionCachedStats( );

	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY2 ), true);
	BOOST_CHECK( section->Section::firstNode( ) == nullptr);
	BOOST_CHECK_EQUAL( section->Section::middleNodes( ).empty(), true);
	BOOST_CHECK( section->Section::lastNode( ) == nullptr);

	// Adding nodes to the section and propagating changes
	// Adding firstNode
	NodePtr firstNode = new Node();

	section->cacheValue( TEST_CACHED_PROPERTY2, 3.4f );
	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY2 ), false);

	section->firstNode( firstNode );
	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY2 ), false);
	BOOST_CHECK( section->Section::firstNode( ) != nullptr);
	BOOST_CHECK( section->Section::firstNode( ) == firstNode);

	// Adding lastNode
	NodePtr lastNode = new Node();

	section->cacheValue( TEST_CACHED_PROPERTY3, 2.0f );
	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY3 ), false);

	section->addNode( lastNode );
	BOOST_CHECK_EQUAL( section->Cached::dirty( TEST_CACHED_PROPERTY3 ), true);
	BOOST_CHECK( section->Section::lastNode( ) != nullptr);
	BOOST_CHECK( section->Section::lastNode( ) == lastNode);

	// Free dynamic memory used
	NSOL_DELETE_PTR( firstNode );
	NSOL_DELETE_PTR( lastNode );
	NSOL_DELETE_PTR( section );
}


BOOST_AUTO_TEST_CASE( section_get_stat)
{
	// Create a section
	SectionCachedStats* section = new SectionCachedStats( );

	BOOST_CHECK_EQUAL( section->Cached::dirty(SectionStats::VOLUME), true);

	float valueStat = section->getStat(SectionStats::VOLUME);

	BOOST_CHECK_EQUAL( section->Cached::dirty(SectionStats::VOLUME), false);
	BOOST_CHECK_EQUAL( section->getStat(SectionStats::VOLUME), valueStat);

	// Free dynamic memory used
	NSOL_DELETE_PTR( section );
}

// EOF
