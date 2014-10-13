#ifndef __NSOL_COLUMNTEST__
#define __NSOL_COLUMNTEST__

#include <limits.h>
#include <gtest/gtest.h>

#include <nsol/nsol.h>

using namespace nsol;


void CheckNullMorphologicalValues( ColumnPtr c )
{

  ASSERT_EQ( c->meanSomaVolume( ), 0 );
  ASSERT_EQ( c->meanSomaSurface( ), 0.0f );
  ASSERT_EQ( c->meanDendriteVolume( ), 0.0f );
  ASSERT_EQ( c->meanDendriteSurface( ), 0.0f );
  ASSERT_EQ( c->maxSomaVolume( ), 0.0f );
  ASSERT_EQ( c->maxSomaSurface( ), 0.0f );
  ASSERT_EQ( c->maxDendriteVolume( ), 0.0f );
  ASSERT_EQ( c->maxDendriteSurface( ), 0.0f );


}

void CheckNoNeurons( ColumnPtr c )
{
  ASSERT_EQ( c->numberOfNeurons(), 0 );
  ASSERT_EQ( c->numberOfNeurons( false ), 0 );
  ASSERT_EQ( c->numberOfNeurons( true, Neuron::PYRAMIDAL ), 0 );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::PYRAMIDAL ), 0 );
  ASSERT_EQ( c->numberOfNeurons( true, Neuron::INTER ), 0 );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::INTER ), 0 );
}

class ColumnTest : public ::testing::Test {
 
protected:

  ColumnPtr c;

  
  ColumnTest( )
    : c( new Column )
  {
    // You can do set-up work for each test here. 
    c->id( ) = 0;  
  }

  virtual ~ColumnTest() 
  {
    // You can do clean-up work that doesn't throw exceptions here.
  }


