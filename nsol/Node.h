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
#ifndef __NSOL_NODE__
#define __NSOL_NODE__

#include <nsol/api.h>
#include "Object.h"
#include "NsolTypes.h"

namespace nsol
{

  class Node
    : public virtual Object
  {

  public:

    NSOL_API
    Node( const Vec3f & point = Vec3f(0,0,0),
          const int & id = 0,
          const float & radius = 0.0f );

    NSOL_API
    virtual ~Node( void );

    NSOL_API
    virtual void point( const Vec3f & point_ );

    NSOL_API
    Vec3f point( void ) const;

    NSOL_API
    virtual void radius( const float radius_ );

    NSOL_API
    float radius( void ) const;

    NSOL_API
    int & id( void );

    NSOL_API
    int id( void ) const;

    NSOL_API
    virtual NodePtr clone( void ) const;

    NSOL_API
    Node & operator = ( const Node & other );

    NSOL_API
    bool operator == ( Node & other ) const;

    NSOL_API
    bool operator != ( Node & other ) const;

    NSOL_API
    virtual NodePtr asNode( void )
    {
      return this;
    }

  protected:

    Vec3f _point;
    float _radius;
    int _id;

  };

} // namespace nsol

#endif

// EOF
