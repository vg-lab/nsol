/**
 * @file    NGVSection.cpp
 * @brief
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "NGVSection.h"

namespace nsol
{

  NGVSection::NGVSection( void )
  {

  }

  NGVSection::~NGVSection( void )
  {

  }

  void NGVSection::addForwardNeighbour( NGVSectionPtr ngvSection_ )
  {
    _forwardNGVSections.push_back( ngvSection_ );
  }

  NGVSections& NGVSection::forwardNeighbors( void )
  {
    return _forwardNGVSections;
  }

  const NGVSections& NGVSection::forwardNeighbors( void ) const
  {
    return _forwardNGVSections;
  }

  void NGVSection::addBackwardNeighbour( NGVSectionPtr ngvSection_ )
  {
    _backwardNGVSections.push_back( ngvSection_ );
  }

  NGVSections& NGVSection::backwardNeighbors( void )
  {
    return _backwardNGVSections;
  }

  const NGVSections& NGVSection::backwardNeighbors( void ) const
  {
    return _backwardNGVSections;
  }

  void NGVSection::addNeighbour( NGVSectionPtr ngvSection_, NodePtr node_ )
  {
    if ( _nodes.size( ) > 1 )
    {
      if ( node_ ==  _nodes.at( 0 ))
        _backwardNGVSections.push_back( ngvSection_ );
      else if ( node_ ==  _nodes.at( _nodes.size( ) - 1 ))
        _forwardNGVSections.push_back( ngvSection_ );
    }
  }

  Nodes& NGVSection::nodes( void )
  {
    return _nodes;
  }

  const Nodes& NGVSection::nodes( void ) const
  {
    return _nodes;
  }

  void NGVSection::addFrontNode( NodePtr node_ )
  {
    _nodes.push_back( node_ );
  }

  void NGVSection::addBackNode( NodePtr node_ )
  {
    _nodes.insert( _nodes.begin( ), node_ );
  }

}
