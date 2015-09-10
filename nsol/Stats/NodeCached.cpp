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
  }

  void NodeCached::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );
  }


  void NodeCached::radius( const float radius_ )
  {
    this->Node::radius( radius_ );
  }


  void NodeCached::point( const Vec3f & point_ )
  {
    this->Node::point( point_ );
  }


} // namespace nsol
