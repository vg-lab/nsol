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
    std::set<SynapsePtr> Circuit::synapses( TDataType dataType )
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
               for( auto it = _preSynapticConnections.begin();
                         it != _preSynapticConnections.end(); it++ )
               {
                   synapses_.insert( it->second );
               }
           }
           break;
           case POSTSYNAPTICCONNECTIONS:
           {
              for( auto it = _postSynapticConnections.begin();
                        it != _postSynapticConnections.end(); it++ )
              {
                  synapses_.insert( it->second );
              }
           }
           break;
           default:
           break;
       }

       return std::move( synapses_ );
    }

    std::set<SynapsePtr> Circuit::synapses( unsigned int neuronGID,
                                            TDataType dataType )
    {
       std::set<SynapsePtr> synapses_;

       switch( dataType )
       {
          case PRESYNAPTICCONNECTIONS:
          {
             auto search = _preSynapticConnections.find( neuronGID );
             if( search != _preSynapticConnections.end( ))
             {
                auto values = _preSynapticConnections.equal_range( neuronGID );
                for( auto it = values.first; it != values.second; ++it )
                {
                   SynapsePtr synapse = it->second;
                   synapses_.insert( synapse );
                }
             }
           }
           break;
           case POSTSYNAPTICCONNECTIONS:
           {
              auto search = _postSynapticConnections.find( neuronGID );
              if( search != _postSynapticConnections.end( ))
              {
                 auto values = _postSynapticConnections.equal_range( neuronGID );
                 for( auto it = values.first; it != values.second; ++it )
                 {
                    SynapsePtr synapse = it->second;
                    synapses_.insert( synapse );
                 }
               }
            }
            break;

            case ALL:
            {
              auto search = _preSynapticConnections.find( neuronGID );
              if( search != _preSynapticConnections.end( ))
              {
                 auto values = _preSynapticConnections.equal_range( neuronGID );
                 for( auto it = values.first; it != values.second; ++it )
                 {
                    SynapsePtr synapse = it->second;
                    synapses_.insert( synapse );
                 }
              }

              search = _postSynapticConnections.find( neuronGID );
              if( search != _postSynapticConnections.end( ))
              {
                 auto values = _postSynapticConnections.equal_range( neuronGID );
                 for( auto it = values.first; it != values.second; ++it )
                 {
                    SynapsePtr synapse = it->second;
                    synapses_.insert( synapse );
                 }
               }
            }
            break;
            default:
            break;
        }

        return std::move( synapses_ );
    }

    std::set<SynapsePtr> Circuit::synapses( std::set<unsigned int> gidsNeurons,
                                            TDataType dataType )
    {
        std::set<SynapsePtr> synapses_;

        for( auto it = gidsNeurons.begin(); it != gidsNeurons.end(); it++ )
        {
            std::set<SynapsePtr> aux = this->synapses( *it, dataType );

            for( auto synapse: aux )
              synapses_.insert( synapse );
        }

        return std::move( synapses_ );
    }


} // namespace nsol
