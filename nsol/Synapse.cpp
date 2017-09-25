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

#include "Synapse.h"

namespace nsol
{

  //! Default constructor and destructor
  Synapse::Synapse( void )
   : _preSynapticNeuron( 0 )
   , _postSynapticNeuron( 0 )
   , _weight( 0.0f )
   {
   }

  Synapse::Synapse( const Synapse& other_ )
  : _preSynapticNeuron( other_.preSynapticNeuron( ))
  , _postSynapticNeuron( other_.postSynapticNeuron( ))
  , _weight( other_.weight( ))
   {
   }

  Synapse::~Synapse( void )
  {
  }

  void Synapse::preSynapticNeuron( const uint32_t neuronID_ )
  {
    _preSynapticNeuron = neuronID_;
  }

  uint32_t Synapse::preSynapticNeuron( void ) const
  {
    return _preSynapticNeuron;
  }

  void Synapse::postSynapticNeuron(const uint32_t neuronID_ )
  {
    _postSynapticNeuron = neuronID_;
  }

  uint32_t Synapse::postSynapticNeuron( void ) const
  {
    return _postSynapticNeuron;
  }

  void Synapse::weight( const float weight_ )
  {
    _weight = weight_;
  }

  float Synapse::weight( void ) const
  {
    return _weight;
  }

  Synapse& Synapse::operator = ( const Synapse& other_ )
  {
    if (this != &other_)
    {
      this->preSynapticNeuron( other_.preSynapticNeuron( ));
      this->postSynapticNeuron( other_.postSynapticNeuron( ));
      this->weight( other_.weight( ));
    }

    return *this;
  }

} // namespace nsol

// EOF
