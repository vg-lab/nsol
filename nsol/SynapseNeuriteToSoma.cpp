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
    const SynapseNeuriteToSoma& other )
    :  Synapse( other)
    , _preSynapticSegment( other.preSynapticSegment( ) )
  {
  }


  void SynapseNeuriteToSoma::preSynapticSegment(
    const SegmentPtr presynaptic_segment)
  {
    _preSynapticSegment = presynaptic_segment;
  }

  SegmentPtr SynapseNeuriteToSoma::preSynapticSegment( void ) const
  {
    return _preSynapticSegment;
  }

  //
  // Operators
  //

  SynapseNeuriteToSoma& SynapseNeuriteToSoma::operator =
  ( const SynapseNeuriteToSoma& other )
  {

    Synapse::operator = ( other );
    this->preSynapticSegment( other.preSynapticSegment( ));

    return *this;
  }

  bool SynapseNeuriteToSoma::operator == ( const SynapseNeuriteToSoma& other )
  {
    return Synapse::operator == ( other ) &&
      ( this->preSynapticSegment( ) ==
        other.preSynapticSegment( ));
  }

  bool SynapseNeuriteToSoma::operator != ( const SynapseNeuriteToSoma& other )
  {
    return !( *this == other );
  }


} // namespace nsol

// EOF
