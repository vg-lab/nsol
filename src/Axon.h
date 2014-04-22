/**
 * @file    Axon.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_AXON__
#define __NOL_AXON__

#include <Neurite.h>

namespace nol {

  class Axon : public Neurite {
    
  public:

    Axon () : Neurite(Neurite::AXON) {};
    

    //! Return pointer as an Axon object
    virtual Axon * asAxon() { return this; }

    
  };

}

#endif
