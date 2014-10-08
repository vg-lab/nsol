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

  void Soma::addNode( NodePtr node )
  {
    _nodes.push_back(node);
    
    _recalculateCenter();
    _recalculateMaxRadius();
  }
  
  void Soma::addNode( Vec3f & xyz, float & radius )
  {
    this->addNode( NodePtr( new Node( xyz, radius )));
    
    _recalculateCenter();
    _recalculateMaxRadius();
  }
  
  float Soma::volume( void ) const
  {
    //TODO: use real volume soma formula, now use sphere volume formula
    return M_4PI_3 * _maxRadius * _maxRadius * _maxRadius;
  }
  
  float Soma::surface( void ) const 
  {
    //TODO: use real soma surface, now use sphere surface formula
    return M_4PI * _maxRadius * _maxRadius;
  }

  void Soma::_recalculateCenter( void )
  {
    Vec3f tmp = Vec3f( 0.0f, 0.0f, 0.0f );
    
    // Recalculated soma center node
    for (unsigned int it = 0; it < _nodes.size(); ++it)
      tmp += _nodes[it]->point();
    
    _center = tmp /_nodes.size();
  }
  
  void Soma::_recalculateMaxRadius( void )
  {
    if ( _nodes.size( ) == 0 )
    {
      _maxRadius = 0.0f;
      return;
    }
    
    _maxRadius = _nodes[0]->radius( );

    for ( unsigned int it = 1; it < _nodes.size( ); ++it )
    {
      float mod = ( _center - _nodes[it]->point( )).length( );
      
      if ( mod > _maxRadius )
        _maxRadius = mod;
    }
  }

} // namespace nsol

// EOF
