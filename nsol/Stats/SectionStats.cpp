/**
 * @file    SectionStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "SectionStats.h"
#include "SegmentStats.h"

namespace nsol
{

  float SectionStats::volume( void ) const
  {
    float accumVolume = 0.0f;

    if ( _firstSegment )
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
        NSOL_DEBUG_CHECK( sP->stats( ), "segment doesn't have stats" );
        accumVolume += sP->stats( )->volume( );
        sP = sP->next();
      }
    }

    return accumVolume;
  }

  float SectionStats::surface( void ) const
  {
    float accumSurface = 0.0f;

    if (_firstSegment)
    {
      SegmentPtr segment = _firstSegment;

      while (segment)
      {
        NSOL_DEBUG_CHECK( segment->stats( ) != nullptr ,
                          "segment doesn't have stats" );

        accumSurface += segment->stats( )->surface( );
        segment = segment->next();
      }
    }

    return accumSurface;
  }

  float SectionStats::length( void ) const
  {
    float accumLength = 0.0f;

    if (_firstSegment)
    {
      SegmentPtr sP = _firstSegment;

      while (sP)
      {
        NSOL_DEBUG_CHECK( sP->stats( ), "segment doesn't have stats" );
        accumLength += sP->stats( )->length( );
        sP = sP->next( );
      }
    }

    return accumLength;
  }


} // namespace nsol
