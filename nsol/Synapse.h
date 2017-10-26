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
     * @param other_ synapse to be copied
     */
    NSOL_API
    Synapse( const Synapse& other_ );

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
    uint32_t preSynapticNeuron( void ) const;

    /**
     * Method to add a presynaptic neuron to the synapse.
     * @param neuronID_ gid of the presynaptic neuron.
     * @see Neuron
     */
    NSOL_API
    void preSynapticNeuron(const uint32_t neuronID_ );

    /**
      * Method to get the gid of the postsynaptic neuron.
      * @return gid of the postsynaptic neuron.
      */
    NSOL_API
    uint32_t postSynapticNeuron( void ) const;

    /**
     * Method to add a postsynaptic neuron to the synapse.
     * @param neuronID_ gid of the postsynaptic neuron.
     * @see Neuron
     */
    NSOL_API
    void postSynapticNeuron( const uint32_t neuronID_ );

    /**
     * Method to set the synaptic weight.
     * @param weight_ synaptic weight.
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
    virtual Synapse& operator = (const Synapse& other_ );

    ///@}

  protected:

    //! GID Presynaptic neuron
    uint32_t _preSynapticNeuron;

    //! GID Postsynaptic neuron
    uint32_t _postSynapticNeuron;

    //! The synaptic weight
    float _weight;

  };

} // namespace nsol

#endif // __NSOL_SYNAPSE__
