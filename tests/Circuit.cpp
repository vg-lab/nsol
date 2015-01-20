/**
 * @file    Circuit.cpp
 * @brief   Test for class nsol::Circuit
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

void CheckNullMorphologicalValues( CircuitPtr cir )
{
	BOOST_CHECK_EQUAL( cir->numberOfColumns( ), 0 );
}

void CheckNoCircuits( CircuitPtr cir )
{
	BOOST_CHECK_EQUAL( cir->numberOfConnections( ), 0 );
}

BOOST_AUTO_TEST_CASE( test_empty_circuit )
{
	nsol::Circuit cir(new nsol::Circuit( ));

	// Check id equal to 0
	#define CIR_ID 2
	BOOST_CHECK_EQUAL( cir.id( ), 0 );

	cir.id( ) = CIR_ID;
	BOOST_CHECK_EQUAL( cir.id( ), CIR_ID );

	// Check morphological values are computed
    // to 0 without errors
	CheckNullMorphologicalValues( &cir );
	CheckNoCircuits( &cir );
}

BOOST_AUTO_TEST_CASE( test_circuit_constructors )
{
	nsol::Circuit cir0;
	BOOST_CHECK_EQUAL( cir0.id( ), 0 );

	nsol::Circuit cir1( 1 );
	BOOST_CHECK_EQUAL( cir1.id( ), 1 );

	nsol::Circuit cir1Copy( cir1 );
	BOOST_CHECK_EQUAL( cir1.id( ), 1 );
	BOOST_CHECK_EQUAL( cir1Copy.id( ), 1 );
	BOOST_CHECK_EQUAL( cir1Copy.id( ), cir1.id( ) );
}

BOOST_AUTO_TEST_CASE( test_circuit_change_id )
{
	nsol::Circuit cir;
	BOOST_CHECK_EQUAL( cir.id( ), 0 );

	cir.id( ) = 1;
	BOOST_CHECK_EQUAL( cir.id( ), 1 );
}

BOOST_AUTO_TEST_CASE( test_circuit_add_column_to_the_morphology )
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	// Create a column
	nsol::ColumnPtr col( new nsol::Column );

	// Add the column to the morphology of the circuit
	cir->addColumn( col );

	// Check if added ok
	BOOST_CHECK_EQUAL( cir->columns( ).size( ), 1);
	BOOST_CHECK_EQUAL( cir->columns( ).size( ),
	cir->numberOfColumns( ));

	// Check morphological values are still computed
	// to 0 without errors
	CheckNullMorphologicalValues( cir );
	CheckNoCircuits( cir );

	// Free dynamic memory used
	NSOL_DELETE_PTR( col );
	NSOL_DELETE_PTR( cir );
}

BOOST_AUTO_TEST_CASE( test_circuit_remove_column_of_the_morphology )
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	// Create two columns
	nsol::ColumnPtr col( new nsol::Column );
	nsol::ColumnPtr col2( new nsol::Column );

	// Add the column to the morphology of the circuit
	cir->addColumn( col );

	// Try to remove the one not added
	BOOST_CHECK_EQUAL( cir->removeColumn( col2 ), false);
	BOOST_CHECK_EQUAL( cir->columns( ).size( ), 1);
    BOOST_CHECK_EQUAL( cir->columns( ).size( ),
	                   cir->numberOfColumns( ));

    // Remove the one added
    BOOST_CHECK_EQUAL( cir->removeColumn( col ), true);
	BOOST_CHECK_EQUAL( cir->columns( ).size( ), 0);
	BOOST_CHECK_EQUAL( cir->columns( ).size( ),
					   cir->numberOfColumns( ));

	// Free dynamic memory used
	NSOL_DELETE_PTR( col2 );
	NSOL_DELETE_PTR( col );
	NSOL_DELETE_PTR( cir );
}

BOOST_AUTO_TEST_CASE( test_circuit_clear_columns )
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	#define NUM_COLS 10

	 // Create and add some columns
	 for ( int i = 0; i < NUM_COLS; i++ )
	   cir->addColumn( ColumnPtr( new nsol::Column ));

	 // Clear columns
     cir->clearColumns( );

     // Check number of columns inside of circuit
     BOOST_CHECK_EQUAL( cir->columns( ).size( ), 0);
     BOOST_CHECK_EQUAL( cir->columns( ).size( ),
    		 	 	    cir->numberOfColumns( ));

     // Check morphological values are still computed
     // to 0 without errors
     CheckNullMorphologicalValues( cir );
     CheckNoNeurons( cir );

     // Free dymanic memory used
     for ( auto colIt = cir->columns( ).begin( );
    		 colIt != cir->columns( ).end( ); colIt++ )
    	 NSOL_DELETE_PTR( ( * colIt ));

     NSOL_DELETE_PTR( cir );

}

BOOST_AUTO_TEST_CASE( test_circuit_operators )
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	// Compare empty columns
	nsol::CircuitPtr cir2( new nsol::Circuit( ));
	BOOST_CHECK_EQUAL( *cir == *cir2, true );
	BOOST_CHECK_EQUAL( *cir != *cir2, false );

	// Change id and compare
	cir2->id( ) = 2;
	BOOST_CHECK_EQUAL( *cir == *cir2, false );
	BOOST_CHECK_EQUAL( *cir != *cir2, true );

	// Assignment operator
	nsol::Circuit cir3 = *cir2 ;
	BOOST_CHECK_EQUAL( cir3 == *cir2, true );
	BOOST_CHECK_EQUAL( cir3 != *cir2, false );

	// Add columns and test if equal
	*cir2 = *cir;
	BOOST_CHECK_EQUAL( *cir == *cir2, true );
	BOOST_CHECK_EQUAL( *cir != *cir2, false );

	nsol::ColumnPtr col( new nsol::Column );
	nsol::ColumnPtr col2( new nsol::Column );

	cir->addColumn( col );
	cir->addColumn( col2 );

	BOOST_CHECK_EQUAL( *cir == *cir2, false );
	BOOST_CHECK_EQUAL( *cir != *cir2, true );

	// Test assignment op with columns
	*cir2 = *cir;
	BOOST_CHECK_EQUAL( *cir == *cir2, true );
	BOOST_CHECK_EQUAL( *cir != *cir2, false );

	// Free dymanic memory used
	NSOL_DELETE_PTR( col );
    NSOL_DELETE_PTR( col2 );
	NSOL_DELETE_PTR( cir );
	NSOL_DELETE_PTR( cir2 );

}

/*BOOST_AUTO_TEST_CASE( test_circuit_number_of_efferentConnectionsOfANeuron )
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	// Create a neuron
	NeuronPtr neuron( new Neuron( ));
	SynapsePtr synapse( new Synapse( ));

	// Add one efferent connection inside of circuit
	cir->addEfferentConnection( neuron, synapse);

	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ), 1 );
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfefferentConnections( neuron ) );

	// Remove the efferent connection
	NeuronPtr neuron2 ( new Neuron( ));
	BOOST_CHECK_EQUAL(cir->removeEfferentConnection( neuron2, SynapsePtr (new Synapse( ))),
					  false);
	BOOST_CHECK_EQUAL(cir->removeEfferentConnection( neuron, synapse),
					  true);

	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ), 0 );
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfefferentConnections( neuron ) );

	// Free dymanic memory used
	NSOL_DELETE_PTR( synapse );
	NSOL_DELETE_PTR( neuron );
	NSOL_DELETE_PTR( neuron2 );
	NSOL_DELETE_PTR( cir );

}

BOOST_AUTO_TEST_CASE( test_circuit_number_of_afferentConnectionsOfANeuron )
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	// Create a neuron
	NeuronPtr neuron( new Neuron( ));
	SynapsePtr synapse( new Synapse( ));

	// Add one afferent connection inside of circuit
	cir->addAfferentConnection( neuron, synapse);

	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ), 1 );
	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfAfferentConnections( neuron ) );

	// Remove the afferent connection
	NeuronPtr neuron2 ( new Neuron( ));
	BOOST_CHECK_EQUAL(cir->removeAfferentConnection( neuron2, SynapsePtr (new Synapse( ))),
					  false);
	BOOST_CHECK_EQUAL(cir->removeAfferentConnection( neuron, synapse),
					  true);

	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ), 0 );
	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfAfferentConnections( neuron ) );

	// Free dymanic memory used
	NSOL_DELETE_PTR( synapse );
	NSOL_DELETE_PTR( neuron );
	NSOL_DELETE_PTR( neuron2 );
	NSOL_DELETE_PTR( cir );

}

BOOST_AUTO_TEST_CASE( test_circuit_clear_eff_aff_connections )
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	// Create a neuron
	NeuronPtr neuron( new Neuron( ));

	#define NUM_EFF_CONN 10
	#define NUM_AFF_CONN 10

	// Create and add some efferent connections
	for ( int i = 0; i < NUM_EFF_CONN; i++ )
	  cir->addEfferentConnection( neuron, NeuronPtr( new nsol::Neuron ));

	// Create and add some afferent connections
	for ( int i = 0; i < NUM_AFF_CONN; i++ )
	  cir->addAfferentConnection( neuron, NeuronPtr( new nsol::Neuron ));


	// Clear efferent and afferent connections
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ), 10 );
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfEfferentConnections( neuron ) );

	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ), 10 );
	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfAfferentConnections( neuron ) );

	cir->clearEfferentConnections( neuron );

	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ), 0 );
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfEfferentConnections( neuron ) );

	cir->clearAfferentConnections( neuron );

	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ), 0 );
	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfAfferentConnections( neuron ) );

	// Free dymanic memory used
	NSOL_DELETE_PTR( neuron );
	NSOL_DELETE_PTR( cir );
}

BOOST_AUTO_TEST_CASE( test_circuit_clear_all_connections )
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	// Create two neurons
	NeuronPtr neuron( new Neuron( ));
	NeuronPtr neuron2( new Neuron( ));

	// Create and add some efferent connections
	for ( int i = 0; i < NUM_EFF_CONN; i++ )
	{
	  cir->addEfferentConnection( neuron, NeuronPtr( new nsol::Neuron ));
	  cir->addEfferentConnection( neuron2, NeuronPtr( new nsol::Neuron ));
	}

	// Create and add some afferent connections
	for ( int i = 0; i < NUM_AFF_CONN; i++ )
	{
	  cir->addAfferentConnection( neuron, NeuronPtr( new nsol::Neuron ));
	  cir->addAfferentConnection( neuron2, NeuronPtr( new nsol::Neuron ));
	}

	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ), 10 );
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfEfferentConnections( neuron ) );

	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ), 10 );
	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfAfferentConnections( neuron ) );

	BOOST_CHECK_EQUAL( cir->numberOfConnections( neuron ), 20 );

	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron2 ).size( ), 10 );
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron2 ).size( ),
					   cir->numberOfEfferentConnections( neuron2 ) );

	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron2 ).size( ), 10 );
	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron2 ).size( ),
					   cir->numberOfAfferentConnections( neuron2 ) );

	BOOST_CHECK_EQUAL( cir->numberOfConnections( neuron2 ), 20 );

	// Clear all the connections of one neuron
	cir->clearConnections( neuron );

	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ), 0 );
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfEfferentConnections( neuron ) );

	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ), 0 );
	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron ).size( ),
					   cir->numberOfAfferentConnections( neuron ) );

	BOOST_CHECK_EQUAL( cir->numberOfConnections( neuron ), 0 );

	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron2 ).size( ), 10 );
	BOOST_CHECK_EQUAL( cir->efferentConnectionsOfANeuron( neuron2 ).size( ),
					   cir->numberOfEfferentConnections( neuron2 ) );

	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron2 ).size( ), 10 );
	BOOST_CHECK_EQUAL( cir->afferentConnectionsOfANeuron( neuron2 ).size( ),
					   cir->numberOfAfferentConnections( neuron2 ) );

	BOOST_CHECK_EQUAL( cir->numberOfConnections( neuron2 ), 0 );

	// Clear all the connections of the circuit
	cir->clearAllConnections( );
	BOOST_CHECK_EQUAL( cir->efferentConnections( ).size( ), 0 );
	BOOST_CHECK_EQUAL( cir->afferentConnections( ).size( ), 0 );

	// Free dymanic memory used
	NSOL_DELETE_PTR( neuron2 );
	NSOL_DELETE_PTR( neuron );
	NSOL_DELETE_PTR( cir );

}
*/

