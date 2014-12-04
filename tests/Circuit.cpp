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
	BOOST_CHECK_EQUAL( cir->numberOfColumns( false ), 0 );
}

void CheckNoCircuits( CircuitPtr cir )
{
	BOOST_CHECK_EQUAL( cir->numberOfConnections( ), 0 );
	BOOST_CHECK_EQUAL( cir->numberOfConnections( false ), 0 );

}

BOOST_AUTO_TEST_CASE( test_empty_circuit)
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
}

BOOST_AUTO_TEST_CASE( test_circuit_constructors )
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

	// Create a Column
	nsol::ColumnPtr col( new nsol::Column );

	// Add the column to the morphology of the circuit
	cir->addColumn( col );

	// Check if added ok
	BOOST_CHECK_EQUAL( cir->columns( ).size( ), 1);
	BOOST_CHECK_EQUAL( cir->columns( ).size( ),
	cir->numberOfColumns( ));

	// Check morphological values are still computed
	// to 0 without errors
	CheckNullMorphologicalValues( &cir );
	CheckNoCircuits( &cir );

	// Free dynamic memory used
}







