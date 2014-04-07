/**
 * @file    Neuron.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NS_DATA_LIB_NEURON_
#define __NS_DATA_LIB_NEURON_

#include <Types.h>
#include <Soma.h>
#include <Neurite.h>

namespace nsdl {
  
  class Neuron {
 


  protected:

    Soma _soma; 
    vector<Neurite> _neurites;
    

  };
  
}


#endif
