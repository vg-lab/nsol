/**
 * @file    NeuriteCachedStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "NeuriteCachedStats.h"
#include "../Neurite.h"
#include "../NeuronMorphology.h"

namespace nsol
{


  NeuriteCachedStats::NeuriteCachedStats( void )
    : NeuriteStats( )
    , Cached( )
  {
  }

  NeuriteCachedStats::~NeuriteCachedStats( void )
  {
  }

  void NeuriteCachedStats::setAndPropagateDirty( unsigned int id )
  {
    NSOL_DEBUG_CHECK( id < NEURITE_NUM_CACHED_VALUES, "id not valid" );

    this->Cached::setAndPropagateDirty( id );
    auto cached = NSOL_DYNAMIC_CAST( Cached, this->morphology( ));
    if ( cached )
      cached->setAndPropagateDirty( id );
  }

  void NeuriteCachedStats::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );

    auto cached = NSOL_DYNAMIC_CAST( Cached, this->morphology( ));
    if ( cached )
      cached->setAndPropagateDirty( );
  }

  void NeuriteCachedStats::firstSection( SectionPtr section_ )
  {
    this->Neurite::firstSection( section_ );
    this->setAndPropagateDirty( );
  }

  float NeuriteCachedStats::volume( void ) const
  {

    if ( ! this->dirty( NeuriteCachedStats::VOLUME ))
      return this->getValue( NeuriteCachedStats::VOLUME );

    float accumVolume = this->NeuriteStats::volume( );

    this->cacheValue( NeuriteCachedStats::SURFACE, accumVolume );

    return accumVolume;

  }

  float NeuriteCachedStats::surface( void ) const
  {

    if ( ! this->dirty( NeuriteCachedStats::SURFACE ))
      return this->getValue( NeuriteCachedStats::SURFACE );

    float accumSurface = this->NeuriteStats::surface( );

    this->cacheValue( NeuriteCachedStats::SURFACE, accumSurface );

    return accumSurface;

  }

  float NeuriteCachedStats::length( void ) const
  {

    if ( ! this->dirty( NeuriteCachedStats::LENGTH ))
      return this->getValue( NeuriteCachedStats::LENGTH );

    float accumLength = this->NeuriteStats::length( );

    this->cacheValue( NeuriteCachedStats::SURFACE, accumLength );

    return accumLength;

  }

} // namespace nsol
