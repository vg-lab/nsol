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
  void Circuit::addSynapse( SynapsePtr synapse )
  {
    _synapses.push_back( synapse );

    std::pair< unsigned int, SynapsePtr> preSynapticConnection(
                                       synapse->preSynapticNeuron( ), synapse );

    std::pair< unsigned int, SynapsePtr> postSynapticConnection(
                                      synapse->postSynapticNeuron( ), synapse );

    _preSynapticConnections.insert( preSynapticConnection );
    _postSynapticConnections.insert( postSynapticConnection );
  }

  void Circuit::clear( void )
  {
    _preSynapticConnections.clear( );
    _postSynapticConnections.clear( );

    _synapses.clear( );
  }

  size_t Circuit::numberOfSynapses( void ) const
  {
    return _synapses.size( );
  }


  /** Efferents and afferents synapses **/
  std::set<SynapsePtr> Circuit::synapses( TDataType dataType ) const
  {
    std::set<SynapsePtr> synapses_;

    switch( dataType )
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

    return std::move( synapses_ );
  }

  std::set<SynapsePtr> Circuit::synapses( unsigned int neuronGID,
                                          TDataType dataType ) const
  {
    std::set<SynapsePtr> synapses_;

    switch( dataType )
    {
      case PRESYNAPTICCONNECTIONS:

        this->_calculatePresynapticConnections( neuronGID, synapses_ );

      break;
      case POSTSYNAPTICCONNECTIONS:

        this->_calculatePostsynapticConnections( neuronGID, synapses_ );

      break;

      case ALL:
      {
        this->_calculatePresynapticConnections( neuronGID, synapses_ );

        this->_calculatePostsynapticConnections( neuronGID, synapses_ );
      }
      break;
      default:
      break;
    }

    return std::move( synapses_ );
  }

  std::set<SynapsePtr>
  Circuit::synapses( const std::set<unsigned int>& gidsNeurons,
                     TDataType dataType ) const
  {
    std::set<SynapsePtr> synapses_;

    for( auto gid: gidsNeurons )
    {
      std::set<SynapsePtr> aux = this->synapses( gid, dataType );

      for( auto synapse: aux )
        synapses_.insert( synapse );
    }

    return std::move( synapses_ );
  }


} // namespace nsol
