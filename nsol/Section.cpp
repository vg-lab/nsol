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

#include "Section.h"

namespace nsol
{

  Section::Section( void )
  {
    _nodes.clear( );
    _backwardSections.clear( );
    _forwardSections.clear( );
  }

  Section::~Section( void )
  {
    if ( _nodes.size( ) > 2 )
    {
      for ( unsigned int i = 1; i < _nodes.size( ) - 1; i++ )
        delete _nodes[i];
    }

    _backwardSections.clear( );
    _forwardSections.clear( );
    _nodes.clear( );
  }

  Sections& Section::backwardNeighbors( void )
  {
    return _backwardSections;
  }

  const Sections& Section::backwardNeighbors( void ) const
  {
    return _backwardSections;
  }

  Sections& Section::forwardNeighbors( void )
  {
    return _forwardSections;
  }

  const Sections& Section::forwardNeighbors( void ) const
  {
    return _forwardSections;
  }

  void Section::addBackwardNeighbour( SectionPtr section_ )
  {
    if ( section_ )
    {
      bool isSection = false;
      for ( auto section: _backwardSections )
      {
        if (( isSection = (section == section_)))
          break;
      }
      if ( !isSection )
        _backwardSections.push_back( section_ );
    }
  }

  void Section::addForwardNeighbour( SectionPtr section_ )
  {
    if ( section_ )
    {
      bool isSection = false;
      for ( auto section: _forwardSections )
      {
        if (( isSection = (section == section_)))
          break;
      }
      if ( !isSection )
        _forwardSections.push_back( section_ );
    }
  }

  bool Section::deleteBackwardNeighbour( SectionPtr section_ )
  {
    bool deletedNeighbour = false;
    for ( auto it = _backwardSections.begin( );  it != _backwardSections.end( );
          it++ )
    {
      if ( *it == section_ )
      {
        deletedNeighbour = true;
        _backwardSections.erase( it );
        it--;
      }
    }
    return deletedNeighbour;
  }

  bool Section::deleteForwardNeighbour( SectionPtr section_ )
  {
    bool deletedNeighbour = false;
    for ( auto it = _forwardSections.begin( );  it != _forwardSections.end( );
          it++ )
    {
      if ( *it == section_ )
      {
        deletedNeighbour = true;
        _forwardSections.erase( it );
        it--;
      }
    }
    return deletedNeighbour;
  }

  void Section::addNeighbour( SectionPtr section_, NodePtr node_ )
  {
    if ( section_ && _nodes.size( ) > 0 )
    {
      if ( node_ ==  _nodes.front( ))
      {
        bool isSection = false;
        for ( auto section: _backwardSections )
        {
          if (( isSection = (section == section_)))
            break;
        }
        if ( !isSection )
          _backwardSections.push_back( section_ );
      }
      if ( node_ ==  _nodes.back( ))
      {
        bool isSection = false;
        for ( auto section: _forwardSections )
        {
          if (( isSection = (section == section_)))
            break;
        }
        if ( !isSection )
          _forwardSections.push_back( section_ );
      }
    }
  }

  Nodes & Section::nodes( void )
  {
    return _nodes;
  }

  const Nodes & Section::nodes( void ) const
  {
    return _nodes;
  }


  void Section::addBackwardNode( NodePtr node_ )
  {
    if ( node_ )
    _nodes.insert( _nodes.begin( ), node_ );
  }

  void Section::addForwardNode( NodePtr node_ )
  {
    if ( node_ )
      _nodes.push_back( node_);
  }

  NodePtr Section::backwardNode( void )
  {
    if ( _nodes.size( ) > 0 )
      return _nodes[0];
    return nullptr;
  }

  NodePtr Section::forwardNode( void )
  {
    if ( _nodes.size( ) > 0 )
      return _nodes[ _nodes.size( ) - 1 ];
    return nullptr;
  }

  SectionPtr Section::clone( void ) const
  {
    SectionPtr section = new Section( );
    for ( unsigned int i = 1; i < _nodes.size( ) - 1; i++ )
    {
      section->addForwardNode( _nodes[i]->clone( ));
    }
    return section;
  }

  bool Section::operator == ( Section & other_ ) const
  {
    unsigned int size = ( unsigned int )this->nodes( ).size( );

    if( size != other_.nodes( ).size( ))
      return false;

    for ( unsigned int i = 0; i < size; i++ )
      if ( this->nodes( )[i] != other_.nodes( )[i] )
        return false;
    return true;
  }

  bool Section::operator != ( Section & other_ ) const
  {
    return ! ( *this == other_ );
  }

} // namespace nsol


// EOF
