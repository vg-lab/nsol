/**
 * @file    Circuit.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *           Do not distribute without further notice.
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
    _synapses.clear();

    _preSynapticConnections.clear( );
    _postSynapticConnections.clear( );
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

  void Circuit::clear( void )
  {
    _preSynapticConnections.clear( );
    _postSynapticConnections.clear( );    

    for( auto synapse: _synapses )
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
  std::vector< SynapsePtr > Circuit::synapses( void ) const
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

    return synapses_;
  }

  std::set< SynapsePtr >
  Circuit::synapses( const std::set< uint32_t >& gidsNeurons_,
                     TDataType dataType_ ) const
  {
    std::set< SynapsePtr > synapses_;

    for( auto gid: gidsNeurons_ )
    {
      std::set< SynapsePtr > aux = std::move(this->synapses( gid, dataType_ ));

      for( auto synapse: aux )
        synapses_.insert( synapse );
    }

    return synapses_;
  }


  // Methods to computing connections
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
