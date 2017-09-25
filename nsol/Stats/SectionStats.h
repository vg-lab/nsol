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
#ifndef __NSOL_SECTION_STATS__
#define __NSOL_SECTION_STATS__


#include "../Section.h"

namespace nsol
{

  /** \class SectionStats
   *  \brief This class allows to compute stats for sections
   *
   *  Using this class instead of Section when constructing the
   *  hierarchy allows to call the method stats from base Section
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/sectionStats.cpp
   */
  class SectionStats : public Section
  {

  public:

    //! Stats that can be computed for Section
    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      RADIUS,
      SECTION_NUM_STATS
    } TSectionStat;

    /**
     * Returns object as SectionStats
     * @return pointer to SectionStats object
     */
    NSOL_API
    SectionStats * stats( void )
    {
      return this;
    }

    NSOL_API
    virtual float getStat( TSectionStat stat,
                           TAggregation agg = /*TAggregation::*/TOTAL ) const;


  protected:

    //! Segment stats
    //SegmentStats _segmentStats;


  }; // class SectionStats

} // namespace nsol

#endif // __NSOL_SECTION_STATS__
