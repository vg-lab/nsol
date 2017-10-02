/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
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

  void SectionCachedStats::setAndPropagateDirty( unsigned int id_ )
  {
    NSOL_DEBUG_CHECK( id_ < SECTION_NUM_STATS, "id not valid" );

    this->Cached::setAndPropagateDirty( id_ );
    auto cached = NSOL_DYNAMIC_CAST( Cached, this->neurite( ));
    if ( cached )
      cached->setAndPropagateDirty( id_ );
  }

  void SectionCachedStats::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );

    auto cached = NSOL_DYNAMIC_CAST( Cached, this->neurite( ));
    if ( cached )
      cached->setAndPropagateDirty( );
  }

  void SectionCachedStats::addNode( NodePtr node )
  {
    this->setAndPropagateDirty( );
    this->Section::addNode( node );
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
