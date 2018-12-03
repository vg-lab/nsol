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

#include "Soma.h"

namespace nsol
{

  Soma::Soma( )
    : _center( Vec3f( 0.0f, 0.0f, 0.0f ))
    , _maxRadius( 0.0f )
    , _minRadius( 0.0f )
    , _meanRadius( 0.0f )
  {
  }

  Soma::~Soma( )
  {
    for ( NodePtr node: _nodes )
      delete node;

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

  const float & Soma::minRadius( void ) const
  {
    return _minRadius;
  }

  const float & Soma::meanRadius( void ) const
  {
    return _meanRadius;
  }

  void Soma::center( const Vec3f & center_ )
  {
    _center = center_;
  }

  void Soma::addNode( NodePtr node )
  {
    _nodes.push_back(node);

    _recalculateParams();
  }

  void Soma::computeParams( void )
  {
    _recalculateParams( );
  }

  SomaPtr Soma::clone( void ) const
  {
    SomaPtr newSoma = new Soma( );
    for ( NodePtr node: _nodes )
    {
      newSoma->addNode( node->clone( ));
    }
    return newSoma;
  }

  bool Soma::operator == ( Soma & other )
  {
    unsigned int size = ( unsigned int )this->nodes( ).size( );

    if ( size != other.nodes( ).size( ))
      return false;

    for ( unsigned int i = 0; i < size; i++ )
      if ( this->nodes( )[i] != other.nodes( )[i] )
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
    _minRadius = std::numeric_limits<float>::max( );

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
      _minRadius = _maxRadius;
      return;
    }

    if( _nodes.size( ) == 3 )
    {
      float centerDiff = ( _nodes[0]->point( ) -
                           ( _nodes[1]->point( ) + _nodes[2]->point( )) / 2.0f
                         ).norm( );
      if ( std::fabs( centerDiff ) < 0.0001f )
      {
        _maxRadius = _nodes[0]->radius( );
        _meanRadius = _maxRadius;
        _minRadius = _maxRadius;
        return;
      }
    }

    for( const auto node: _nodes )
    {
      float radius = ( _center - node->point( )).norm( );
      if ( radius > _maxRadius )
        _maxRadius = radius;
      if ( radius < _minRadius )
        _minRadius = radius;
      _meanRadius += radius;
    }
    _meanRadius /= ( float )_nodes.size( );
  }

} // namespace nsol

// EOF
