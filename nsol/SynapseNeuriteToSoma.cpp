/**
 * @file    SynapseNeuriteToSoma.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include "SynapseNeuriteToSoma.h"
#include "error.h"

namespace nsol
{

		SynapseNeuriteToSoma::SynapseNeuriteToSoma (
				TSynapseType synapseType_)
			: Synapse( synapseType_ )
			, _preSynapticSegment( nullptr )
			{
				NSOL_DEBUG_CHECK( synapseType_ == Synapse::DENDROSOMATIC ||
						          synapseType_ == Synapse::AXOSOMATIC,
						          "synapse type not consistent");
		}


		void SynapseNeuriteToSoma::preSynapticSegment( SegmentPtr presynaptic_segment)
		{
			_preSynapticSegment = presynaptic_segment;
		}

		SegmentPtr SynapseNeuriteToSoma::preSynapticSegment( void )
		{
			 return _preSynapticSegment;
		}


} // namespace nsol

// EOF
