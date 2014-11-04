/**
 * @file    Node.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include "Node.h"

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

  Vec3f & Node::point(void)
  {
    return _point;
  }

  Vec3f Node::point(void) const
  {
    return _point;
  }
  
  float & Node::radius(void)
  {
    return _radius;
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
