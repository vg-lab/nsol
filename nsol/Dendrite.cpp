/**
 * @file    Dendrite.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Dendrite.h"

namespace nsol
{

  Dendrite::Dendrite( TDendriteType inDendriteType )
    : Neurite( Neurite::DENDRITE )
    , _dendriteType( inDendriteType )
  {

  }

  Dendrite::TDendriteType & Dendrite::dendriteType( void )
  {
    return _dendriteType;
  }

} // namespace nsol

// EOF
