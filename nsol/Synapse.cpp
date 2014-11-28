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

} // namespace nsol

// EOF
