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

		SynapseNeuriteToSoma::SynapseNeuriteToSoma(
				SynapseNeuriteToSoma & other )
		:  Synapse( other)
		, _preSynapticSegment( other.preSynapticSegment( ) )
		{
		}


		void SynapseNeuriteToSoma::preSynapticSegment( SegmentPtr presynaptic_segment)
		{
			_preSynapticSegment = presynaptic_segment;
		}

		SegmentPtr SynapseNeuriteToSoma::preSynapticSegment( void )
		{
			 return _preSynapticSegment;
		}

		//
        // Operators
	    //

		 SynapseNeuriteToSoma & SynapseNeuriteToSoma::operator = (Synapse & other)
		  {

			SynapseNeuriteToSoma * synapseDerivedPtr;
			synapseDerivedPtr = dynamic_cast< SynapseNeuriteToSoma*>(&other);

			if ( synapseDerivedPtr == 0)
				throw std::runtime_error("Unlike types.");

			if (this != synapseDerivedPtr)
			{
			  this->synapseType( ) = synapseDerivedPtr->synapseType( );
			  this->preSynapticNeuron(synapseDerivedPtr->preSynapticNeuron( ));
			  this->postSynapticNeuron(synapseDerivedPtr->postSynapticNeuron( ));
			  this->preSynapticSegment(synapseDerivedPtr->preSynapticSegment( ));
			}

			return *this;
		  }

		  bool SynapseNeuriteToSoma::operator == (Synapse & other )
		  {
			SynapseNeuriteToSoma * synapseDerivedPtr;
			synapseDerivedPtr = dynamic_cast<SynapseNeuriteToSoma*>(&other);

			if ( synapseDerivedPtr == 0)
				return false;

			return ( ( this->synapseType( ) == synapseDerivedPtr->synapseType( ) ) &&
				   ( (this->preSynapticNeuron( )) == (synapseDerivedPtr->preSynapticNeuron( ))) &&
				   ( (this->postSynapticNeuron( )) == (synapseDerivedPtr->postSynapticNeuron( ))) &&
				   ( (this->preSynapticSegment( )) == (synapseDerivedPtr->preSynapticSegment( ))));
		  }

		  bool SynapseNeuriteToSoma::operator != (Synapse & other )
		  {
			SynapseNeuriteToSoma * synapseDerivedPtr;
			synapseDerivedPtr = dynamic_cast<SynapseNeuriteToSoma*>(&other);

			if ( synapseDerivedPtr == 0)
			   return true;

			return !( *this == *synapseDerivedPtr);
		  }


} // namespace nsol

// EOF
