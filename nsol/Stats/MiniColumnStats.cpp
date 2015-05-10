/**
 * @file    MiniColumnStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "MiniColumnStats.h"
#include "NeuronMorphologyStats.h"

namespace nsol
{

#define __NMS NeuronMorphologyStats/*::TNeuronMorphologyStat*/
#define __MCS MiniColumnStats/*::TMiniColumnStat*/

  NeuronMorphologyStats::TNeuronMorphologyStat
  toNeuronMorphologyStat( MiniColumnStats::TMiniColumnStat stat )
  {
    switch( stat )
    {
      // Volume
    case __MCS::DENDRITIC_VOLUME:
      return __NMS::DENDRITIC_VOLUME;
    case __MCS::AXON_VOLUME:
      return __NMS::AXON_VOLUME;
    case __MCS::NEURITIC_VOLUME:
      return __NMS::NEURITIC_VOLUME;
    case __MCS::SOMA_VOLUME:
      return __NMS::SOMA_VOLUME;
    case __MCS::VOLUME:
      return __NMS::VOLUME;

      // Surface
    case __MCS::DENDRITIC_SURFACE:
      return __NMS::DENDRITIC_SURFACE;
    case __MCS::AXON_SURFACE:
      return __NMS::AXON_SURFACE;
    case __MCS::NEURITIC_SURFACE:
      return __NMS::NEURITIC_SURFACE;
    case __MCS::SOMA_SURFACE:
      return __NMS::SOMA_SURFACE;
    case __MCS::SURFACE:
      return __NMS::SURFACE;

      // Length
    case __MCS::DENDRITIC_LENGTH:
      return __NMS::DENDRITIC_LENGTH;
    case __MCS::AXON_LENGTH:
      return __NMS::AXON_LENGTH;
    case __MCS::NEURITIC_LENGTH:
      return __NMS::NEURITIC_LENGTH;

      // Bifurcations
      case __MCS::DENDRITIC_BIFURCATIONS:
        return __NMS::DENDRITIC_BIFURCATIONS;
      case __MCS::AXON_BIFURCATIONS:
        return __NMS::AXON_BIFURCATIONS;
      case __MCS::NEURITIC_BIFURCATIONS:
        return __NMS::NEURITIC_BIFURCATIONS;

    case __NMS::NEURON_MORPHOLOGY_NUM_STATS:
    default:
      NSOL_THROW(
        "no know converstion from TMiniColumnStat to TNeuronMorphologyStat");
    }

  return NeuronMorphologyStats::/*TNeuronMorphologyStat::*/SURFACE;
  }



  MiniColumnStats::MiniColumnStats( const ColumnPtr column_,
                                    const unsigned short id_ )
    : MiniColumn( column_, id_ )
  {
  }

  MiniColumnStats * MiniColumnStats::stats( void )
  {
    return this;
  }

  float MiniColumnStats::getStat( TMiniColumnStat stat,
                                  TAggregation agg ) const
  {

    NeuronMorphologyStats::TNeuronMorphologyStat nStat =
      toNeuronMorphologyStat( stat );

    float value = 0;
    float mean;

    if ( agg == /*TAggregation::*/STD_DEV )
      return sqrt( this->getStat( stat, /*TAggregation::*/VARIANCE ));

    if ( agg == /*TAggregation::*/MIN )
      value = std::numeric_limits< float >::max( );

    if ( agg == /*TAggregation::*/MAX )
      value = std::numeric_limits< float >::min( );

    if ( agg == /*TAggregation::*/VARIANCE )
      mean = this->getStat( stat, /*TAggregation::*/MEAN );

    if ( agg == /*TAggregation::*/MEAN )
      return ( _neurons.size( ) == 0 ? 0.0f :
               this->getStat( stat, /*TAggregation::*/TOTAL ) /
               float( _neurons.size( )));

    NSOL_CONST_FOREACH( neuron, _neurons )
    {
      NeuronMorphologyPtr morphology = ( * neuron )->morphology( );
      NSOL_DEBUG_CHECK( morphology, "neuron without morphology" );
      NSOL_DEBUG_CHECK( morphology->stats( ),
                        "neuron without morphology stats" );

      float tmpValue = morphology->stats( )->getStat( nStat );

    if ( agg == /*TAggregation::*/VARIANCE )
      value += ( mean - tmpValue ) * ( mean - tmpValue );

    else if ( agg == /*TAggregation::*/MIN )
      value = std::min( value, tmpValue );
    else if ( agg == /*TAggregation::*/MAX )
      value = std::max( value, tmpValue );
    else
      value += tmpValue;
  }
  switch ( agg )
  {
  case /*TAggregation::*/TOTAL:
  case /*TAggregation::*/MIN:
  case /*TAggregation::*/MAX:
    return value;
  case /*TAggregation::*/VARIANCE:
    return ( _neurons.size( ) == 0 ? 0.0f :
             value / float( _neurons.size( )));
  case /*TAggregation::*/MEAN:
  case /*TAggregation::*/STD_DEV:
    break;
  }
  NSOL_THROW( "aggregation op not valid" )
  return 0;

  }


  //
  // Volume related methods
  //

