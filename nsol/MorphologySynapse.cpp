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
  , _preSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
  , _postSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
  , _preSynapticSection( nullptr )
  , _postSynapticSection( nullptr )
  {
  }

  MorphologySynapse::MorphologySynapse( const MorphologySynapse& other_ )
  : Synapse( )
  , _preSynapticSurfacePosition( other_.preSynapticSurfacePosition( ))
  , _postSynapticSurfacePosition( other_.postSynapticSurfacePosition( ))
  , _preSynapticSection( other_.preSynapticSection( ))
  , _postSynapticSection( other_.postSynapticSection( ))
  {
  }

  MorphologySynapse::~MorphologySynapse( void )
  {
  }

  MorphologySynapse::TSynapseType MorphologySynapse::synapseType( void ) const
  {
    // -- Treatment of synapse type -- //
    MorphologySynapse::TSynapseType synapseType_ =
                                                  MorphologySynapse::UNDEFINED;

    if( _preSynapticSection == nullptr )
    {
      if( _postSynapticSection == nullptr )
      {
        return MorphologySynapse::SOMATOSOMATIC;
      }
      else
      {
        return synapseType_;
      }
    }

    Neurite::TNeuriteType neuritePresynaptic, neuritePostsynaptic;
    neuritePresynaptic  = Neurite::DENDRITE;
    neuritePostsynaptic = Neurite::DENDRITE;

    this->_calculateSynapticSection( neuritePresynaptic,
                                     MorphologySynapse::PRESYNAPTICSECTION );
    this->_calculateSynapticSection( neuritePostsynaptic,
                                     MorphologySynapse::POSTSYNAPTICSECTION );

    // Checking type of synapse...
    if( neuritePresynaptic == Neurite::DENDRITE ) // 1st Checkup
    {
      if( _postSynapticSection == nullptr )
      {
        return MorphologySynapse::DENDROSOMATIC;
      }
      if( neuritePostsynaptic == Neurite::DENDRITE )
      {
        return MorphologySynapse::DENDRODENDRITIC;
      }
    }

    if( neuritePresynaptic == Neurite::AXON ) // 2nd Checkup
    {
      if( _postSynapticSection == nullptr )
      {
        return MorphologySynapse::AXOSOMATIC;
      }
      if( neuritePostsynaptic == Neurite::DENDRITE )
      {
        return MorphologySynapse::AXODENDRITIC;
      }
      if( neuritePostsynaptic == Neurite::AXON )
      {
        return MorphologySynapse::AXOAXONIC;
      }
    }

    return synapseType_;
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
  MorphologySynapse::preSynapticSection( const SectionPtr preSynapticSection_ )
  {
    _preSynapticSection = preSynapticSection_;
  }

  SectionPtr MorphologySynapse::preSynapticSection( void ) const
  {
    return _preSynapticSection;
  }

  void MorphologySynapse::postSynapticSection( const SectionPtr section_ )
  {
    _postSynapticSection = section_;
  }

  SectionPtr MorphologySynapse::postSynapticSection( void ) const
  {
    return _postSynapticSection;
  }

  MorphologySynapse&
  MorphologySynapse::operator = ( const MorphologySynapse& other_ )
  {
    if (this != &other_)
    {
      this->preSynapticNeuron( other_.preSynapticNeuron( ));
      this->postSynapticNeuron( other_.postSynapticNeuron( ));
      this->weight( other_.weight( ));

      this->preSynapticSurfacePosition( other_.preSynapticSurfacePosition( ));
      this->postSynapticSurfacePosition( other_.postSynapticSurfacePosition( ));
      this->preSynapticSection( other_.preSynapticSection( ));
      this->postSynapticSection( other_.postSynapticSection( ));
    }

    return *this;
  }


} // namespace nsol

// EOF
