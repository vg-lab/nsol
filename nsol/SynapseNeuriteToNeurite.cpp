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


}// namespace nsol

//EOF
