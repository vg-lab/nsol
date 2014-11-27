/**
 * @file    SynapseNeuriteToSoma.cpp
 * @brief   Test for class nsol::SynapseNeuriteToSoma
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;


BOOST_AUTO_TEST_CASE( test_constructor_synapseNeuriteToSoma )
{
	// Create a synapse neurite to soma by default
	nsol::SynapseNeuriteToSomaPtr  snts(new nsol::SynapseNeuriteToSoma());

	// Check the type of the synapse
	BOOST_CHECK_EQUAL( snts->synapseType( ), Synapse::DENDROSOMATIC );

	// Create the type of the synapse axosomatic
	nsol::SynapseNeuriteToSomaPtr  sats(new nsol::SynapseNeuriteToSoma(Synapse::AXOSOMATIC));

	// Check the type of the synapse
	BOOST_CHECK_EQUAL( sats->synapseType( ), Synapse::AXOSOMATIC );

	// Add the presynaptic segment
	nsol::SegmentPtr presynaptic_segment(new nsol::Segment);

	sats->preSynapticSegment( presynaptic_segment );

	BOOST_CHECK_EQUAL( sats->preSynapticSegment( ), presynaptic_segment );

	// Free dymanic memory used
	NSOL_DELETE_PTR( snts );
	NSOL_DELETE_PTR( sats );

}
