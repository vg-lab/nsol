/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo Pellon <raquel.jarillo@urjc.es>
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

#include "MorphologySynapse.h"

namespace nsol
{

  MorphologySynapse::MorphologySynapse( void )
  : Synapse( )
  , _gid( 0 )
  , _preSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
  , _postSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
  , _preSynapticSection( nullptr )
  , _postSynapticSection( nullptr )
  {
  }

  MorphologySynapse::MorphologySynapse( const MorphologySynapse& other_ )
  : Synapse( other_ )
  , _gid( other_._gid )
  , _preSynapticSurfacePosition( other_.preSynapticSurfacePosition( ))
  , _postSynapticSurfacePosition( other_.postSynapticSurfacePosition( ))
  , _preSynapticSection( other_.preSynapticSection( ))
  , _postSynapticSection( other_.postSynapticSection( ))
  {
  }

  MorphologySynapse::~MorphologySynapse( void )
  {
  }

  unsigned int MorphologySynapse::gid( void ) const
  {
    return _gid;
  }

  void MorphologySynapse::gid( unsigned int gid_ )
  {
    _gid = gid_;
  }

  MorphologySynapse::TSynapseType MorphologySynapse::synapseType( void ) const
  {

    if( !_postSynapticSection )
    {
      if( !_preSynapticSection )
        return SOMATOSOMATIC;

      switch( _preSynapticSection->neurite( )->neuriteType( ) )
      {
        case Neurite::DENDRITE:
          return DENDROSOMATIC;
        case Neurite::AXON:
          return AXOSOMATIC;
      }
    }
    else
    {
      auto typePre = _preSynapticSection->neurite( )->neuriteType( );

      if( typePre == Neurite::DENDRITE )
        return DENDRODENDRITIC;

      auto typePost = _postSynapticSection->neurite( )->neuriteType( );

      if( typePre == Neurite::AXON )
      {
        if( typePost == Neurite::DENDRITE )
          return AXODENDRITIC;
        else if( typePost == Neurite::AXON )
          return AXOAXONIC;
      }
    }

    return UNDEFINED;
  }

  void MorphologySynapse::preSynapticSurfacePosition
                                  ( const Vec3f& presynaptic_surface_position_ )
  {
    _preSynapticSurfacePosition = presynaptic_surface_position_;
  }

  Vec3f MorphologySynapse::preSynapticSurfacePosition( void ) const
  {
    return _preSynapticSurfacePosition;
  }

  void MorphologySynapse::postSynapticSurfacePosition( const Vec3f& position_ )
  {
    _postSynapticSurfacePosition = position_;
  }

  Vec3f MorphologySynapse::postSynapticSurfacePosition( void ) const
  {
    return _postSynapticSurfacePosition;
  }

  void
  MorphologySynapse::preSynapticSection(
    const NeuronMorphologySectionPtr preSynapticSection_ )
  {
    _preSynapticSection = preSynapticSection_;
  }

  NeuronMorphologySectionPtr MorphologySynapse::preSynapticSection( void ) const
  {
    return _preSynapticSection;
  }

  void MorphologySynapse::postSynapticSection(
    const NeuronMorphologySectionPtr section_ )
  {
    _postSynapticSection = section_;
  }

  NeuronMorphologySectionPtr MorphologySynapse::postSynapticSection( void ) const
  {
    return _postSynapticSection;
  }

} // namespace nsol

// EOF
