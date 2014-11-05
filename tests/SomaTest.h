#ifndef __NSOL_SOMATEST__
#define __NSOL_SOMATEST__

#include <limits.h>
#include <gtest/gtest.h>

#include <nsol/Soma.h>

class SomaTest : public ::testing::Test {
 
protected:

  SomaTest()
  {
    // You can do set-up work for each test here. 
  }

  virtual ~SomaTest() 
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


TEST_F(SomaTest, firstTest) 
{
  ASSERT_EQ(0,0); 
}



#endif
