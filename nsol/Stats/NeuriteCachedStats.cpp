/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "NeuriteCachedStats.h"
#include "../Neurite.h"
#include "../NeuronMorphology.h"

namespace nsol
{


  NeuriteCachedStats::NeuriteCachedStats( TNeuriteType neuriteType_ )
    : NeuriteStats( neuriteType_ )
    , Cached( )
  {
  }

  NeuriteCachedStats::~NeuriteCachedStats( void )
  {
  }

  void NeuriteCachedStats::setAndPropagateDirty( unsigned int id )
  {
    NSOL_DEBUG_CHECK( id < NEURITE_NUM_STATS, "id not valid" );

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

  void NeuriteCachedStats::firstSection( NeuronMorphologySectionPtr section_ )
  {
    this->Neurite::firstSection( section_ );
    this->setAndPropagateDirty( );
  }


  float NeuriteCachedStats::getStat(
    TNeuriteStat stat, TAggregation agg ) const
  {
    // Only totals are cached
    if ( agg == /*TAggregation::*/TOTAL )
    {
      if ( ! this->dirty( stat ))
        return this->getValue( stat );

      float statValue = this->NeuriteStats::getStat( stat, agg );
      this->cacheValue( stat, statValue );

      return statValue;
    }

    return this->NeuriteStats::getStat( stat, agg );
  }


  // float NeuriteCachedStats::volume( void ) const
  // {

  //   if ( ! this->dirty( NeuriteCachedStats::VOLUME ))
  //     return this->getValue( NeuriteCachedStats::VOLUME );

  //   float accumVolume = this->NeuriteStats::volume( );

  //   this->cacheValue( NeuriteCachedStats::SURFACE, accumVolume );

  //   return accumVolume;

  // }

  // float NeuriteCachedStats::surface( void ) const
  // {
  //   if ( ! this->dirty( NeuriteCachedStats::SURFACE ))
  //     return this->getValue( NeuriteCachedStats::SURFACE );

  //   float accumSurface = this->NeuriteStats::surface( );

  //   this->cacheValue( NeuriteCachedStats::SURFACE, accumSurface );

  //   return accumSurface;

  // }

  // float NeuriteCachedStats::length( void ) const
  // {

  //   if ( ! this->dirty( NeuriteCachedStats::LENGTH ))
  //     return this->getValue( NeuriteCachedStats::LENGTH );

  //   float accumLength = this->NeuriteStats::length( );

  //   this->cacheValue( NeuriteCachedStats::LENGTH, accumLength );

  //   return accumLength;

  // }

  // unsigned int NeuriteCachedStats::bifurcations( void ) const
  // {

  //   if ( ! this->dirty( NeuriteCachedStats::BIFURCATIONS ))
  //     return int( this->getValue( NeuriteCachedStats::BIFURCATIONS ));

  //   unsigned int  accumBifurcations = this->NeuriteStats::bifurcations( );

  //   this->cacheValue( NeuriteCachedStats::BIFURCATIONS,
  //                     float( accumBifurcations ) );

  //   return accumBifurcations;

  // }


} // namespace nsol
