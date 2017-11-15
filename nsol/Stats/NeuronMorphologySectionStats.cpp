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

#include "NeuronMorphologySectionStats.h"
#include "SegmentStats.h"


namespace nsol
{

  SegmentStats::TSegmentStat
  toSegmentStat(
    NeuronMorphologySectionStats::TNeuronMorphologySectionStat stat )
  {
    switch( stat )
    {
    case NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                        */SURFACE:
      return SegmentStats::/*TSegmentStat::*/SURFACE;
      break;

    case NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::*/VOLUME:
      return SegmentStats::/*TSegmentStat::*/VOLUME;
      break;

    case NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::*/LENGTH:
      return SegmentStats::/*TSegmentStat::*/LENGTH;
      break;

    case NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::*/RADIUS:
      return SegmentStats::/*TSegmentStat::*/RADIUS;
      break;

    case NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                        */NEURON_MORPHOLOGY_SECTION_NUM_STATS:
    default:
      NSOL_THROW( "no known conversion from TSectionStat to TSegmentStat");
    }

    return SegmentStats::/*TSegmentStat::*/SURFACE;
  }

  //TODO Make SEGMENT_RADIUS stat lenght-weighted
  float NeuronMorphologySectionStats::getStat(
    TNeuronMorphologySectionStat stat, TAggregation agg ) const
  {
    NSOL_DEBUG_CHECK( stat < NEURON_MORPHOLOGY_SECTION_NUM_STATS,
                      "section stat unknown");
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
