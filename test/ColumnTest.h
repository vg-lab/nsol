#ifndef __NSOL_COLUMNTEST__
#define __NSOL_COLUMNTEST__

#include <limits.h>
#include <gtest/gtest.h>

#include <nsol/nsol.h>

using namespace nsol;

class ColumnTest : public ::testing::Test {
 
protected:

  ColumnPtr c;

  
  ColumnTest( )
    : c( new Column )
  {
    // You can do set-up work for each test here. 
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

  c->id( ) = 0;

  ASSERT_EQ( c->meanSomaVolume( ), 0 );
  ASSERT_EQ( c->meanSomaSurface( ), 0.0f );
  ASSERT_EQ( c->meanDendriteVolume( ), 0.0f );
  ASSERT_EQ( c->meanDendriteSurface( ), 0.0f );
  ASSERT_EQ( c->maxSomaVolume( ), 0.0f );
  ASSERT_EQ( c->maxSomaSurface( ), 0.0f );
  ASSERT_EQ( c->maxDendriteVolume( ), 0.0f );
  ASSERT_EQ( c->maxDendriteSurface( ), 0.0f );
  ASSERT_EQ( c->numberOfNeurons(), 0 );
  ASSERT_EQ( c->numberOfNeurons( false ), 0 );
  ASSERT_EQ( c->numberOfNeurons( true, Neuron::PYRAMIDAL ), 0 );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::PYRAMIDAL ), 0 );
  ASSERT_EQ( c->numberOfNeurons( true, Neuron::INTER ), 0 );
  ASSERT_EQ( c->numberOfNeurons( false, Neuron::INTER ), 0 );

}

TEST_F(ColumnTest, oneMiniColumn) 
{

  MiniColumnPtr mc ( new MiniColumn ( c, 1 ));
  ASSERT_EQ( mc->id( ), 1 );
  ASSERT_EQ( mc->column( ), c );

}


#endif
