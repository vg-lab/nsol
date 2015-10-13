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
  Synapse::Synapse( TSynapseType synapseType_,
                    const unsigned short initId )
    : _id( initId )
    , _preSynapticNeuron( nullptr )
    , _postSynapticNeuron( nullptr )
    , _preSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
    , _postSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
    , _synapseType( synapseType_ )
  {
  }

  Synapse::Synapse( const Synapse& other )
    :  _id( other.id( ))
    ,_preSynapticNeuron( other.preSynapticNeuron( ))
    ,_postSynapticNeuron( other.postSynapticNeuron( ))
    ,_preSynapticSurfacePosition( other.preSynapticSurfacePosition( ))
    ,_postSynapticSurfacePosition( other.postSynapticSurfacePosition( ))
    ,_synapseType( other.synapseType( ) )
  {
  }

  Synapse::~Synapse( void )
  {
  }

  //! Get the type of synapse
  unsigned short & Synapse::id( void )
  {
    return _id;
  }

  unsigned short Synapse::id( void ) const
  {
    return _id;
  }

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

  void Synapse::preSynapticSurfacePosition( Vec3f presynaptic_surface_position)
  {
  		 _preSynapticSurfacePosition = presynaptic_surface_position;
  }

  Vec3f Synapse::preSynapticSurfacePosition( void ) const
  {
	  return _preSynapticSurfacePosition;
  }

  void Synapse::postSynapticSurfacePosition( Vec3f postsynaptic_surface_position)
  {
	  _postSynapticSurfacePosition = postsynaptic_surface_position;
  }

  Vec3f Synapse::postSynapticSurfacePosition( void ) const
  {
	  return _postSynapticSurfacePosition;
  }

  //
  // Operators
  //const

  Synapse& Synapse::operator = ( const Synapse& other)
  {
    if (this != &other)
    {
      this->id( ) = other.id( );
      this->synapseType( other.synapseType( ));
      this->preSynapticNeuron( other.preSynapticNeuron( ));
      this->postSynapticNeuron( other.postSynapticNeuron( ));
      this->preSynapticSurfacePosition( other.preSynapticSurfacePosition( ));
      this->postSynapticSurfacePosition( other.postSynapticSurfacePosition( ));
    }

    return *this;
  }

  bool Synapse::operator == ( const Synapse& other )
  {
    return ( ( this->id( ) == other.id( ) ) &&
             ( this->synapseType( ) == other.synapseType( ) ) &&
             ( (this->preSynapticNeuron( )) == (other.preSynapticNeuron( ))) &&
             ( (this->postSynapticNeuron( )) == (other.postSynapticNeuron( ))) &&
             ( (this->preSynapticSurfacePosition( )) == (other.preSynapticSurfacePosition())) &&
             ( (this->postSynapticSurfacePosition( ) == (other.postSynapticSurfacePosition( )))));
  }

  bool Synapse::operator != ( const Synapse& other )
  {

    return !( *this == other );
  }

} // namespace nsol

// EOF
