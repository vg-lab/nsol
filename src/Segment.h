/**
 * @file    Segment.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include <math.h>
#include "Node.h"

#ifndef __NSOL_SEGMENT__
#define __NSOL_SEGMENT__

namespace nsol
{
  class Segment
  {

    friend class Section;

  public:

    ~Segment()
    {
      //TODO:review shared nodes between segments
      delete _end;
    }

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

        tmpVec = _begin->point() - _end->point();

        double mod = sqrt((double) (tmpVec[0] * tmpVec[0] + tmpVec[1] * tmpVec[1]
                          + tmpVec[2] * tmpVec[2]));

        //Cylinder volume
        volume = (float) (3.14159265359 * mod * _end->radius() * _end->radius());
      }

      return volume;
    }

    float surface(void)
    {
      float surface = 0.0f;

      if (_begin && _end)
      {
        Vec3f tmpVec;

        tmpVec = _begin->point() - _end->point();

        double mod = sqrt((double) (tmpVec[0] * tmpVec[0] + tmpVec[1] * tmpVec[1]
                          + tmpVec[2] * tmpVec[2]));

        //Cylinder surface
        //2PI = 6.283185307
        surface = 6.283185307 * _end->radius() * mod;
      }

      return surface;
    }

    float length(void)
    {
      float length = 0.0f;

      if (_begin && _end)
      {
        Vec3f tmpVec;

        tmpVec = _begin->point() - _end->point();

        length = (float) sqrt((double) (tmpVec[0] * tmpVec[0]
                                        + tmpVec[1] * tmpVec[1]
                                        + tmpVec[2] * tmpVec[2]));;
      }

      return length;
    }

  protected:

    void removeNodes (void)
    {
      //TODO:erase memory allocation. Control share nodes between segments
    }

    NodePtr _begin, _end;

    SegmentPtr _next;
    SegmentPtr _prev;

    SectionPtr _parent;

  };

}

#endif
