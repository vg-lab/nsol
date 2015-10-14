/**
 * @file    SynapseSomaToSoma.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SYNAPSE_SOMA_TO_SOMA__
#define __NSOL_SYNAPSE_SOMA_TO_SOMA__

#include <nsol/api.h>
#include "NsolTypes.h"
#include "Neuron.h"
#include "Synapse.h"

namespace nsol
{

  /*! \class SynapseSomaToSoma
    \brief A class to represent synapses soma to soma.

    TODO: extend long description
  */
  class SynapseSomaToSoma : public virtual Synapse
  {

  public:

    /** @name Constructors  */
    ///@{

    /**
     * Default SynapseSomaToSoma class constructor.
     * TODO: construct protected objects
     */
    NSOL_API
    SynapseSomaToSoma ( const unsigned short id = 0 );

    /**
     * Copy constructor
     * @param other synapse somaToSoma to be copied
     */
    NSOL_API
    SynapseSomaToSoma( const SynapseSomaToSoma& other );

    ///@}

    /** @name getters and setters methods */
    ///@{

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
    virtual SynapseSomaToSoma& operator = ( const SynapseSomaToSoma& other );

    NSOL_API
    virtual bool operator == ( const SynapseSomaToSoma& other );

    NSOL_API
    virtual bool operator != ( const SynapseSomaToSoma& other );

    ///@}


  protected:

    //! Node of a presynaptic neuron (soma)
    NodePtr _preSynapticNode;

    //! Node of a postsynaptic neuron (soma)
    NodePtr _postSynapticNode;

  }; // class SynapseSomaToSoma

}// namespace nsol

#endif // __NSOL_SYNAPSE_SOMA_TO_SOMA__

//EOF
