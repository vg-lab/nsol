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

    Segment() :
      _begin(nullptr), _end(nullptr),
      _next(nullptr), _prev(nullptr),
      _parent(nullptr)
    {
    }

    ~Segment()
    {
      //TODO:review shared nodes between segments

      // @pablo: this delete can cause segmentation fault if the 
      // _end node is not in dynamic memory
      // if (_end)
      // delete _end;
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
      return (_begin && _end) ? 
	M_PI * 
	(_begin->point() - _end->point()).length() * 
	_end->radius() *
	_end->radius() : 0.0f;
    }

    float surface(void)
    {
      return (_begin && _end) ?
	M_2_PI * _end->radius() * (_begin->point() - _end->point()).length() :
	0.0f;
    }

    float length(void)
    {
      return (_begin && _end) ?
        (_begin->point() - _end->point()).length() : 0.0f;
    }

  protected:

    void removeNodes (void)
    {
      //TODO:erase memory allocation. Control shared nodes between segments
      //@pablo: be careful, if memory to be deleted 
      // is allocated outside of this class you might end deleting
      // non dynamic memory
    }

    NodePtr _begin, _end;

    SegmentPtr _next;
    SegmentPtr _prev;

    SectionPtr _parent;

  };

}

#endif
