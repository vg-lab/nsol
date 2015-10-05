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
  SynapseSomaToSoma::SynapseSomaToSoma ( void )
    :Synapse(Synapse::SOMATOSOMAL)
  {
  }

  SynapseSomaToSoma::SynapseSomaToSoma(
    const SynapseSomaToSoma& other )
    :  Synapse( other)
  {
  }

  //
  // Operators
  //

  SynapseSomaToSoma& SynapseSomaToSoma::operator = (
    const SynapseSomaToSoma& other)
  {
    Synapse::operator = ( other );
    return *this;
  }

  bool SynapseSomaToSoma::operator == ( const SynapseSomaToSoma& other )
  {
    return Synapse::operator == ( other );
  }

  bool SynapseSomaToSoma::operator != ( const SynapseSomaToSoma& other )
  {
    return !( *this == other );
  }

}

//  EOF
