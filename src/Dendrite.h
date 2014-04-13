/**
 * @file    Dendrite.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NS_DATA_LIB_DENDRITE__
#define __NS_DATA_LIB_DENDRITE__

#include <Neurite.h>

namespace nsdl {

  class Dendrite : public Neurite {


  public:

    typedef enum TDendriteType {BASAL = 0, APICAL} TDendriteType;
    
    Dendrite (TDendriteType dendriteType = BASAL) : Neurite(Neurite::DENDRITE) {
      _dendriteType = dendriteType;
    }
    
    //! Get the type of neurite
    TDendriteType & dendriteType() {
      return _dendriteType;
    };
    
    //! Return pointer to Dendrite objetc
    virtual Dendrite * asDendrite() { return this; }
    
    
  protected:
    TDendriteType _dendriteType;

  };


  //! Definition of pointer to Dendrite
#if !BOOST
  typedef  Dendrite * DendritePtr;
#else
  typedef  boost::shared_ptr<Dendrite> * DendritePtr;
#endif
}


#endif
