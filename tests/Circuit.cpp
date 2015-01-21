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
	nsol::Circuit cir;

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
     CheckNoCircuits( cir );

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

BOOST_AUTO_TEST_CASE( test_circuit_add_connections )
{
		// Create a circuit
		nsol::CircuitPtr cir( new nsol::Circuit );

		// Create a synapse
		nsol::SynapsePtr syn( new nsol::Synapse( ));

		// Add the synapse to the circuit
		cir->addConnection( syn );

		// Check if added ok
		BOOST_CHECK_EQUAL( cir->connections( ).size( ), 1);
		BOOST_CHECK_EQUAL( cir->connections( ).size( ),
		cir->numberOfConnections( ));

		// Free dynamic memory used
		NSOL_DELETE_PTR( syn );
		NSOL_DELETE_PTR( cir );
}

BOOST_AUTO_TEST_CASE( test_circuit_remove_connections )
{
		// Create a circuit
		nsol::CircuitPtr cir( new nsol::Circuit );

		// Create two columns
		nsol::SynapsePtr syn( new nsol::Synapse );
		nsol::SynapsePtr syn2( new nsol::Synapse );

		// Add the column to the morphology of the circuit
		cir->addConnection( syn );

		// Try to remove the one not added
		BOOST_CHECK_EQUAL( cir->removeConnection( syn2 ), false);
		BOOST_CHECK_EQUAL( cir->connections( ).size( ), 1);
	    BOOST_CHECK_EQUAL( cir->connections( ).size( ),
		                   cir->numberOfConnections( ));

	    // Remove the one added
	    BOOST_CHECK_EQUAL( cir->removeConnection( syn ), true);
		BOOST_CHECK_EQUAL( cir->connections( ).size( ), 0);
		BOOST_CHECK_EQUAL( cir->connections( ).size( ),
						   cir->numberOfConnections( ));

		// Free dynamic memory used
		NSOL_DELETE_PTR( syn2 );
		NSOL_DELETE_PTR( syn );
		NSOL_DELETE_PTR( cir );
}


BOOST_AUTO_TEST_CASE( test_circuit_clear_connections)
{
	// Create a circuit
	nsol::CircuitPtr cir( new nsol::Circuit );

	#define NUM_SYNS 10

	 // Create and add some connections (synapses)
	 for ( int i = 0; i < NUM_SYNS; i++ )
	   cir->addConnection( SynapsePtr( new nsol::Synapse ));

	 // Clear connections
     cir->clearConnections( );

     // Check number of synapses inside of circuit
     BOOST_CHECK_EQUAL( cir->connections( ).size( ), 0);
     BOOST_CHECK_EQUAL( cir->connections( ).size( ),
    		 	 	    cir->numberOfConnections( ));

     // Check morphological values are still computed
     // to 0 without errors
     CheckNullMorphologicalValues( cir );
     CheckNoCircuits( cir );

     // Free dymanic memory used
     for ( auto synIt = cir->connections( ).begin( );
    		 synIt != cir->connections( ).end( ); synIt++ )
    	 delete( * synIt );

     NSOL_DELETE_PTR( cir );

}



