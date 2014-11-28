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

namespace nsol
{

  NeuronMorphologyStats * NeuronMorphologyStats::stats( void )
  {
    return this;
  }

  //
  // Volume related methods
  //

  float NeuronMorphologyStats::dendriticVolume( void ) const
  {
    float accumVolume = 0.0f;

    NSOL_CONST_FOREACH( neurite, _neurites )
    {
      if ( ( * neurite )->neuriteType( ) == Neurite::DENDRITE )
      {
        NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Dendrite, * neurite ),
                          "dendrite type not consistent" );
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "dendrite does not have stats" );
//        accumVolume += ( * neurite )->stats( )->volume( );
        accumVolume += ( * neurite )->stats( )->getStat(
          NeuriteStats::TNeuriteStat::VOLUME );
      }
    }
    return accumVolume;
  }

  float NeuronMorphologyStats::axonVolume( void ) const
  {
    float accumVolume = 0.0f;

    NSOL_CONST_FOREACH( neurite, _neurites )
    {
      if ( ( * neurite )->neuriteType( ) == Neurite::AXON )
      {
        NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Axon, * neurite ),
                          "axon type not consistent" );
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "axon does not have stats" );
        accumVolume += ( * neurite )->stats( )->getStat(
          NeuriteStats::TNeuriteStat::VOLUME );
      }
    }
    return accumVolume;
  }

  float NeuronMorphologyStats::neuriticVolume( void ) const
  {
    return this->dendriticVolume( ) + this->axonVolume( );
  }

  float NeuronMorphologyStats::somaVolume( void ) const
  {
    return 0.0f; //!TODO: compute soma volume
  }

  float NeuronMorphologyStats::volume( void ) const
  {
    return this->neuriticVolume( ) + this->somaVolume( );
  }

  //
  // Surface related methods
  //

  float NeuronMorphologyStats::dendriticSurface( void ) const
  {
    float accumSurface = 0.0f;

    NSOL_CONST_FOREACH( neurite, _neurites )
    {
      if ( ( * neurite )->neuriteType( ) == Neurite::DENDRITE )
      {
        NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Dendrite, * neurite ),
                          "dendrite type not consistent" );
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "dendrite does not have stats" );
        accumSurface += ( * neurite )->stats( )->getStat(
          NeuriteStats::TNeuriteStat::SURFACE );
      }
    }
    return accumSurface;
  }

  float NeuronMorphologyStats::axonSurface( void ) const
  {
    float accumSurface = 0.0f;

    NSOL_CONST_FOREACH( neurite, _neurites )
    {
      if ( ( * neurite )->neuriteType( ) == Neurite::AXON )
      {
        NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Axon, * neurite ),
                          "axon type not consistent" );
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "axon does not have stats" );
        accumSurface += ( * neurite )->stats( )->getStat(
          NeuriteStats::TNeuriteStat::SURFACE );
      }
    }
    return accumSurface;
  }

  float NeuronMorphologyStats::neuriticSurface( void ) const
  {
    return this->dendriticSurface( ) + this->axonSurface( );
  }

  float NeuronMorphologyStats::somaSurface( void ) const
  {
    return 0.0f; //!TODO: compute soma surface
  }

  float NeuronMorphologyStats::surface( void ) const
  {
    return this->neuriticSurface( ) + this->somaSurface( );
  }

  //
  // Length related methods
  //

  float NeuronMorphologyStats::dendriticLength( void ) const
  {
    float accumLength = 0.0f;

    NSOL_CONST_FOREACH( neurite, _neurites )
    {
      if ( ( * neurite )->neuriteType( ) == Neurite::DENDRITE )
      {
        NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Dendrite, * neurite ),
                          "dendrite type not consistent" );
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "dendrite does not have stats" );
        accumLength += ( * neurite )->stats( )->getStat(
          NeuriteStats::TNeuriteStat::LENGTH );
      }
    }
    return accumLength;
  }

  float NeuronMorphologyStats::axonLength( void ) const
  {
    float accumLength = 0.0f;

    NSOL_CONST_FOREACH( neurite, _neurites )
    {
      if ( ( * neurite )->neuriteType( ) == Neurite::AXON )
      {
        NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Axon, * neurite ),
                          "axon type not consistent" );
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "axon does not have stats" );
        accumLength += ( * neurite )->stats( )->getStat(
          NeuriteStats::TNeuriteStat::LENGTH );
      }
    }
    return accumLength;
  }

  float NeuronMorphologyStats::neuriticLength( void ) const
  {
    return this->dendriticLength( ) + this->axonLength( );
  }

  //
  // Bifuractions methods
  //
  unsigned int NeuronMorphologyStats::dendriticBifurcations( void ) const
  {
    unsigned int accumBifurcations = 0;

    NSOL_CONST_FOREACH( neurite, _neurites )
    {
      if ( ( * neurite )->neuriteType( ) == Neurite::DENDRITE )
      {
        NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Dendrite, * neurite ),
                          "dendrite type not consistent" );
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "dendrite does not have stats" );
        accumBifurcations += ( * neurite )->stats( )->getStat(
          NeuriteStats::TNeuriteStat::BIFURCATIONS );

      }
    }
    return accumBifurcations;

  }

  unsigned int NeuronMorphologyStats::axonBifurcations( void ) const
  {
    unsigned int accumBifurcations = 0;

    NSOL_CONST_FOREACH( neurite, _neurites )
    {
      if ( ( * neurite )->neuriteType( ) == Neurite::AXON )
      {
        NSOL_DEBUG_CHECK( NSOL_DYNAMIC_CAST( Axon, * neurite ),
                          "axon type not consistent" );
        NSOL_DEBUG_CHECK( ( * neurite )->stats( ),
                          "axon does not have stats" );
        accumBifurcations += ( * neurite )->stats( )->getStat(
          NeuriteStats::TNeuriteStat::BIFURCATIONS );
      }
    }
    return accumBifurcations;
  }

  unsigned int NeuronMorphologyStats::neuriticBifurcations( void ) const
  {
    return this->dendriticBifurcations( ) + this->axonBifurcations( );
  }



} // namespace nsol

// EOF
