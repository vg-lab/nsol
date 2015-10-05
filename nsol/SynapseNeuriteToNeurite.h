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
#include "Segment.h"
#include "Synapse.h"

namespace nsol
{

  /*! \class SynapseNeuriteToNeurite
    \brief A class to represent synapses neurite to neurite.

    TODO: extend long description
  */
  class SynapseNeuriteToNeurite : public Synapse
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
                              Synapse::AXODENDRITIC );

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
     * Method to add a presynaptic segment to the synapse.
     * @param presynaptic segment.
     * @see Synapse
     * @return pointer to the added presynaptic segment added
     */
    NSOL_API
    void preSynapticSegment( const SegmentPtr preSynapticSegment);

    /**
     * Method to add a postsynaptic segment to the synapse.
     * @param postsynaptic segment.
     * @see Synapse
     * @return pointer to the added postsynaptic segment added
     */
    NSOL_API
    void postSynapticSegment( const SegmentPtr postSynapticSegment);

    /**
     * Method to get the presynaptic segment.
     * @return pointer to the presynaptic segment.
     */
    NSOL_API
    SegmentPtr preSynapticSegment( void ) const;

    /**
     * Method to get the postsynaptic segment.
     * @return pointer to the postsynaptic segment.
     */
    NSOL_API
    SegmentPtr postSynapticSegment( void ) const;

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

    //! Segment of a presynaptic neuron
    SegmentPtr _preSynapticSegment;

    //! Segment of a postsynaptic neuron
    SegmentPtr _postSynapticSegment;

  }; // class SynapseNeuriteToNeurite

}// namespace nsol

#endif

//EOF
