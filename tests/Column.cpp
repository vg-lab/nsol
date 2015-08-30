/**
 * @file    Column.cpp
 * @brief   Test for class nsol::Column
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

void CheckNullMorphologicalValues( ColumnPtr /* c */ )
{

  // BOOST_CHECK_EQUAL( c->meanSomaVolume( ), 0 );
  // BOOST_CHECK_EQUAL( c->meanSomaSurface( ), 0.0f );
  // BOOST_CHECK_EQUAL( c->meanDendriteVolume( ), 0.0f );
  // BOOST_CHECK_EQUAL( c->meanDendriteSurface( ), 0.0f );
  // BOOST_CHECK_EQUAL( c->maxSomaVolume( ), 0.0f );
  // BOOST_CHECK_EQUAL( c->maxSomaSurface( ), 0.0f );
  // BOOST_CHECK_EQUAL( c->maxDendriteVolume( ), 0.0f );
  // BOOST_CHECK_EQUAL( c->maxDendriteSurface( ), 0.0f );

}

void CheckNoNeurons( ColumnPtr c )
{
  BOOST_CHECK_EQUAL( c->numberOfNeurons(), 0 );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( false ), 0 );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( true, Neuron::PYRAMIDAL ), 0 );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( false, Neuron::PYRAMIDAL ), 0 );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( true, Neuron::INTER ), 0 );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( false, Neuron::INTER ), 0 );
}


BOOST_AUTO_TEST_CASE( test_empty_column )
{

  nsol::Column col;

  // Check id equal to 0
  #define COL_ID 115
  BOOST_CHECK_EQUAL( col.id( ), 0 );

  col.id( ) = COL_ID;
  BOOST_CHECK_EQUAL( col.id( ), COL_ID );

  // Check morphological values are computed
  // to 0 without errors
  CheckNullMorphologicalValues( & col );
  CheckNoNeurons( & col );

}

BOOST_AUTO_TEST_CASE( test_column_constructors )
{
  nsol::Column col0;
  BOOST_CHECK_EQUAL( col0.id( ), 0 );

  nsol::Column col1( 1 );
  BOOST_CHECK_EQUAL( col1.id( ), 1 );

  nsol::Column col1Copy( col1 );
  BOOST_CHECK_EQUAL( col1.id( ), 1 );
  BOOST_CHECK_EQUAL( col1Copy.id( ), 1 );
}

BOOST_AUTO_TEST_CASE( test_column_change_id )
{

    nsol::Column col;
    BOOST_CHECK_EQUAL( col.id( ), 0 );

    col.id( ) = 1;
    BOOST_CHECK_EQUAL( col.id( ), 1 );

}

BOOST_AUTO_TEST_CASE( test_column_add_minicolumn )
{

  // Create a column
  nsol::ColumnPtr col( new nsol::Column );

  // Create a minicolumn
  nsol::MiniColumnPtr mc( new nsol::MiniColumn ( col, 1 ));

  // Check if created right (maybe this should be in MiniColum test
  BOOST_CHECK_EQUAL( mc->id( ), 1 );
  BOOST_CHECK_EQUAL( mc->column( ), col );

  // Add the miniColumn to the column
  col->addMiniColumn( mc );

  // Check if added ok
  BOOST_CHECK_EQUAL( col->miniColumns( ).size( ), 1);
  BOOST_CHECK_EQUAL( col->miniColumns( ).size( ),
    col->numberOfMiniColumns( ));

  // Check morphological values are still computed
  // to 0 without errors
  CheckNullMorphologicalValues( col );
  CheckNoNeurons( col );

  // Free dymanic memory used
  NSOL_DELETE_PTR( mc );
  NSOL_DELETE_PTR( col );

}

BOOST_AUTO_TEST_CASE( test_column_remove_minicolumn )
{
  // Create a column
  nsol::ColumnPtr col( new nsol::Column );

  // Create two minicolumns
  MiniColumnPtr miniCol ( new MiniColumn ( col, 1 ));
  MiniColumnPtr miniCol2 ( new MiniColumn );

  // Add one of them to the column
  col->addMiniColumn( miniCol );

  // Try to remove the one not added
  BOOST_CHECK_EQUAL( col->removeMiniColumn( miniCol2 ), false );
  BOOST_CHECK_EQUAL( col->miniColumns( ).size( ), 1);
  BOOST_CHECK_EQUAL( col->miniColumns( ).size( ),
                     col->numberOfMiniColumns( ));

  // Remove the one added
  BOOST_CHECK_EQUAL( col->removeMiniColumn( miniCol ), true );
  BOOST_CHECK_EQUAL( col->miniColumns( ).size( ), 0);
  BOOST_CHECK_EQUAL( col->miniColumns( ).size( ),
                     col->numberOfMiniColumns( ));

  // Check morphological values are still computed
  // to 0 without errors
  CheckNullMorphologicalValues( col );
  CheckNoNeurons( col );

  // Free dymanic memory used
  NSOL_DELETE_PTR( miniCol);
  NSOL_DELETE_PTR( miniCol2);
  NSOL_DELETE_PTR( col );


}

BOOST_AUTO_TEST_CASE( test_column_clear_minicolumns )
{

  // Create a column
  nsol::ColumnPtr col( new nsol::Column );

  #define NUM_MINICOLS 10

  // Create and add some minicolumns
  for ( int i = 0; i < NUM_MINICOLS; ++i )
    col->addMiniColumn( MiniColumnPtr( new MiniColumn ( col, i )));

  // Clear minicolumns
  col->clearMiniColumns( );

  // Remove the one added
  BOOST_CHECK_EQUAL( col->miniColumns( ).size( ), 0);
  BOOST_CHECK_EQUAL( col->miniColumns( ).size( ),
                     col->numberOfMiniColumns( ));

  // Check morphological values are still computed
  // to 0 without errors
  CheckNullMorphologicalValues( col );
  CheckNoNeurons( col );

  // Free dymanic memory used
  for ( auto miniColIt = col->miniColumns( ).begin( );
        miniColIt != col->miniColumns( ).end( ); miniColIt++ )
    NSOL_DELETE_PTR( ( * miniColIt ));

  NSOL_DELETE_PTR( col );


}


