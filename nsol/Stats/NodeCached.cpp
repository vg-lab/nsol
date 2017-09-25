/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
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
    // TODO: propagate dirtiness to parents
  }

  void NodeCached::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );
    // TODO: propagate dirtiness to parents
  }


  void NodeCached::radius( const float radius_ )
  {
    this->Node::radius( radius_ );
    // TODO: propagate dirtiness to parents

  }


  void NodeCached::point( const Vec3f & point_ )
  {
    this->Node::point( point_ );
    // TODO: propagate dirtiness to parents
  }


} // namespace nsol
