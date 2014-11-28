/**
 * @file    SegmentCachedStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "SegmentCachedStats.h"
#include "SectionCachedStats.h"

namespace nsol
{


  SegmentCachedStats::SegmentCachedStats( void )
    : SegmentStats( )
    , Cached( )
  {
  }

  SegmentCachedStats::~SegmentCachedStats( void )
  {
  }

  void SegmentCachedStats::setAndPropagateDirty( unsigned int id )
  {
    this->Cached::setAndPropagateDirty( id );

    auto cached = NSOL_DYNAMIC_CAST( Cached, this->parentSection( ));
    if ( cached )
      cached->setAndPropagateDirty( id );
  }

  void SegmentCachedStats::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );

    auto cached = NSOL_DYNAMIC_CAST( Cached, this->parentSection( ));

    if ( cached )
      cached->setAndPropagateDirty( );
  }

  void SegmentCachedStats::begin( NodePtr begin_ )
  {
    this->Segment::begin( begin_ );
    this->setAndPropagateDirty( );
  }

  void SegmentCachedStats::end( NodePtr end_ )
  {
    this->Segment::end( end_ );
    this->setAndPropagateDirty( );
  }

  float SegmentCachedStats::getStat( TSegmentStat stat ) const
  {
    if ( ! this->dirty( stat ))
      return this->getValue( stat );

    float statValue = this->SegmentStats::getStat( stat );
    this->cacheValue( stat, statValue );

    return statValue;
  }


  // float SegmentCachedStats::volume( void ) const
  // {

  //   if ( ! this->dirty( SegmentCachedStats::VOLUME ))
  //     return this->getValue( SegmentCachedStats::VOLUME );

  //   float accumVolume = this->SegmentStats::volume( );

  //   this->cacheValue( SegmentCachedStats::SURFACE, accumVolume );

  //   return accumVolume;

  // }

  // float SegmentCachedStats::surface( void ) const
  // {

  //   if ( ! this->dirty( SegmentCachedStats::SURFACE ))
  //     return this->getValue( SegmentCachedStats::SURFACE );

  //   float accumSurface = this->SegmentStats::surface( );

  //   this->cacheValue( SegmentCachedStats::SURFACE, accumSurface );

  //   return accumSurface;

  // }

  // float SegmentCachedStats::length( void ) const
  // {

  //   if ( ! this->dirty( SegmentCachedStats::LENGTH ))
  //     return this->getValue( SegmentCachedStats::LENGTH );

  //   float accumLength = this->SegmentStats::length( );

  //   this->cacheValue( SegmentCachedStats::SURFACE, accumLength );

  //   return accumLength;

  // }

} // namespace nsol
