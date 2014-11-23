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
#include "error.h"
#include <nsol/NsolTypes.h>
#include <nsol/Segment.h>
#include <nsol/Container/Sections.h>
#include <nsol/Container/Segments.h>

namespace nsol
{

  class Neurite;
  class SectionStats;

  class Section
  {

  public:

    /**
     * Default constructor
     */
    NSOL_API
    Section( void );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~Section( );

    /**
     * Gets the parent Neurite of the Section
     * @return pointer to the parent Neurite
     */
    NSOL_API
    NeuritePtr neurite( void );

    /**
     * Sets the parent neurite of this Section
     * @param neurite pointer to parent neurite
     */
    NSOL_API
    void neurite( NeuritePtr neurite );

    /**
     * Gets the parent Section of this Section
     * @return pointer to the parent Section
     */
    NSOL_API
    SectionPtr parent( void );

    /**
     * Sets the parent Section of this Section
     * @param parent pointer to parent Section
     */
    NSOL_API
    void parent( SectionPtr parent );

    /**
     * Adds child Section to this Section
     * @param section pointer to the section to be added
     */
    NSOL_API
    void addChild( SectionPtr section );

    /**
     * Return the children sections
     * @return container of children sections
     */
    NSOL_API
    Sections & childs( void );

    /**
     * Adds a segment at the end of the section
     * @param segment pointer to the segment to add.
     *        Precondition: pointer is not null.
     * @return pointer to the segment added
     *         (for compatibility with older nsol versions)
     */
    NSOL_API
    virtual SegmentPtr addSegment( SegmentPtr segment );

    /**
     * Gets the first Segment of the Section.
     * @return pointer to the firts segment, null in case it doesn't have any
     */
    NSOL_API
    SegmentPtr firstSegment( void );

    /**
     * Sets first Segment of the Section. This method is virtual to allow
     * reimplementation for cached objects and dirty state propagation
     * @param firstSegment pointer to the the segment.
     */
    NSOL_API
    virtual void firstSegment( SegmentPtr firstSegment );

    /**
     * Gets the first Segment of the Section.
     * @return pointer to the firts segment, null in case it doesn't have any
     */
    NSOL_API
    SegmentPtr lastSegment( void );

    /**
     * Sets last Segment of the Section. This method is virtual to allow
     * reimplementation for cached objects and dirty state propagation
     * @param lastSegment pointer to the the segment.
     */
    NSOL_API
    virtual void lastSegment( SegmentPtr lastSegment );

    /**
     * Returns object as SectionStats
     * @return pointer to SectionStats object
     */
    NSOL_API
    virtual SectionStats * stats( void );

    NSOL_API
    unsigned int fuseSection( void );


  protected:

    //! Parent neurite of the section
    NeuritePtr _neurite;

    //! Parent section of this section
    SectionPtr _parent;

    //! Container of the childrens sections of this section
    Sections _childs;

    //! First segment
    SegmentPtr _firstSegment;

    //! First segment
    SegmentPtr _lastSegment;

  private:
    unsigned int _removeSegment (SegmentPtr sP);


  }; // class Section

} // namespace nsol

#endif
