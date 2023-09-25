/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
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
    Node( const Vec3f & initPoint = Vec3f(0,0,0),
          const int & initId = 0,
          const float & initRadius = 0.0f )
        : _point( initPoint )
        , _radius( initRadius )
        , _id( initId )
    {
    }

    NSOL_API
    virtual ~Node( void )
    {
    }

    NSOL_API
    virtual void point( const Vec3f & point_ )
    {
        _point = point_;
    }

    NSOL_API
    Vec3f point( void ) const
    {
        return _point;
    }

    NSOL_API
    virtual void radius( const float radius_ )
    {
        _radius = radius_;
    }

    NSOL_API
    float radius( void ) const
    {
        return _radius;
    }

    /**
     * Set the node id
     * @return node id
     */
    NSOL_API
    virtual void id( const int id_ )
    {
        _id = id_;
    }

    /**
     * Get the node id
     * @return node id
     */
    NSOL_API
    int id( void ) const
    {
        return _id;
    }

    NSOL_API
    virtual NodePtr clone( void ) const
    {
        return new Node( _point, _id, _radius );
    }

    NSOL_API
    bool operator == ( const Node & other ) const
    {
      return ( ( this->_id == other._id ) &&
               ( this->_radius == other._radius ) &&
               ( this->_point == other._point ) );
    }

    NSOL_API
    bool operator != ( const Node & other ) const
    {
      return ! ( *this == other );
    }

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
