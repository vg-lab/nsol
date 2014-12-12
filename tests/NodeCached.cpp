/**
 * @file    NodeCached.cpp
 * @brief   Test for class nsol::NodeCached
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */


#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

void CheckDirtiness( SegmentCachedStatsPtr segment,
                     bool surfaceDirtiness,
                     bool volumeDirtiness,
                     bool lengthDirtiness )
{
  BOOST_CHECK_EQUAL( segment->dirty( SegmentStats::SURFACE ),
                     surfaceDirtiness );
  BOOST_CHECK_EQUAL( segment->dirty( SegmentStats::VOLUME ),
                     volumeDirtiness );
  BOOST_CHECK_EQUAL( segment->dirty( SegmentStats::LENGTH ),
                     lengthDirtiness );
}

void ComputeAllStats( SegmentCachedStatsPtr segment )
{
  segment->getStat( SegmentStats::SURFACE );
  segment->getStat( SegmentStats::VOLUME );
  segment->getStat( SegmentStats::LENGTH );
}

BOOST_AUTO_TEST_CASE( node_cached )
{

  SegmentCachedStatsPtr segment =
    SegmentCachedStatsPtr( new SegmentCachedStats );

  NodePtr node1 = NodePtr( new NodeCached( Vec3f( 1, 2, 3 ), 0, 1.2f ));
  NodePtr node2 = NodePtr( new NodeCached( Vec3f( 4, 5, 6 ), 0, 3.4f ));

  segment->begin( node1 );
  segment->end( node2 );

  CheckDirtiness( segment, true, true, true );
  ComputeAllStats( segment );
  CheckDirtiness( segment, false, false, false );

  node1->radius( 2.2f );
  BOOST_CHECK_EQUAL( node1->radius( ), 2.2f );
  CheckDirtiness( segment, true, true, false );

  ComputeAllStats( segment );
  CheckDirtiness( segment, false, false, false );

  node1->point( Vec3f( 7, 8, 9 ));
  BOOST_CHECK_EQUAL( node1->point( ), Vec3f( 7, 8, 9 ));
  CheckDirtiness( segment, true, true, true );

  auto nodeCached = NSOL_DYNAMIC_CAST( NodeCached, node1 );

  ComputeAllStats( segment );
  CheckDirtiness( segment, false, false, false );
  nodeCached->setAndPropagateDirty( );
  CheckDirtiness( segment, true, true, true );

  ComputeAllStats( segment );
  CheckDirtiness( segment, false, false, false );
  nodeCached->setAndPropagateDirty( SegmentStats::VOLUME );
  CheckDirtiness( segment, false, true, false );

}

// EOF
