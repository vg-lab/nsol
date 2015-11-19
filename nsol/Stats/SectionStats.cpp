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
    case SectionStats::/*TSectionStat::*/SURFACE:
      return SegmentStats::/*TSegmentStat::*/SURFACE;
      break;

    case SectionStats::/*TSectionStat::*/VOLUME:
      return SegmentStats::/*TSegmentStat::*/VOLUME;
      break;

    case SectionStats::/*TSectionStat::*/LENGTH:
      return SegmentStats::/*TSegmentStat::*/LENGTH;
      break;

    case SectionStats::/*TSectionStat::*/SEGMENT_RADIUS:
      return SegmentStats::/*TSegmentStat::*/RADIUS;
      break;

    case SectionStats::/*TSectionStat::*/SECTION_NUM_STATS:
    default:
      NSOL_THROW( "no known conversion from TSectionStat to TSegmentStat");
    }

    return SegmentStats::/*TSegmentStat::*/SURFACE;
  }

  //TODO Make SEGMENT_RADIUS stat lenght-weighted
  float SectionStats::getStat( TSectionStat stat, TAggregation agg ) const
  {
    NSOL_DEBUG_CHECK( stat < SECTION_NUM_STATS, "section stat unknown");
    NSOL_DEBUG_CHECK( validAggregation( agg ), "unknown aggregation");

    float value = 0.0f;
    float mean;

    if ( agg == /*TAggregation::*/STD_DEV )
      return sqrt( this->getStat( stat, /*TAggregation::*/VARIANCE ));

    if ( agg == /*TAggregation::*/MIN )
      value = std::numeric_limits< float >::max( );

    if ( agg == /*TAggregation::*/MAX )
      value = std::numeric_limits< float >::min( );

    if ( agg == /*TAggregation::*/VARIANCE )
      mean = this->getStat( stat,  /*TAggregation::*/MEAN );

    if( _firstNode && _lastNode )
    {
      unsigned int size_middleNodes = ( unsigned int )_middleNodes.size();
      NodePtr first = _firstNode;
      NodePtr second = _lastNode;
      for ( unsigned int i=0; i< size_middleNodes + 1 ; i++)
      {
        if( i == size_middleNodes )
          second = _lastNode;
        else
          second = _middleNodes[i];

        if ( agg == /*TAggregation::*/VARIANCE )
        {
          float tmpValue =
            SegmentStats::getStat( toSegmentStat( stat ), first, second );
          value += ( mean - tmpValue ) * ( mean - tmpValue );
        }
        else if ( agg == /*TAggregation::*/MIN )
        {
          value = std::min( value,
                            SegmentStats::getStat( toSegmentStat( stat ),
                                                   first, second ));
        }
        else if ( agg == /*TAggregation::*/MAX )
        {
          value = std::max( value,
                            SegmentStats::getStat( toSegmentStat( stat ),
                                                   first, second ));
        }
        else //TOTAL, MEAN and STD_DEV
        {
          value += SegmentStats::getStat( toSegmentStat( stat ),
                                          first, second );
        }

        first = second;
      }

      switch ( agg )
      {
      case /*TAggregation::*/TOTAL:
      case /*TAggregation::*/MIN:
      case /*TAggregation::*/MAX:
        return value;
      case /*TAggregation::*/MEAN:
      case /*TAggregation::*/VARIANCE:
        //(size_middleNodes+1) = number of segments
        return value / ( size_middleNodes + 1 );
      case /*TAggregation::*/STD_DEV:
        break;
      }
      NSOL_THROW( "aggregation op not valid" )
        }

    return 0;
  }

} // namespace nsol
