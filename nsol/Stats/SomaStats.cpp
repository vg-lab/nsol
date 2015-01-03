/**
 * @file    SomaStats.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "SomaStats.h"
#include "../error.h"

namespace nsol
{

  SomaStats::SomaStats( )
    : Soma( )
  {
  }

  SomaStats::~SomaStats( )
  {
  }


  const SomaStats * SomaStats::stats( void ) const
  {
    return this;
  }

  float SomaStats::getStat( TSomaStat stat ) const
  {

    switch ( stat )
    {
    case SURFACE:
      return float( M_4PI * _maxRadius * _maxRadius );
      break;
    case VOLUME:
      return float( M_4PI_3 * _maxRadius * _maxRadius * _maxRadius );
      break;
    case SOMA_NUM_STATS:
    default:
      NSOL_THROW( "stat for soma not valid" );
    }

    return 0.0f;
  }

} // namespace nsol
