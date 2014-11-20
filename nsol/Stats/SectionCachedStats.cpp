/**
 * @file    SectionCachedStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "SectionCachedStats.h"

namespace nsol
{


  SectionCachedStats::SectionCachedStats( void )
    : SectionStats( )
    , Cached( )
  {
  }

  SectionCachedStats::~SectionCachedStats( void )
  {
  }

  void SectionCachedStats::setAndPropagateDirty( unsigned int id )
  {
    this->setAndPropagateDirty( id );

    auto cached = NSOL_DYNAMIC_CAST( Cached, this->parent( ));
    if ( cached )
      cached->setAndPropagateDirty( id );
  }

  void SectionCachedStats::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );

    auto cached = NSOL_DYNAMIC_CAST( Cached, this->parent( ));
    if ( cached )
      cached->setAndPropagateDirty( );
  }

  SegmentPtr SectionCachedStats::addSegment( SegmentPtr segment )
  {
    this->setAndPropagateDirty( );
    return this->Section::addSegment( segment );
  }

  void SectionCachedStats::firstSegment( SegmentPtr firstSegment_ )
  {
    return this->Section::firstSegment( firstSegment_ );
    this->setAndPropagateDirty( );
  }

  void SectionCachedStats::lastSegment( SegmentPtr lastSegment_ )
  {
    return this->Section::lastSegment( lastSegment_ );
    this->setAndPropagateDirty( );
  }

  float SectionCachedStats::volume( void )
  {

    float accumVolume = 0.0f;

    // if ( this->dirty( ))
    //   return this->value( SectionCachedStats::VOLUME );

    // float accumVolume = this->SectionStats::volume( );

    // this->value( SectionCachedStats::VOLUME ) = accumVolume;
    // this->setClean( );

    return accumVolume;

  }

  float SectionCachedStats::surface( void ) const
  {

    if ( ! this->dirty( SectionCachedStats::SURFACE ))
      return this->getValue( SectionCachedStats::SURFACE );

    float accumSurface = this->SectionStats::surface( );

    this->cacheValue( SectionCachedStats::SURFACE, accumSurface );

    return accumSurface;

  }

} // namespace nsol
