/**
 * @file    SynapseNeuriteToNeurite.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include "SynapseNeuriteToNeurite.h"
#include "error.h"

namespace nsol
{

  SynapseNeuriteToNeurite::SynapseNeuriteToNeurite (const TSynapseType synapseType_,
    const unsigned int initId )
    :  Synapse( synapseType_, initId )
    , _preSynapticSection( nullptr )
    , _postSynapticSection( nullptr )
    , _preSynapticNode( nullptr )
    , _postSynapticNode( nullptr )
  {
    NSOL_DEBUG_CHECK( synapseType_ == Synapse::AXODENDRITIC ||
                      synapseType_ == Synapse::DENDRODENDRITIC ||
                      synapseType_ == Synapse::AXOAXONIC,
                      "synapse type not consistent");
  }

  SynapseNeuriteToNeurite::SynapseNeuriteToNeurite(
    const SynapseNeuriteToNeurite& other )
    :  Synapse( other)
    , _preSynapticSection( other.preSynapticSection( ) )
    , _postSynapticSection( other.postSynapticSection( ))
    , _preSynapticNode( other.preSynapticNode( ) )
    , _postSynapticNode( other.postSynapticNode( ))
  {
  }

  void SynapseNeuriteToNeurite::preSynapticSection( SectionPtr presynaptic_section)
  {
    _preSynapticSection = presynaptic_section;
  }

  void SynapseNeuriteToNeurite::postSynapticSection( SectionPtr postsynaptic_section)
  {
    _postSynapticSection = postsynaptic_section;
  }

  void SynapseNeuriteToNeurite::preSynapticNode( NodePtr presynaptic_node)
  {
    _preSynapticNode = presynaptic_node;
  }

  void SynapseNeuriteToNeurite::postSynapticNode( NodePtr postsynaptic_node)
  {
    _postSynapticNode = postsynaptic_node;
  }

  SectionPtr SynapseNeuriteToNeurite::preSynapticSection( void ) const
  {
    return _preSynapticSection;
  }

  SectionPtr SynapseNeuriteToNeurite::postSynapticSection( void ) const
  {
    return _postSynapticSection;
  }

  NodePtr SynapseNeuriteToNeurite::preSynapticNode( void ) const
  {
    return _preSynapticNode;
  }

  NodePtr SynapseNeuriteToNeurite::postSynapticNode( void ) const
  {
    return _postSynapticNode;
  }

  //
  // Operators
  //

  SynapseNeuriteToNeurite&
  SynapseNeuriteToNeurite::operator = ( const SynapseNeuriteToNeurite& other )
  {
    Synapse::operator = ( other );
    this->preSynapticSection( other.preSynapticSection( ));
    this->postSynapticSection( other.postSynapticSection( ));
    this->preSynapticNode( other.preSynapticNode( ));
    this->postSynapticNode( other.postSynapticNode( ));

    return *this;
  }

  bool SynapseNeuriteToNeurite::operator ==
  ( const SynapseNeuriteToNeurite& other )
  {
    return Synapse::operator == ( other ) &&
      ( this->preSynapticSection( ) ==
        other.preSynapticSection( )) &&
      ( this->postSynapticSection( ) ==
        other.postSynapticSection( )) &&
      ( this->preSynapticNode( ) ==
        other.preSynapticNode( )) &&
      ( this->postSynapticNode( ) ==
        other.postSynapticNode( ));
  }

  bool SynapseNeuriteToNeurite::operator !=
  ( const SynapseNeuriteToNeurite& other )
  {
    return !( *this == other );
  }


}// namespace nsol

//EOF