BOOST_AUTO_TEST_CASE( test_column_operators )
{

  // Create a column
  nsol::ColumnPtr c( new nsol::Column );

  // Compare empty columns
  ColumnPtr c2( new Column( ));
  BOOST_CHECK_EQUAL( *c == *c2, true );
  BOOST_CHECK_EQUAL( *c != *c2, false );

  // Change id and compare
  c2->id( ) = 10;
  BOOST_CHECK_EQUAL( *c == *c2, false );
  BOOST_CHECK_EQUAL( *c != *c2, true );

  // Assignment operator
  Column c3 = *c2 ;
  BOOST_CHECK_EQUAL( c3 == *c2, true );
  BOOST_CHECK_EQUAL( c3 != *c2, false );

  // Add minicolumns and test if equal
  *c2 = *c;
  BOOST_CHECK_EQUAL( *c == *c2, true );
  BOOST_CHECK_EQUAL( *c != *c2, false );

  for ( int i = 0 ; i < NUM_MINICOLS ; ++i )
  {
    c->addMiniColumn( MiniColumnPtr( new MiniColumn ( c, i )));
  }

  BOOST_CHECK_EQUAL( *c == *c2, false );
  BOOST_CHECK_EQUAL( *c != *c2, true );

  // Test assignment op with minicols
  *c2 = *c;
  BOOST_CHECK_EQUAL( *c == *c2, true );
  BOOST_CHECK_EQUAL( *c != *c2, false );


  // Test copy constructor
  Column c4( c3 );
  BOOST_CHECK_EQUAL( *c == c4, false );
  BOOST_CHECK_EQUAL( *c != c4, true );

  Column c5( *c );
  BOOST_CHECK_EQUAL( *c == c5, true );
  BOOST_CHECK_EQUAL( *c != c5, false );


  // Free dymanic memory used
  for ( auto miniColIt = c->miniColumns( ).begin( );
	miniColIt != c->miniColumns( ).end( ); miniColIt++ )
    NSOL_DELETE_PTR( ( * miniColIt ));

  NSOL_DELETE_PTR( c );
  NSOL_DELETE_PTR( c2 );

}

BOOST_AUTO_TEST_CASE( test_column_number_of_neurons )
{

#define NUM_NEURONS_PYR_PER_LAYER 10
#define NUM_NEURONS_INT_PER_LAYER 8

  // Create a column
  nsol::ColumnPtr c( new nsol::Column );

  unsigned int gid = 0;
  for ( int i = 0 ; i < NUM_MINICOLS ; ++i )
  {
    c->addMiniColumn( MiniColumnPtr( new MiniColumn ( c, i )));
  }

  MiniColumns miniCols = c->miniColumns( );

  for ( MiniColumns::iterator mcIt = miniCols.begin( );
        mcIt != miniCols.end( ); ++mcIt )
  {
    for ( int l = 1 ; l < 7 ; ++l )
    {
      for ( int j = 0 ; j < NUM_NEURONS_PYR_PER_LAYER ; ++j )
      {
        ( *mcIt )->addNeuron(
          NeuronPtr( new Neuron( NeuronMorphologyPtr(
                                   new NeuronMorphology ( new Soma ) ),
                                 l, gid++,
                                 Matrix4_4f::IDENTITY,
                                 *mcIt, Neuron::PYRAMIDAL )));
      }
      for ( int j = 0 ; j < NUM_NEURONS_INT_PER_LAYER ; ++j )
      {
        ( *mcIt )->addNeuron(
          NeuronPtr( new Neuron( NeuronMorphologyPtr(
                                   new NeuronMorphology ( new Soma ) ),
                                 l, gid++,
                                 Matrix4_4f::IDENTITY,
                                 *mcIt, Neuron::INTER )));
      }
    }
  }

  BOOST_CHECK_EQUAL( c->numberOfNeurons( ), gid );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( ),
	     NUM_MINICOLS * 6 * ( NUM_NEURONS_PYR_PER_LAYER +
				  NUM_NEURONS_INT_PER_LAYER ) );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( false, Neuron::PYRAMIDAL ),
	     NUM_MINICOLS * 6 * NUM_NEURONS_PYR_PER_LAYER );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( false, Neuron::INTER ),
	     NUM_MINICOLS * 6 * NUM_NEURONS_INT_PER_LAYER );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( false, Neuron::PYRAMIDAL, 2 ),
	     NUM_MINICOLS * NUM_NEURONS_PYR_PER_LAYER );
  BOOST_CHECK_EQUAL( c->numberOfNeurons( false, Neuron::INTER , 2 ),
	     NUM_MINICOLS * NUM_NEURONS_INT_PER_LAYER );

  // Check morphological values are still computed
  // to 0 without errors
  CheckNullMorphologicalValues( c );

  // Free dymanic memory used
  for ( auto miniColIt = c->miniColumns( ).begin( );
	miniColIt != c->miniColumns( ).end( ); ++miniColIt )
  {

    for ( auto neuronIt = ( * miniColIt )->neurons( ).begin( );
	  neuronIt != ( * miniColIt )->neurons( ).end( ); ++neuronIt )
      NSOL_DELETE_PTR( ( * neuronIt ));

    NSOL_DELETE_PTR( ( * miniColIt ));
  }

  NSOL_DELETE_PTR( c );


}
