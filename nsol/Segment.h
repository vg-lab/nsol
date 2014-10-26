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
  class Segment
  {

    friend class Section;

  public:

    NSOL_API
    Segment( void );

    NSOL_API
    ~Segment( void );

    NSOL_API
    SegmentPtr next( void ) const;

    NSOL_API
    SegmentPtr prev( void ) const;

    NSOL_API
    void next( SegmentPtr next);

    NSOL_API
    void prev( SegmentPtr prev);

    NSOL_API
    void parentSection( SectionPtr parent);

    NSOL_API
    SectionPtr parentSection( void);

    NSOL_API
    NodePtr begin( void) const;

    NSOL_API
    NodePtr end( void) const;

    NSOL_API
    void begin( NodePtr begin );

    NSOL_API
    void end( NodePtr end );

    NSOL_API
    float volume( void );

    NSOL_API
    float surface( void );

    NSOL_API
    float length( void );

  protected:

    void _removeNodes (void);

    NodePtr _begin, _end;

    SegmentPtr _next;
    SegmentPtr _prev;

    SectionPtr _parent;

  };

} // namespace nsol

#endif

// EOF
