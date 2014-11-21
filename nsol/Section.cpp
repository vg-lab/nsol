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

  Section::Section( )
    : _neurite( nullptr )
    , _parent( nullptr )
    , _firstSegment( nullptr )
    , _lastSegment( nullptr )
  {
  }

  Section::~Section()
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
    _childs.push_back(section);
  }

  Sections & Section::childs()
  {
    return _childs;
  }

  SegmentPtr Section::addSegment( SegmentPtr segment )
  {

    NSOL_DEBUG_CHECK( segment, "given segment is null" )

    SegmentPtr s = segment;

    // Pablo: I commented out this and added a check before
    // to allow construction from classes derived from Segment
    // If needed segment is created
    // if ( ! s )
    // {
    //   s = SegmentPtr( new Segment );
    //   s->begin( nullptr );
    //   s->end( nullptr );
    // }

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


  // float Section::volume( void )
  // {
  //   float tmpVolume = 0.0f;

  //   if ( _firstSegment )
  //   {
  //     SegmentPtr sP = _firstSegment;

  //     while (sP)
  //     {
  // 	tmpVolume += sP->volume();
  // 	sP = sP->next();
  //     }
  //   }

  //   return tmpVolume;
  // }

  // float Section::surface( void )
  // {
  //   float tmpSurface = 0.0f;

  //   if (_firstSegment)
  //   {
  //     SegmentPtr sP = _firstSegment;

  //     while (sP)
  //     {
  // 	tmpSurface += sP->surface();
  // 	sP = sP->next();
  //     }
  //   }

  //   return tmpSurface;
  // }

  // float Section::length( void )
  // {
  //   float tmpLength = 0.0f;

  //   if (_firstSegment)
  //   {
  //     SegmentPtr sP = _firstSegment;

  //     while (sP)
  //     {
  // 	tmpLength += sP->length();
  // 	sP = sP->next();
  //     }
  //   }

  //   return tmpLength;
  // }

  unsigned int Section::fuseSection( void )
  {
    SegmentPtr sP = _firstSegment;

    while (sP != _lastSegment)
    {
      SegmentPtr nP = sP->next();
      _removeSegment(sP);
      sP = nP;
    }

    _firstSegment->end(_lastSegment->end());

    _lastSegment = _firstSegment;

    return 0;
  }

  // float Section::meanRadius( void )
  // {
  //   float radius = 0.0f;
  //   unsigned int nN = 0;

  //   if (_firstSegment)
  //   {
  //     SegmentPtr sP = _firstSegment;

  //     while (sP)
  //     {
  // 	radius += sP->begin()->radius();
  // 	nN++;

  // 	sP = sP->next();
  //     }

  //     radius += _lastSegment->end()->radius();
  //   }

  //   return radius/(nN + 1);
  // }


  unsigned int Section::_removeSegment (SegmentPtr sP)
  {
    if (sP)
    {
      if (sP == _firstSegment)
      {
        sP->end(sP->next()->end());
        sP->next()->_removeNodes();
        NSOL_DELETE_PTR( sP->next() );
      }
      else
      {
        sP->_removeNodes();
        sP->prev()->end(sP->next()->end());
        NSOL_DELETE_PTR( sP->next() );
        NSOL_DELETE_PTR( sP );
      }

      return 1;
    }

    return 0;
  }

} // namespace nsol


// EOF
