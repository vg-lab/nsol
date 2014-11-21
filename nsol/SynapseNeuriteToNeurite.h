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
#include <nsol/Neuron.h>
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

	  /**
	  * Default SynapseNeuriteToNeurite class constructor.
	  * TODO: construct protected objects
	  */
	  NSOL_API
	  SynapseNeuriteToNeurite ( void );

	  ///@}


  protected:

	  SegmentPtr _preSynapticSegment;  // Segment of a presynaptic neuron

	  SegmentPtr _postSynapticSegment; // Segment of a postsynaptic neuron

  }; // class SynapseNeuriteToNeurite

}// namespace nsol

#endif

//EOF
