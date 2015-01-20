/**
 * @file    Circuits.h
 * @brief   Test for class nsol::CircuitPtr
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_CIRCUITS__
#define __NSOL_CIRCUITS__

#include <nsol/NsolTypes.h>
#include <nsol/Circuit.h>

namespace nsol {

  class Circuit : public Vector<CircuitPtr> {
  };

}

#endif /* __NSOL_CIRCUITS__ */
