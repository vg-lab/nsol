/**
 * @file    Section.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_SECTION__
#define __NOL_SECTION__

#include <Types.h>
#include <Segment.h>
#include <Container/Sections.h>
#include <Container/Segments.h>

namespace nol
{

  class Neurite;

  class Section
  {

  public:
    Section()
    {
      _neurite = NULL;
      _parent = NULL;
      _firstSegment = _lastSegment = NULL;
    }

    /* NeuronPtr  neuron(void) { */
    /*   // TODO: handle the error of no parent */
    /*   assert(_neurite); */
    /*   return (_neurite->neuron()); */
    /* } */

    NeuritePtr neurite(void)
    {
      return _neurite;
    }

    void neurite(NeuritePtr neurite)
    {
      _neurite = neurite;
    }

    /* Section & parent (void) { */
    /*   // TODO: handle the error of no parent */
    /*   assert(_parent); */
    /*   return *_parent; */
    /* } */

    /* const Section & parent() const                                  */
    /* { */
    /*   return const_cast< Section& >( *this ).parent(); */
    /* }      */

    /* SectionPtr parentPtr (void) { */
    /*   return _parent; */
    /* } */

    SectionPtr parent(void)
    {
      return _parent;
    }

    void parent(SectionPtr parent)
    {
      _parent = parent;
    }

    void addChild(SectionPtr section)
    {
      assert(section);
      _childs.push_back(section);
    }

    Sections & childs()
    {
      return _childs;
    }

    SegmentPtr addSegment(void)
    {

      SegmentPtr s = new Segment;

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

    SegmentPtr & firstSegment()
    {
      return _firstSegment;
    }

    float volume(void)
    {
      float volume = 0.0f;

      if (_firstSegment)
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

    float surface(void)
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

    float length(void)
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

    unsigned int fuseSection(void)
    {
      SegmentPtr sP = _firstSegment;

      while (sP != _lastSegment)
      {
        SegmentPtr nP = sP->next();
        removeSegment(sP);
        sP = nP;
      }

      _firstSegment->end(_lastSegment->end());

      _lastSegment = _firstSegment;

      return 0;
    }

    float meanRadius(void)
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

  protected:

  private:
    unsigned int removeSegment (SegmentPtr sP)
    {
      if (sP)
      {
        if (sP == _firstSegment)
        {
          sP->end(sP->next()->end());
          sP->next()->removeNodes();
          delete sP->next();
        }
        else
        {
          sP->removeNodes();
          sP->prev()->end(sP->next()->end());

          delete sP->next();
          delete sP;
       }

        return 1;
      }

      return 0;
    }

  public:

    /* //! Parent neuron of the section */
    /* NeuronPtr *_neuron; */

    //! Parent dendrite of the section
    NeuritePtr _neurite;

    //! Parent section of this section
    SectionPtr _parent;

    //! Container of the childrens sections of this section
    Sections _childs;

    //! Container of the segments of this section
    /* Segments _segments; */

    //! First segment
    SegmentPtr _firstSegment;

    //! First segment
    SegmentPtr _lastSegment;

  };

}

#endif
