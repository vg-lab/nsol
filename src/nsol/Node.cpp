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

  Node::Node( const Vec3f &point, 
	      const int &id, 
	      const float &radius )
    : _point( point )
    , _radius( radius )
    , _id( id )
  {
  }

  Vec3f & Node::point(void) 
  {
    return _point;
  }
  
  float & Node::radius(void) 
  {
    return _radius;
  }
  
  int & Node::id(void)
  {
    return _id;
  }

} // namespace nsol

// EOF
