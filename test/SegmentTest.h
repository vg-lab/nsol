

#include <limits.h>
//#include "sample1.h"
#include <gtest/gtest.h>

#include <Segment.h>
#include <Section.h>
#include <NsolTypes.h>

#define EPSILON_VALUE 1e-10

class SegmentTest : public ::testing::Test 
{
protected:

  nsol::Section sec;
  nsol::Segment seg1, seg2;

  nsol::Vec3f v1, v2;

  nsol::Node node1, node2;


  //  nsol::Vec3f vec3f1;
  //nsol::Vec3f vec3f2;
  //nsol::Vec3f vec3f1;

#define RADIUS1 10.0f
#define RADIUS2 20.0f

  SegmentTest() : 
    v1(1.0,2.0,3.0),
    v2(4.0,5.0,6.0),
    node1(nsol::Node(v1, 0, RADIUS1)),
    node2(nsol::Node(v2, 0, RADIUS2))
  {
    // You can do set-up work for each test here.

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


TEST_F(SegmentTest, pointers) {

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
}

TEST_F(SegmentTest, length) {

  // Test length 
  ASSERT_EQ(seg1.length(), 0.0f);
  ASSERT_EQ(seg2.length(), (v2-v1).length() );

}

TEST_F(SegmentTest, surface) {
  // Test surface
  ASSERT_EQ(seg1.surface(), 0.0f);
  //ASSERT_EQ(seg2.surface(), 66.1595);
  ASSERT_NEAR(seg2.surface(),
              RADIUS2 * float(M_2PI) * (v2-v1).length(),
              EPSILON_VALUE);

}

TEST_F(SegmentTest, volume) {

  // Test volume
  ASSERT_EQ(seg1.volume(), 0.0f);
  ASSERT_NEAR(seg2.volume(),
              RADIUS2 * RADIUS2 * float(M_PI) * (v2-v1).length(),
              EPSILON_VALUE);

}


