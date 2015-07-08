/**
 * @file    SynapseNeuriteToNeurite.cpp
 * @brief   Test for class nsol::SynapseNeuriteToNeurite
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;


BOOST_AUTO_TEST_CASE( test_constructor_synapseNeuriteToNeurite )
{
	// Create a synapse neurite to neurite by default
	nsol::SynapseNeuriteToNeuritePtr  sntn(new nsol::SynapseNeuriteToNeurite());

	// Check the type of the synapse
	BOOST_CHECK_EQUAL( sntn->synapseType( ), Synapse::AXODENDRITIC );

	// Create a synapse dendrodendritic

	nsol::SynapseNeuriteToNeuritePtr sdd(new nsol::SynapseNeuriteToNeurite(Synapse::DENDRODENDRITIC));

	// Check the type of the synapse
	BOOST_CHECK_EQUAL( sdd->synapseType( ), Synapse::DENDRODENDRITIC );

	// Create a synapse axoaxonic
	nsol::SynapseNeuriteToNeuritePtr  saa(new nsol::SynapseNeuriteToNeurite(Synapse::AXOAXONIC ));

	// Check the type of the synapse
	BOOST_CHECK_EQUAL( saa->synapseType( ), Synapse::AXOAXONIC );

	// Add presynaptic segment and postsynaptic segment to the synapse
	nsol::SegmentPtr presynaptic_segment(new nsol::Segment);
	nsol::SegmentPtr postsynaptic_segment(new nsol::Segment);

	saa->preSynapticSegment( presynaptic_segment );
	saa->postSynapticSegment( postsynaptic_segment );

	BOOST_CHECK_EQUAL( saa->preSynapticSegment( ), presynaptic_segment );
	BOOST_CHECK_EQUAL( saa->postSynapticSegment( ), postsynaptic_segment );

	// Free dymanic memory used
    NSOL_DELETE_PTR( sntn);
    NSOL_DELETE_PTR( sdd);
    NSOL_DELETE_PTR( saa );

}

BOOST_AUTO_TEST_CASE( test_synapseNeuriteToNeurite_operators)
{
	// Create a neuritetoneurite synsapse
	nsol::SynapseNeuriteToNeuritePtr  s(new nsol::SynapseNeuriteToNeurite());

	//Compare empty neuritetoneurite synsapses
	nsol::SynapseNeuriteToNeuritePtr s2( new nsol::SynapseNeuriteToNeurite( ));
	BOOST_CHECK_EQUAL( *s == *s2, true );
	BOOST_CHECK_EQUAL( *s != *s2, false );

	// Change the type and compare
	s2->synapseType() = Synapse::DENDRODENDRITIC;
	BOOST_CHECK_EQUAL( *s == *s2, false );
	BOOST_CHECK_EQUAL( *s != *s2, true );

	// Assignment operator
	SynapseNeuriteToNeurite s3 = *s2;
	BOOST_CHECK_EQUAL( s3 == *s2, true );
	BOOST_CHECK_EQUAL( s3 != *s2, false );

	// Add presynaptic segment and postsynaptic segment, and test if equal
    *s2 = *s;
    BOOST_CHECK_EQUAL( *s == *s2, true );
    BOOST_CHECK_EQUAL( *s != *s2, false );

    s->preSynapticSegment(SegmentPtr( new nsol::Segment( )));
    s->postSynapticSegment(SegmentPtr( new nsol::Segment( )));

    BOOST_CHECK_EQUAL( *s == *s2, false );
    BOOST_CHECK_EQUAL( *s != *s2, true );

    // Test assigment op with presynaptic and postsynaptic segments
    *s2 = *s;
    BOOST_CHECK_EQUAL( *s == *s2, true );
    BOOST_CHECK_EQUAL( *s != *s2, false );

    // Test copy constructor
    nsol::SynapseNeuriteToNeurite s4( s3 );
    BOOST_CHECK_EQUAL( *s == s4, false );
    BOOST_CHECK_EQUAL( *s != s4, true );

    nsol::SynapseNeuriteToNeurite s5( *s );
    BOOST_CHECK_EQUAL( *s == s5, true );
    BOOST_CHECK_EQUAL( *s != s5, false );

	// Free dymanic memory used
	NSOL_DELETE_PTR( s );
	NSOL_DELETE_PTR( s2 );
}

