/**
 * @file    Soma.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SOMA__
#define __NSOL_SOMA__

#include <nsol/Container/Nodes.h>

namespace nsol {

class Soma {

public:
	Soma() :
		_maxRadius(0.0)
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

    /**
     * Method to get de max radius of the soma
     * @return max radius of the soma
     */
	const float & maxRadius(void) const
	{
		return _maxRadius;
	}

	void addNode(NodePtr node)
	{
		_nodes.push_back(node);

		recalculateCenter();
		recalculateMaxRadius();
	}

	void addNode(Vec3f & xyz, float & radius)
	{
		this->addNode(new Node(xyz, radius));

		recalculateCenter();
		recalculateMaxRadius();
	}

	float volume(void)
	{
		//TODO: use real volume soma formula, now use sphere volume formula
		return M_4PI_3 * _maxRadius * _maxRadius * _maxRadius;
	}

	float surface(void)
	{
		//TODO: use real soma surface, now use sphere surface formula
		return M_4PI * _maxRadius * _maxRadius;
	}

protected:

	Vec3f _center;
	Nodes _nodes;
	float _maxRadius;

private:

	void recalculateCenter(void)
	{
		Vec3f tmp = Vec3f(0,0,0);

		//Recalculated soma center node
		for (unsigned int it = 0; it < _nodes.size(); ++it)
		tmp += _nodes[it]->point();

		_center = tmp /_nodes.size();
	}

  void recalculateMaxRadius(void)
  {
    if (_nodes.size() == 0)
    {
      _maxRadius = 0.0f;
      return;
    }

    _maxRadius = _nodes[0]->radius();

    for (unsigned int it = 1; it < _nodes.size(); ++it)
    {
      float mod = (_center - _nodes[it]->point()).length();

      if (mod > _maxRadius)
        _maxRadius = mod;
    }
  }
};

}

#endif