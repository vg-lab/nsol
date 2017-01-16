/**
 * @file    NeuronMorphologyStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "NeuronMorphologyStats.h"
#include "NeuriteStats.h"
#include "SomaStats.h"

namespace nsol
{

#define __NMS NeuronMorphologyStats/*::TNeuronMorphologyStat*/

  NeuriteStats::TNeuriteStat
  toNeuriteStat( NeuronMorphologyStats::TNeuronMorphologyStat stat )
  {
    switch( stat )
    {
      // Volume
      case __NMS::DENDRITIC_VOLUME:
      case __NMS::AXON_VOLUME:
      case __NMS::NEURITIC_VOLUME:
      case __NMS::VOLUME:
        return NeuriteStats::/*TNeuriteStat::*/VOLUME;
        break;
      // Surface
      case __NMS::DENDRITIC_SURFACE:
      case __NMS::AXON_SURFACE:
      case __NMS::NEURITIC_SURFACE:
      case __NMS::SURFACE:
        return NeuriteStats::/*TNeuriteStat::*/SURFACE;
        break;
      // Length
      case __NMS::DENDRITIC_LENGTH:
      case __NMS::AXON_LENGTH:
      case __NMS::NEURITIC_LENGTH:
        return NeuriteStats::/*TNeuriteStat::*/LENGTH;
        break;
      // Bifurcations
      case __NMS::DENDRITIC_BIFURCATIONS:
      case __NMS::AXON_BIFURCATIONS:
      case __NMS::NEURITIC_BIFURCATIONS:
        return NeuriteStats::/*TNeuriteStat::*/BIFURCATIONS;
        break;

    case __NMS::SOMA_SURFACE:
    case __NMS::SOMA_VOLUME:
    case __NMS::NEURON_MORPHOLOGY_NUM_STATS:
    default:
      NSOL_THROW(
        "no know converstion from TNeuronMorphologyStat to TNeuriteStat");
    }

    return NeuriteStats::/*TNeuriteStat::*/SURFACE;
  }

  NeuronMorphologyStats * NeuronMorphologyStats::stats( void )
  {
    return this;
  }

  bool RelevantNeurite( NeuronMorphologyStats::TNeuronMorphologyStat stat,
                        NeuritePtr neurite )
  {


    switch( stat )
    {
    // Dendrite
    case __NMS::DENDRITIC_VOLUME:
    case __NMS::DENDRITIC_SURFACE:
    case __NMS::DENDRITIC_LENGTH:
    case __NMS::DENDRITIC_BIFURCATIONS:
      NSOL_DEBUG_CHECK( ( neurite->neuriteType( ) == Neurite::DENDRITE ) ==
                        bool( NSOL_DYNAMIC_CAST( Dendrite, neurite )),
                        "dendrite type not consistent" );
      return ( neurite->neuriteType( ) == Neurite::DENDRITE );
      break;

    // Axon
    case __NMS::AXON_VOLUME:
    case __NMS::AXON_SURFACE:
    case __NMS::AXON_LENGTH:
    case __NMS::AXON_BIFURCATIONS:
      NSOL_DEBUG_CHECK( ( neurite->neuriteType( ) == Neurite::AXON ) ==
                        bool( NSOL_DYNAMIC_CAST( Axon, neurite )),
                        "axon type not consistent" );
      return ( neurite->neuriteType( ) == Neurite::AXON );
      break;

    case __NMS::NEURITIC_VOLUME:
    case __NMS::NEURITIC_SURFACE:
    case __NMS::NEURITIC_LENGTH:
    case __NMS::NEURITIC_BIFURCATIONS:
    case __NMS::VOLUME:
    case __NMS::SURFACE:
      return true;
      break;

    case __NMS::SOMA_VOLUME:
    case __NMS::SOMA_SURFACE:
      return false;
      break;

    case __NMS::NEURON_MORPHOLOGY_NUM_STATS:
    default:
      NSOL_THROW( "no know type of TNeuronMorphologyStat");
    }

    return false;
  }

  float NeuronMorphologyStats::getStat( TNeuronMorphologyStat stat,
                                        TAggregation agg ) const
  {
    NSOL_DEBUG_CHECK( stat < NEURON_MORPHOLOGY_NUM_STATS,
                      "neuron morphology stat unknown");
    NSOL_DEBUG_CHECK( validAggregation( agg ), "unknown aggregation");


    if ( stat == SURFACE )
    {
      NSOL_DEBUG_CHECK( agg == /*TAggregation::*/TOTAL,
                        "invalid aggregation" );
      return
        this->getStat( NEURITIC_SURFACE ) +
        this->getStat( SOMA_SURFACE );
    }

    if ( stat == VOLUME )
    {
      NSOL_DEBUG_CHECK( agg == /*TAggregation::*/TOTAL,
                        "invalid aggregation" );
      return
        this->getStat( NEURITIC_VOLUME ) +
        this->getStat( SOMA_VOLUME );
    }


    // Computation for soma based
    if ( stat == SOMA_SURFACE )
    {
      NSOL_DEBUG_CHECK( agg == /*TAggregation::*/TOTAL,
                        "soma stats aggregation invalid" );
      NSOL_DEBUG_CHECK( _soma->stats( ), "soma without stats" );
      return _soma->stats( )->getStat( SomaStats::/*TSomaStat::*/SURFACE );
    }
    if ( stat == SOMA_VOLUME )
    {
      NSOL_DEBUG_CHECK( agg == /*TAggregation::*/TOTAL,
                        "soma stats aggregation invalid" );
      NSOL_DEBUG_CHECK( _soma->stats( ), "soma without stats" );
      return _soma->stats( )->getStat( SomaStats::VOLUME );
    }

    // Computation for neurite based
    float value = 0.0f;
    float mean = 0.0f;

    if ( agg == /*TAggregation::*/STD_DEV )
      return sqrt( this->getStat( stat, /*TAggregation::*/VARIANCE ));

    if ( agg == /*TAggregation::*/MIN )
      value = std::numeric_limits< float >::max( );

    if ( agg == /*TAggregation::*/MAX )
      value = std::numeric_limits< float >::min( );

    if ( agg == /*TAggregation::*/VARIANCE )
      mean = this->getStat( stat,  /*TAggregation::*/MEAN );


    NSOL_CONST_FOREACH( neurite, _neurites )
    {

      if ( RelevantNeurite( stat, * neurite )  )
      {
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "dendrite does not have stats" );

        float tmpValue =
          ( * neurite )->stats( )->getStat(
            toNeuriteStat( stat ), /*TAggregation::*/TOTAL  );

        if ( agg == /*TAggregation::*/VARIANCE )
          value += ( mean - tmpValue ) * ( mean - tmpValue );
        else if ( agg == /*TAggregation::*/MIN )
          value = std::min( value, tmpValue );
        else if ( agg == /*TAggregation::*/MAX )
          value = std::max( value, tmpValue );
        else
          value += tmpValue;

      }
    }

    switch ( agg )
    {
    case /*TAggregation::*/TOTAL:
    case /*TAggregation::*/MIN:
    case /*TAggregation::*/MAX:
      return value;
    case /*TAggregation::*/MEAN:
    case /*TAggregation::*/VARIANCE:
      return ( _neurites.size( ) == 0 ? 0 : value / _neurites.size( ));
    case /*TAggregation::*/STD_DEV:
      // Shouldn't get here
      break;
    }
    NSOL_THROW( "aggregation op not valid" )
    return 0.0f;

  }


  //
  // Volume related methods
  //

