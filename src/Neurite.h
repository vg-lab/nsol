/**
 * @file    Neurite.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NS_DATA_LIB_NEURITE_
#define __NS_DATA_LIB_NEURITE_

#include <Types.h>
#include <Section.h>

namespace nsdl {

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


    // Casting virtual functions
    
    //! Return pointer to Dendrite objetc
    virtual Dendrite * asDendrite() { return 0; }

    //! Return pointer to Dendrite objetc
    virtual Axon * asAxon() { return 0; }

  protected:
    
    TNeuriteType _neuriteType;

    Vector <Section> _sections;
    
  };

}

#endif
