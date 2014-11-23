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

  float NeuriteStats::volume( void ) const
  {
    float accumVolume = 0.0f;

    if ( _firstSection )
    {
      std::stack< SectionPtr > sectionsToProcess;
      sectionsToProcess.push(_firstSection);

      while ( ! sectionsToProcess.empty( ))
      {
        SectionPtr section = sectionsToProcess.top( );
        sectionsToProcess.pop( );

        NSOL_DEBUG_CHECK( section->stats( ), "section doesn't have stats" );
        accumVolume += section->stats( )->volume( );

        if ( section->childs( ).size( ) > 0 )
          for ( auto childrenIt = section->childs( ).begin( );
                childrenIt != section->childs( ).end( ); childrenIt++ )
            sectionsToProcess.push( * childrenIt );
      }
    }
    return accumVolume;
  }


  float NeuriteStats::surface( void ) const
  {
    float accumSurface = 0.0f;

    std::cout << "neurite stats surface" 
              << firstSection() << std::endl;

    if ( _firstSection )
    {
      std::stack< SectionPtr > sectionsToProcess;
      sectionsToProcess.push(_firstSection);

      while ( ! sectionsToProcess.empty( ))
      {
        SectionPtr section = sectionsToProcess.top( );
        sectionsToProcess.pop( );

        NSOL_DEBUG_CHECK( section->stats( ), "section doesn't have stats" );
        accumSurface += section->stats( )->surface( );

        if ( section->childs( ).size( ) > 0 )
          for ( auto childrenIt = section->childs( ).begin( );
                childrenIt != section->childs( ).end( ); childrenIt++ )
            sectionsToProcess.push( * childrenIt );
      }
    }
    return accumSurface;
  }


  float NeuriteStats::length( void ) const
  {
    float accumLength = 0.0f;

    if ( _firstSection )
    {
      std::stack< SectionPtr > sectionsToProcess;
      sectionsToProcess.push(_firstSection);

      while ( ! sectionsToProcess.empty( ))
      {
        SectionPtr section = sectionsToProcess.top( );
        sectionsToProcess.pop( );

        NSOL_DEBUG_CHECK( section->stats( ), "section doesn't have stats" );
        accumLength += section->stats( )->length( );

        if ( section->childs( ).size( ) > 0 )
          for ( auto childrenIt = section->childs( ).begin( );
                childrenIt != section->childs( ).end( ); childrenIt++ )
            sectionsToProcess.push( * childrenIt );
      }
    }
    return accumLength;
  }


} // namespace nsol
