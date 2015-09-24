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



BOOST_AUTO_TEST_CASE( section_stats_getStat)
{
	// Create a section
	SectionCachedStats* section = new SectionCachedStats( );

	// Check without parent neurite of this section
	BOOST_CHECK_EQUAL( section->dirty( ), true);

	section->dirty() = false;
	BOOST_CHECK_EQUAL( section->dirty( ), false);

	section->setAndPropagateDirty ( 3 );
	BOOST_CHECK_EQUAL( section->dirty( ), true);

	// Check with parent neurite of this section
	NeuriteCachedStats* neurite ( new NeuriteCachedStats );
	section->neurite( neurite );

	neurite->dirty() = false;

	section->setAndPropagateDirty ( 3 );
	BOOST_CHECK_EQUAL( section->dirty( ), true);
	BOOST_CHECK_EQUAL( neurite->dirty( ), true);
}

// EOF
