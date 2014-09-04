/**
 * @file    Soma.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SOMA__
#define __NSOL_SOMA__

#include <Container/Nodes.h>

namespace nsol
{

  class Soma
  {

  public:
    Soma()
    {
    }

    ~Soma()
    {
      for (Vector<Node *>::iterator it = _nodes.begin();
      it != _nodes.end(); ++it)
        delete *it;

      _nodes.clear();
    }

    Vec3f & center(void)
    {
      return _center;
    }

    Nodes & nodes(void)
    {
      return _nodes;
    }

    void addNode(NodePtr node)
    {
      _nodes.push_back(node);

      recalculateCenter();
    }

    void addNode(Vec3f & xyz, float & radius)
    {
      this->addNode(new Node(xyz, radius));

      recalculateCenter();
    }

    float volume(void)
    {
      float radius = maxRadius();

      //TODO: use real volume soma formula, now use sphere volume formula
      return M_4PI_3 * radius * radius * radius;
    }

    float surface(void)
    {
      float radius = maxRadius();

      //TODO: use real soma surface, now use sphere surface formula
      return M_4PI * radius * radius;
    }

  protected:

    Vec3f _center;
    Nodes _nodes;

  private:

    void recalculateCenter(void)
    {
      Vec3f tmp = Vec3f(0,0,0);

      //Recalculated soma center node
      for (unsigned int it = 0; it < _nodes.size(); ++it)
        tmp += _nodes[it]->point();

     _center = tmp /_nodes.size();
    }

    float maxRadius(void)
    {
      float radius = _nodes[0]->radius(), mod = 0.0f;
      Vec3f tmp = Vec3f(0,0,0);

      for (unsigned int it = 1; it < _nodes.size(); ++it)
      {
        tmp = _center - _nodes[it]->point();

        mod = (float)sqrt((double) (tmp[0] * tmp[0] + tmp[1] * tmp[1]
                          + tmp[2] * tmp[2]));

        if (mod > radius)
          radius = mod;
      }

      return radius;
    }

  };

}

#endif
