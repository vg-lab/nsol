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



BOOST_AUTO_TEST_CASE( section_parent_neurites )
{
	// Create a section
	nsol::SectionPtr section = new nsol::Section();

	// Adding parent Neurite at Section
	nsol::NeuritePtr neurite = new nsol::Neurite( );

	BOOST_CHECK( section->neurite( ) == nullptr );

	section->neurite( neurite );
	BOOST_CHECK( section->neurite( ) == neurite );

	// Adding parent Section at Section
	nsol::SectionPtr parent ( new nsol::Section );
	BOOST_CHECK( section->parent( ) == nullptr );

	section->parent( parent );
	BOOST_CHECK( section->parent( ) == parent );

	// Free dynamic memory used
	NSOL_DELETE_PTR( neurite );
	NSOL_DELETE_PTR( parent );

	NSOL_DELETE_PTR( section );
}


BOOST_AUTO_TEST_CASE( section_children )
{
	// Create a section
	nsol::SectionPtr section = new nsol::Section ();

	#define NUM_SECTIONS  20

	// Check if the section has some child (section)
	 BOOST_CHECK_EQUAL( section->children().empty(), true );
	 BOOST_CHECK_EQUAL( section->children().size(), 0 );

	// Create and add some sections to the section
	  for ( int i = 0; i < NUM_SECTIONS; i++ )
	    section->addChild( nsol::SectionPtr(new nsol::Section));

		 BOOST_CHECK_EQUAL( section->children().empty(), false );
		 BOOST_CHECK_EQUAL( section->children().size(), 20 );

	 // Free dynamic memory used
	  for ( auto sectionIt = section->children( ).begin( );
			  sectionIt != section->children( ).end( ); sectionIt++ )
		NSOL_DELETE_PTR( ( * sectionIt ));

	  NSOL_DELETE_PTR( section );
}


BOOST_AUTO_TEST_CASE( section_nodes )
{
	// Create a section
	nsol::SectionPtr section = new nsol::Section ();

	#define NUM_NODES  20

	// Check if the section has some node
	BOOST_CHECK( section->firstNode() == nullptr );

	BOOST_CHECK_EQUAL( section->middleNodes().empty(), true );
	BOOST_CHECK_EQUAL( section->middleNodes().size(), 0 );

	BOOST_CHECK( section->lastNode() == nullptr );

	// Create and add some nodes
	nsol::NodePtr firstNode( new nsol::Node );
	section->firstNode( firstNode );
	BOOST_CHECK( section->firstNode() == firstNode );

	nsol::NodePtr lastNode(new nsol::Node );
	section->addNode( lastNode );
	BOOST_CHECK( section->lastNode() == lastNode );

	for ( int i = 0; i < NUM_NODES; i++ )
	    section->addNode( nsol::NodePtr( new nsol::Node ));

	BOOST_CHECK_EQUAL( section->middleNodes().empty(), false );
	BOOST_CHECK_EQUAL( section->middleNodes().size(), 22 );

	 // Free dynamic memory used
	  for ( auto nodeIt = section->middleNodes( ).begin( );
			  nodeIt != section->middleNodes( ).end( ); nodeIt++ )
		NSOL_DELETE_PTR( ( * nodeIt ));

	  NSOL_DELETE_PTR( firstNode );
	  NSOL_DELETE_PTR( section->lastNode() );
	  NSOL_DELETE_PTR( section );
}

// EOF
