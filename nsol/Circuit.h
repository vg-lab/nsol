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

      //! Possible types of data to get
      typedef enum
      {
        ALL = 0,
        PRESYNAPTICCONNECTIONS,
        POSTSYNAPTICCONNECTIONS
      } TDataType;

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
     * Method to add a connection into the cirtuit.
     * @param synapse to add to this circuit
     * @return true if connection added false otherwise
     */
    NSOL_API
    virtual void addSynapse( SynapsePtr synapse );

    /**
     * Method to clear all the connections
     * of all the circuit.
     */
    NSOL_API
    void clear( void );

    /**
     * Method to get the total number of connections of the circuit.
     * @return total numbers of synapses
     */
    NSOL_API
    virtual size_t numberOfSynapses( void ) const;

    ///@}

    /** @name Afferent & Efferent synapses related methods */
    ///@{

    /**
     * Method to get all the synapses from the circuit.
     * @return subset with all the synapses
     */
    NSOL_API
    std::set<SynapsePtr> synapses( TDataType dataType );

    /**
     * Method to get all the sinapses of the neuron into the circuit.
     * @param neuron id
     * @return all the synapses of this neuron.
     */
    NSOL_API
    std::set<SynapsePtr> synapses( unsigned int neuronGID, TDataType dataType );

    /**
     * Method to get all the sinapses from a subset of neurons.
     * @param subset of ids neurons
     * @return all the synapses of this subset of neurons.
     */
    NSOL_API
    std::set<SynapsePtr> synapses( std::set< unsigned int > gidsNeurons,
                                   TDataType dataType );

    ///@}


  protected:

    //! Container with all the connections between neurons
    std::vector< SynapsePtr > _synapses;

    //! Container with all the efferents connections into the circuit
    SynapsesMap _preSynapticConnections;

    //! Container with all the afferents connections into the circuit
    SynapsesMap _postSynapticConnections;


  }; // class Circuit

} // namespace nsol


#endif // CIRCUIT_H
// EOF
