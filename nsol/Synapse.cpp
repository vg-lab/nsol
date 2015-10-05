/**
 * @file    Synapse.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include "Synapse.h"

namespace nsol
{
  //! Default constructor and destructor
  Synapse::Synapse( TSynapseType synapseType_ )
    : _preSynapticNeuron( nullptr )
    , _postSynapticNeuron( nullptr )
    , _synapseType( synapseType_ )
  {
  }

  Synapse::Synapse( const Synapse& other )
    :_preSynapticNeuron( other.preSynapticNeuron( ))
    ,_postSynapticNeuron( other.postSynapticNeuron( ))
    ,_synapseType( other.synapseType( ) )
  {
  }

  Synapse::~Synapse( void )
  {
  }

  //! Get the type of synapse
  Synapse::TSynapseType Synapse::synapseType( void ) const
  {
    return _synapseType;
  }

  void Synapse::synapseType( Synapse::TSynapseType synapseType_ )
  {
    _synapseType = synapseType_;
  }


  void Synapse::preSynapticNeuron( NeuronPtr preSynapticNeuron_ )
  {
    _preSynapticNeuron = preSynapticNeuron_;
  }

  void Synapse::postSynapticNeuron( NeuronPtr postSynapticNeuron_ )
  {
    _postSynapticNeuron = postSynapticNeuron_;
  }

  NeuronPtr Synapse::preSynapticNeuron( void ) const
  {
    return _preSynapticNeuron;
  }

  NeuronPtr Synapse::postSynapticNeuron( void ) const
  {
    return _postSynapticNeuron;
  }

  //
  // Operators
  //const

  Synapse& Synapse::operator = ( const Synapse& other)
  {
    this->synapseType( other.synapseType( ));
    this->preSynapticNeuron( other.preSynapticNeuron( ));
    this->postSynapticNeuron( other.postSynapticNeuron( ));

    return *this;
  }

  bool Synapse::operator == ( const Synapse& other )
  {
    return ( ( this->synapseType( ) == other.synapseType( ) ) &&
             ( (this->preSynapticNeuron( )) == (other.preSynapticNeuron( ))) &&
             ( (this->postSynapticNeuron( )) == (other.postSynapticNeuron( ))));
  }

  bool Synapse::operator != ( const Synapse& other )
  {

    return !( *this == other );
  }

} // namespace nsol

// EOF
