/**
 * @file    Segment.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_SEGMENT__
#define __NOL_SEGMENT__


namespace nol {
  
  class Segment {
    
    
    
  public:

    SegmentPtr next() const {
      return  _next;
    }

    SegmentPtr  prev() const {
      return  _prev;
    }

    void next(SegmentPtr next) {
      _next = next;
    }
    
    void  prev(SegmentPtr prev) {
      _prev = prev;
    }

    void parentSection(SectionPtr parent) {
      _parent = parent;
    }



  protected:

    NodePtr _begin, _end;
    
    SegmentPtr _next;
    SegmentPtr _prev;

    SectionPtr _parent;


  };

}


#endif
