#ifndef __NSOL_NEURONMORPHOLOGYTEST__
#define __NSOL_NEURONMORPHOLOGYTEST__

#include <limits.h>
#include <gtest/gtest.h>

#include <nsol/NeuronMorphology.h>

using namespace nsol;

class NeuronMorphologyTest : public ::testing::Test {
 
protected:

  nsol::NeuronMorphologyPtr nm;

  NeuronMorphologyTest( void ) 
    : nm( new nsol::NeuronMorphology )
  {
  }
  


  virtual ~NeuronMorphologyTest() 
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


TEST_F(NeuronMorphologyTest, firstTest) 
{
  ASSERT_EQ(0,0); 

  ASSERT_EQ( nm->dendritesVolume( ), 0.0f );

  DendritePtr d = nm->addDendrite( );

  NeuritePtr n(d);

  ASSERT_EQ( nm->dendritesVolume( ), 0.0f );

//  d->

}



#endif
