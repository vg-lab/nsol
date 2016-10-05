/**
 * @file    SynapseNeuriteToNeurite.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SYNAPSE_NEURITE_TO_NEURITE__
#define __NSOL_SYNAPSE_NEURITE_TO_NEURITE__

#include <nsol/api.h>
#include "NsolTypes.h"
#include "Synapse.h"

namespace nsol
{

  /*! \class SynapseNeuriteToNeurite
    \brief A class to represent synapses neurite to neurite.

    TODO: extend long description
  */
  class SynapseNeuriteToNeurite : public virtual Synapse
  {

  public:

    /** @name Constructors  */
    ///@{

    /**
     * Default SynapseNeuriteToNeurite class constructor.
     * TODO: construct protected objects
     */
    NSOL_API
    SynapseNeuriteToNeurite ( const TSynapseType synapseType_ =
                              Synapse::AXODENDRITIC,
                              const unsigned int id = 0 );

    /**
     * Copy constructor
     * @param other synapse neutiteToneurite to be copied
     */
    NSOL_API
    SynapseNeuriteToNeurite( const SynapseNeuriteToNeurite& other );

    ///@}
    /** @name getters and setters methods */
    ///@{

    /**
     * Method to add a presynaptic section to the synapse.
     * @param presynaptic section.
     * @see Synapse
     * @return pointer to the added presynaptic section added
     */
    NSOL_API
    void preSynapticSection( const SectionPtr preSynapticSection);

    /**
     * Method to add a postsynaptic section to the synapse.
     * @param postsynaptic section.
     * @see Synapse
     * @return pointer to the added postsynaptic section added
     */
    NSOL_API
    void postSynapticSection( const SectionPtr postSynapticSection);

    /**
     * Method to add a presynaptic node to the synapse.
     * @param presynaptic node.
     * @see Synapse
     * @return pointer to the added presynaptic node added
     */
    NSOL_API
    void preSynapticNode( const NodePtr preSynapticNode);

    /**
     * Method to add a postsynaptic node to the synapse.
     * @param postsynaptic node.
     * @see Synapse
     * @return pointer to the added postsynaptic node added
     */
    NSOL_API
    void postSynapticNode( const NodePtr postSynapticNode);

    /**
     * Method to get the presynaptic section.
     * @return pointer to the presynaptic section.
     */
    NSOL_API
    SectionPtr preSynapticSection( void ) const;

    /**
     * Method to get the postsynaptic section.
     * @return pointer to the postsynaptic section.
     */
    NSOL_API
    SectionPtr postSynapticSection( void ) const;

    /**
     * Method to get the presynaptic node.
     * @return pointer to the presynaptic node.
     */
    NSOL_API
    NodePtr preSynapticNode( void ) const;

    /**
     * Method to get the postsynaptic node.
     * @return pointer to the postsynaptic node.
     */
    NSOL_API
    NodePtr postSynapticNode( void ) const;

    ///@}

    /** @name Operators */
    ///@{

    NSOL_API
    virtual SynapseNeuriteToNeurite& operator =
    ( const SynapseNeuriteToNeurite& other );

    NSOL_API
    virtual bool operator == ( const SynapseNeuriteToNeurite& other );

    NSOL_API
    virtual bool operator != ( const SynapseNeuriteToNeurite& other );

    ///@}


  protected:

    //! Section of a presynaptic neuron (neurite)
    SectionPtr _preSynapticSection;

    //! Section of a postsynaptic neuron (neurite)
    SectionPtr _postSynapticSection;

    //! Node of a presynaptic neuron (neurite)
    NodePtr _preSynapticNode;

    //! Node of a postsynaptic neuron (neurite)
    NodePtr _postSynapticNode;

  }; // class SynapseNeuriteToNeurite

}// namespace nsol

#endif

//EOF
