/**
 * @file    SynapseSomaToSoma.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "SynapseSomaToSoma.h"

namespace nsol
{
  SynapseSomaToSoma::SynapseSomaToSoma (const unsigned int initId )
    :Synapse(Synapse::SOMATOSOMAL, initId )
    , _preSynapticNode( nullptr )
    , _postSynapticNode( nullptr )
  {
  }

  SynapseSomaToSoma::SynapseSomaToSoma(
    const SynapseSomaToSoma& other )
    :  Synapse( other)
    , _preSynapticNode( other.preSynapticNode( ))
    , _postSynapticNode( other.postSynapticNode( ))
  {
  }

  void SynapseSomaToSoma::preSynapticNode(
    const NodePtr presynaptic_node)
  {
    _preSynapticNode = presynaptic_node;
  }

  void SynapseSomaToSoma::postSynapticNode(
    const NodePtr postsynaptic_node)
  {
    _postSynapticNode = postsynaptic_node;
  }

  NodePtr SynapseSomaToSoma::preSynapticNode( void ) const
  {
    return _preSynapticNode;
  }

  NodePtr SynapseSomaToSoma::postSynapticNode( void ) const
  {
    return _postSynapticNode;
  }

  //
  // Operators
  //

  SynapseSomaToSoma& SynapseSomaToSoma::operator = (
    const SynapseSomaToSoma& other)
  {
    if (this != &other)
    {
      Synapse::operator = ( other );
      this->preSynapticNode( other.preSynapticNode( ));
      this->postSynapticNode( other.postSynapticNode( ));
    }
    return *this;
  }

  bool SynapseSomaToSoma::operator == ( const SynapseSomaToSoma& other )
  {
    return Synapse::operator == ( other )&&
        ( this->preSynapticNode( ) ==
          other.preSynapticNode( )) &&
        ( this->postSynapticNode( ) ==
          other.postSynapticNode( ));
  }

  bool SynapseSomaToSoma::operator != ( const SynapseSomaToSoma& other )
  {
    return !( *this == other );
  }

}

//  EOF
