/**
 * @file    Axon.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_AXON__
#define __NSOL_AXON__

#include "Neurite.h"

namespace nsol 
{

  class Axon 
    : public Neurite 
  {
    
  public:

    Axon ( void );

    //! Return pointer as an Axon object
    // virtual Axon * asAxon( void );
   
  };

}

#endif
