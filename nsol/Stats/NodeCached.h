/**
 * @file    NodeCached.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NODE_CACHED__
#define __NSOL_NODE_CACHED__

#include <nsol/api.h>

#include "Cached.h"
#include "SegmentStats.h"

namespace nsol
{


  class NodeCached
    : public Node
    , public Cached<>
  {

  public:

    NSOL_API
    NodeCached( const Vec3f & point_ = Vec3f(0,0,0),
                const int & id_ = 0,
                const float & radius_ = 0.0f );

    NSOL_API
    virtual ~NodeCached( void );

    NSOL_API
    virtual void setAndPropagateDirty( unsigned int id );

    NSOL_API
    virtual void setAndPropagateDirty( void );

    NSOL_API
    virtual void radius( const float radius_ );

    NSOL_API
    virtual void point( const Vec3f & point_ );


  }; // class NodeCached

} // namespace nsol

#endif // __NSOL_NODE_CACHED__
