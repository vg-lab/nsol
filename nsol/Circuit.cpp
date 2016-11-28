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
    void Circuit::addConnection( SynapsePtr synapse )
    {
        Synapse synapse_ = ( *synapse );
        _synapses.push_back( synapse_ );

        std::pair< unsigned int, SynapsePtr> preSynapticConnection(
                                       synapse->preSynapticNeuron( ), synapse );

        std::pair< unsigned int, SynapsePtr> postSynapticConnection(
                                      synapse->postSynapticNeuron( ), synapse );

        _preSynapticConnections.insert( preSynapticConnection );
        _postSynapticConnections.insert( postSynapticConnection );
    }

    bool Circuit::removeConnection( SynapsePtr synapse )
    {

        bool existSynapse = false;

        for( auto it = _synapses.begin(); it != _synapses.end(); ++it )
        {
            if( it->id( ) == synapse->id( ))
            {
                _synapses.erase( it );
                existSynapse = true;
                break;
            }
        }

        for( auto itMap= _preSynapticConnections.begin();
                  itMap != _preSynapticConnections.end(); ++itMap )
        {
            unsigned int idNeuron = itMap->first;

            auto synapses = _preSynapticConnections.equal_range( idNeuron );
            for( auto it = synapses.first; it != synapses.second; ++it )
            {
                SynapsePtr s = it->second;
                if( s->id( ) == synapse->id( ))
                {
                    _preSynapticConnections.erase( it );
                    break;
                }
            }
        }

        for( auto itMap= _postSynapticConnections.begin();
                  itMap != _postSynapticConnections.end(); ++itMap )
        {
            unsigned int idNeuron = itMap->first;

            auto synapses = _postSynapticConnections.equal_range( idNeuron );
            for( auto it = synapses.first; it != synapses.second; ++it )
            {
                SynapsePtr s = it->second;
                if( s->id( ) == synapse->id( ))
                {
                    _postSynapticConnections.erase( it );
                    break;
                }
            }
        }

        return existSynapse = true;;

    }

    void Circuit::clearConnections( void )
    {
        _preSynapticConnections.clear( );
        _postSynapticConnections.clear( );

        _synapses.clear( );
    }

    unsigned int Circuit::numberOfConnections( void ) const
    {
        return _synapses.size( );
    }

    std::set< SynapsePtr> Circuit::afferentSynapses( NeuronPtr neuron )
    {
       std::set< SynapsePtr> synapses;

       auto search = _postSynapticConnections.find( neuron->gid( ));

       if( search != _postSynapticConnections.end( ))
       {
           auto values = _postSynapticConnections.equal_range( neuron->gid( ));
           for( auto it = values.first; it != values.second; ++it )
           {
               SynapsePtr synapse = it->second;
               synapses.insert( synapse );
           }
       }

       return std::move( synapses );
    }

    std::set< SynapsePtr > Circuit::efferentSynapses( NeuronPtr neuron )
    {
        std::set< SynapsePtr> synapses;

        auto search = _preSynapticConnections.find( neuron->gid( ));

        if( search != _preSynapticConnections.end( ))
        {
            auto values = _preSynapticConnections.equal_range( neuron->gid( ));
            for( auto it = values.first; it != values.second; ++it )
            {
                SynapsePtr synapse = it->second;
                synapses.insert( synapse );
            }
        }

        return std::move( synapses );
    }

    void Circuit::clearAfferentSynapses( NeuronPtr neuron )
    {
        auto synapses = _postSynapticConnections.equal_range( neuron->gid( ));
        for( auto synapse = synapses.first; synapse != synapses.second; )
        {
            synapse = _postSynapticConnections.erase( synapse );
        }
    }

    void Circuit::clearEfferentSynapses( NeuronPtr neuron )
    {
        auto synapses = _preSynapticConnections.equal_range( neuron->gid( ));
        for( auto synapse = synapses.first; synapse != synapses.second; )
        {
            synapse = _preSynapticConnections.erase( synapse );
        }
    }

    Eigen::SparseMatrix< float > Circuit::contactsNeurons( NeuronsMap neurons )
    {
        unsigned int dim = neurons.size();

        Eigen::SparseMatrix< float > contacts;

        contacts.resize(dim, dim);
        contacts.setZero();

        for( unsigned int i = 0; i < neurons.size(); i++ )
            contacts.insert(i, i) = 1.f;

        bool success = true;
        Eigen::SparseMatrix< float > C = contacts;

        for( auto neuron: neurons )
        {
            std::set<SynapsePtr> efferents = this->efferentSynapses
                                                              ( neuron.second );
            if( !efferents.empty( ))
            {
                for( auto synapse: efferents )
                {
                    unsigned int nPre  = synapse->preSynapticNeuron();
                    unsigned int nPost = synapse->postSynapticNeuron();

                    C.insert( nPre - 1, nPost - 1 ) += 1.f;
                    C.insert( nPost - 1, nPre - 1 ) += 1.f;
                }
            }
            else
            {
                success = false;
            }
        }

        if( !success )
            return contacts;

        contacts.swap( C );

        return contacts;

    }


} // namespace nsol
