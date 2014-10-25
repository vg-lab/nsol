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

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Segment.h>
#include <nsol/Container/Sections.h>
#include <nsol/Container/Segments.h>

namespace nsol
{

  class Neurite;

  class Section
  {

  public:

    NSOL_API
    Section();

    NSOL_API
    ~Section();

    NSOL_API
    NeuritePtr neurite(void);

    NSOL_API
    void neurite(NeuritePtr neurite);

    NSOL_API
    SectionPtr parent(void);

    NSOL_API
    void parent(SectionPtr parent);

    NSOL_API
    void addChild(SectionPtr section);

    NSOL_API
    Sections & childs();

    NSOL_API
    SegmentPtr addSegment(void);

    NSOL_API
    SegmentPtr & firstSegment();

    NSOL_API
    SegmentPtr & lastSegment();

    NSOL_API
    float volume(void);

    NSOL_API
    float surface(void);

    NSOL_API
    float length(void);

    NSOL_API
    unsigned int fuseSection(void);

    NSOL_API
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
