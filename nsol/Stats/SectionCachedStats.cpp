/**
 * @file    SectionCachedStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "SectionCachedStats.h"
#include "../Neurite.h"

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
    NSOL_DEBUG_CHECK( id < SECTION_NUM_STATS, "id not valid" );

    this->Cached::setAndPropagateDirty( id );
    auto cached = NSOL_DYNAMIC_CAST( Cached, this->neurite( ));
    if ( cached )
      cached->setAndPropagateDirty( id );
  }

  void SectionCachedStats::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );

    auto cached = NSOL_DYNAMIC_CAST( Cached, this->neurite( ));
    if ( cached )
      cached->setAndPropagateDirty( );
  }

  NodePtr SectionCachedStats::addNode( NodePtr node )
  {
    this->setAndPropagateDirty( );
    return this->Section::addNode( node );
  }

  void SectionCachedStats::firstNode( NodePtr firstNode_ )
  {
    return this->Section::firstNode( firstNode_ );
    this->setAndPropagateDirty( );
  }

  float SectionCachedStats::getStat( TSectionStat stat ) const
  {
    if ( ! this->dirty( stat ))
      return this->getValue( stat );

    float statValue = this->SectionStats::getStat( stat );
    this->cacheValue( stat, statValue );

    return statValue;
  }

  // float SectionCachedStats::volume( void ) const
  // {

  //   if ( ! this->dirty( SectionCachedStats::VOLUME ))
  //     return this->getValue( SectionCachedStats::VOLUME );

  //   float accumVolume = this->SectionStats::volume( );

  //   this->cacheValue( SectionCachedStats::SURFACE, accumVolume );

  //   return accumVolume;

  // }

  // float SectionCachedStats::surface( void ) const
  // {

  //   if ( ! this->dirty( SectionCachedStats::SURFACE ))
  //     return this->getValue( SectionCachedStats::SURFACE );

  //   float accumSurface = this->SectionStats::surface( );

  //   this->cacheValue( SectionCachedStats::SURFACE, accumSurface );

  //   return accumSurface;

  // }

  // float SectionCachedStats::length( void ) const
  // {

  //   if ( ! this->dirty( SectionCachedStats::LENGTH ))
  //     return this->getValue( SectionCachedStats::LENGTH );

  //   float accumLength = this->SectionStats::length( );

  //   this->cacheValue( SectionCachedStats::SURFACE, accumLength );

  //   return accumLength;

  // }

} // namespace nsol
