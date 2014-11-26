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
	nsol::SynapseNeuriteToNeuritePtr  sdd(new nsol::SynapseNeuriteToNeurite(Synapse::DENDRODENDRITIC ));

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

	BOOST_CHECK_EQUAL( sats->preSynapticSegment( ), presynaptic_segment );
	BOOST_CHECK_EQUAL( sats->postSynapticSegment( ), postsynaptic_segment );

	// Free dymanic memory used
    NSOL_DELETE_PTR( sntn);
    NSOL_DELETE_PTR( sdd);
    NSOL_DELETE_PTR( saa );

}
