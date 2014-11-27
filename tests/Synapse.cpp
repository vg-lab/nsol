/**
 * @file    Synapse.cpp
 * @brief   Test for class nsol::Synapse
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( test_constructor_synapse)
{
	// Create a synapse by default
	nsol::SynapsePtr  synapse(new nsol::Synapse());

	// Check the type of the synapse
	BOOST_CHECK_EQUAL( synapse->synapseType( ), Synapse::AXODENDRITIC );

	// Add a presynaptic neuron and a postsynaptic neuron to the synapse
	nsol::NeuronPtr presynapticNeuron(new nsol::Neuron);
	nsol::NeuronPtr postsynapticNeuron(new nsol::Neuron);

	synapse->preSynapticNeuron( presynapticNeuron );
	synapse->postSynapticNeuron( postsynapticNeuron );

	BOOST_CHECK_EQUAL( synapse->preSynapticNeuron( ), presynapticNeuron );
	BOOST_CHECK_EQUAL( synapse->postSynapticNeuron( ), postsynapticNeuron );

	// Free dymanic memory used
	NSOL_DELETE_PTR( synapse );
}

