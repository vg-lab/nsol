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

#include "NeuriteStats.h"
#include "SectionStats.h"

#include <stack>

namespace nsol
{

  SectionStats::TSectionStat
  toSectionStat( NeuriteStats::TNeuriteStat stat )
  {
    switch( stat )
    {
    case NeuriteStats::/*TNeuriteStat::*/SURFACE:
      return SectionStats::/*TSectionStat::*/SURFACE;
      break;

    case NeuriteStats::/*TNeuriteStat::*/VOLUME:
      return SectionStats::/*TSectionStat::*/VOLUME;
      break;

    case NeuriteStats::/*TNeuriteStat::*/LENGTH:
      return SectionStats::/*TSectionStat::*/LENGTH;
      break;

    case NeuriteStats::/*TNeuriteStat::*/NEURITE_NUM_STATS:
    default:
      NSOL_THROW( "no know converstion from TNeuriteStat to TSectionStat");
    }

    return SectionStats::/*TSectionStat::*/SURFACE;
  }


  NeuriteStats::NeuriteStats( TNeuriteType neuriteType_ )
    : Neurite( neuriteType_ )
  {
  }


  float NeuriteStats::getStat( TNeuriteStat stat,
                               TAggregation agg ) const
  {
    NSOL_DEBUG_CHECK( stat < NEURITE_NUM_STATS, "neurite stat unknown");
    NSOL_DEBUG_CHECK( validAggregation( agg ), "unknown aggregation");

    NSOL_DEBUG_CHECK( ! ( stat == /*TNeuriteStat::*/BIFURCATIONS &&
                          agg != /*TAggregation::*/TOTAL ) ,
                      std::string("non compatible aggregation " ) +
                      std::to_string( ( long long ) agg ));

    float value = 0.0f;
    float mean = 0.0f;
    int numSections = 0;

    if ( agg == /*TAggregation::*/STD_DEV )
      return sqrt( this->getStat( stat, /*TAggregation::*/VARIANCE ));

    if ( agg == /*TAggregation::*/MIN )
      value = std::numeric_limits< float >::max( );

    if ( agg == /*TAggregation::*/MAX )
      value = std::numeric_limits< float >::min( );

    if ( agg == /*TAggregation::*/VARIANCE )
      mean = this->getStat( stat,  /*TAggregation::*/MEAN );

    if ( _firstSection )
    {
      std::stack< SectionPtr > sectionsToProcess;
      sectionsToProcess.push( _firstSection );

      while ( ! sectionsToProcess.empty( ))
      {
        SectionPtr section = sectionsToProcess.top( );
        sectionsToProcess.pop( );

        NSOL_DEBUG_CHECK( section->stats( ),
                          "section doesn't have stats" );

        if ( stat != /*TNeuriteStat::*/BIFURCATIONS )
        {

          if ( agg == /*TAggregation::*/VARIANCE )
          {
            float tmpValue =
              section->stats( )->getStat( toSectionStat( stat ));
            value += ( mean - tmpValue ) * ( mean - tmpValue );
          }
          else if ( agg == /*TAggregation::*/MIN )
            value =
              std::min( value,
                        section->stats( )->getStat( toSectionStat( stat )));
          else if ( agg == /*TAggregation::*/MAX )
            value =
              std::max( value,
                        section->stats( )->getStat( toSectionStat( stat )));
          else if (  agg != /*TAggregation::*/MEAN )
            value += section->stats( )->getStat( toSectionStat( stat ));
        }

        if ( section->children( ).size( ) > 0 )
        {
          if ( stat == /*TNeuriteStat::*/BIFURCATIONS )
            value++;

          NSOL_CONST_FOREACH( child, section->children( ))
            sectionsToProcess.push( * child );
        }
        numSections++;
      } // while sections to process

      switch ( agg )
      {
      case /*TAggregation::*/TOTAL:
      case /*TAggregation::*/MIN:
      case /*TAggregation::*/MAX:
        return value;
        break;
      case /*TAggregation::*/MEAN:
        NSOL_DEBUG_CHECK( value == 0.0f, "value should be 0" );
        return this->getStat( stat, /*TAggregation::*/TOTAL ) / numSections;
        break;
      case /*TAggregation::*/VARIANCE:
        return value / numSections;
        break;
      case /*TAggregation::*/STD_DEV:
        break;
      }
      NSOL_THROW( "aggregation op not valid" )
    }
    return 0;

  }


} // namespace nsol
