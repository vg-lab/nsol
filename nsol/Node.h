/**
 * @file    Node.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
            Do not distribute without further notice.
 */
#ifndef __NSOL_NODE__
#define __NSOL_NODE__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>

namespace nsol
{

  class Node
  {

  public:

    NSOL_API
    Node( const Vec3f & point = Vec3f(0,0,0),
          const int & id = 0,
          const float & radius = 0.0f );

    NSOL_API
    Vec3f & point( void );

    NSOL_API
    Vec3f point( void ) const;

    NSOL_API
    float & radius( void );

    NSOL_API
    float radius( void ) const;

    NSOL_API
    int & id( void );

    NSOL_API
    int id( void ) const;

    NSOL_API
    bool operator == ( Node & other ) const;

    NSOL_API
    bool operator != ( Node & other ) const;

  protected:

    Vec3f _point;
    float _radius;
    int _id;

  };

} // namespace nsol

#endif

// EOF
