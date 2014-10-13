#ifndef __NSOL_MINICOLUMNTEST__
#define __NSOL_MINICOLUMNTEST__


#include <limits.h>
#include <gtest/gtest.h>

#include <nsol/nsol.h>

using namespace nsol;


void CheckNullMorphologicalValues( MiniColumnPtr c )
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

void CheckNoNeurons( MiniColumnPtr c )
{
  ASSERT_EQ( c->numberOfNeurons(), 0 );
  ASSERT_EQ( c->numberOfNeurons( false ), 0 );
  ASSERT_EQ( c->numberOfNeurons( true, Neuron::PYRAMIDAL ), 0 );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::PYRAMIDAL ), 0 );
  ASSERT_EQ( c->numberOfNeurons( true, Neuron::INTER ), 0 );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::INTER ), 0 );
}

class MiniColumnTest : public ::testing::Test {
 
protected:

  MiniColumnPtr mc;

  
  MiniColumnTest( )
    : mc( new MiniColumn )
  {
    // You can do set-up work for each test here. 
    mc->id( ) = 0;  
  }

  virtual ~MiniColumnTest() 
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

TEST_F(MiniColumnTest, emptyMiniColumn) 
{
  // Check id equal to 0
  #define COL_ID 115
  ASSERT_EQ( mc->id( ), 0 );
  mc->id( ) = COL_ID;
  ASSERT_EQ( mc->id( ), COL_ID );


  // Check morphological values are computed 
  // to 0 without errors
  CheckNullMorphologicalValues( mc );
  CheckNoNeurons( mc );

}

TEST_F(MiniColumnTest, addNeuron) 
{

  // Create a minicolumn
  NeuronPtr n ( new Neuron ( ));

  // Add the miniColumn to the column
  mc->addNeuron( n );

  // Check if added ok
  ASSERT_EQ( mc->neurons( ).size( ), 1);
  ASSERT_EQ( mc->neurons( ).size( ), mc->numberOfNeurons( ));

  // Check morphological values are still computed 
  // to 0 without errors
  CheckNullMorphologicalValues( mc );

}

TEST_F(MiniColumnTest, removeNeuron) 
{
  
  // Create two neurons
  NeuronPtr n1 ( new Neuron );
  NeuronPtr n2 ( new Neuron );
  
  // Add one of them to the column
  mc->addNeuron( n1 );

  // Try to remove the one not added 
  ASSERT_EQ( mc->removeNeuron( n2 ), false );
  ASSERT_EQ( mc->neurons( ).size( ), 1);
  ASSERT_EQ( mc->neurons( ).size( ), mc->numberOfNeurons( ));

  // Remove the one added
  ASSERT_EQ( mc->removeNeuron( n1 ), true );
  ASSERT_EQ( mc->neurons( ).size( ), 0);
  ASSERT_EQ( mc->neurons( ).size( ), mc->numberOfNeurons( ));

  // Check morphological values are still computed 
  // to 0 without errors
  CheckNullMorphologicalValues( mc );
  CheckNoNeurons( mc );

}


TEST_F(MiniColumnTest, clearMiniColumns) 
{
  
  #define NUM_NEURONS 100

  // Create and add some minicolumns
  for ( int i = 0; i < NUM_NEURONS; i++ ) 
    mc->addNeuron( NeuronPtr( new Neuron ));
  
  // Clear minicolumns
  mc->clearNeurons( );

  ASSERT_EQ( mc->neurons( ).size( ), 0);
  ASSERT_EQ( mc->neurons( ).size( ), mc->numberOfNeurons( ));

  // Check morphological values are still computed 
  // to 0 without errors
  CheckNullMorphologicalValues( mc );
  CheckNoNeurons( mc );

}

TEST_F( MiniColumnTest, operators )
{

  // Compare empty columns
  MiniColumnPtr mc2( new MiniColumn( ));
  ASSERT_EQ( *mc == *mc2, true );
  ASSERT_EQ( *mc != *mc2, false );

  // Change id and compare
  mc2->id( ) = 10;
  ASSERT_EQ( *mc == *mc2, false );
  ASSERT_EQ( *mc != *mc2, true );

  // Assignment operator
  MiniColumn mc3 = *mc2 ;
  ASSERT_EQ( mc3 == *mc2, true );
  ASSERT_EQ( mc3 != *mc2, false );

  // Add neurons and test if equal
  *mc2 = *mc;
  ASSERT_EQ( *mc == *mc2, true );
  ASSERT_EQ( *mc != *mc2, false );

  for ( int i = 0 ; i < NUM_NEURONS ; i++ )
  {
    mc->addNeuron( NeuronPtr( new Neuron ));
  }

  ASSERT_EQ( *mc == *mc2, false );
  ASSERT_EQ( *mc != *mc2, true );

  // Test assignment op with minicols
  *mc2 = *mc;
  ASSERT_EQ( *mc == *mc2, true );
  ASSERT_EQ( *mc != *mc2, false );


  // Test copy constructor
  MiniColumn mc4( mc3 );
  ASSERT_EQ( *mc == mc4, false );
  ASSERT_EQ( *mc != mc4, true );

  MiniColumn mc5( *mc );
  ASSERT_EQ( *mc == mc5, true );
  ASSERT_EQ( *mc != mc5, false );


}


TEST_F( MiniColumnTest, numberOfNeurons )
{

#define NUM_NEURONS_PYR_PER_LAYER 10
#define NUM_NEURONS_INT_PER_LAYER 8

  
  unsigned int gid = 0;
  
  for ( int l = 1 ; l < 7 ; l++ )
  {
    for ( int j = 0 ; j < NUM_NEURONS_PYR_PER_LAYER ; j++ )
    {
      mc->addNeuron( NeuronPtr( new Neuron( true, l, gid++, 
					    Matrix4_4f::IDENTITY, 
					    mc, Neuron::PYRAMIDAL )));	
    }
    for ( int j = 0 ; j < NUM_NEURONS_INT_PER_LAYER ; j++ )
    {
      mc->addNeuron( NeuronPtr( new Neuron( true, l, gid++, 
					    Matrix4_4f::IDENTITY, 
					    mc, Neuron::INTER )));	
    }
  }

  
  ASSERT_EQ( mc->numberOfNeurons( ), gid );
  ASSERT_EQ( mc->numberOfNeurons( ), 
	     6 * ( NUM_NEURONS_PYR_PER_LAYER + 
		   NUM_NEURONS_INT_PER_LAYER ) );
  ASSERT_EQ( mc->numberOfNeurons( false, Neuron::PYRAMIDAL ), 
	     6 * NUM_NEURONS_PYR_PER_LAYER );
  ASSERT_EQ( mc->numberOfNeurons( false, Neuron::INTER ), 
	     6 * NUM_NEURONS_INT_PER_LAYER );
  ASSERT_EQ( mc->numberOfNeurons( false, Neuron::PYRAMIDAL, 2 ), 
	     NUM_NEURONS_PYR_PER_LAYER );
  ASSERT_EQ( mc->numberOfNeurons( false, Neuron::INTER , 2 ), 
  	     NUM_NEURONS_INT_PER_LAYER );
  
  // Check morphological values are still computed 
  // to 0 without errors
  CheckNullMorphologicalValues( mc );

  
}



#endif
