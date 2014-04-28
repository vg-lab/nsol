/**
 * @file    Neurite.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_NEURITE_
#define __NOL_NEURITE_

#include <Types.h>
#include <Section.h>

namespace nol {

  class Dendrite;
  class Axon;

  class Neurite {

  public:

    //! Pssible types of neurite
    typedef enum {DENDRITE = 0, AXON} TNeuriteType;

    //! Default constructor
    Neurite(TNeuriteType neuriteType = DENDRITE) {
      _neuriteType = neuriteType;};

    //! Get the type of neurite
    TNeuriteType & neuriteType() {
      return _neuriteType;
    };

    NeuronPtr neuron() const {
      return  _neuron;
    }

    NeuronPtr neuron(NeuronPtr neuron)  {
      return  _neuron = neuron;
    }

    bool hasNeuron() {
      return _neuron;
    }

    /* SectionPtr addSection() { */
    /*   _sections.push_back(new Section); */
    /*   return _sections.back(); */
    /* }; */

    SectionPtr firstSection() {
      return _firstSection;
    }

    void firstSection(SectionPtr section) {
      _firstSection = section;
    }

    /* Sections sections() { */
    /*   return _sections; */
    /* } */

    // Casting virtual functions
    
    //! Return pointer to Dendrite objetc
    virtual Dendrite * asDendrite() { return 0; }

    //! Return pointer to Dendrite objetc
    virtual Axon * asAxon() { return 0; }

  protected:
    
    TNeuriteType _neuriteType;

    //    Vector <Section> 
    /* Sections _sections; */

    SectionPtr _firstSection;

    NeuronPtr _neuron;
    
  };


}

#endif
