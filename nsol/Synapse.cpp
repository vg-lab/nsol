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

  bool Synapse::operator == ( const Synapse& other_ )
  {
    return (( this->preSynapticNeuron( ) == other_.preSynapticNeuron( )) &&
            ( this->postSynapticNeuron( ) == other_.postSynapticNeuron( )) &&
            ( this->weight( ) == other_.weight( )));
  }

  bool Synapse::operator != ( const Synapse& other_ )
  {
    return !( *this == other_ );
  }

} // namespace nsol

// EOF
