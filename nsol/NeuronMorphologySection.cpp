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

#include "NeuronMorphologySection.h"

namespace nsol
{

  NeuronMorphologySection::NeuronMorphologySection( void )
    : Section( )
    , _id( 0 )
    , _neurite( nullptr )
  {
  }

  NeuronMorphologySection::~NeuronMorphologySection( void )
  {
    if ( _nodes.size( ) > 1 )
    {
      delete _nodes.back( );
    }

  }

  unsigned int NeuronMorphologySection::id( void ) const
  {
      return _id;
  }

  void NeuronMorphologySection::id ( unsigned int id_ )
  {
      _id = id_;
  }

  NeuritePtr NeuronMorphologySection::neurite( void )
  {
    return _neurite;
  }

  void NeuronMorphologySection::neurite( NeuritePtr newNeurite_ )
  {
    _neurite = newNeurite_;
  }

  SectionPtr NeuronMorphologySection::parent( void )
  {
    if ( !this->_backwardSections.empty( ))
      return this->_backwardSections.front( );
    else
      return nullptr;
  }

  void NeuronMorphologySection::parent( SectionPtr parent_ )
  {
    auto actualParent = dynamic_cast< NeuronMorphologySectionPtr >( parent_ );
    if ( actualParent )
    {
      if ( _backwardSections.empty( ))
      {
        this->_backwardSections.push_back( actualParent );
        if ( actualParent->lastNode( ))
          firstNode( actualParent->lastNode( ));
      }
    }
  }

  void NeuronMorphologySection::addChild( SectionPtr section_ )
  {
    this->_forwardSections.push_back( section_ );
  }

  Sections& NeuronMorphologySection::children( void )
  {
    return this->_forwardSections;
  }

  const Sections& NeuronMorphologySection::children( void ) const
  {
    return this->_forwardSections;
  }

  void NeuronMorphologySection::addNode( NodePtr node_ )
  {
    addForwardNode( node_ );
  }

  NodePtr NeuronMorphologySection::firstNode( void )
  {
    return backwardNode( );
  }

  void NeuronMorphologySection::firstNode( NodePtr firstNode_ )
  {
    addBackwardNode( firstNode_ );
  }

  NodePtr NeuronMorphologySection::lastNode( void )
  {
    return forwardNode( );
  }

  NeuronMorphologySectionStats * NeuronMorphologySection::stats( void )
  {
    return nullptr;
  }

  SectionPtr NeuronMorphologySection::clone( void ) const
  {
    NeuronMorphologySectionPtr section = new NeuronMorphologySection( );
    for ( unsigned int i = 1; i < _nodes.size( ); i++ )
    {
      section->addNode( _nodes[i]->clone( ));
    }
    return section;
  }

} // namespace nsol


// EOF
