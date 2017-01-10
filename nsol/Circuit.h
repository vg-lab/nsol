/**
 * @file    Circuit.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_CIRCUIT__
#define __NSOL_CIRCUIT__

#include <nsol/api.h>
#include "Container/Synapses.h"

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>
#include <set>


namespace nsol
{
  /*! \class Circuit
    \brief A class to represent connections between neurons.
    TODO: extend long description
  */
  class Circuit
  {

  public:

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default constructor
     * @param id id of the circuit.
     */
    NSOL_API
    Circuit( unsigned short id = 0 );

    /**
     * Copy constructor
     * @param other circuit to be copied
     */
    NSOL_API
    Circuit( const Circuit & other );


    /**
     * Default destructor
     */
    NSOL_API
    virtual ~Circuit( void ) ;

    ///@}

    /** @name Id related methods */
    ///@{

    /**
     * Method to get-set the circuit id.
     * @return circuit id
     */
    NSOL_API
    unsigned short & id( void );

    /**
     * Method to get the circuit id.
     * @return reference to circuit id
     */
    NSOL_API
    unsigned short id( void ) const;

    ///@}

    /** @name Operators */
    ///@{

    NSOL_API
    Circuit & operator = (const Circuit & other);

    NSOL_API
    bool operator == (Circuit & other ) const;

    NSOL_API
    bool operator != (Circuit & other ) const;

    ///@}

    /** @name Connections related methods */
    ///@{

    /**
     * Method to add a connection.
     * @param synapse to add to this circuit
     * @return true if connection added false otherwise
     */
    NSOL_API
    virtual void addConnection( SynapsePtr synapse );

    /**
     * Method to remove a connection.
     * @param synapse to be removed
     * @return true if the connection removed false otherwise
     */
    NSOL_API
    virtual bool removeConnection( SynapsePtr synapse );

    /**
     * Method to clear all the connections
     * of all the circuit.
     */
    NSOL_API
    virtual void clearConnections( void );

    /**
     * Method to get all the connections (synapses of the circuit).
     * @return synapses of the circuit
     */
    NSOL_API
    virtual std::set<SynapsePtr>& connections( void );

    /**
     * Method to get all the connections as const.
     * @return synapses of the circuit
     */
    NSOL_API
    virtual const std::set<SynapsePtr>& connections( void ) const;

    /**
     * Method to get the total number of connections of the circuit.
     * @return total numbers of connections
     */
    NSOL_API
    virtual unsigned int numberOfConnections( void ) const;

    ///@}

    /** @name Afferent & Efferent synapses related methods */
    ///@{

    /**
     * Method to get the afferent (incoming) synapses projecting onto a neuron.
     * @param neuron
     * @return afferent synapses of this neuron.
     */
    NSOL_API
    std::set< SynapsePtr > afferentSynapses( NeuronPtr neuron );

    /**
     * Method to get the efferent (outgoing) synapses projecting onto a neuron.
     * @param neuron
     * @return efferent synapses of this neuron.
     */
    NSOL_API
    std::set< SynapsePtr > efferentSynapses( NeuronPtr neuron );

    /**
     * Method to clear the afferent (incoming) synapses
     * projecting onto a neuron.
     * @param neuron
     */
    NSOL_API
    void clearAfferentSynapses( NeuronPtr neuron );

    /**
     * Method to clear the efferent (incoming) synapses
     * projecting onto a neuron.
     * @param neuron
     */
    NSOL_API
    void clearEfferentSynapses( NeuronPtr neuron );

    /**
     * Method to obtain the sparse matrix with the relationships
     * between each pair of neurons.
     * @param neurons
     */
    NSOL_API
    Eigen::SparseMatrix< float > contactsNeurons( NeuronsMap neurons );

     ///@}


  protected:

    //! Identifier of the circuit
    unsigned short _id;

    //! Container with the all connections between neurons
    std::set<SynapsePtr> _connections;


  }; // class Circuit

} // namespace nsol


#endif // __NSOL_CIRCUIT__
// EOF
