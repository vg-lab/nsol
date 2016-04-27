/**
 * @file    Node.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
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
