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

BOOST_AUTO_TEST_CASE( test_synapseSomaToSoma_operators)
{
	// Create a somatosoma synapse
	nsol::SynapseSomaToSomaPtr  s(new nsol::SynapseSomaToSoma());

	//Compare empty neuritetosoma synapses
	nsol::SynapseSomaToSomaPtr s2( new nsol::SynapseSomaToSoma( ));
	BOOST_CHECK_EQUAL( *s == *s2, true );
	BOOST_CHECK_EQUAL( *s != *s2, false );

	// Assignment operator
	SynapseSomaToSoma s3 = *s2;
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
	nsol::SynapseSomaToSoma s4( s3 );
	BOOST_CHECK_EQUAL( *s == s4, false );
	BOOST_CHECK_EQUAL( *s != s4, true );

	nsol::SynapseSomaToSoma s5( *s );
	BOOST_CHECK_EQUAL( *s == s5, true );
	BOOST_CHECK_EQUAL( *s != s5, false );

	// Free dymanic memory used
	NSOL_DELETE_PTR( s );
	NSOL_DELETE_PTR( s2 );


}