  virtual void SetUp() 
  {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() 
  {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(ColumnTest, emptyColumn) 
{
  // Check id equal to 0
  #define COL_ID 115
  ASSERT_EQ( c->id( ), 0 );
  c->id( ) = COL_ID;
  ASSERT_EQ( c->id( ), COL_ID );

  // Check morphological values are computed 
  // to 0 without errors
  CheckNullMorphologicalValues( c );
  CheckNoNeurons( c );

}

TEST_F(ColumnTest, addMiniColumn) 
{

  // Create a minicolumn
  MiniColumnPtr mc ( new MiniColumn ( c, 1 ));

  // Check if created right (maybe this should be in MiniColum test
  ASSERT_EQ( mc->id( ), 1 );
  ASSERT_EQ( mc->column( ), c );

  // Add the miniColumn to the column
  c->addMiniColumn( mc );

  // Check if added ok
  ASSERT_EQ( c->miniColumns( ).size( ), 1);
  ASSERT_EQ( c->miniColumns( ).size( ), c->numberOfMiniColumns( ));

  // Check morphological values are still computed 
  // to 0 without errors
  CheckNullMorphologicalValues( c );
  CheckNoNeurons( c );

}

TEST_F(ColumnTest, removeMiniColumn) 
{
  
  // Create two minicolumns
  MiniColumnPtr mc ( new MiniColumn ( c, 1 ));
  MiniColumnPtr mc2 ( new MiniColumn );
  
  // Add one of them to the column
  c->addMiniColumn( mc );

  // Try to remove the one not added 
  ASSERT_EQ( c->removeMiniColumn( mc2 ), false );
  ASSERT_EQ( c->miniColumns( ).size( ), 1);
  ASSERT_EQ( c->miniColumns( ).size( ), c->numberOfMiniColumns( ));

  // Remove the one added
  ASSERT_EQ( c->removeMiniColumn( mc ), true );
  ASSERT_EQ( c->miniColumns( ).size( ), 0);
  ASSERT_EQ( c->miniColumns( ).size( ), c->numberOfMiniColumns( ));

  // Check morphological values are still computed 
  // to 0 without errors
  CheckNullMorphologicalValues( c );
  CheckNoNeurons( c );

}


TEST_F(ColumnTest, clearMiniColumns) 
{
  
  #define NUM_MINICOLS 10

  // Create and add some minicolumns
  for ( int i = 0; i < NUM_MINICOLS; i++ ) 
    c->addMiniColumn( MiniColumnPtr( new MiniColumn ( c, i )));
  
  // Clear minicolumns
  c->clearMiniColumns( );

  // Remove the one added
  ASSERT_EQ( c->miniColumns( ).size( ), 0);
  ASSERT_EQ( c->miniColumns( ).size( ), c->numberOfMiniColumns( ));

  // Check morphological values are still computed 
  // to 0 without errors
  CheckNullMorphologicalValues( c );
  CheckNoNeurons( c );

}

TEST_F( ColumnTest, operators )
{

  // Compare empty columns
  ColumnPtr c2( new Column( ));
  ASSERT_EQ( *c == *c2, true );
  ASSERT_EQ( *c != *c2, false );

  // Change id and compare
  c2->id( ) = 10;
  ASSERT_EQ( *c == *c2, false );
  ASSERT_EQ( *c != *c2, true );

  // Assignment operator
  Column c3 = *c2 ;
  ASSERT_EQ( c3 == *c2, true );
  ASSERT_EQ( c3 != *c2, false );

  // Add minicolumns and test if equal
  *c2 = *c;
  ASSERT_EQ( *c == *c2, true );
  ASSERT_EQ( *c != *c2, false );

  for ( int i = 0 ; i < NUM_MINICOLS ; i++ )
  {
    c->addMiniColumn( MiniColumnPtr( new MiniColumn ( c, i )));
  }

  ASSERT_EQ( *c == *c2, false );
  ASSERT_EQ( *c != *c2, true );

  // Test assignment op with minicols
  *c2 = *c;
  ASSERT_EQ( *c == *c2, true );
  ASSERT_EQ( *c != *c2, false );


  // Test copy constructor
  Column c4( c3 );
  ASSERT_EQ( *c == c4, false );
  ASSERT_EQ( *c != c4, true );

  Column c5( *c );
  ASSERT_EQ( *c == c5, true );
  ASSERT_EQ( *c != c5, false );



}


TEST_F( ColumnTest, numberOfNeurons )
{

#define NUM_NEURONS_PYR_PER_LAYER 10
#define NUM_NEURONS_INT_PER_LAYER 8

  unsigned int gid = 0;
  for ( int i = 0 ; i < NUM_MINICOLS ; i++ )
  {
    c->addMiniColumn( MiniColumnPtr( new MiniColumn ( c, i )));
  }
  
  MiniColumns miniCols = c->miniColumns( );
  
  for ( MiniColumns::iterator mcIt = miniCols.begin( );
	mcIt != miniCols.end( ); mcIt++ )
  {
    for ( int l = 1 ; l < 7 ; l++ )
    {
      for ( int j = 0 ; j < NUM_NEURONS_PYR_PER_LAYER ; j++ )
      {
	( *mcIt )->addNeuron( NeuronPtr( new Neuron( true, l, gid++, 
						     Matrix4_4f::IDENTITY, 
						     *mcIt, Neuron::PYRAMIDAL )));	
      }
      for ( int j = 0 ; j < NUM_NEURONS_INT_PER_LAYER ; j++ )
      {
	( *mcIt )->addNeuron( NeuronPtr( new Neuron( true, l, gid++, 
						     Matrix4_4f::IDENTITY, 
						     *mcIt, Neuron::INTER )));	
      }
    }
  }
  
  ASSERT_EQ( c->numberOfNeurons( ), gid );
  ASSERT_EQ( c->numberOfNeurons( ), 
	     NUM_MINICOLS * 6 * ( NUM_NEURONS_PYR_PER_LAYER + 
				  NUM_NEURONS_INT_PER_LAYER ) );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::PYRAMIDAL ), 
	     NUM_MINICOLS * 6 * NUM_NEURONS_PYR_PER_LAYER );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::INTER ), 
	     NUM_MINICOLS * 6 * NUM_NEURONS_INT_PER_LAYER );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::PYRAMIDAL, 2 ), 
	     NUM_MINICOLS * NUM_NEURONS_PYR_PER_LAYER );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::INTER , 2 ), 
	     NUM_MINICOLS * NUM_NEURONS_INT_PER_LAYER );
  
  // Check morphological values are still computed 
  // to 0 without errors
  CheckNullMorphologicalValues( c );

  
}



#endif
