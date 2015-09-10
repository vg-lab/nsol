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

  NodeStats::TNodeStat
  toNodeStat( SectionStats::TSectionStat stat )
  {
	  //TODO:
  }


  float SectionStats::getStat( TSectionStat stat, TAggregation agg ) const
  {
    NSOL_DEBUG_CHECK( stat < SECTION_NUM_STATS, "section stat unknown");
    NSOL_DEBUG_CHECK( validAggregation( agg ), "unknown aggregation");

    float value = 0.0f;
    float mean;
    int numSegments = 0;

    if ( agg == /*TAggregation::*/STD_DEV )
      return sqrt( this->getStat( stat, /*TAggregation::*/VARIANCE ));

    if ( agg == /*TAggregation::*/MIN )
      value = std::numeric_limits< float >::max( );

    if ( agg == /*TAggregation::*/MAX )
      value = std::numeric_limits< float >::min( );

    if ( agg == /*TAggregation::*/VARIANCE )
      mean = this->getStat( stat,  /*TAggregation::*/MEAN );

    if ( _firstSegment )
    {
      SegmentPtr segment = _firstSegment;

      while ( segment )
      {
        NSOL_DEBUG_CHECK( segment->stats( ),
                          "segment doesn't have stats" );

        if ( agg == /*TAggregation::*/VARIANCE )
        {
          float tmpValue =
            segment->stats( )->getStat( toSegmentStat( stat ));
          value += ( mean - tmpValue ) * ( mean - tmpValue );
        }
        else if ( agg == /*TAggregation::*/MIN )
          value =
            std::min( value,
                      segment->stats( )->getStat( toSegmentStat( stat )));
        else if ( agg == /*TAggregation::*/MAX )
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
      case /*TAggregation::*/TOTAL:
      case /*TAggregation::*/MIN:
      case /*TAggregation::*/MAX:
        return value;
      case /*TAggregation::*/MEAN:
      case /*TAggregation::*/VARIANCE:
        return value / numSegments;
      case /*TAggregation::*/STD_DEV:
        break;
      }
      NSOL_THROW( "aggregation op not valid" )
    }
    return 0;
  }

} // namespace nsol
