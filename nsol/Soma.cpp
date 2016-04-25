/**
 * @file    Soma.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Soma.h"

namespace nsol
{

  Soma::Soma( )
    : _center( Vec3f( 0.0f, 0.0f, 0.0f ))
    , _maxRadius( 0.0f )
    , _meanRadius( 0.0f )
  {
  }

  Soma::~Soma( )
  {
    // for (Nodes::iterator it = _nodes.begin();
    // 	 it != _nodes.end(); ++it)
    //   delete *it;
    _nodes.clear();
  }

  Vec3f Soma::center( void ) const
  {
    return _center;
  }

  Nodes & Soma::nodes( void )
  {
    return _nodes;
  }

  const float & Soma::maxRadius( void ) const
  {
    return _maxRadius;
  }

  const float & Soma::meanRadius( void ) const
  {
    return _meanRadius;
  }

  void Soma::center( Vec3f center_ )
  {
    _center = center_;
  }

  void Soma::addNode( NodePtr node )
  {
    _nodes.push_back(node);

    _recalculateParams();
  }

  bool Soma::operator == ( Soma & other )
  {
    unsigned int size = this->nodes( ).size( );

    if ( size != other.nodes( ).size( ))
      return false;

    for ( unsigned int i = 0; i < size; i++ )
      if ( this->nodes( )[i] != other.nodes( )[i])
        return false;

    return true;
  }

  bool Soma::operator != ( Soma & other )
  {
    return ! ( *this == other );
  }

  void Soma::_recalculateParams( void )
  {
    Vec3f tmp = Vec3f( 0.0f, 0.0f, 0.0f );
    _maxRadius = 0.0f;
    _meanRadius = 0.0f;

    // Recalculate soma center
    for ( auto node: _nodes )
      tmp += node->point( );
    _center = tmp / float( _nodes.size( ));


    // Recalculate soma max radius and mean
    if( _nodes.size( ) < 1 )
      return;

    if( _nodes.size( ) == 1 )
    {
      _maxRadius = _nodes[0]->radius( );
      _meanRadius = _maxRadius;
      return;
    }

    for( auto node: _nodes )
    {
      float radius = ( _center - node->point( )).length( );
      if ( radius > _maxRadius )
        _maxRadius = radius;
      _meanRadius += radius;
    }
    _meanRadius /= ( float )_nodes.size( );
  }

} // namespace nsol

// EOF
