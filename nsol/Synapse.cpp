/**
 * @file    Synapse.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
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

	 Synapse::Synapse( Synapse & other )
	     : _preSynapticNeuron( other.preSynapticNeuron( ))
	 	 , _postSynapticNeuron( other.postSynapticNeuron( ) )
	 	 , _synapseType( other.synapseType( ) )
	 {
	 }

	 Synapse::~Synapse( void )
	 {
	 }

	 // !Get the type of synapse
	 Synapse::TSynapseType & Synapse::synapseType( void )
     {
		 return _synapseType;
     }

	 void Synapse::preSynapticNeuron( NeuronPtr presynaptic_neuron)
	 {
		 _preSynapticNeuron = presynaptic_neuron;
	 }

	 void Synapse::postSynapticNeuron( NeuronPtr postsynaptic_neuron)
	 {
		 _postSynapticNeuron = postsynaptic_neuron;
	 }

	 NeuronPtr Synapse::preSynapticNeuron( void )
	 {
		 return _preSynapticNeuron;
	 }

	 NeuronPtr Synapse::postSynapticNeuron( void )
	 {
		 return _postSynapticNeuron;
	 }

	  //
	  // Operators
	  //const

	  Synapse & Synapse::operator = (Synapse & other)
	  {
		 Synapse * SynapseDerivedPtr;
		 SynapseDerivedPtr = dynamic_cast<  Synapse *>(&other);
		if ( SynapseDerivedPtr == 0)
			throw std::runtime_error("Unlike types.");

	    if (this != SynapseDerivedPtr)
	    {
	      this->synapseType( ) = SynapseDerivedPtr->synapseType( );
	      this->preSynapticNeuron(SynapseDerivedPtr->preSynapticNeuron( ) );
	      this->postSynapticNeuron(SynapseDerivedPtr->postSynapticNeuron( ));
	    }

	    return *this;
	  }

	  bool Synapse::operator == (Synapse & other )
	  {
	    return ( ( this->synapseType( ) == other.synapseType( ) ) &&
	    	   ( (this->preSynapticNeuron( )) == (other.preSynapticNeuron( ))) &&
	    	   ( (this->postSynapticNeuron( )) == (other.postSynapticNeuron( ))));
	  }

	  bool Synapse::operator != (Synapse & other )
	  {

		  Synapse * synapseDerivedPtr;
		  synapseDerivedPtr = dynamic_cast<Synapse *>(&other);

		 if ( synapseDerivedPtr == 0)
		    return true;

	     return !( *this == *synapseDerivedPtr);
	  }

} // namespace nsol

// EOF
