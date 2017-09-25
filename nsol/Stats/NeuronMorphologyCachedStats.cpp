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

#include "NeuronMorphologyCachedStats.h"
#include "../NeuronMorphology.h"

namespace nsol
{

  float NeuronMorphologyCachedStats::getStat( TNeuronMorphologyStat stat,
                                              TAggregation agg ) const
  {
    // Only totals are cached
    if ( agg == /*TAggregation::*/TOTAL )
    {
      if ( ! this->dirty( stat ))
        return this->getValue( stat );

      float statValue =
        this->NeuronMorphologyStats::getStat( stat, agg );
      this->cacheValue( stat, statValue );

      return statValue;
    }

    return this->NeuronMorphologyStats::getStat( stat, agg );
  }



  void NeuronMorphologyCachedStats::setAndPropagateDirty( unsigned int id )
  {
    NSOL_DEBUG_CHECK( id < NEURON_MORPHOLOGY_NUM_STATS,
                      "id not valid" );

    this->Cached::setAndPropagateDirty( id );

    //TODO: analyze if it should propagate to neuron, which requires
    // a big refactor

  }

  void NeuronMorphologyCachedStats::setAndPropagateDirty( void )
  {
    this->Cached::setAndPropagateDirty( );

    //TODO: analyze if it should propagate to neuron, which requires
    // a big refactor

  }

// #define NSOL_GET_UPDATE_CACHED_STAT( __STAT__, __METHOD__ )
//   if ( ! this->dirty( __STAT__ ))
//     return this->getValue( __STAT__ );
//
//   auto value = this->__METHOD__;
//   this->cacheValue( __STAT__, value );
//
//   return value;


//   float NeuronMorphologyCachedStats::dendriticVolume( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::DENDRITIC_VOLUME,
//       NeuronMorphologyStats::dendriticVolume( ));
//   }

//   float NeuronMorphologyCachedStats::axonVolume( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::AXON_VOLUME,
//       NeuronMorphologyStats::axonVolume( ));  }

//   float NeuronMorphologyCachedStats::neuriticVolume( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::NEURITIC_VOLUME,
//       NeuronMorphologyStats::neuriticVolume( ));
//   }

//   // float NeuronMorphologyCachedStats::somaVolume( void ) const
//   // {
//   // }

//   float NeuronMorphologyCachedStats::volume( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT( NeuronMorphologyStats::VOLUME,
//                                  NeuronMorphologyStats::volume( ));
//   }

//   //
//   // Surface related methods
//   //

//   float NeuronMorphologyCachedStats::dendriticSurface( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::DENDRITIC_SURFACE,
//       NeuronMorphologyStats::dendriticSurface( ));
//   }

//   float NeuronMorphologyCachedStats::axonSurface( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::AXON_SURFACE,
//       NeuronMorphologyStats::axonSurface( ));
//   }

//   float NeuronMorphologyCachedStats::neuriticSurface( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::NEURITIC_SURFACE,
//       NeuronMorphologyStats::neuriticSurface( ));
//   }

//   // float NeuronMorphologyCachedStats::somaSurface( void ) const
//   // {
//   // }

//   float NeuronMorphologyCachedStats::surface( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::SURFACE,
//       NeuronMorphologyStats::surface( ));
//   }


//   //
//   // Length related methods
//   //

//   float NeuronMorphologyCachedStats::dendriticLength( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::DENDRITIC_LENGTH,
//       NeuronMorphologyStats::dendriticLength( ));
//   }

//   float NeuronMorphologyCachedStats::axonLength( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::AXON_LENGTH,
//       NeuronMorphologyStats::axonLength( ));  }

//   float NeuronMorphologyCachedStats::neuriticLength( void ) const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::NEURITIC_LENGTH,
//       NeuronMorphologyStats::neuriticLength( ));
//   }

//   //
//   // Bifuractions methods
//   //
//   unsigned int NeuronMorphologyCachedStats::dendriticBifurcations( void )
//     const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::DENDRITIC_BIFURCATIONS,
//       NeuronMorphologyStats::dendriticBifurcations( ));
//   }

//   unsigned int NeuronMorphologyCachedStats::axonBifurcations( void )
//     const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::AXON_BIFURCATIONS,
//       NeuronMorphologyStats::axonBifurcations( ));  }

//   unsigned int NeuronMorphologyCachedStats::neuriticBifurcations( void )
//     const
//   {
//     NSOL_GET_UPDATE_CACHED_STAT(
//       NeuronMorphologyStats::NEURITIC_BIFURCATIONS,
//       NeuronMorphologyStats::neuriticBifurcations( ));
//   }


}
