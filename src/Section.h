/**
 * @file    Section.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NS_DATA_LIB_SECTION__
#define __NS_DATA_LIB_SECTION__

#include <Sections.h>
#include <Segment.h>



namespace nsdl {
  
  class Section {
    
  protected:
    Section *_parent;
    Sections _childs;
    
    Vector<Segment> _segments;
    
  };
  
/*   //! Definition of pointer to Dendrite */
/* #if !BOOST */
/*   typedef  Section * SectionPtr; */
/* #else */
/*   typedef  boost::shared_ptr<Section> * SectionPtr; */
/* #endif */
  
}


#endif
