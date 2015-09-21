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
              const float & initRadius
              /*const int & initId*/ )
    : _point( initPoint )
    , _radius( initRadius )
#ifdef NSOL_USE_NODE_WITH_ID
    , _id( initId )
#endif
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

#ifdef NSOL_USE_NODE_WITH_ID
    return _id;
#else
    NSOL_THROW( "Node doesn't have id" );
#endif
  }

  int Node::id(void) const
  {
#ifdef NSOL_USE_NODE_WITH_ID
    return _id;
#else
    NSOL_THROW( "Node doesn't have id" );
#endif
  }

  Node & Node::operator = ( const Node & other )
  {
    if (this != &other)
    {
      this->point( other.point( ));
      this->radius( other.radius( ));
#ifdef NSOL_USE_NODE_WITH_ID
      this->id( ) = other.id( );
#endif
    }
    return *this;
  }

  bool Node::operator == ( Node & other ) const
  {
    return ( ( this->point( ) == other.point( ) ) &&
             ( this->radius( ) == other.radius( ) )
#ifdef NSOL_USE_NODE_WITH_ID
             && ( this->id( ) == other.id( ) )
#endif
             );
  }

  bool Node::operator != ( Node & other ) const
  {
    return ! ( *this == other );
  }

} // namespace nsol

// EOF
