/**
 * @file    Neurites.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_NEURITES__
#define __NSOL_NEURITES__

#include <nsol/NsolTypes.h>
#include <nsol/Neurite.h>

namespace nsol {

  class Neurites : public Vector<NeuritePtr> {
  };

}

#endif
