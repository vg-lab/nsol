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
    this->Cached::setAndPropagateDirty( id );

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
    this->Section::lastSegment( lastSegment_ );
    this->setAndPropagateDirty( );
  }

  float SectionCachedStats::volume( void ) const
  {

    if ( ! this->dirty( SectionCachedStats::VOLUME ))
      return this->getValue( SectionCachedStats::VOLUME );

    float accumVolume = this->SectionStats::volume( );

    this->cacheValue( SectionCachedStats::SURFACE, accumVolume );

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

  float SectionCachedStats::length( void ) const
  {

    if ( ! this->dirty( SectionCachedStats::LENGTH ))
      return this->getValue( SectionCachedStats::LENGTH );

    float accumLength = this->SectionStats::length( );

    this->cacheValue( SectionCachedStats::SURFACE, accumLength );

    return accumLength;

  }

} // namespace nsol
