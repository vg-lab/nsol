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

#include "Node.h"
#include "NsolTypes.h"

namespace nsol
{
  class Segment
  {

    friend class Section;

  public:

    Segment( void );

    ~Segment( void );

    SegmentPtr next( void ) const;

    SegmentPtr prev( void ) const;

    void next( SegmentPtr next);

    void prev( SegmentPtr prev);

    void parentSection( SectionPtr parent);

    SectionPtr parentSection( void);

    NodePtr begin( void) const;

    NodePtr end( void) const;

    void begin( NodePtr begin );

    void end( NodePtr end );

    float volume( void );

    float surface( void );

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
