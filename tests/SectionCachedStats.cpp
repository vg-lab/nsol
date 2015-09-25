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



BOOST_AUTO_TEST_CASE( section_set_and_propagate_dirty)
{
	// Create a section
	SectionCachedStats* section = new SectionCachedStats( );

	// Check without parent neurite of this section
	BOOST_CHECK_EQUAL( section->dirty( ), true);

	section->dirty() = false;
	BOOST_CHECK_EQUAL( section->dirty( ), false);

	section->setAndPropagateDirty ( );
	BOOST_CHECK_EQUAL( section->dirty( ), true);

	// Propagate changes to parent neurite of this section with id
	NeuriteCachedStats* neurite ( new NeuriteCachedStats );
	section->neurite( neurite );

	neurite->dirty() = false;
	section->dirty() = false;

	section->setAndPropagateDirty ( 5 );
	BOOST_CHECK_EQUAL( section->dirty( ), true);
	BOOST_CHECK_EQUAL( neurite->dirty( ), true);

	// Free dynamic memory used
	NSOL_DELETE_PTR( neurite );
	NSOL_DELETE_PTR( section );
}


BOOST_AUTO_TEST_CASE( section_add_nodes)
{
	// Create a section
	SectionCachedStats* section = new SectionCachedStats( );

	BOOST_CHECK_EQUAL( section->dirty( ), true);
	BOOST_CHECK( section->firsNode( ) == nullptr);
	BOOST_CHECK_EQUAL( section->middleNodes( ).empty(), true);
	BOOST_CHECK( section->lastNode( ) == nullptr);

	// Adding nodes to the section and propagating changes
	// Adding firstNode
	NodePtr firstNode = new Node();

	section->dirty() = false;
	BOOST_CHECK_EQUAL( section->dirty( ), false);

	section->firstNode( firstNode );
	BOOST_CHECK_EQUAL( section->dirty( ), true);
	BOOST_CHECK( section->firsNode( ) != nullptr);
	BOOST_CHECK( section->firsNode( ) == firstNode);

	// Adding lastNode
	NodePtr lastNode = new Node();

	section->dirty() = false;
	BOOST_CHECK_EQUAL( section->dirty( ), false);

	section->addNode( lastNode );
	BOOST_CHECK_EQUAL( section->dirty( ), true);
	BOOST_CHECK( section->lastNode( ) != nullptr);
	BOOST_CHECK( section->lastNode( ) == lastNode);

	// Free dynamic memory used
	NSOL_DELETE_PTR( firsNode );
	NSOL_DELETE_PTR( lastNode );
	NSOL_DELETE_PTR( section );
}


BOOST_AUTO_TEST_CASE( section_get_stat)
{
	// Create a section
	SectionCachedStats* section = new SectionCachedStats( );

	BOOST_CHECK_EQUAL( section->dirty(SectionStats::VOLUME), true);

	float valueStat = section->getStat(SectionStats::VOLUME);

	BOOST_CHECK_EQUAL( section->dirty(SectionStats::VOLUME), false);
	BOOST_CHECK_EQUAL( section->getStat(SectionStats::VOLUME), value);

	// Free dynamic memory used
	NSOL_DELETE_PTR( section );
}

// EOF
