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
