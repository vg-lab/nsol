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

  Synapse::Synapse( const Synapse& other )
  : _preSynapticNeuron( other.preSynapticNeuron( ))
  , _postSynapticNeuron( other.postSynapticNeuron( ))
  , _weight( other.weight( ))
   {
   }

  Synapse::~Synapse( void )
  {
  }

  void Synapse::preSynapticNeuron(const unsigned int neuronID )
  {
    _preSynapticNeuron = neuronID;
  }

  unsigned int Synapse::preSynapticNeuron( void ) const
  {
    return _preSynapticNeuron;
  }

  void Synapse::postSynapticNeuron(const unsigned int neuronID )
  {
    _postSynapticNeuron = neuronID;
  }

  unsigned int Synapse::postSynapticNeuron( void ) const
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

  Synapse& Synapse::operator = ( const Synapse& other )
  {
    if (this != &other)
    {
      this->preSynapticNeuron( other.preSynapticNeuron( ));
      this->postSynapticNeuron( other.postSynapticNeuron( ));
      this->weight( other.weight( ));
    }

    return *this;
  }

  bool Synapse::operator == ( const Synapse& other )
  {
    return (( this->preSynapticNeuron( ) == other.preSynapticNeuron( )) &&
            ( this->postSynapticNeuron( ) == other.postSynapticNeuron( )) &&
            ( this->weight( ) == other.weight( )));
  }

  bool Synapse::operator != ( const Synapse& other )
  {
    return !( *this == other );
  }

} // namespace nsol

// EOF
