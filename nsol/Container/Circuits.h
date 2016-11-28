/**
 * @file    Circuits.h
 * @brief   Container for class nsol::CircuitPtr
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_CIRCUITS__
#define __NSOL_CIRCUITS__

#include <nsol/NsolTypes.h>
#include <nsol/Circuit.h>

namespace nsol
{

  class Circuits : public NsolVector<CircuitPtr>
  {

  protected:

  };

}

#endif /* __NSOL_CIRCUITS__ */
