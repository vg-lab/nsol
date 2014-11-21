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
#include <nsol/NsolTypes.h>
#include <nsol/Neuron.h>
#include <nsol/Segment.h>

namespace nsol
{

	/*! \class SynapseNeuriteToSoma
	  \brief A class to represent synapses neurite to soma.

	  TODO: extend long description
	*/
  class SynapseNeuriteToSoma : public Synapse
  {

  public:

	  /** @name Constructors  */
	  ///@{

	  /**
	  * Default SynapseNeuriteToSoma class constructor.
	  * TODO: construct protected objects
	  */
	  NSOL_API
	  SynapseSomaToSoma ( void );

	  ///@}

  protected:

	  SegmentPtr _preSynapticSegment;  // Segment of a presynaptic neuron

	  SegmentPtr _postSynapticSegment; // Segment of a postsynaptic neuron

  }; // class SynapseNeuriteToSoma

}// namespace nsol

#endif

//EOF
