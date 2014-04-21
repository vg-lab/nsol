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
#include <Container/Dendrites.h>

namespace nsdl {


  /*! \class Neuron
    \brief A class to represent neurons.
    
    TODO: extend long description
  */  
  class Neuron {

  public:
    
    /**
     * Default Neuron class constructor.
     * TODO: construct protected objects
     */
    Neuron() {}

    /**
       * Method to add a new neurite to the neuron.
       * @param neuriteType type of Neurite.
       * @see Neurite::TNeuriteType
       * @return pointer to the added neurite
       */
    NeuritePtr addNeurite(Neurite::TNeuriteType neuriteType = 
			  Neurite::DENDRITE) {
      if (neuriteType == Neurite::DENDRITE)
	_neurites.push_back(new Dendrite());
      else if (neuriteType == Neurite::AXON)
	_neurites.push_back(new Axon());
      else
	return NULL;
      return  _neurites.back();
    };

    /**
       * Method to add a new dendrite to the neuron.
       * @param dendriteType type of Dendrite
       * @see ndsl::Dendrite::TDendriteType
       * @return pointer to the added dendrite
       */
    Dendrite * addDendrite(Dendrite::TDendriteType dendriteType = 
			   Dendrite::BASAL) {
      _neurites.push_back(new Dendrite(dendriteType));
      return _neurites.back()->asDendrite();
    };

    unsigned int numNeurites(void) {
      return _neurites.size();
    }

    unsigned int numDendrites(void) {
      unsigned int nd = 0;
      for (Vector<Neurite *>::iterator it = _neurites.begin(); 
	   it != _neurites.end(); ++it) 
	if ((*it)->asDendrite()) nd++;
      return nd;
    }

    /**
       * Method to get all the dendrites in a container. 
       * Memory for the container is allocated.
       * @return pointer to the container of Dendrites
       */
    Dendrites * dendrites(void) {
      Dendrites *dendrites = new Dendrites;
      for (Vector<Neurite *>::iterator it = _neurites.begin(); 
	   it != _neurites.end(); ++it) 
	if ((*it)->asDendrite())
	  dendrites->push_back((*it)->asDendrite());      
      return dendrites;
    }
    
    /**
       * Method to get all the basal dendrites in a container. 
       * Memory for the container is allocated.
       * @return pointer to the container of Dendrites
       */
    Dendrites * basalDendrites(void) {
      // TODO: create a list of all basal dendrites
      return new Dendrites;
    }

    /**
       * Method to add a new dendrite to the neuron.
       * @param dendriteType  .
       * @see Neurite::TNeuriteType
       * @return pointer to the added dendrite
       */
    Dendrite * apicalDendrite(void) {
      for (Vector<Neurite *>::iterator it = _neurites.begin(); 
	   it != _neurites.end(); ++it) {
	if ((*it)->asDendrite() && 
	    ((*it)->asDendrite()->dendriteType() == Dendrite::APICAL))
	  return (*it)->asDendrite();
      }
      return NULL;
    }
    
    
    Soma & soma(void) {
      return _soma;
    }

  
  protected:
    
    Soma _soma; 
    Vector<Neurite *> _neurites;
    

  };

/*   //! Definition of pointer to Dendrite */
/* #if !BOOST */
/*   typedef  Neuron * NeuronPtr; */
/* #else */
/*   typedef  boost::shared_ptr<Neuron> * NeuronPtr; */
/* #endif */
  
  
}


#endif
