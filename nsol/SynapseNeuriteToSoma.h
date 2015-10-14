/**
 * @file    SynapseNeuriteToSoma.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SYNAPSE_NEURITE_TO_SOMA__
#define __NSOL_SYNAPSE_NEURITE_TO_SOMA__

#include <nsol/api.h>
#include "NsolTypes.h"
#include "Synapse.h"
#include "Neuron.h"

namespace nsol
{

  /*! \class SynapseNeuriteToSoma
    \brief A class to represent synapses neurite to soma.

    TODO: extend long description
  */
  class SynapseNeuriteToSoma : public virtual Synapse
  {

  public:

    /** @name Constructors  */
    ///@{

    /**
     * Default SynapseNeuriteToSoma class constructor.
     * TODO: construct protected objects
     */
    NSOL_API
    SynapseNeuriteToSoma( const TSynapseType synapseType_ =
                          Synapse::DENDROSOMATIC,
                          const unsigned short id = 0 );

    /**
     * Copy constructor
     * @param other synapse neuriteToSoma to be copied
     */
    NSOL_API
    SynapseNeuriteToSoma( const SynapseNeuriteToSoma& other );

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
    void preSynapticSection( const SectionPtr presynaptic_section );

    /**
     * Method to add a presynaptic node to the synapse.
     * @param presynaptic node.
     * @see Synapse
     * @return pointer to the added presynaptic node added
     */
    NSOL_API
    void preSynapticNode( const NodePtr presynaptic_node );

    /**
     * Method to add a postsynaptic node to the synapse.
     * @param postsynaptic node.
     * @see Synapse
     * @return pointer to the added postsynaptic node added
     */
    NSOL_API
    void postSynapticNode( const NodePtr postsynaptic_node );

    /**
     * Method to get the presynaptic section.
     * @return pointer to the presynaptic section.
     */
    NSOL_API
    SectionPtr preSynapticSection( void ) const;

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
    virtual SynapseNeuriteToSoma& operator =
    ( const SynapseNeuriteToSoma & other);

    NSOL_API
    virtual bool operator == ( const SynapseNeuriteToSoma& other );

    NSOL_API
    virtual bool operator != ( const SynapseNeuriteToSoma& other );

    ///@}


  protected:

    //! Section of a presynaptic neuron (neurite)
    SectionPtr _preSynapticSection;

    //! Node of a presynaptic neuron (neurite)
    NodePtr _preSynapticNode;

    //! Node of a postsynaptic neuron (soma)
    NodePtr _postSynapticNode;

  }; // class SynapseNeuriteToSoma

}// namespace nsol

#endif

//EOF
