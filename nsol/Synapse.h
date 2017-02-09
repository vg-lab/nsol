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

  /*! \class Synapse
    \brief A class to represent synapses.

    TODO: extend long description
  */
  class Synapse
  {

  public:

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default Synapse constructor
     */
    NSOL_API
    Synapse( void );

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

    /** @name getters and setters methods */
    ///@{

    /**
     * Method to get the gid of the presynaptic neuron.
     * @return gid of the presynaptic neuron.
     */
    NSOL_API
    unsigned int preSynapticNeuron( void ) const;

    /**
     * Method to add a presynaptic neuron to the synapse.
     * @param gid of the presynaptic neuron.
     * @see Neuron
     */
    NSOL_API
    void preSynapticNeuron( const unsigned int neuronID );

    /**
      * Method to get the gid of the postsynaptic neuron.
      * @return gid of the postsynaptic neuron.
      */
    NSOL_API
    unsigned int postSynapticNeuron( void ) const;

    /**
     * Method to add a postsynaptic neuron to the synapse.
     * @param gid of the postsynaptic neuron.
     * @see Neuron
     */
    NSOL_API
    void postSynapticNeuron( const unsigned int neuronID );

    /**
     * Method to set the synaptic weight.
     * @param synaptic weight.
     */
    NSOL_API
    void weight( const float weight_ );

    /**
     * Method to get the synaptic weight.
     * @return synaptic weight.
     */
    NSOL_API
    float weight( void ) const;

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

    //! GID Presynaptic neuron
    unsigned int _preSynapticNeuron;

    //! GID Postsynaptic neuron
    unsigned int _postSynapticNeuron;

    //! The synaptic weight
    float _weight;

  };

} // namespace nsol

#endif // __NSOL_SYNAPSE__
