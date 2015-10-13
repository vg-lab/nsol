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
    , _postSynapticNode( nullptr )
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
    , _postSynapticNode( other.postSynapticNode( ))
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

  void SynapseNeuriteToSoma::postSynapticNode(
    const NodePtr postsynaptic_node)
  {
    _postSynapticNode = postsynaptic_node;
  }

  SectionPtr SynapseNeuriteToSoma::preSynapticSection( void ) const
  {
    return _preSynapticSection;
  }

  NodePtr SynapseNeuriteToSoma::preSynapticNode( void ) const
  {
    return _preSynapticNode;
  }

  NodePtr SynapseNeuriteToSoma::postSynapticNode( void ) const
  {
    return _postSynapticNode;
  }

  //
  // Operators
  //

  SynapseNeuriteToSoma& SynapseNeuriteToSoma::operator =
  ( const SynapseNeuriteToSoma& other )
  {
    if (this != &other)
    {
      Synapse::operator = ( other );
      this->preSynapticSection( other.preSynapticSection( ));
      this->preSynapticNode( other.preSynapticNode( ));
      this->postSynapticNode( other.postSynapticNode( ));
    }
    return *this;
  }

  bool SynapseNeuriteToSoma::operator == ( const SynapseNeuriteToSoma& other )
  {
    return Synapse::operator == ( other ) &&
      ( this->preSynapticSection( ) ==
        other.preSynapticSection( )) &&
      ( this->preSynapticNode( ) ==
        other.preSynapticNode( )) &&
      ( this->postSynapticNode( ) ==
        other.postSynapticNode( ));
  }

  bool SynapseNeuriteToSoma::operator != ( const SynapseNeuriteToSoma& other )
  {
    return !( *this == other );
  }


} // namespace nsol

// EOF
