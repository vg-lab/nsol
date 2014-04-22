/**
 * @file    Node.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_NODE__
#define __NOL_NODE__


namespace nol {
  
  class Node {

  public:

    Node(Vec3f & point, float radius = 0.0f) {
      _point = point;
      _radius = radius;
    }
    
  protected:

    Vec3f _point; 
    float _radius; 
    
  };

}


#endif
