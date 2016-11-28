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
   , _weight( other.getWeight( ))
    {
    }

   Synapse::~Synapse( void )
   {
   }

   unsigned int & Synapse::id( void )
   {
     return _id;
   }

   unsigned int Synapse::id( void ) const
   {
     return _id;
   }

   void Synapse::preSynapticNeuron( const unsigned int neuron )
   {
       _preSynapticNeuron = neuron;
   }

   unsigned int Synapse::preSynapticNeuron( void ) const
   {
       return _preSynapticNeuron;
   }

   void Synapse::postSynapticNeuron( const unsigned int neuron )
   {
       _postSynapticNeuron = neuron;
   }

   unsigned int Synapse::postSynapticNeuron( void ) const
   {
       return _postSynapticNeuron;
   }

   void Synapse::setWeight( const float weight )
   {
       _weight = weight;
   }

   float Synapse::getWeight( void ) const
   {
       return _weight;
   }

   Synapse::TSynapseType Synapse::getType( void ) const
   {
       return Synapse::UNDEFINED;
   }

   Synapse& Synapse::operator = ( const Synapse& other )
   {
     if (this != &other)
     {
       this->preSynapticNeuron( other.preSynapticNeuron( ));
       this->postSynapticNeuron( other.postSynapticNeuron( ));
       this->setWeight( other.getWeight( ));
     }

     return *this;
   }

   bool Synapse::operator == ( const Synapse& other )
   {
     return (( this->preSynapticNeuron( ) == other.preSynapticNeuron( )) &&
             ( this->postSynapticNeuron( ) == other.postSynapticNeuron( )) &&
             ( this->getWeight( ) == other.getWeight( )));
   }

   bool Synapse::operator != ( const Synapse& other )
   {
     return !( *this == other );
   }

} // namespace nsol

// EOF
