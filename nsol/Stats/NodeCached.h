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
#ifndef __NSOL_NODE_CACHED__
#define __NSOL_NODE_CACHED__

#include <nsol/api.h>

#include "Cached.h"
#include "SegmentStats.h"

namespace nsol
{


  /** \class NodeCached
   *
   *  Using this class with SectionCachedStats allows to dirty
   *  cached section stats when node's radius or point values change
   *
   *  Example: @include examples/sectionStats.cpp
   */
  class NodeCached
    : public Node
    , public Cached<>
  {

  public:

    /*
     * Default constructor
     */
    NSOL_API
    NodeCached( const Vec3f & point_ = Vec3f(0,0,0),
                const int & id_ = 0,
                const float & radius_ = 0.0f );

    /*
     * Default destructor
     */
    NSOL_API
    virtual ~NodeCached( void );

    /*
     * Reimplementation of the Cached class method to
     * propagate dirtiness to parent section for an
     * specific property
     * @param id property to propagate dirtiness
     */
    NSOL_API
    virtual void setAndPropagateDirty( unsigned int id );

    /*
     * Reimplementation of the Cached class method to
     * propagate dirtiness to parent section for all
     * property
     */
    NSOL_API
    virtual void setAndPropagateDirty( void );

    /*
     * Reimplementation of the Node base class method
     * that sets a new radius. This method propagates
     * dirtiness to parents
     * @param radius new radius to be set
     */
    NSOL_API
    virtual void radius( const float radius );

    /*
     * Reimplementation of the Node base class method
     * that sets a new point. This method propagates
     * dirtiness to parents
     * @param point new point to be set
     */
    NSOL_API
    virtual void point( const Vec3f & point );

  }; // class NodeCached

} // namespace nsol

#endif // __NSOL_NODE_CACHED__
