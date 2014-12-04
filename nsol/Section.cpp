/**
 * @file    Section.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Section.h"

namespace nsol
{

  Section::Section( void )
    : _neurite( nullptr )
    , _parent( nullptr )
    , _firstSegment( nullptr )
    , _lastSegment( nullptr )
  {
  }

  Section::~Section( void )
  {
    // if (_firstSegment)
    // {
    //   SegmentPtr sP = _firstSegment;

    //   while (sP)
    //   {
    // 	SegmentPtr next = sP->_next;
    // 	delete sP;
    // 	sP = next;
    //   }
    // }
  }

  NeuritePtr Section::neurite( void )
  {
    return _neurite;
  }

  void Section::neurite( NeuritePtr newNeurite )
  {
    _neurite = newNeurite;
  }

  SectionPtr Section::parent( void )
  {
    return _parent;
  }

  void Section::parent( SectionPtr newParent )
  {
    _parent = newParent;
  }

  void Section::addChild( SectionPtr section )
  {
    assert(section);
    _children.push_back(section);
  }

  Sections & Section::children( void )
  {
    return _children;
  }

  const Sections & Section::children( void ) const
  {
    return _children;
  }

  SegmentPtr Section::addSegment( SegmentPtr segment )
  {

    NSOL_DEBUG_CHECK( segment, "given segment is null" )

    SegmentPtr s = segment;

    // If this section doesn't have first segment the segment
    // passed or created is added;
    if (!_firstSegment)
    {
      _firstSegment = _lastSegment = s;
      s->next( nullptr );
      s->prev( nullptr );
    }
    // In other case segment is concatenated to last segment
    else
    {
      _lastSegment->next( s );
      s->next( nullptr );
      s->prev( _lastSegment );
      _lastSegment = s;
    }

    return s;

  }

  SegmentPtr Section::firstSegment( void )
  {
    return _firstSegment;
  }

  void Section::firstSegment( SegmentPtr firstSegment_ )
  {
    _firstSegment = firstSegment_;
  }

  SegmentPtr Section::lastSegment( void )
  {
    return _lastSegment;
  }

  void Section::lastSegment( SegmentPtr lastSegment_ )
  {
    _lastSegment = lastSegment_;
  }

  SectionStats * Section::stats( void )
  {
    return nullptr;
  }

  unsigned int Section::fuseSection( void )
  {
    SegmentPtr sP = _firstSegment;

    while (sP != _lastSegment)
    {
      SegmentPtr nP = sP->next( );
      _removeSegment(sP);
      sP = nP;
    }

    _firstSegment->end(_lastSegment->end( ));

    _lastSegment = _firstSegment;

    return 0;
  }

  unsigned int Section::_removeSegment( SegmentPtr segment )
  {
    if ( segment )
    {
      if ( segment == _firstSegment )
      {
        segment->end( segment->next( )->end( ));
        segment->next( )->_removeNodes( );
        NSOL_DELETE_PTR( segment->next( ) );
      }
      else
      {
        segment->_removeNodes( );
        segment->prev( )->end(segment->next( )->end( ));
        NSOL_DELETE_PTR( segment->next( ) );
        NSOL_DELETE_PTR( segment );
      }

      return 1;
    }

    return 0;
  }

} // namespace nsol


// EOF
