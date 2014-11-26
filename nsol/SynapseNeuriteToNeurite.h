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
#include <nsol/NsolTypes.h>
#include <nsol/Segment.h>

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
	  void
	  /**
	  * Default SynapseNeuriteToNeurite class constructor.
	  * TODO: construct protected objects
	  */
	  NSOL_API
	  SynapseNeuriteToNeurite ( SegmentPtr preSynapticSegment = nullptr,
			                    SegmentPtr postSynapticSegment = nullptr );

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
	  void preSynapticSegment( SegmentPtr presynaptic_segment);

	  /**
	  * Method to add a postsynaptic segment to the synapse.
	  * @param postsynaptic segment.
	  * @see Synapse
	  * @return pointer to the added postsynaptic segment added
	  */
	  NSOL_API
	  void postSynapticSegment( SegmentPtr postsynaptic_segment);

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


  protected:

	  //! Segment of a presynaptic neuron
	  SegmentPtr _preSynapticSegment;

	  //! Segment of a postsynaptic neuron
	  SegmentPtr _postSynapticSegment;

  }; // class SynapseNeuriteToNeurite

}// namespace nsol

#endif

//EOF
