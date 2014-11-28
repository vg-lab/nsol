/**
 * @file    NeuriteStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
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
    case NeuriteStats::TNeuriteStat::SURFACE:
      return SectionStats::TSectionStat::SURFACE;
      break;

    case NeuriteStats::TNeuriteStat::VOLUME:
      return SectionStats::TSectionStat::VOLUME;
      break;

    case NeuriteStats::TNeuriteStat::LENGTH:
      return SectionStats::TSectionStat::LENGTH;
      break;

    // case NeuriteStats::TNeuriteStat::MEAN_RADIUS:
    //   return SectionStats::TSectionStat::MEAN_RADIUS;
    //   break;

    case NeuriteStats::TNeuriteStat::NEURITE_NUM_STATS:
    default:
      NSOL_THROW( "no know converstion from TNeuriteStat to TSectionStat");
    }

    return SectionStats::TSectionStat::SURFACE;
  }


  NeuriteStats::NeuriteStats( TNeuriteType neuriteType_ )
    : Neurite( neuriteType_ )
  {
  }


  float NeuriteStats::getStat( TNeuriteStat stat,
                               TAggregation agg ) const
  {
    NSOL_DEBUG_CHECK( stat < NEURITE_NUM_STATS, "section stat unknown");
    NSOL_DEBUG_CHECK( validAggregation( agg ), "unknown aggregation");

    NSOL_DEBUG_CHECK( ! ( stat == TNeuriteStat::BIFURCATIONS &&
                          agg != TAggregation::TOTAL ) ,
                      std::string("non compatible aggregation " ) +
                      std::to_string( int( agg )));

    float value = 0.0f;
    float mean;
    int numSections = 0;

    if ( agg == TAggregation::STD_DEV )
      return sqrt( this->getStat( stat, TAggregation::VARIANCE ));

    if ( agg == TAggregation::MIN )
      value = std::numeric_limits< float >::max( );

    if ( agg == TAggregation::MAX )
      value = std::numeric_limits< float >::min( );

    if ( agg == TAggregation::VARIANCE )
      mean = this->getStat( stat,  TAggregation::MEAN );

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

        if ( stat != TNeuriteStat::BIFURCATIONS )
        {

          if ( agg == TAggregation::VARIANCE )
          {
            float tmpValue =
              section->stats( )->getStat( toSectionStat( stat ));
            value += ( mean - tmpValue ) * ( mean - tmpValue );
          }
          else if ( agg == TAggregation::MIN )
            value =
              std::min( value,
                        section->stats( )->getStat( toSectionStat( stat )));
          else if ( agg == TAggregation::MAX )
            value =
              std::max( value,
                        section->stats( )->getStat( toSectionStat( stat )));
          else
            value += section->stats( )->getStat( toSectionStat( stat ));
        }

        if ( section->children( ).size( ) > 0 )
        {
          if ( stat == TNeuriteStat::BIFURCATIONS )
            value++;

          NSOL_CONST_FOREACH( child, section->children( ))
            sectionsToProcess.push( * child );
        }
        numSections++;
      } // while sections to process

      switch ( agg )
      {
      case TAggregation::TOTAL:
      case TAggregation::MIN:
      case TAggregation::MAX:
        return value;
      case TAggregation::MEAN:
      case TAggregation::VARIANCE:
        return value / numSections;
      case TAggregation::STD_DEV:
        break;
      }
      NSOL_THROW( "aggregation op not valid" )
    }
    return 0;

  }


//   float NeuriteStats::volume( void ) const
//   {
//     float accumVolume = 0.0f;

//     if ( _firstSection )
//     {
//       std::stack< SectionPtr > sectionsToProcess;
//       sectionsToProcess.push(_firstSection);

//       while ( ! sectionsToProcess.empty( ))
//       {
//         SectionPtr section = sectionsToProcess.top( );
//         sectionsToProcess.pop( );

//         NSOL_DEBUG_CHECK( section->stats( ),
//                           "section doesn't have stats" );

// //        accumVolume += section->stats( )->volume( );
//         accumVolume += section->stats( )->getStat(
//           SectionStats::TSectionStat::VOLUME );

//         if ( section->children( ).size( ) > 0 )
//           for ( auto childrenIt = section->children( ).begin( );
//                 childrenIt != section->children( ).end( ); childrenIt++ )
//             sectionsToProcess.push( * childrenIt );
//       }
//     }
//     return accumVolume;
//   }


//   float NeuriteStats::surface( void ) const
//   {
//     float accumSurface = 0.0f;

//     if ( _firstSection )
//     {
//       std::stack< SectionPtr > sectionsToProcess;
//       sectionsToProcess.push(_firstSection);

//       while ( ! sectionsToProcess.empty( ))
//       {
//         SectionPtr section = sectionsToProcess.top( );
//         sectionsToProcess.pop( );

//         NSOL_DEBUG_CHECK( section->stats( ), "section doesn't have stats" );
// //        accumSurface += section->stats( )->surface( );
//         accumSurface += section->stats( )->getStat(
//           SectionStats::TSectionStat::SURFACE );

//         if ( section->children( ).size( ) > 0 )
//           for ( auto childrenIt = section->children( ).begin( );
//                 childrenIt != section->children( ).end( ); childrenIt++ )
//             sectionsToProcess.push( * childrenIt );
//       }
//     }
//     return accumSurface;
//   }


//   float NeuriteStats::length( void ) const
//   {
//     float accumLength = 0.0f;

//     if ( _firstSection )
//     {
//       std::stack< SectionPtr > sectionsToProcess;
//       sectionsToProcess.push(_firstSection);

//       while ( ! sectionsToProcess.empty( ))
//       {
//         SectionPtr section = sectionsToProcess.top( );
//         sectionsToProcess.pop( );

//         NSOL_DEBUG_CHECK( section->stats( ),
//                           "section doesn't have stats" );

// //        accumLength += section->stats( )->length( );
//         accumLength += section->stats( )->getStat(
//           SectionStats::TSectionStat::LENGTH );



//         if ( section->children( ).size( ) > 0 )
//           for ( auto childrenIt = section->children( ).begin( );
//                 childrenIt != section->children( ).end( ); childrenIt++ )
//             sectionsToProcess.push( * childrenIt );
//       }
//     }
//     return accumLength;
//   }

//   NSOL_API
//   unsigned int NeuriteStats::bifurcations( void ) const
//   {

//     unsigned int accumBifurcations = 0;

//     if ( _firstSection )
//     {
//       std::stack< SectionPtr > sectionsToProcess;
//       sectionsToProcess.push(_firstSection);

//       while ( ! sectionsToProcess.empty( ))
//       {
//         SectionPtr section = sectionsToProcess.top( );
//         sectionsToProcess.pop( );

//         NSOL_DEBUG_CHECK( section->stats( ),
//                           "section doesn't have stats" );

//         if ( section->children( ).size( ) > 0 )
//         {
//           accumBifurcations++;
//           NSOL_CONST_FOREACH( child, section->children( ))
//             sectionsToProcess.push( * child );
//         }
//       }
//     }
//     return accumBifurcations;


//   }


} // namespace nsol