//   float NeuronMorphologyStats::dendriticVolume( void ) const
//   {
//     float accumVolume = 0.0f;

//     NSOL_CONST_FOREACH( neurite, _neurites )
//     {
//       if ( ( * neurite )->neuriteType( ) == Neurite::DENDRITE )
//       {
//         NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Dendrite, * neurite ),
//                           "dendrite type not consistent" );
//         NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
//                           "dendrite does not have stats" );
// //        accumVolume += ( * neurite )->stats( )->volume( );
//         accumVolume += ( * neurite )->stats( )->getStat(
//           NeuriteStats::TNeuriteStat::VOLUME );
//       }
//     }
//     return accumVolume;
//   }

//   float NeuronMorphologyStats::axonVolume( void ) const
//   {
//     float accumVolume = 0.0f;

//     NSOL_CONST_FOREACH( neurite, _neurites )
//     {
//       if ( ( * neurite )->neuriteType( ) == Neurite::AXON )
//       {
//         NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Axon, * neurite ),
//                           "axon type not consistent" );
//         NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
//                           "axon does not have stats" );
//         accumVolume += ( * neurite )->stats( )->getStat(
//           NeuriteStats::TNeuriteStat::VOLUME );
//       }
//     }
//     return accumVolume;
//   }

//   float NeuronMorphologyStats::neuriticVolume( void ) const
//   {
//     return this->dendriticVolume( ) + this->axonVolume( );
//   }

//   float NeuronMorphologyStats::somaVolume( void ) const
//   {
//     return 0.0f; //!TODO: compute soma volume
//   }

//   float NeuronMorphologyStats::volume( void ) const
//   {
//     return this->neuriticVolume( ) + this->somaVolume( );
//   }

