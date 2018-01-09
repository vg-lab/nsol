/*
 * Copyright (c) 2017 GMRV/URJC.
 *
 * Authors: Juan Guerrero Martín <juan.guerrero@urjc.es>
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
#ifndef __NSOL_ESPINA_SKELETON_READER__
#define __NSOL_ESPINA_SKELETON_READER__

#include "../Log.h"

// std.
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <unordered_set>

// neurosegmentations.
#include <neurosegmentations/neurosegmentations.h>

namespace nsol
{

  struct VectorsReaderInput
  {
    std::vector< float > points = std::vector< float >( );
    std::vector< unsigned int > segments = std::vector< unsigned int >( );
  };

  struct Segment
  {
    Segment( unsigned int a_,
             unsigned int b_ )
    {
      if( b_ < a_ )
      {
        std::swap( a_, b_ );
      }
      this->a = a_;
      this->b = b_;
    }

    inline bool operator==( const Segment& other_ ) const
    {
      return std::tie( this->a, this->b ) ==
             std::tie( other_.a, other_.b );
    }

    unsigned int a;
    unsigned int b;
  };

} // namespace nsol

namespace std
{

  template <> struct hash< nsol::Segment >
  {
    std::size_t operator()( const nsol::Segment& segment ) const
    {
      size_t aHash = hash< unsigned int >( )( segment.a );
      size_t bHash = hash< unsigned int >( )( segment.b );
      return aHash ^ ( bHash << 1 );
    }
  };

  template <> struct hash< nsol::Segment* >
  {
    std::size_t operator()( const nsol::Segment* segment ) const
    {
      return hash< nsol::Segment >( )( *segment );
    }
  };

} // namespace std

namespace nsol
{

  struct SegmentPtrEqual
  {
    bool operator()( const Segment* lhs, const Segment* rhs ) const
    {
      return *lhs == *rhs;
    }
  };

  class EspINASkeletonReader
  {

  public:

    VectorsReaderInput* read( const std::string& fileName );

  }; // class EspINASkeletonReader

} // namespace nsol

#endif
