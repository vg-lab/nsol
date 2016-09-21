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
  Circuit::Circuit( const unsigned short identifier )
  {
    _id = identifier;
  }

  Circuit::Circuit( const Circuit& other )
    : _id ( other.id( ))
    ,_connections( other.connections( ))
  {
  }

  Circuit::~Circuit( void )
  {
    _connections.clear( );
  }

  //
  // Morphological measures methods
  //
  unsigned short& Circuit::id( void )
  {
    return _id;
  }

  unsigned short Circuit::id( void ) const
  {
    return _id;
  }

  //
  // Operators
  //
  Circuit& Circuit::operator = ( const Circuit& other )
  {
    if ( this != &other )
    {
      this->id( ) = other.id( );
      this->connections( ) = other.connections( );
    }

    return *this;

  }

  bool Circuit::operator == ( Circuit& other ) const
  {
    return ( ( this->id( ) == other.id( ) ) &&
             ( this->connections( ) == other.connections( )));
  }

  bool Circuit::operator != (Circuit & other ) const
  {
    return !( ( this->id( ) == other.id( ) ) &&
              ( this->connections( ) == other.connections( )));
  }


  //
  // Connections methods
  //
  void Circuit::addConnection( SynapsePtr synapse )
  {

    _connections.insert(synapse);

  }

  bool Circuit::removeConnection( SynapsePtr synapse )
  {
    std::set< SynapsePtr >::iterator cIt = _connections.find( synapse );

    if( cIt == _connections.end( ))
      return false;

    _connections.erase( cIt );
    return true;

  }

  void Circuit::clearConnections( void )
  {
    _connections.clear( );
  }

  std::set< SynapsePtr > & Circuit::connections( void )
  {
    return _connections;
  }

  const std::set< SynapsePtr >& Circuit::connections( void ) const
  {
    return _connections;
  }

  unsigned int Circuit::numberOfConnections( ) const
  {
    return ( unsigned int ) _connections.size( );
  }

  //
  // Afferent & Efferent synapses methods
  //
  std::set< SynapsePtr > Circuit::afferentSynapses( NeuronPtr neuron )
  {
     std::set< SynapsePtr > affSynapses;

     NSOL_FOREACH( connection, _connections )
     {
         NeuronPtr n_post = (*connection)->postSynapticNeuron( );
         SynapsePtr syn   = (*connection);

         if( n_post == neuron )
             affSynapses.insert( syn );
     }

     return affSynapses;
  }

  std::set< SynapsePtr > Circuit::efferentSynapses( NeuronPtr neuron )
  {
    std::set< SynapsePtr > effSynapses;

    NSOL_FOREACH( connection, _connections )
    {
        NeuronPtr n_pre = (*connection)->preSynapticNeuron( );
        SynapsePtr syn  = (*connection);

        if( n_pre == neuron )
            effSynapses.insert( syn );
    }

    return effSynapses;
  }

  void Circuit::clearAfferentSynapses( NeuronPtr neuron )
  {
     std::set< SynapsePtr > affSynapses;

     if( this->afferentSynapses(neuron).empty( ) )
         return;

     affSynapses = this->afferentSynapses(neuron);
     affSynapses.clear( );
  }

  void Circuit::clearEfferentSynapses( NeuronPtr neuron )
  {
    std::set< SynapsePtr > effSynapses;

    if( this->efferentSynapses(neuron).empty( ) )
        return;

    effSynapses = this->efferentSynapses(neuron);
    effSynapses.clear( );
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

    for( std::set<SynapsePtr>::iterator it=_connections.begin();
         it != _connections.end(); ++it )
    {
        SynapsePtr connection = (*it);
        NeuronPtr nPre  = connection->preSynapticNeuron();
        NeuronPtr nPost = connection->postSynapticNeuron();

        NeuronsMap::iterator itNeuronPre  = neurons.find( nPre->gid() );
        NeuronsMap::iterator itNeuronPost = neurons.find( nPost->gid() );

        if( itNeuronPre == neurons.end() || itNeuronPost == neurons.end() )
        {
            success = false;
            break;
        }

        C.insert( nPre->gid()-1, nPost->gid()-1 ) = 1.f;
        C.insert( nPost->gid()-1, nPre->gid()-1 ) = 1.f;
    }

    if( !success )
        return contacts;

    contacts.swap( C );

    return contacts;
  }


} // namespace nsol
