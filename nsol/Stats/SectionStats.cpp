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

		case SectionStats::/*TSectionStat::*/SECTION_NUM_STATS:
		default:
		  NSOL_THROW( "no know converstion from TSectionStat to TSegmentStat");
		}

		return SegmentStats::/*TSegmentStat::*/SURFACE;
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

    if( _firstNode )
    {
    	int size_middleNodes = _middleNodes.size();
		NodePtr first, second;
		for ( int i=-1; i< size_middleNodes; i++)
		{
			//Computing pairs of nodes (segments)
			if( size_middleNodes == 0) 				 // without middle nodes
			{
				first  = _firstNode;
				second = _lastNode;
			}else {
				if(i == -1)  						 // first segment
				{
					first  = _firstNode;
					second = _middleNodes.at(i+1);
				}else
				{
					if( i == ( size_middleNodes - 1)) // last segment
					{
						first  = second;
						second = _lastNode;
					}
					else							  // middle segments
					{
						first  = second;
						second = _middleNodes.at(i+1);
					}
				}
			}


			if ( agg == /*TAggregation::*/VARIANCE )
			{
			  float tmpValue =
					SegmentStats::getStat( toSegmentStat( stat ), first, second );
			  value += ( mean - tmpValue ) * ( mean - tmpValue );
			}
			else if ( agg == /*TAggregation::*/MIN )
			  value =
				std::min( value,
						SegmentStats::getStat( toSegmentStat( stat ), first, second ));
			else if ( agg == /*TAggregation::*/MAX )
			  value =
				std::max( value,
						 SegmentStats::getStat( toSegmentStat( stat ), first, second ));
			else
			  value += SegmentStats::getStat( toSegmentStat( stat ), first, second );

			numSegments++;
		 }

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
