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



namespace nol {
  
  class Neurite;

  class Section {

  public:
    Section () {
      _neurite = NULL;
      _parent = NULL;
      _firstSegment = _lastSegment = NULL;
    }

    /* NeuronPtr  neuron(void) { */
    /*   // TODO: handle the error of no parent */
    /*   assert(_neurite); */
    /*   return (_neurite->neuron()); */
    /* } */

    NeuritePtr  neurite(void) {
      return  _neurite;
    }

    void neurite(NeuritePtr neurite) {
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


    SectionPtr parent(void) {
      return _parent;
    }

    void parent(SectionPtr parent) {
      _parent = parent;;
    }

    void addChild (SectionPtr section) {
      assert(section);
      _childs.push_back(section);
    }


    SegmentPtr addSegment(void) {

      SegmentPtr s = new Segment;

      if (!_firstSegment)
	_firstSegment = _lastSegment = s;
      else {
	_lastSegment->next(s);
	s->next(NULL);
	s->prev(_lastSegment);
	_lastSegment = s;
      }

      return s;

    }

  protected:
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
