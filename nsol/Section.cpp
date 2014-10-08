/**
 * @file    Section.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "Section.h"

namespace nsol
{

  Section::Section( )
    : _neurite( nullptr )
    , _parent( nullptr )
    , _firstSegment( nullptr )
    , _lastSegment( nullptr )
  {
  }

  Section::~Section()
  {
    // if (_firstSegment)
    // {
    //   SegmentPtr sP = _firstSegment;
    
    //   while (sP)
    //   {
    // 	SegmentPtr next = sP->_next;
    // 	delete sP;
    // 	sP = next;
    //   }
    // }
  }

  NeuritePtr Section::neurite(void)
  {
    return _neurite;
  }

  void Section::neurite(NeuritePtr neurite)
  {
    _neurite = neurite;
  }

  SectionPtr Section::parent(void)
  {
    return _parent;
  }

  void Section::parent(SectionPtr parent)
  {
    _parent = parent;
  }

  void Section::addChild(SectionPtr section)
  {
    assert(section);
    _childs.push_back(section);
  }

  Sections & Section::childs()
  {
    return _childs;
  }

  SegmentPtr Section::addSegment(void)
  {

    SegmentPtr s = SegmentPtr( new Segment );

    s->begin(NULL);
    s->end(NULL);

    if (!_firstSegment)
    {
      _firstSegment = _lastSegment = s;
      s->next(NULL);
      s->prev(NULL);
    }
    else
    {
      _lastSegment->next(s);
      s->next(NULL);
      s->prev(_lastSegment);
      _lastSegment = s;
    }

    return s;

  }

  SegmentPtr & Section::firstSegment()
  {
    return _firstSegment;
  }

  SegmentPtr & Section::lastSegment()
  {
    return _lastSegment;
  }


  float Section::volume(void)
  {
    float volume = 0.0f;

    if ( _firstSegment )
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
	volume += sP->volume();
	sP = sP->next();
      }
    }

    return volume;
  }

  float Section::surface(void)
  {
    float surface = 0.0f;

    if (_firstSegment)
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
	surface += sP->surface();
	sP = sP->next();
      }
    }

    return surface;
  }

  float Section::length(void)
  {
    float length = 0.0f;

    if (_firstSegment)
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
	length += sP->length();
	sP = sP->next();
      }
    }

    return length;
  }

  unsigned int Section::fuseSection(void)
  {
    SegmentPtr sP = _firstSegment;

    while (sP != _lastSegment)
    {
      SegmentPtr nP = sP->next();
      _removeSegment(sP);
      sP = nP;
    }

    _firstSegment->end(_lastSegment->end());

    _lastSegment = _firstSegment;

    return 0;
  }

  float Section::meanRadius(void)
  {
    float radius = 0.0f;
    unsigned int nN = 0;

    if (_firstSegment)
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
	radius += sP->begin()->radius();
	nN++;

	sP = sP->next();
      }

      radius += _lastSegment->end()->radius();
    }

    return radius/(nN + 1);
  }


  unsigned int Section::_removeSegment (SegmentPtr sP)
  {
    if (sP)
    {
      if (sP == _firstSegment)
      {
	sP->end(sP->next()->end());
	sP->next()->_removeNodes();
#ifndef NSOL_WITH_SHARED_PTR
	delete sP->next();
#endif
      }
      else
      {
	sP->_removeNodes();
	sP->prev()->end(sP->next()->end());
#ifndef NSOL_WITH_SHARED_PTR
	delete sP->next();
	delete sP;
#endif
      }

      return 1;
    }

    return 0;
  }

} // namespace nsol


// EOF