//   //
//   // Surface related methods
//   //

//   float NeuronMorphologyStats::dendriticSurface( void ) const
//   {
//     float accumSurface = 0.0f;

//     NSOL_CONST_FOREACH( neurite, _neurites )
//     {
//       if ( ( * neurite )->neuriteType( ) == Neurite::DENDRITE )
//       {
//         NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Dendrite, * neurite ),
//                           "dendrite type not consistent" );
//         NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
//                           "dendrite does not have stats" );
//         accumSurface += ( * neurite )->stats( )->getStat(
//           NeuriteStats::TNeuriteStat::SURFACE );
//       }
//     }
//     return accumSurface;
//   }

//   float NeuronMorphologyStats::axonSurface( void ) const
//   {
//     float accumSurface = 0.0f;

//     NSOL_CONST_FOREACH( neurite, _neurites )
//     {
//       if ( ( * neurite )->neuriteType( ) == Neurite::AXON )
//       {
//         NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Axon, * neurite ),
//                           "axon type not consistent" );
//         NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
//                           "axon does not have stats" );
//         accumSurface += ( * neurite )->stats( )->getStat(
//           NeuriteStats::TNeuriteStat::SURFACE );
//       }
//     }
//     return accumSurface;
//   }

//   float NeuronMorphologyStats::neuriticSurface( void ) const
//   {
//     return this->dendriticSurface( ) + this->axonSurface( );
//   }

//   float NeuronMorphologyStats::somaSurface( void ) const
//   {
//     return 0.0f; //!TODO: compute soma surface
//   }

//   float NeuronMorphologyStats::surface( void ) const
//   {
//     return this->neuriticSurface( ) + this->somaSurface( );
//   }

//   //
//   // Length related methods
//   //

//   float NeuronMorphologyStats::dendriticLength( void ) const
//   {
//     float accumLength = 0.0f;

//     NSOL_CONST_FOREACH( neurite, _neurites )
//     {
//       if ( ( * neurite )->neuriteType( ) == Neurite::DENDRITE )
//       {
//         NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Dendrite, * neurite ),
//                           "dendrite type not consistent" );
//         NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
//                           "dendrite does not have stats" );
//         accumLength += ( * neurite )->stats( )->getStat(
//           NeuriteStats::TNeuriteStat::LENGTH );
//       }
//     }
//     return accumLength;
//   }

//   float NeuronMorphologyStats::axonLength( void ) const
//   {
//     float accumLength = 0.0f;

//     NSOL_CONST_FOREACH( neurite, _neurites )
//     {
//       if ( ( * neurite )->neuriteType( ) == Neurite::AXON )
//       {
//         NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Axon, * neurite ),
//                           "axon type not consistent" );
//         NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
//                           "axon does not have stats" );
//         accumLength += ( * neurite )->stats( )->getStat(
//           NeuriteStats::TNeuriteStat::LENGTH );
//       }
//     }
//     return accumLength;
//   }

//   float NeuronMorphologyStats::neuriticLength( void ) const
//   {
//     return this->dendriticLength( ) + this->axonLength( );
//   }

//   //
//   // Bifuractions methods
//   //
//   unsigned int NeuronMorphologyStats::dendriticBifurcations( void ) const
//   {
//     unsigned int accumBifurcations = 0;

//     NSOL_CONST_FOREACH( neurite, _neurites )
//     {
//       if ( ( * neurite )->neuriteType( ) == Neurite::DENDRITE )
//       {
//         NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Dendrite, * neurite ),
//                           "dendrite type not consistent" );
//         NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
//                           "dendrite does not have stats" );
//         accumBifurcations += ( * neurite )->stats( )->getStat(
//           NeuriteStats::TNeuriteStat::BIFURCATIONS );

//       }
//     }
//     return accumBifurcations;

//   }

//   unsigned int NeuronMorphologyStats::axonBifurcations( void ) const
//   {
//     unsigned int accumBifurcations = 0;

//     NSOL_CONST_FOREACH( neurite, _neurites )
//     {
//       if ( ( * neurite )->neuriteType( ) == Neurite::AXON )
//       {
//         NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Axon, * neurite ),
//                           "axon type not consistent" );
//         NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
//                           "axon does not have stats" );
//         accumBifurcations += ( * neurite )->stats( )->getStat(
//           NeuriteStats::TNeuriteStat::BIFURCATIONS );
//       }
//     }
//     return accumBifurcations;
//   }

//   unsigned int NeuronMorphologyStats::neuriticBifurcations( void ) const
//   {
//     return this->dendriticBifurcations( ) + this->axonBifurcations( );
//   }



} // namespace nsol

// EOF
