/**
 * @file    Segment.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include <math.h>
#include "Node.h"

#ifndef __NOL_SEGMENT__
#define __NOL_SEGMENT__

namespace nol
{

  class Segment
  {

  public:

    SegmentPtr next() const
    {
      return _next;
    }

    SegmentPtr prev() const
    {
      return _prev;
    }

    void next(SegmentPtr next)
    {
      _next = next;
    }

    void prev(SegmentPtr prev)
    {
      _prev = prev;
    }

    void parentSection(SectionPtr parent)
    {
      _parent = parent;
    }

    NodePtr begin(void) const
    {
      return _begin;
    }

    NodePtr end(void) const
    {
      return _end;
    }

    void begin(NodePtr begin)
    {
      _begin = begin;
    }

    void end(NodePtr end)
    {
      _end = end;
    }

    float volume(void)
    {
      float volume = 0.0f;

      if (_begin && _end)
      {
        Vec3f tmpVec;

        tmpVec[0] = _begin->point()[0] - _end->point()[0];
        tmpVec[1] = _begin->point()[1] - _end->point()[1];
        tmpVec[2] = _begin->point()[2] - _end->point()[2];

        double mod = sqrt((double) (tmpVec[0] * tmpVec[0] + tmpVec[1] * tmpVec[1]
                          + tmpVec[2] * tmpVec[2]));

        //TODO: use accurate volume formula
        //Pi/3 = 1.047197551; Truncated cone formula
        volume = (float) (1.047197551 * mod * (_begin->radius() * _begin->radius()
               + _end->radius() * _end->radius() + _begin->radius()
               * _end->radius()));
      }

      return volume;
    }

    float surface(void)
    {
      float surface = 0.0f;

      if (_begin && _end)
      {
        Vec3f tmpVec;

        tmpVec[0] = _begin->point()[0] - _end->point()[0];
        tmpVec[1] = _begin->point()[1] - _end->point()[1];
        tmpVec[2] = _begin->point()[2] - _end->point()[2];

        double mod = sqrt((double) (tmpVec[0] * tmpVec[0] + tmpVec[1] * tmpVec[1]
                          + tmpVec[2] * tmpVec[2]));

        float rT = _begin->radius() - _end->radius();

        double g = sqrt(mod * mod + rT * rT);

        //TODO: use accurate surface formula
        //Volume cone formula
        surface = (float) (3.14159265359 * (g * (_begin->radius() + _end->radius())
                           + _begin->radius() * _begin->radius()
                           + _end->radius() * _end->radius()));
      }

      return surface;
    }

    float length(void)
    {
      float length = 0.0f;

      if (_begin && _end)
      {
        Vec3f tmpVec;

        tmpVec[0] = _begin->point()[0] - _end->point()[0];
        tmpVec[1] = _begin->point()[1] - _end->point()[1];
        tmpVec[2] = _begin->point()[2] - _end->point()[2];

        double mod = sqrt((double) (tmpVec[0] * tmpVec[0] + tmpVec[1] * tmpVec[1]
                          + tmpVec[2] * tmpVec[2]));

        length = (float) mod;
      }

      return length;
    }

  protected:

    NodePtr _begin, _end;

    SegmentPtr _next;
    SegmentPtr _prev;

    SectionPtr _parent;

  };

}

#endif
