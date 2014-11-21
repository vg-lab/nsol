/**
 * @file    NodeCached.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "NodeCached.h"
#include "SectionCachedStats.h"
#include "SegmentCachedStats.h"

namespace nsol
{


  NodeCached::NodeCached( const Vec3f & point_,
                          const int & id_,
                          const float & radius_ )
    : Node( point_, id_, radius_ )
    , Cached( )
  {
  }

  NodeCached::~NodeCached( void )
  {
  }

  void NodeCached::setAndPropagateDirty( unsigned int id_ )
  {
    this->Cached::setAndPropagateDirty( id_ );

    for ( auto segIt = _parentSegments.begin( );
          segIt != _parentSegments.end( ); segIt++ )
    {

      auto cached = NSOL_DYNAMIC_CAST( Cached, * segIt );
      if ( cached )
        cached->setAndPropagateDirty( id_ );
    }
  }

  void NodeCached::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );

    for ( auto segIt = _parentSegments.begin( );
          segIt != _parentSegments.end( ); segIt++ )
    {

      auto cached = NSOL_DYNAMIC_CAST( Cached, * segIt );
      if ( cached )
        cached->setAndPropagateDirty( );
    }
  }


  void NodeCached::radius( const float radius_ )
  {
    std::cout << "changing radius" << std::endl;
    this->Node::radius( radius_ );
    setAndPropagateDirty( SegmentCachedStats::SURFACE );
    setAndPropagateDirty( SegmentCachedStats::VOLUME );
    setAndPropagateDirty( SegmentCachedStats::MEAN_RADIUS );
  }


  void NodeCached::point( const Vec3f & point_ )
  {
    this->Node::point( point_ );
    setAndPropagateDirty( SegmentCachedStats::SURFACE );
    setAndPropagateDirty( SegmentCachedStats::VOLUME );
    setAndPropagateDirty( SegmentCachedStats::LENGTH );
  }


} // namespace nsol
