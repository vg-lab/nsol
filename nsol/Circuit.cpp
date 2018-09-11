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

#include "Circuit.h"

namespace nsol
{

  //
  // Constructors and destructors
  //
  Circuit::Circuit( void )
  {
  }

  Circuit::~Circuit( void )
  {
    clear( );
  }

  //
  // Connections methods
  //
  void Circuit::addSynapse( SynapsePtr synapse_ )
  {
    _synapses.push_back( synapse_ );

    _preSynapticConnections.insert( std::make_pair(
                                    synapse_->preSynapticNeuron( ), synapse_ ));
    _postSynapticConnections.insert( std::make_pair(
                                   synapse_->postSynapticNeuron( ), synapse_ ));
  }

  void Circuit::addSynapses( const std::vector< SynapsePtr >& synapses )
  {
    _synapses.reserve( _synapses.size( ) + synapses.size( ));
    for( auto synapse : synapses )
    {
      if( synapse )
      {
        addSynapse( synapse );
      }
    }

    _synapses.shrink_to_fit( );
  }

  void Circuit::addSynapses( const std::vector< MorphologySynapsePtr >& synapses )
  {
    _synapses.reserve( _synapses.size( ) + synapses.size( ));
    for( auto synapse : synapses )
    {
      if( synapse )
      {
        addSynapse(( SynapsePtr )synapse );
      }
    }

    _synapses.shrink_to_fit( );
  }

  void Circuit::clear( void )
  {
    _preSynapticConnections.clear( );
    _postSynapticConnections.clear( );

    for( auto synapse : _synapses )
    {
      delete( synapse );
    }

    _synapses.clear( );
  }

  unsigned int Circuit::numberOfSynapses( void ) const
  {
    return (( unsigned int )_synapses.size( ));
  }


  /** Efferents and afferents synapses **/
  const std::vector< SynapsePtr >& Circuit::synapses( void ) const
  {
     return _synapses;
  }

  std::set< SynapsePtr > Circuit::synapses( TDataType dataType_ ) const
  {
    std::set< SynapsePtr > synapses_;

    switch( dataType_ )
    {
      case ALL:
      {
        for( auto synapse: _synapses )
          synapses_.insert( synapse );
      }
      break;
      case PRESYNAPTICCONNECTIONS:
      {
        for( const auto& connection: _preSynapticConnections )
        {
          synapses_.insert( connection.second );
        }
      }
      break;
      case POSTSYNAPTICCONNECTIONS:
      {
        for( const auto& connection: _postSynapticConnections )
        {
          synapses_.insert( connection.second );
        }
      }
      break;
      default:
      break;
    }

    return synapses_;
  }

  std::set< SynapsePtr > Circuit::synapses( uint32_t neuronGID_,
                                            TDataType dataType_ ) const
  {
    std::set< SynapsePtr > synapses_;

    this->_calculateConnections( neuronGID_, synapses_, dataType_ );

    return synapses_;
  }

  std::set< SynapsePtr >
  Circuit::synapses( const std::set< uint32_t >& gidsNeurons_,
                     TDataType dataType_ ) const
  {

    std::set< SynapsePtr > synapses_;

    for( auto gid: gidsNeurons_ )
    {
      this->_calculateConnections( gid, synapses_, dataType_ );
    }

    return synapses_;
  }

  // Methods to computing connections
  void
  Circuit::_calculateConnections( unsigned int& neuronGID_,
                                  std::set< SynapsePtr >& synapses_,
                                  TDataType& dataType_) const
  {
    switch( dataType_ )
    {
      case PRESYNAPTICCONNECTIONS:
        this->_calculatePresynapticConnections( neuronGID_, synapses_ );
      break;
      case POSTSYNAPTICCONNECTIONS:
        this->_calculatePostsynapticConnections( neuronGID_, synapses_ );
      break;
      case ALL:
      {
        this->_calculatePresynapticConnections( neuronGID_, synapses_ );
        this->_calculatePostsynapticConnections( neuronGID_, synapses_ );
      }
      break;
        default:
      break;
    }
  }

  void
  Circuit::_calculatePresynapticConnections( unsigned int& neuronGID_,
                                    std::set< SynapsePtr >& synapses_ ) const
  {
    auto values = _preSynapticConnections.equal_range( neuronGID_ );
    for( auto value = values.first; value != values.second; ++value )
    {
      SynapsePtr synapse = value->second;
      synapses_.insert( synapse );
    }
  }

  void
  Circuit::_calculatePostsynapticConnections( unsigned int& neuronGID_,
                                     std::set< SynapsePtr >& synapses_ ) const
  {
    auto values = _postSynapticConnections.equal_range( neuronGID_ );
    for( auto value = values.first; value != values.second; ++value )
    {
      SynapsePtr synapse = value->second;
      synapses_.insert( synapse );
    }
  }


} // namespace nsol
