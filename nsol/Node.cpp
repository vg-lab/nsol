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

#include "Node.h"
#include "error.h"

namespace nsol
{

  Node::Node( const Vec3f & initPoint,
              const int & initId,
              const float & initRadius )
    : _point( initPoint )
    , _radius( initRadius )
    , _id( initId )
  {
  }

  Node::~Node( void )
  {
  }

  void Node::point( const Vec3f & point_ )
  {
    _point = point_;
  }

  Vec3f Node::point(void) const
  {
    return _point;
  }

  void Node::radius( const float radius_ )
  {
    _radius = radius_;
  }

  float Node::radius(void) const
  {
    return _radius;
  }

  int & Node::id(void)
  {
    return _id;
  }

  int Node::id(void) const
  {
    return _id;
  }

  NodePtr Node::clone( void ) const
  {
    return new Node( _point, _id, _radius );
  }

  Node & Node::operator = ( const Node & other )
  {
    if (this != &other)
    {
      this->id( ) = other.id( );
      this->radius( other.radius( ));
      this->point( other.point( ));
    }
    return *this;
  }

  bool Node::operator == ( Node & other ) const
  {
    return ( ( this->id( ) == other.id( ) ) &&
             ( this->radius( ) == other.radius( ) ) &&
             ( this->point( ) == other.point( ) ) );
  }

  bool Node::operator != ( Node & other ) const
  {
    return ! ( *this == other );
  }

} // namespace nsol

// EOF
