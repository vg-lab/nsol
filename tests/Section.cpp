/**
 * @file    Section.cpp
 * @brief   Test for class nsol::Section
 * @author  Raquel Jarillo <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */


#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"


using namespace nsol;


BOOST_AUTO_TEST_CASE( section_parent_neurites )
{
	Section section (new Section );

	// Adding parent Neurite at Section
	NeuritePtr neurite = new Neurite( );

	BOOST_CHECK_EQUAL( section.neurite( ), nullptr );

	section.neurite( neurite );
	BOOST_CHECK_EQUAL( section.neurite( ), neurite );

	// Adding parent Section at Section
	SectionPtr parent ( new Section );
	BOOST_CHECK_EQUAL( section.parent( ), nullptr );

	section.parent( parent );
	BOOST_CHECK_EQUAL( section.parent( ), parent );
}
BOOST_AUTO_TEST_CASE( section_children )
{
// TODO:
}
BOOST_AUTO_TEST_CASE( section_getters_setters )
{
// TODO:
}
