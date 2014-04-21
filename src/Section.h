/**
 * @file    Section.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NS_DATA_LIB_SECTION__
#define __NS_DATA_LIB_SECTION__

#include <Types.h>
#include <Segment.h>
#include <Container/Sections.h>
#include <Container/Segments.h>



namespace nsdl {
  
  class Section {
    
    Section () {
      _neuron = NULL;
      _parent = NULL;
    }

  protected:
    Section *_neuron;
    Section *_parent;
    Sections _childs;
    Segments _segments;
    /* Vector<Segment> _segments; */
    
  };
  
  
}


#endif
