/**
 * @file    SynapseSomaToSoma.cpp
 * @brief   Test for class nsol::SynapseSomaToSoma
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( test_constructor_synapseSomaToSoma )
{
	// Create a synapse somatosomal
	nsol::SynapseSomaToSomaPtr  ssts(new nsol::SynapseSomaToSoma());

	// Check the type of the synapse
	BOOST_CHECK_EQUAL( ssts->synapseType( ), Synapse::SOMATOSOMAL );

	// Free dymanic memory used
	NSOL_DELETE_PTR( ssts );
}
