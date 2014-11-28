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

  SegmentStats::TSegmentStat
  toSegmentStat( SectionStats::TSectionStat stat )
  {
    switch( stat )
    {
    case SectionStats::TSectionStat::SURFACE:
      return SegmentStats::TSegmentStat::SURFACE;
      break;

    case SectionStats::TSectionStat::VOLUME:
      return SegmentStats::TSegmentStat::VOLUME;
      break;

    case SectionStats::TSectionStat::LENGTH:
      return SegmentStats::TSegmentStat::LENGTH;
      break;

    // case SectionStats::TSectionStat::MEAN_RADIUS:
    //   return SegmentStats::TSegmentStat::MEAN_RADIUS;
    //   break;

    case SectionStats::TSectionStat::SECTION_NUM_STATS:
    default:
      NSOL_THROW( "no know converstion from TSectionStat to TSegmentStat");
    }

    return SegmentStats::TSegmentStat::SURFACE;
  }


  float SectionStats::getStat( TSectionStat stat, TAggregation agg ) const
  {
    NSOL_DEBUG_CHECK( stat < SECTION_NUM_STATS, "section stat unknown");
    NSOL_DEBUG_CHECK( validAggregation( agg ), "unknown aggregation");

    float value = 0.0f;
    float mean;
    int numSegments = 0;

    if ( agg == TAggregation::STD_DEV )
      return sqrt( this->getStat( stat, TAggregation::VARIANCE ));

    if ( agg == TAggregation::MIN )
      value = std::numeric_limits< float >::max( );

    if ( agg == TAggregation::MAX )
      value = std::numeric_limits< float >::min( );

    if ( agg == TAggregation::VARIANCE )
      mean = this->getStat( stat,  TAggregation::MEAN );

    if ( _firstSegment )
    {
      SegmentPtr segment = _firstSegment;

      while ( segment )
      {
        NSOL_DEBUG_CHECK( segment->stats( ),
                          "segment doesn't have stats" );

        if ( agg == TAggregation::VARIANCE )
        {
          float tmpValue =
            segment->stats( )->getStat( toSegmentStat( stat ));
          value += ( mean - tmpValue ) * ( mean - tmpValue );
        }
        else if ( agg == TAggregation::MIN )
          value =
            std::min( value,
                      segment->stats( )->getStat( toSegmentStat( stat )));
        else if ( agg == TAggregation::MAX )
          value =
            std::max( value,
                      segment->stats( )->getStat( toSegmentStat( stat )));
        else
          value += segment->stats( )->getStat( toSegmentStat( stat ));

        segment = segment->next( );
        numSegments++;
      } // while segments


      switch ( agg )
      {
      case TAggregation::TOTAL:
      case TAggregation::MIN:
      case TAggregation::MAX:
        return value;
      case TAggregation::MEAN:
      case TAggregation::VARIANCE:
        return value / numSegments;
      case TAggregation::STD_DEV:
        break;
      }
      NSOL_THROW( "aggregation op not valid" )
    }
    return 0;
  }

  // float SectionStats::volume( void ) const
  // {
  //   float accumVolume = 0.0f;

  //   if ( _firstSegment )
  //   {
  //     SegmentPtr sP = _firstSegment;

  //     while (sP)
  //     {
  //       NSOL_DEBUG_CHECK( sP->stats( ), "segment doesn't have stats" );
  //       accumVolume += sP->stats( )->volume( );
  //       sP = sP->next();
  //     }
  //   }

  //   return accumVolume;
  // }

  // float SectionStats::surface( void ) const
  // {
  //   float accumSurface = 0.0f;

  //   if (_firstSegment)
  //   {
  //     SegmentPtr segment = _firstSegment;

  //     while (segment)
  //     {
  //       NSOL_DEBUG_CHECK( segment->stats( ) != nullptr ,
  //                         "segment doesn't have stats" );

  //       accumSurface += segment->stats( )->surface( );
  //       segment = segment->next();
  //     }
  //   }

  //   return accumSurface;
  // }

  // float SectionStats::length( void ) const
  // {
  //   float accumLength = 0.0f;

  //   if (_firstSegment)
  //   {
  //     SegmentPtr sP = _firstSegment;

  //     while (sP)
  //     {
  //       NSOL_DEBUG_CHECK( sP->stats( ), "segment doesn't have stats" );
  //       accumLength += sP->stats( )->length( );
  //       sP = sP->next( );
  //     }
  //   }

  //   return accumLength;
  // }


} // namespace nsol
