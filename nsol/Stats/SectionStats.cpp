/**
 * @file    SectionStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "SectionStats.h"

namespace nsol
{

  float SectionStats::volume( void )
  {
    float accumVolume = 0.0f;

    if ( _firstSegment )
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
        accumVolume += sP->volume();
        sP = sP->next();
      }
    }

    return accumVolume;
  }

  float SectionStats::surface( void )
  {
    float accumSurface = 0.0f;

    if (_firstSegment)
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
        accumSurface += sP->surface();
        sP = sP->next();
      }
    }

    return accumSurface;
  }

  float SectionStats::length( void )
  {
    float accumLength = 0.0f;

    if (_firstSegment)
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
        accumLength += sP->length();
        sP = sP->next();
      }
    }

    return accumLength;
  }


  // float SectionStats::cachedSurface( SectionPtr section_ )
  // {
  //   auto cachedSection = dynamic_cast< CachedSection * >( section_);
  //   NSOL_DEBUG_CHECK( cachedSection, "section not cached");
  //   return SectionStats::cachedSurface( cachedSection );
  // }

  // float SectionStats::cachedSurface( CachedSectionPtr cachedSection_ )
  // {
  //   NSOL_DEBUG_CHECK( cachedSection_, "cachedSection pointing to null");

  //   // If cached and not dirty no need to recompute surface
  //   if ( ! cachedSection_->dirty( ))
  //     return cachedSection_->value( CachedSection::SURFACE );

  //   float accumSurface = SectionStats::surface( cachedSection_ );

  //   cachedSection_->value( CachedSection::SURFACE ) = accumSurface;
  //   cachedSection_->setClean( );

  //   return accumSurface;

  // }

  // float SectionStats::surface( SectionPtr section_, bool tryCached )
  // {
  //   NSOL_DEBUG_CHECK( section_, "section pointing to null");

  //   CachedSection * cachedSection = nullptr;

  //   if ( tryCached )
  //   {
  //     cachedSection = NSOL_DYNAMIC_CAST( CachedSection ,  section_ );

  //     // If cached and not dirty no need to recompute surface
  //     if ( cachedSection && ! cachedSection->dirty( ))
  //       return cachedSection->value( CachedSection::SURFACE );
  //   }

  //   // Otherwise volume need to be computed
  //   float accumSurface = 0.0f;

  //   if ( section_->firstSegment( ))
  //   {
  //     SegmentPtr segment = section_->firstSegment( );

  //     while ( segment )
  //     {
  //       accumSurface += SegmentStats::surface( segment, tryCached );
  //       segment = segment->next( );
  //     }
  //   }

  //   // If cached update the cached value and set clean
  //   if ( cachedSection )
  //   {
  //     cachedSection->value( CachedSection::SURFACE ) = accumSurface;
  //     cachedSection->setClean( );
  //   }

  //   return accumSurface;

  // } // SectionStats::surface


  // float SectionStats::volume( SectionPtr section_ )
  // {

  //   auto cachedSection = dynamic_cast< CachedSection * >( section_);

  //   // If cached and not dirty no need to recompute surface
  //   if ( cachedSection && !cachedSection->dirty( ) )
  //     return cachedSection->value( CachedSection::VOLUME );    
      
  //   // Otherwise volume need to be computed
  //   float accumVolume = 0.0f;
      
  //   if ( section_->firstSegment( ))
  //   {
  //     SegmentPtr segment = section_->firstSegment( );
	
  //     while ( segment )
  //     {
  //       accumVolume += segment->volume( );
  //       segment = segment->next( );
  //     }
  //   }

  //   // If cached update the cached value and set clean
  //   if ( cachedSection )
  //   {
  //     cachedSection->value( CachedSection::VOLUME ) = accumVolume;
  //     cachedSection->setClean( );
  //   }
      
  //   return accumVolume;

  // } // SectionStats::volume

  // float SectionStats::length( SectionPtr section_ )
  // {
    
  //   auto cachedSection = dynamic_cast< CachedSection * >( section_);
    
  //   // If cached and not dirty no need to recompute surface
  //   if ( cachedSection && !cachedSection->dirty( ) )
  //     return cachedSection->value( CachedSection::LENGTH );    
      
  //   // Otherwise length need to be computed
  //   float accumLength = 0.0f;
      
  //   if ( section_->firstSegment( ))
  //   {
  //     SegmentPtr segment = section_->firstSegment( );
	
  //     while ( segment )
  //     {
  //       accumLength += segment->length( );
  //       segment = segment->next( );
  //     }
  //   }

  //   // If cached update the cached value and set clean
  //   if ( cachedSection )
  //   {
  //     cachedSection->value( CachedSection::LENGTH ) = accumLength;
  //     cachedSection->setClean( );
  //   }
      
  //   return accumLength;


  // } // SectionStats::length


  // float SectionStats::meanRadius( SectionPtr section_ )
  // {

  //  auto cachedSection = dynamic_cast< CachedSection * >( section_);
    
  //   // If cached and not dirty no need to recompute surface
  //   if ( cachedSection && !cachedSection->dirty( ) )
  //     return cachedSection->value( CachedSection::MEAN_RADIUS );

  //   // Otherwise mean radius has to be computed

  //   float acummRadius = 0.0f;

  //   unsigned int numSegments = 0;


  //   if ( section_->firstSegment( ))
  //   {
  //     SegmentPtr segment = section_->firstSegment( );

  //     while ( segment )
  //     {
  //       #ifdef DEBUG
  //       if ( ! segment->begin( ) )
  //         NSOL_THROW( "segment has no begin node " );
  //       #endif

  // 	acummRadius += segment->begin( )->radius( );
  // 	numSegments++;

  // 	segment = segment->next( );
  //     }
      
  //     #ifdef DEBUG
  //     if ( ! segment->end( ) )
  //       NSOL_THROW( "segment has no end node " );
  //     #endif

  //     acummRadius += section_->lastSegment( )->end( )->radius( );

  //   }

  //   float meanRadius = acummRadius / ( numSegments + 1 );

  //   // If cached update the cached value and set clean
  //   if ( cachedSection )
  //   {
  //     cachedSection->value( CachedSection::MEAN_RADIUS ) = meanRadius;
  //     cachedSection->setClean( );
  //   }


  //   return meanRadius;


  // } // SectionStats::meanRadius



} // namespace nsol

