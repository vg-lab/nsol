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

BOOST_AUTO_TEST_CASE( test_synapse_operators )
{
	// Create a synapse
	nsol::SynapsePtr s( new nsol::Synapse );

	// Compare empty synapses
	nsol::SynapsePtr s2( new nsol::Synapse( ));
	BOOST_CHECK_EQUAL( *s == *s2, true );
	BOOST_CHECK_EQUAL( *s != *s2, false );

	// Change the type and compare
	s2->synapseType() = Synapse::DENDRODENDRITIC;
	BOOST_CHECK_EQUAL( *s == *s2, false );
	BOOST_CHECK_EQUAL( *s != *s2, true );

	// Assignment operator
	Synapse s3 = *s2;
	BOOST_CHECK_EQUAL( s3 == *s2, true );
	BOOST_CHECK_EQUAL( s3 != *s2, false );

	// Add presynaptic neuron a postsynaptic neuron, and test if equal
    *s2 = *s;
    BOOST_CHECK_EQUAL( *s == *s2, true );
    BOOST_CHECK_EQUAL( *s != *s2, false );

    s->preSynapticNeuron(NeuronPtr( new nsol::Neuron( )));
    s->postSynapticNeuron(NeuronPtr( new nsol::Neuron( )));

    BOOST_CHECK_EQUAL( *s == *s2, false );
    BOOST_CHECK_EQUAL( *s != *s2, true );

    // Test assigment op with presynaptic and postsynaptic neurons
    *s2 = *s;
    BOOST_CHECK_EQUAL( *s == *s2, true );
    BOOST_CHECK_EQUAL( *s != *s2, false );

    // Test copy constructor
    nsol::Synapse s4( s3 );
    BOOST_CHECK_EQUAL( *s == s4, false );
    BOOST_CHECK_EQUAL( *s != s4, true );

    nsol::Synapse s5( *s );
    BOOST_CHECK_EQUAL( *s == s5, true );
    BOOST_CHECK_EQUAL( *s != s5, false );

    // Free dymanic memory used
    NSOL_DELETE_PTR( s );
    NSOL_DELETE_PTR( s2 );
}

