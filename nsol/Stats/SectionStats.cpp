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

    case SectionStats::/*TSectionStat::*/RADIUS:
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
    float accumLength;

    if ( agg == /*TAggregation::*/STD_DEV )
      return sqrt( this->getStat( stat, /*TAggregation::*/VARIANCE ));

    if ( agg == /*TAggregation::*/MIN )
      value = std::numeric_limits< float >::max( );

    if ( agg == /*TAggregation::*/MAX )
      value = std::numeric_limits< float >::min( );

    if ( agg == /*TAggregation::*/VARIANCE )
      mean = this->getStat( stat,  /*TAggregation::*/MEAN );

    if( agg == /*TAggregation::*/MEAN && stat == RADIUS )
    {
      accumLength = 0.0f;
    }

    if( _nodes.size( ) > 1 )
    {
      unsigned int size_nodes = ( unsigned int ) _nodes.size();
      NodePtr first;
      NodePtr second;
      //First node already included in middle nodes.
      for ( unsigned int i=0; i < size_nodes - 1 ; i++)
      {
        first = _nodes[i];
        second = _nodes[i+1];

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
        else if (agg == /*TAggregation::*/MEAN)
        {
          if(stat == RADIUS)
          {
            float segmentLength =
                SegmentStats::getStat( toSegmentStat( LENGTH ),
                                       first, second );
            value += ( SegmentStats::getStat( toSegmentStat( stat ),
                         first, second ) * segmentLength );
            accumLength += segmentLength;
          }
          else
          {
            value += SegmentStats::getStat( toSegmentStat( stat ),
                                            first, second );
          }
        }
        else //TOTAL
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
        if(stat == RADIUS)
        {
          return value / accumLength;
        }
        else
        {
          return value / ( size_nodes - 1 );
        }
      case /*TAggregation::*/VARIANCE:
        //(size_middleNodes+1) = number of segments
        return value / ( size_nodes - 1 );
      case /*TAggregation::*/STD_DEV:
        break;
      }
      NSOL_THROW( "aggregation op not valid" )
        }

    return 0;
  }

} // namespace nsol
