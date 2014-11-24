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

namespace nsol
{

  /** \class SectionStats
   *  \brief This class allows to compute stats for sections
   *
   *  Using this class instead of Section when constructing the
   *  hierarchy allows to call the method stats from base Section
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/stats.cpp
   */
  class SectionStats : public Section
  {

  public:

    /**
     * Returns object as SectionStats
     * @return pointer to SectionStats object
     */
    NSOL_API
    SectionStats * stats( void )
    {
      return this;
    }

    /**
     * Computes volume of the section
     * @return volume of section
     */
    NSOL_API
    virtual float volume( void ) const;

    /**
     * Computes surface of the section
     * @return surface of section
     */
    NSOL_API
    virtual float surface( void ) const;

    /**
     * Computes length of the section
     * @return length of section
     */
    NSOL_API
    virtual float length( void ) const;

  }; // class SectionStats

} // namespace nsol

#endif // __NSOL_SECTION_STATS__