/**
 * @file    Circuit.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *           Do not distribute without further notice.
 */

#ifndef __NSOL_CIRCUIT__
#define __NSOL_CIRCUIT__

#include <nsol/api.h>
#include "Synapse.h"

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
     */
    NSOL_API
    Circuit( void );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~Circuit( void ) ;

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
    std::set< SynapsePtr> afferentSynapses( NeuronPtr neuron );

    /**
     * Method to get the efferent (outgoing) synapses projecting onto a neuron.
     * @param neuron
     * @return efferent synapses of this neuron.
     */
    NSOL_API
    std::set< SynapsePtr> efferentSynapses( NeuronPtr neuron );

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

    //! Container with all the connections between neurons
    std::vector< Synapse > _synapses;

    //! Container with all the efferents connections into the circuit
    std::unordered_multimap< unsigned int, SynapsePtr> _preSynapticConnections;

    //! Container with all the afferents connections into the circuit
    std::unordered_multimap< unsigned int, SynapsePtr> _postSynapticConnections;


  }; // class Circuit

} // namespace nsol


#endif // CIRCUIT_H
// EOF
