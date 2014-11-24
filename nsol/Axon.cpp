/**
 * @file    Axon.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Axon.h"


namespace nsol
{

  Axon::Axon ( void )
    : Neurite( Neurite::AXON )
  {
    // std::cout << "Axon  " <<  _neuriteType
    //           << std::endl;
  }

  // Axon * Axon::asAxon( void )
  // {
  //   return this; // AxonPtr(this);
  // }

}

// EOF
