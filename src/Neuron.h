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
#include <Dendrite.h>

namespace nsdl {
  
  class Neuron {

  public:
    

    Neuron() {}

    Neurite * addNeurite(Neurite::TNeuriteType type = Neurite::DENDRITE) {
      if (type == Neurite::DENDRITE)
	_neurites.push_back(new Dendrite());
      else if (type == Neurite::AXON)
	_neurites.push_back(new Axon());
      else
	return NULL;

      return  _neurites.back();
    };

    Dendrite * addDendrite(Dendrite::TDendriteType dendriteType = Dendrite::BASAL) {
      _neurites.push_back(new Dendrite(dendriteType));
      return _neurites.back()->asDendrite();
    };


      /* _neurites.push_back(Dendrite()); */
      /* for (int i = 0; i <  _neurites.size(); i++) */
      /* 	std::cout << _neurites[i].NeuriteType() << " "; */
      /* std::cout << std::endl; */



  protected:

    Soma _soma; 
    Vector<Neurite *> _neurites;
    

  };
  
}


#endif
