/**
 * @file    Axon.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_AXON__
#define __NSOL_AXON__

#include <nsol/api.h>
#include "Neurite.h"

namespace nsol
{

  class Axon
    : public virtual Neurite
  {

  public:

    NSOL_API
    Axon ( void );

  };

}

#endif
