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

namespace nol
{

  class Soma
  {

  public:
    Soma()
    {
    }

    Vec3f & center()
    {
      return _center;
    }

    void addNode(NodePtr node)
    {
      _nodes.push_back(node);
    }

    void addNode(Vec3f & xyz, float & radius)
    {
      this->addNode(new Node(xyz, radius));
    }

    float volume()
    {
      //TODO: use real volume soma formula, now use sphere formula
      //4pi/3 = 4,188790205
      if (!_nodes.empty())
        return _nodes[0]->radius()*_nodes[0]->radius()*_nodes[0]->radius()
               * 4.188790205f;
      else
        return 0.0f;
    }

    float surface()
    {
      //TODO: calculate soma surface
      return 0.0f;
    }

Nodes & nodes(void)
{
	return _nodes;
}

  protected:

    Vec3f _center;
    Nodes _nodes;

  };

}

#endif
