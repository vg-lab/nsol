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
    , _preSynapticSection( nullptr )
    , _preSynapticNode( nullptr )
  {
    NSOL_DEBUG_CHECK( synapseType_ == Synapse::DENDROSOMATIC ||
                      synapseType_ == Synapse::AXOSOMATIC,
                      "synapse type not consistent");
  }

  SynapseNeuriteToSoma::SynapseNeuriteToSoma(
    const SynapseNeuriteToSoma& other )
    :  Synapse( other)
    , _preSynapticSection( other.preSynapticSection( ))
    , _preSynapticNode( other.preSynapticNode( ))
  {
  }

  void SynapseNeuriteToSoma::preSynapticSection(
    const SectionPtr presynaptic_section)
  {
    _preSynapticSection = presynaptic_section;
  }

  void SynapseNeuriteToSoma::preSynapticNode(
    const NodePtr presynaptic_node)
  {
    _preSynapticNode = presynaptic_node;
  }

  SectionPtr SynapseNeuriteToSoma::preSynapticSection( void ) const
  {
    return _preSynapticSection;
  }

  NodePtr SynapseNeuriteToSoma::preSynapticNode( void ) const
  {
    return _preSynapticNode;
  }

  //
  // Operators
  //

  SynapseNeuriteToSoma& SynapseNeuriteToSoma::operator =
  ( const SynapseNeuriteToSoma& other )
  {

    Synapse::operator = ( other );
    this->preSynapticSection( other.preSynapticSection( ));
    this->preSynapticNode( other.preSynapticNode( ));

    return *this;
  }

  bool SynapseNeuriteToSoma::operator == ( const SynapseNeuriteToSoma& other )
  {
    return Synapse::operator == ( other ) &&
      ( this->preSynapticSection( ) ==
        other.preSynapticSection( )) &&
      ( this->preSynapticNode( ) ==
        other.preSynapticNode( ));
  }

  bool SynapseNeuriteToSoma::operator != ( const SynapseNeuriteToSoma& other )
  {
    return !( *this == other );
  }


} // namespace nsol

// EOF
