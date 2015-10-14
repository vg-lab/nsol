/**
 * @file    Synapse.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
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
      UNDEFINED = 0,
      DENDRODENDRITIC,
      AXODENDRITIC,
      AXOAXONIC,
      SOMATOSOMAL,
      AXOSOMATIC,
      DENDROSOMATIC
    } TSynapseType;

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default Synapse constructor
     * @param type of synapse.
     * @param id id of the synapse.
     */
    NSOL_API
    Synapse ( const TSynapseType synapseType = AXODENDRITIC,
              const unsigned short id = 0 );

    /**
     * Copy constructor
     * @param other synapse to be copied
     */
    NSOL_API
    Synapse( const Synapse& other );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~Synapse( void );

    ///@}

    /** @name Id related methods */
    ///@{

    /**
     * Method to get-set synapse id.
     * @return reference to synapse id
     */
    NSOL_API
    unsigned short & id( void );

    /**
     * Method to get the synapse id as const.
     * @return id of the synapse
     */
    NSOL_API
    unsigned short id( void ) const;

    ///@}

    /** @name getters and setters methods */
    ///@{

    /**
     * Method to get the presynaptic neuron.
     * @return pointer to the presynaptic neuron.
     */
    NSOL_API
    NeuronPtr preSynapticNeuron( void ) const;

    /**
     * Method to add a presynaptic neuron to the synapse.
     * @param presynaptic neuron.
     * @see Neuron
     */
    NSOL_API
    void preSynapticNeuron( const NeuronPtr preSynapticNeuron );


    /**
     * Method to get the postsynaptic neuron.
     * @return pointer to the postsynaptic neuron.
     */
    NSOL_API
    NeuronPtr postSynapticNeuron( void ) const;

    /**
     * Method to add a postsynaptic neuron to the synapse.
     * @param postsynaptic neuron.
     * @see Neuron
     */
    NSOL_API
    void postSynapticNeuron( const NeuronPtr postSynapticNeuron );

	 /**
	 * Method to get the presynaptic surface position.
	 * @return presynaptic surface position.
	 */
	 NSOL_API
	 Vec3f preSynapticSurfacePosition( void ) const;

	 /**
	 * Method to set presynaptic surface position to the synapse.
	 * @param presynaptic surface position.
	 */
	 NSOL_API
	 void preSynapticSurfacePosition( const Vec3f presynaptic_surface_position);

	 /**
	 * Method to get the postsynaptic surface position.
	 * @return postsynaptic surface position.
	 */
	 NSOL_API
	 Vec3f postSynapticSurfacePosition( void ) const;

	 /**
	 * Method to set postsynaptic surface position to the synapse.
	 * @param postsynaptic surface position.
	 */
	 NSOL_API
	 void postSynapticSurfacePosition( const Vec3f postsynaptic_surface_position);

    /**
     * Method to get the synapse type.
     * @return synapse type
     */
    NSOL_API
    //! Get the type of synapse
    TSynapseType synapseType( void ) const;

    NSOL_API
    //! Set the type of synapse
    void synapseType( const TSynapseType synapseType );

    ///@}

    /** @name Operators */
    ///@{

    NSOL_API
    virtual Synapse& operator = ( const Synapse& other );

    NSOL_API
    virtual bool operator == ( const Synapse& other );

    NSOL_API
    virtual bool operator != ( const Synapse& other );

    ///@}

  protected:

    //! id of this synapse
    unsigned short _id;

    //! Presynaptic neuron
    NeuronPtr _preSynapticNeuron;

    //! Postsynaptic neuron
    NeuronPtr _postSynapticNeuron;

    //! Presynaptic surface position
    Vec3f _preSynapticSurfacePosition;

    //! Postsynaptic surface position
    Vec3f _postSynapticSurfacePosition;

    TSynapseType _synapseType;

  }; // namespace nsol

}

#endif

// EOF