//    std::cout << this << "," << morphology << "," <<  morphology->stats( )->__STAT_METHOD__( ) << std::endl;

#define RETURN_ACCUMULATED_FOR_ALL_NEURONS(                              \
  __TYPE__, __STAT_METHOD__, __AGGREG__ )                               \
  __TYPE__ value = 0;                                                   \
                                                                        \
  if ( __AGGREG__ == /*TAggregation::*/MIN )                                \
    value = std::numeric_limits< float >::max( );                       \
  if ( __AGGREG__ == /*TAggregation::*/MAX )                                \
    value = std::numeric_limits< float >::min( );                       \
                                                                        \
  __TYPE__ mean;                                                        \
                                                                        \
  if ( __AGGREG__ == /*TAggregation::*/STD_DEV )                            \
    return sqrt( this->__STAT_METHOD__( /*TAggregation::*/VARIANCE ));      \
                                                                        \
  if ( __AGGREG__ == /*TAggregation::*/VARIANCE )                           \
    mean = this->__STAT_METHOD__( /*TAggregation::*/MEAN );                 \
  NSOL_CONST_FOREACH( neuron, _neurons )                                \
  {                                                                     \
  NeuronMorphologyPtr morphology = ( * neuron )->morphology( );         \
  NSOL_DEBUG_CHECK( morphology, "neuron without morphology" );          \
  NSOL_DEBUG_CHECK( morphology->stats( ),                               \
                    "neuron without morphology stats" );                \
                                                                        \
  if ( __AGGREG__ == /*TAggregation::*/VARIANCE )                           \
  {                                                                     \
    __TYPE__ tmpValue = morphology->stats( )->__STAT_METHOD__( );       \
    value += ( mean - tmpValue ) * ( mean - tmpValue );                 \
  }                                                                     \
  else if ( __AGGREG__ == /*TAggregation::*/MIN )                           \
    value = std::min( value, morphology->stats( )->__STAT_METHOD__( )); \
  else if ( __AGGREG__ == /*TAggregation::*/MAX )                           \
    value = std::max( value, morphology->stats( )->__STAT_METHOD__( )); \
  else                                                                  \
    value += morphology->stats( )->__STAT_METHOD__( );                  \
  }                                                                     \
  switch ( __AGGREG__ )                                                 \
  {                                                                     \
  case /*TAggregation::*/TOTAL:                                             \
  case /*TAggregation::*/MIN:                                               \
  case /*TAggregation::*/MAX:                                               \
    return value;                                                       \
  case /*TAggregation::*/MEAN:                                              \
    return ( __TYPE__ )( float( value ) / float( _neurons.size( )));    \
  case /*TAggregation::*/VARIANCE:                                          \
    return ( __TYPE__ )( float( value ) / float( _neurons.size( )));    \
  case /*TAggregation::*/STD_DEV:                                           \
    break;                                                              \
  }                                                                     \
  NSOL_THROW( "aggregation op not valid" )                              \
  return 0;


  // float MiniColumnStats::dendriticVolume( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, dendriticVolume, op );
  // }


  // float MiniColumnStats::axonVolume( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, axonVolume, op );
  // }

  // float MiniColumnStats::neuriticVolume( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, neuriticVolume, op );
  // }

  // float MiniColumnStats::somaVolume( TAggregation  ) const
  // {
  //   return 0.0f; //!TODO: compute soma surface
  // }

  // float MiniColumnStats::volume( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, volume, op );
  // }

  // //
  // // Surface related methods
  // //

  // float MiniColumnStats::dendriticSurface( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, dendriticSurface, op );
  // }

  // float MiniColumnStats::axonSurface( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, axonSurface, op );
  // }

  // float MiniColumnStats::neuriticSurface( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, neuriticSurface, op );
  // }

  // float MiniColumnStats::somaSurface( TAggregation ) const
  // {
  //   return 0.0f; //!TODO: compute soma surface
  // }

  // float MiniColumnStats::surface( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, surface, op );
  // }

  // //
  // // Length related methods
  // //

  // float MiniColumnStats::dendriticLength( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, dendriticLength, op );
  // }

  // float MiniColumnStats::axonLength( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, axonLength, op );
  // }

  // float MiniColumnStats::neuriticLength( TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( float, neuriticLength, op );
  // }

  // //
  // // Bifuractions methods
  // //
  // unsigned int MiniColumnStats::dendriticBifurcations(
  //   TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( unsigned int,
  //                                       dendriticBifurcations, op );
  // }

  // unsigned int MiniColumnStats::axonBifurcations(
  //   TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( unsigned int,
  //                                       axonBifurcations, op );
  // }

  // unsigned int MiniColumnStats::neuriticBifurcations(
  //   TAggregation op ) const
  // {
  //   RETURN_ACCUMULATED_FOR_ALL_NEURONS( unsigned int,
  //                                       neuriticBifurcations, op );
  // }



} // namespace nsol

// EOF
