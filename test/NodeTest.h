#ifndef __NSOL_NODETEST__
#define __NSOL_NODETEST__

#include <limits.h>
#include <gtest/gtest.h>

#include <Node.h>
#include <Section.h>

class NodeTest : public ::testing::Test {
 
protected:

  NodeTest()
  {
    // You can do set-up work for each test here. 
  }

  virtual ~NodeTest() 
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


TEST_F(NodeTest, firstTest) 
{
  ASSERT_EQ(0,0); 
}



#endif
