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
#include "Segment.h"

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
	  SynapseNeuriteToSoma (TSynapseType synapseType_ = Synapse::DENDROSOMATIC);

	  /**
	  * Copy constructor
	  * @param other synapse neuriteToSoma to be copied
	  */
	  NSOL_API
	  SynapseNeuriteToSoma( SynapseNeuriteToSoma & other );

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
	  * Method to get the presynaptic segment.
	  * @return pointer to the presynaptic segment.
	  */
	  NSOL_API
	  SegmentPtr preSynapticSegment( void );

	  ///@}

	  /** @name Operators */
	  ///@{

	  NSOL_API
	  virtual SynapseNeuriteToSoma & operator = (Synapse & other);

	  NSOL_API
	  virtual bool operator == (Synapse & other );

	  NSOL_API
	  virtual bool operator != (Synapse & other );

	  ///@}



  protected:

	  SegmentPtr _preSynapticSegment;  // Segment of a presynaptic neuron

  }; // class SynapseNeuriteToSoma

}// namespace nsol

#endif

//EOF
