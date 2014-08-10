

#include <limits.h>
//#include "sample1.h"
#include <gtest/gtest.h>

#include <Segment.h>
#include <Section.h>

class SegmentTest : public ::testing::Test 
{
protected:

  nsol::Section sec;
  nsol::Segment seg1, seg2;

  nsol::Node node1;
  nsol::Node node2;

  //  nsol::Vec3f vec3f1;
  //nsol::Vec3f vec3f2;
  //nsol::Vec3f vec3f1;

  SegmentTest() : 
    node1(nsol::Node(nsol::Vec3f(1.0,2.0,3.0), 0, 10.0f)),
    node2(nsol::Node(nsol::Vec3f(4.0,5.0,6.0), 0, 20.0f))
  {
    // You can do set-up work for each test here.
    
    
    //  nsol::Vec3f 
    
    //    node1 = 
    //node2 = nsol::Node(nsol::Vec3f(4.0,5.0,6.0), 0, 20.0f);
    
    seg1.next(&seg2);  
    seg2.prev(&seg1);
    
    seg2.begin(&node1);
    seg2.end(&node2);
    
    
  }

virtual ~SegmentTest() 
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


// Tests that the Foo::Bar() method does Abc.
TEST_F(SegmentTest, firstTest) {

  // Test next and prev
  ASSERT_EQ(seg1.prev(), nullptr);
  ASSERT_EQ(seg1.next(), &seg2);
  ASSERT_EQ(seg2.prev(), &seg1);
  ASSERT_EQ(seg2.next(), nullptr);

  //TODO
  //ASSERT_EQ(seg1.parentSection(), nullptr);

  // Test begin and end nodes 
  ASSERT_EQ(seg1.begin(), nullptr);
  ASSERT_EQ(seg1.end(), nullptr);
  ASSERT_EQ(seg2.begin(), &node1);
  ASSERT_EQ(seg2.end(), &node2);

  // Test length 
  ASSERT_EQ(seg1.length(), 0.0f);
  ASSERT_EQ(seg2.length(),
	    sqrtf( (4.0f-1.0f)*(4.0f-1.0f) +
		   (5.0f-2.0f)*(5.0f-2.0f) +
		   (6.0f-3.0f)*(6.0f-3.0f) ) );


  // Test surface
  ASSERT_EQ(seg1.surface(), 0.0f);
  //ASSERT_EQ(seg2.surface(), 66.1595);
  seg2.surface();

  // Test volume
  ASSERT_EQ(seg1.volume(), 0.0f);

}


