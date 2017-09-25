/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( test_empty_circuit )
{
    Circuit circuit;
    BOOST_CHECK_EQUAL( circuit.synapses( ).empty( ), true );
    BOOST_CHECK_EQUAL( circuit.synapses( Circuit::ALL ).empty( ), true );
    BOOST_CHECK_EQUAL( circuit.synapses( Circuit::PRESYNAPTICCONNECTIONS )
                       .empty( ), true );
    BOOST_CHECK_EQUAL( circuit.synapses( Circuit::POSTSYNAPTICCONNECTIONS )
                       .empty( ), true );
}

BOOST_AUTO_TEST_CASE( test_circuit_add_synapse )
{
    // Create a circuit
    CircuitPtr circuit( new Circuit );

    // Create a synapse
    SynapsePtr synapse( new Synapse );
    synapse->preSynapticNeuron( 1 );
    synapse->postSynapticNeuron( 2 );
    synapse->weight( 1.0f );

    // Add the synapse to the circuit
    circuit->addSynapse( synapse );

    // Check if added ok
    BOOST_CHECK_EQUAL( circuit->synapses( ).size( ), 1 );
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::ALL ).size( ),
                       circuit->numberOfSynapses( ) );
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::PRESYNAPTICCONNECTIONS ).size( ), 1 );
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::POSTSYNAPTICCONNECTIONS ).size( ), 1 );

    BOOST_CHECK_EQUAL( circuit->synapses( ).at( 0 )->preSynapticNeuron( ), 1 );
    BOOST_CHECK_EQUAL( circuit->synapses( ).at( 0 )->postSynapticNeuron( ), 2 );
    BOOST_CHECK_EQUAL( circuit->synapses( ).at( 0 )->weight( ), 1.0f );

    // Free dymanic memory used
    NSOL_DELETE_PTR( synapse );
    NSOL_DELETE_PTR( circuit );
}

BOOST_AUTO_TEST_CASE( test_circuit_clear_synapses )
{
    // Create a circuit
    CircuitPtr circuit( new Circuit );

    #define NUM_SYNAPSES 10

    // Create and add some synapses
    for( int i = 0; i < NUM_SYNAPSES; ++i )
    {
        SynapsePtr synapse( new Synapse );
        circuit->addSynapse( synapse );
    }

    BOOST_CHECK_EQUAL( circuit->synapses( ).size( ), 10);

    // Clear synapses
    circuit->clear( );

    BOOST_CHECK_EQUAL( circuit->synapses( ).size( ), 0);
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::PRESYNAPTICCONNECTIONS ).size( ), 0 );
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::POSTSYNAPTICCONNECTIONS ).size( ), 0 );
    BOOST_CHECK_EQUAL( circuit->numberOfSynapses( ), 0);

    // Free dymanic memory used
    NSOL_DELETE_PTR( circuit );

}

BOOST_AUTO_TEST_CASE( test_circuit_synapses )
{
    // Create a circuit
    CircuitPtr circuit( new Circuit );

    // Add first synapse
    SynapsePtr synapse1( new Synapse );
    synapse1->preSynapticNeuron( 1 );
    synapse1->postSynapticNeuron( 2 );
    synapse1->weight( 1.0f );

    circuit->addSynapse( synapse1 );

    BOOST_CHECK_EQUAL( circuit->synapses( ).at( 0 )->preSynapticNeuron( ), 1 );
    BOOST_CHECK_EQUAL( circuit->synapses( ).at( 0 )->postSynapticNeuron( ), 2 );
    BOOST_CHECK_EQUAL( circuit->synapses( ).at( 0 )->weight( ), 1.0f );

    // Add second synapse
    SynapsePtr synapse2( new Synapse );
    synapse2->preSynapticNeuron( 3 );
    synapse2->postSynapticNeuron( 4 );
    synapse2->weight( 2.0f );

    circuit->addSynapse( synapse2 );

    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::ALL).size( ), 2 );
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::PRESYNAPTICCONNECTIONS).size( ), 2 );
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::POSTSYNAPTICCONNECTIONS).size( ), 2 );

    std::set<SynapsePtr> synapses = circuit->synapses( 3, Circuit::PRESYNAPTICCONNECTIONS );
    BOOST_CHECK_EQUAL( synapses.size( ), 1 );
    BOOST_CHECK_EQUAL( synapses.find( synapse2 ) != synapses.end( ), true );
    BOOST_CHECK_EQUAL( (*(synapses.find( synapse2 )))->preSynapticNeuron( ), 3 );
    BOOST_CHECK_EQUAL( (*(synapses.find( synapse2 )))->postSynapticNeuron( ), 4 );
    BOOST_CHECK_EQUAL( (*(synapses.find( synapse2 )))->weight( ), 2.0f );

    std::set<SynapsePtr> synapses1 = circuit->synapses( 4, Circuit::POSTSYNAPTICCONNECTIONS );
    BOOST_CHECK_EQUAL( synapses1.size( ), 1 );
    BOOST_CHECK_EQUAL( synapses1.find( synapse2 ) != synapses1.end( ), true );
    BOOST_CHECK_EQUAL( (*(synapses.find( synapse2 )))->postSynapticNeuron( ), 4);

    // Add third synapse
    SynapsePtr synapse3( new Synapse );
    synapse3->preSynapticNeuron( 1 );
    synapse3->postSynapticNeuron( 4 );
    synapse3->weight( 3.0f );

    circuit->addSynapse( synapse3 );

    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::ALL ).size( ), 3 );
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::PRESYNAPTICCONNECTIONS ).size( ), 3 );
    BOOST_CHECK_EQUAL( circuit->synapses( Circuit::POSTSYNAPTICCONNECTIONS ).size( ), 3 );

    std::set<SynapsePtr> synapses2 = circuit->synapses( 4, Circuit::POSTSYNAPTICCONNECTIONS );
    BOOST_CHECK_EQUAL( synapses2.size( ), 2);
    BOOST_CHECK_EQUAL( synapses2.find( synapse2 ) != synapses2.end( ), true );
    BOOST_CHECK_EQUAL( synapses2.find( synapse3 ) != synapses2.end( ), true );
    BOOST_CHECK_EQUAL( (*(synapses2.find( synapse2 )))->postSynapticNeuron( ), 4);
    BOOST_CHECK_EQUAL( (*(synapses2.find( synapse3 )))->postSynapticNeuron( ), 4);

    std::set< uint32_t > gidsNeurons;
    gidsNeurons.insert( 2 );
    gidsNeurons.insert( 4 );

    BOOST_CHECK_EQUAL( circuit->synapses( gidsNeurons,
                                Circuit::POSTSYNAPTICCONNECTIONS ).size( ), 3 );

    // Free dymanic memory used
    NSOL_DELETE_PTR( synapse1 );
    NSOL_DELETE_PTR( synapse2 );
    NSOL_DELETE_PTR( synapse3 );
    NSOL_DELETE_PTR( circuit );
}


