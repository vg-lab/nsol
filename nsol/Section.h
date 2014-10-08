/**
 * @file    Section.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SECTION__
#define __NSOL_SECTION__

#include "NsolTypes.h"
#include "Segment.h"
#include "Container/Sections.h"
#include "Container/Segments.h"

namespace nsol
{

  class Neurite;

  class Section
  {

  public:
    Section();

    ~Section();

    NeuritePtr neurite(void);

    void neurite(NeuritePtr neurite);

    SectionPtr parent(void);

    void parent(SectionPtr parent);

    void addChild(SectionPtr section);

    Sections & childs();

    SegmentPtr addSegment(void);

    SegmentPtr & firstSegment();

    SegmentPtr & lastSegment();

    float volume(void);

    float surface(void);

    float length(void);

    unsigned int fuseSection(void);

    float meanRadius(void);

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
    /* Segments _segments; */

    //! First segment
    SegmentPtr _firstSegment;

    //! First segment
    SegmentPtr _lastSegment;

  private:
    unsigned int _removeSegment (SegmentPtr sP);


      }; // class Section

} // namespace nsol

#endif
