/**
 * @file    Segment.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 * Do not distribute without further notice.
 */
#ifndef __NSOL_SEGMENT__
#define __NSOL_SEGMENT__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Node.h>

namespace nsol
{

  class SegmentStats;

  class Segment
  {

    friend class Section;

  public:

    NSOL_API
    Segment( void );

    NSOL_API
    virtual ~Segment( void );

    NSOL_API
    SegmentPtr next( void ) const;

    NSOL_API
    SegmentPtr prev( void ) const;

    NSOL_API
    void next( SegmentPtr next_ );

    NSOL_API
    void prev( SegmentPtr prev_ );

    NSOL_API
    void parentSection( SectionPtr parent_ );

    NSOL_API
    SectionPtr parentSection( void );

    NSOL_API
    NodePtr begin( void ) const;

    NSOL_API
    NodePtr end( void ) const;

    NSOL_API
    virtual void begin( NodePtr begin_ );

    NSOL_API
    virtual void end( NodePtr end_ );

    NSOL_API
    virtual SegmentStats * stats( void );

  protected:

    void _removeNodes ( void );

    NodePtr _begin, _end;

    SegmentPtr _next;
    SegmentPtr _prev;

    SectionPtr _parent;

  };

} // namespace nsol

#endif

// EOF
