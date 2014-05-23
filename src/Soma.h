/**
 * @file    Soma.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_SOMA__
#define __NOL_SOMA__

#include <Container/Nodes.h>

namespace nol {

  class Soma {


  public:
    Soma () {}
    
    Vec3f & center() { 
      return _center;
    }

    void addNode(NodePtr node) {
      _nodes.push_back(node);
    }

    void addNode(Vec3f & xyz, float & radius) {
      this->addNode(new Node(xyz,radius));
    }


    float volume() {
      //TODO
    	return 0.0f;
    }

  protected:

    Vec3f _center;
    Nodes _nodes;

    
  };


}

#endif
