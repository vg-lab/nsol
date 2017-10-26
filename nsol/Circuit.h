/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo Pellon <raquel.jarillo@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
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
    }TDataType;

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
     * @param synapse_ synapse to add to this circuit
     */
    NSOL_API
    void addSynapse( SynapsePtr synapse_ );

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
    unsigned int numberOfSynapses( void ) const;

    ///@}

    /** @name Afferent & Efferent synapses related methods */
    ///@{

    /**
     * Method to get all the synapses from the circuit.
     * @return vector with all the ordered synapses by its gid
     */
    NSOL_API
    std::vector< SynapsePtr > synapses( void ) const;

    /**
     * Method to get all the synapses from the circuit.
     * @param dataType_ Data type
     * @return subset with all the synapses
     */
    NSOL_API
    std::set< SynapsePtr > synapses( TDataType dataType_ ) const;

    /**
     * Method to get all the sinapses of the neuron into the circuit.
     * @param neuronGID_ neuron id
     * @param dataType_ Data type
     * @return all the synapses of this neuron.
     */
    NSOL_API
    std::set< SynapsePtr >
    synapses(uint32_t neuronGID_, TDataType dataType_ ) const;

    /**
     * Method to get all the sinapses from a subset of neurons.
     * @param gidsNeurons_ subset of ids neurons
     * @param dataType_ Data type
     * @return all the synapses of this subset of neurons.
     */
    NSOL_API
    std::set< SynapsePtr >
    synapses(const std::set< uint32_t > &gidsNeurons_,
              TDataType dataType_ ) const;

    ///@}

  private:

    void
    _calculateConnections( unsigned int& neuronGID_,
                           std::set< SynapsePtr >& synapses_ ,
                           TDataType &dataType_ ) const;

    void
    _calculatePresynapticConnections( unsigned int& neuronGID_,
                                      std::set< SynapsePtr >& synapses_ ) const;

    void
    _calculatePostsynapticConnections( unsigned int& neuronGID_,
                                      std::set< SynapsePtr >& synapses_ ) const;

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
