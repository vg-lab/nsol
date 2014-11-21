/**
 * @file    Synapse.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SYNAPSE__
#define __NSOL_SYNAPSE__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Neuron.h>


namespace nsol
{

	class SynapseNeuriteToNeurite;
	class SynapseNeuriteToSoma;
	class SynapseSomaToSoma;

	/*! \class Synapse
	  \brief A class to represent synapses.

	  TODO: extend long description
	*/
  class Synapse
  {

  public:

	 //! Possible types of synapse
	  typedef enum
	  {
		  AXODENDRITIC,
		  SOMATOSOMAL,
		  AXOSOMATIC,
		  AXOAXONIC,
		  DENDRODENDRÍTIC,
		  DENDROSOMATIC
	  } TSynapseType;

	  /** @name Constructors and destructors  */
	  ///@{

	 /**
	  * Default Synapse class constructor.
	  */
	  NSOL_API
	  Synapse(const TSynapseType neuriteType);

	  NSOL_API
	  virtual ~Synapse(void);

	  ///@}


	  /** @name getters and setters methods */
	  ///@{

	  /**
	  * Method to add a presynaptic neuron to the synapse.
	  * @param presynaptic neuron.
	  * @see Neuron
	  * @return pointer to the added presynaptic neuron added
	  */
	 NSOL_API
	 NeuronPtr addPreSinapticNeuron( Neuron presinaptic_neuron);

	  /**
	  * Method to add a postsynaptic neuron to the synapse.
	  * @param postsynaptic neuron.
	  * @see Neuron
	  * @return pointer to the added postsynaptic neuron added
	  */
	 NSOL_API
	 NeuronPtr addPostSinapticNeuron( Neuron postsinaptic_neuron);

	 /**
	 * Method to get the presynaptic neuron.
	 * @return pointer to the presynaptic neuron.
	 */
	 NSOL_API
	 NeuronPtr preSynapticNeuron( void ) const;

	 /**
	 * Method to get the postsynaptic neuron.
	 * @return pointer to the postsynaptic neuron.
	 */
	 NSOL_API
	 NeuronPtr postSynapticNeuron( void ) const;

	 /**
	 * Method to get the synapse type.
	 * @return synapse type
	 */
	NSOL_API
	TSynapseType & synapseType();

	///@}

  protected:

	  NeuronPtr _preSynapticNeuron;

	  NeuronPtr _postSynapticNeuron;

	  TSynapseType _type;
  }; // namespace nsol

}

#endif

// EOF
