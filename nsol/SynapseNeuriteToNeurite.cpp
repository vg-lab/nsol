/**
 * @file    SynapseNeuriteToNeurite.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include "SynapseNeuriteToNeurite.h"
#include "error.h"

namespace nsol
{

	SynapseNeuriteToNeurite::SynapseNeuriteToNeurite (
			TSynapseType synapseType_)
	:  Synapse( synapseType_ )
	, _preSynapticSegment( nullptr )
	, _postSynapticSegment( nullptr )
	{
		NSOL_DEBUG_CHECK( synapseType_ == Synapse::AXODENDRITIC ||
				          synapseType_ == Synapse::DENDRODENDRITIC ||
				          synapseType_ == Synapse::AXOAXONIC,
				          "synapse type not consistent");
	}

	SynapseNeuriteToNeurite::SynapseNeuriteToNeurite(
			SynapseNeuriteToNeurite & other )
	:  Synapse( other)
	, _preSynapticSegment( other.preSynapticSegment( ) )
	, _postSynapticSegment( other.postSynapticSegment( ))
	{
	}

	void SynapseNeuriteToNeurite::preSynapticSegment( SegmentPtr presynaptic_segment)
	{
		_preSynapticSegment = presynaptic_segment;
	}

	void SynapseNeuriteToNeurite::postSynapticSegment( SegmentPtr postsynaptic_segment)
	{
		_postSynapticSegment = postsynaptic_segment;
	}


	SegmentPtr SynapseNeuriteToNeurite::preSynapticSegment( void ) const
	{
		 return _preSynapticSegment;
	}

	SegmentPtr SynapseNeuriteToNeurite::postSynapticSegment( void ) const
	{
		 return _postSynapticSegment;
	}

	  //
	  // Operators
	  //

	  SynapseNeuriteToNeurite & SynapseNeuriteToNeurite::operator = (Synapse & other)
	  {

		SynapseNeuriteToNeurite * synapseDerivedPtr;
		synapseDerivedPtr = dynamic_cast< SynapseNeuriteToNeurite*>(&other);

		if ( synapseDerivedPtr == 0)
			throw std::runtime_error("Unlike types.");

	    if (this != synapseDerivedPtr)
	    {
	      this->synapseType( ) = synapseDerivedPtr->synapseType( );
	      this->preSynapticNeuron(synapseDerivedPtr->preSynapticNeuron( ));
	      this->postSynapticNeuron(synapseDerivedPtr->postSynapticNeuron( ));
	      this->preSynapticSegment(synapseDerivedPtr->preSynapticSegment( ));
	      this->postSynapticSegment(synapseDerivedPtr->postSynapticSegment( ));
	    }

	    return *this;
	  }

	  bool SynapseNeuriteToNeurite::operator == (Synapse & other )
	  {
	    SynapseNeuriteToNeurite * synapseDerivedPtr;
	    synapseDerivedPtr = dynamic_cast<SynapseNeuriteToNeurite *>(&other);

		if ( synapseDerivedPtr == 0)
			return false;

	    return ( ( this->synapseType( ) == synapseDerivedPtr->synapseType( ) ) &&
	    	   ( this->preSynapticNeuron( ) == synapseDerivedPtr->preSynapticNeuron( )) &&
	    	   ( this->postSynapticNeuron( ) == synapseDerivedPtr->postSynapticNeuron( )) &&
	    	   ( this->preSynapticSegment( ) == synapseDerivedPtr->preSynapticSegment( )) &&
	    	   ( this->postSynapticSegment( ) == synapseDerivedPtr->postSynapticSegment( )));
	  }

	  bool SynapseNeuriteToNeurite::operator != (Synapse & other )
	  {
	    SynapseNeuriteToNeurite * synapseDerivedPtr;
	    synapseDerivedPtr = dynamic_cast<SynapseNeuriteToNeurite *>(&other);

	    if ( synapseDerivedPtr == 0)
		   return true;

	    return !( *this == *synapseDerivedPtr);
	  }


}// namespace nsol

//EOF
