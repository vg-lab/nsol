/**
 * @file    SynapseSomaToSoma.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include "SynapseSomaToSoma.h"

namespace nsol
{
 	SynapseSomaToSoma::SynapseSomaToSoma ( void )
	:Synapse(Synapse::SOMATOSOMAL)
	{
	}

 	SynapseSomaToSoma::SynapseSomaToSoma(
 			SynapseSomaToSoma & other )
	:  Synapse( other)
	{
	}

   //
   // Operators
   //

   SynapseSomaToSoma & SynapseSomaToSoma::operator = (Synapse & other)
   {

 	 SynapseSomaToSoma * synapseDerivedPtr;
	 synapseDerivedPtr = dynamic_cast<SynapseSomaToSoma*>(&other);

 	 if ( synapseDerivedPtr == 0)
	   	throw std::runtime_error("Unlike types.");

	 if (this != synapseDerivedPtr)
	 {
	   this->synapseType( ) = synapseDerivedPtr->synapseType( );
	   this->preSynapticNeuron(synapseDerivedPtr->preSynapticNeuron( ));
	   this->postSynapticNeuron(synapseDerivedPtr->postSynapticNeuron( ));
	  }

	 return *this;
   }

   bool SynapseSomaToSoma::operator == (Synapse & other )
   {
	 SynapseSomaToSoma * synapseDerivedPtr;
	 synapseDerivedPtr = dynamic_cast<SynapseSomaToSoma*>(&other);

	 if ( synapseDerivedPtr == 0)
		 return false;

	 return ( ( this->synapseType( ) == synapseDerivedPtr->synapseType( ) ) &&
		    ( (this->preSynapticNeuron( )) == (synapseDerivedPtr->preSynapticNeuron( ))) &&
		    ( (this->postSynapticNeuron( )) == (synapseDerivedPtr->postSynapticNeuron( ))));
   }

   bool SynapseSomaToSoma::operator != (Synapse & other )
   {
	 SynapseSomaToSoma * synapseDerivedPtr;
	 synapseDerivedPtr = dynamic_cast<SynapseSomaToSoma*>(&other);

	 if ( synapseDerivedPtr == 0)
	    return true;

	 return !( *this == *synapseDerivedPtr);
   }

}

//  EOF
