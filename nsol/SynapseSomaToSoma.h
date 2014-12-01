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
#include "Segment.h"
#include "Synapse.h"

namespace nsol
{

	/*! \class SynapseSomaToSoma
	  \brief A class to represent synapses soma to soma.

	  TODO: extend long description
	*/
  class SynapseSomaToSoma : public Synapse
  {

  public:

	  /** @name Constructors  */
	  ///@{

	  /**
	  * Default SynapseSomaToSoma class constructor.
	  * TODO: construct protected objects
	  */
	  NSOL_API
	  SynapseSomaToSoma ( void );

	  /**
	  * Copy constructor
	  * @param other synapse somaToSoma to be copied
	  */
	  NSOL_API
	  SynapseSomaToSoma( SynapseSomaToSoma & other );

	  ///@}

	  /** @name Operators */
	  ///@{

	  NSOL_API
	  virtual SynapseSomaToSoma & operator = (Synapse & other);

	  NSOL_API
	  virtual bool operator == (Synapse & other );

	  NSOL_API
	  virtual bool operator != (Synapse & other );

	  ///@}

	  /** @name Operators */
	  ///@{

	  NSOL_API
	  virtual SynapseSomaToSoma & operator = (const Synapse & other);

	  NSOL_API
	  virtual bool operator == (Synapse & other ) const;

	  NSOL_API
	  virtual bool operator != (Synapse & other ) const;

	  ///@}

  }; // class SynapseSomaToSoma

}// namespace nsol

#endif // __NSOL_SYNAPSE_SOMA_TO_SOMA__

//EOF
