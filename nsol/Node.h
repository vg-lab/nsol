/**
 * @file    Node.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_NODE__
#define __NSOL_NODE__

#include "NsolTypes.h"

namespace nsol
{

  class Node
  {

  public:

    Node( const Vec3f & point = Vec3f(0,0,0), 
	  const int &id = 0, 
	  const float &radius = 0.0f );

    Vec3f & point( void );

    float & radius( void );

    int & id( void );

  protected:

    Vec3f _point;
    float _radius;
    int _id;

  };

} // namespace nsol

#endif

// EOF
