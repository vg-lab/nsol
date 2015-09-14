/**
 * @file    SectionStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SECTION_STATS__
#define __NSOL_SECTION_STATS__


#include "../Section.h"
#include "SegmentStats.h"

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
    SegmentStats _segmentStats;


  }; // class SectionStats

} // namespace nsol

#endif // __NSOL_SECTION_STATS__
