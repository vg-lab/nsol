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
    }

    /* NeuronPtr  neuron(void) { */
    /*   // TODO: handle the error of no parent */
    /*   assert(_neurite); */
    /*   return (_neurite->neuron()); */
    /* } */

    NeuritePtr * neurite(void) {
      // TODO: handle the error of no parent
      return & _neurite;
    }


    Section & parent (void) {
      // TODO: handle the error of no parent
      assert(_parent);
      return *_parent;
    }
    
    const Section & parent() const                                 
    {
      return const_cast< Section& >( *this ).parent();
    }     

    Section * parent_ptr (void) {
      return _parent;
    }

  protected:

    /* //! Parent neuron of the section */
    /* NeuronPtr *_neuron; */

    //! Parent dendrite of the section
    NeuritePtr _neurite;

    //! Parent section of this section
    SectionPtr _parent;

    //! Container of the childrens sections of this section
    Sections _childs;

    //! Container of the segments of this section
    Segments _segments;
    
  };
  
  
}


#endif
