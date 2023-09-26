/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
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

#include "ColumnStats.h"
#include "MiniColumnStats.h"

namespace nsol
{

#define __MCS MiniColumnStats/*::TMiniColumnStat*/
#define __CS ColumnStats/*::TColumnStat*/

  MiniColumnStats::TMiniColumnStat
  toMiniColumnStat(  ColumnStats::TColumnStat stat )
  {
    switch( stat )
    {
      // Volume
    case __CS::DENDRITIC_VOLUME:
      return __MCS::DENDRITIC_VOLUME;
    case __CS::AXON_VOLUME:
      return __MCS::AXON_VOLUME;
    case __CS::NEURITIC_VOLUME:
      return __MCS::NEURITIC_VOLUME;
    case __CS::SOMA_VOLUME:
      return __MCS::SOMA_VOLUME;
    case __CS::VOLUME:
      return __MCS::VOLUME;

      // Surface
    case __CS::DENDRITIC_SURFACE:
      return __MCS::DENDRITIC_SURFACE;
    case __CS::AXON_SURFACE:
      return __MCS::AXON_SURFACE;
    case __CS::NEURITIC_SURFACE:
      return __MCS::NEURITIC_SURFACE;
    case __CS::SOMA_SURFACE:
      return __MCS::SOMA_SURFACE;
    case __CS::SURFACE:
      return __MCS::SURFACE;

      // Length
    case __CS::DENDRITIC_LENGTH:
      return __MCS::DENDRITIC_LENGTH;
    case __CS::AXON_LENGTH:
      return __MCS::AXON_LENGTH;
    case __CS::NEURITIC_LENGTH:
      return __MCS::NEURITIC_LENGTH;

      // Bifurcations
      case __CS::DENDRITIC_BIFURCATIONS:
        return __MCS::DENDRITIC_BIFURCATIONS;
      case __CS::AXON_BIFURCATIONS:
        return __MCS::AXON_BIFURCATIONS;
      case __CS::NEURITIC_BIFURCATIONS:
        return __MCS::NEURITIC_BIFURCATIONS;

    case __CS::COLUMN_NUM_STATS:
    default:
      NSOL_THROW(
        "no know converstion from TMiniColumnStat to TNeuronMorphologyStat");
    }

    return MiniColumnStats/*::TMiniColumnStat*/::SURFACE;
  }



  ColumnStats::ColumnStats( const unsigned short id_ )
    : Column( id_ )
  {
  }

  ColumnStats * ColumnStats::stats( void )
  {
    return this;
  }

  float ColumnStats::getStat( TColumnStat stat,
                              TAggregation miniColAgg,
                              TAggregation neuronAgg ) const
  {

    MiniColumnStats::TMiniColumnStat nStat =
      toMiniColumnStat( stat );

    float value = 0.f;
    float mean = 0.f;

    if ( miniColAgg == /*TAggregation::*/STD_DEV )
      return sqrt( this->getStat( stat, /*TAggregation::*/VARIANCE ));

    if ( miniColAgg == /*TAggregation::*/MIN )
      value = std::numeric_limits< float >::max( );

    if ( miniColAgg == /*TAggregation::*/MAX )
      value = std::numeric_limits< float >::min( );

    if ( miniColAgg == /*TAggregation::*/VARIANCE )
      mean = this->getStat( stat, /*TAggregation::*/MEAN );

    // if ( miniColAgg == /*TAggregation::*/MEAN )
    //   return ( _miniColumns.size( ) == 0 ? 0.0f :
    //            this->getStat( stat, /*TAggregation::*/TOTAL ) /
    //            float( _miniColumns.size( )));

    NSOL_CONST_FOREACH( miniCol, _miniColumns )
    {
      NSOL_DEBUG_CHECK( ( * miniCol )->stats( ),
                        "neuron without morphology stats" );

      float tmpValue =
        ( * miniCol )->stats( )->getStat( nStat, neuronAgg );

      if ( miniColAgg == /*TAggregation::*/VARIANCE )
        value += ( mean - tmpValue ) * ( mean - tmpValue );

      else if ( miniColAgg == /*TAggregation::*/MIN )
        value = std::min( value, tmpValue );
      else if ( miniColAgg == /*TAggregation::*/MAX )
        value = std::max( value, tmpValue );
      else
        value += tmpValue;
    }
    switch ( miniColAgg )
    {
    case /*TAggregation::*/TOTAL:
    case /*TAggregation::*/MIN:
    case /*TAggregation::*/MAX:
      return value;
    case /*TAggregation::*/VARIANCE:
    case /*TAggregation::*/MEAN:
      return ( _miniColumns.size( ) == 0 ? 0.0f :
               value / float( _miniColumns.size( )));
    case /*TAggregation::*/STD_DEV:
      break;
    }
    NSOL_THROW( "aggregation op not valid" );

    return 0;
  }



} // namespace nsol

// EOF
