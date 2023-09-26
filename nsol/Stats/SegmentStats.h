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
#ifndef __NSOL_SEGMENT_STATS__
#define __NSOL_SEGMENT_STATS__

#include <nsol/api.h>
#include "../NsolTypes.h"
#include "../Node.h"

namespace nsol
{

  class SegmentStats
  {

  public:

    //! Stats that can be computed for a segment
    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      RADIUS,
      SEGMENT_NUM_STATS
    } TSegmentStat;


    NSOL_API
    SegmentStats * stats( void );

    NSOL_API
    static float getStat( TSegmentStat stat,
                          const NodePtr begin,
                          const NodePtr end);
  }; // class SegmentStats


} // namespace nsol

#endif // __NSOL_SEGMENT_STATS__
