/**
 * @file    Segment.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Segment.h"
#include "error.h"

#include <math.h>

namespace nsol
{

  Segment::Segment( void )
    : _begin( nullptr )
    , _end( nullptr )
    , _next( nullptr )
    , _prev( nullptr )
    , _parent( nullptr )
  {
  }

  Segment::~Segment( void )
  {
    //TODO:review shared nodes between segments

    // @pablo: this delete can cause segmentation fault if the
    // _end node is not in dynamic memory
    // if (_end)
    // delete _end;
  }

  SegmentPtr Segment::next( void ) const
  {
    return _next;
  }

  SegmentPtr Segment::prev( void ) const
  {
    return _prev;
  }

  void Segment::next( SegmentPtr next_ )
  {
    _next = next_;
  }

  void Segment::prev( SegmentPtr prev_ )
  {
    _prev = prev_;
  }

  void Segment::parentSection( SectionPtr parent_ )
  {
    _parent = parent_;
  }

  SectionPtr Segment::parentSection( void )
  {
    return _parent;
  }

  NodePtr Segment::begin( void ) const
  {
    return _begin;
  }

  NodePtr Segment::end( void ) const
  {
    return _end;
  }

  void Segment::begin( NodePtr begin_ )
  {

    NSOL_DEBUG_CHECK( begin_, "begin node is null" );

    if ( _begin )
    {
      Segments::iterator segment =
        std::find ( _begin->parentSegments( ).begin( ),
                    _begin->parentSegments( ).end( ),
                    NSOL_THIS_POINTER );

      if ( segment != _begin->parentSegments( ).end( ) && _begin != _end)
        _begin->parentSegments( ).erase( segment );
    }

    _begin = begin_;
    _begin->parentSegments( ).push_back( NSOL_THIS_POINTER );
  }

  void Segment::end( NodePtr end_ )
  {

    NSOL_DEBUG_CHECK( end_, "begin node is null" );

    if ( _end )
    {
      Segments::iterator segment =
        std::find ( _begin->parentSegments( ).begin( ),
                    _begin->parentSegments( ).end( ),
                    NSOL_THIS_POINTER );

      if ( segment != _end->parentSegments( ).end( ) && _begin != _end)
        _begin->parentSegments( ).erase( segment );
    }

    _end = end_;
    _end->parentSegments( ).push_back( NSOL_THIS_POINTER );
  }

  SegmentStats * Segment::stats( void )
  {
    return nullptr;
  }



  // float Segment::volume( void )
  // {
  //   return ( _begin && _end) ?
  //     float( M_PI) *
  //     ( _begin->point( ) - _end->point( )).length( ) *
  //     _end->radius( ) *
  //     _end->radius( ) : 0.0f;
  // }

  // float Segment::surface( void )
  // {
  //   return ( _begin && _end) ?
  //     float( M_2PI) * _end->radius( ) *
  //     ( _begin->point( ) - _end->point( )).length( ) :
  //     0.0f;
  // }

  // float Segment::length( void )
  // {
  //   return ( _begin && _end) ?
  //     ( _begin->point( ) - _end->point( )).length( ) : 0.0f;
  // }


  void Segment::_removeNodes ( void )
  {
    //TODO:erase memory allocation. Control shared nodes between segments
    //@pablo: be careful, if memory to be deleted
    // is allocated outside of this class you might end deleting
    // non dynamic memory
  }

} // class nsol

// EOF
