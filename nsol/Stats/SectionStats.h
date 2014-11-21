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

  class SectionStats : public Section
  {

  public:

    NSOL_API
    SectionStats * stats( void )
    {
      return this;
    }

    NSOL_API
    virtual float volume( void ) const;

    NSOL_API
    virtual float surface( void ) const;

    NSOL_API
    virtual float length( void ) const;


  }; // class SectionStats


} // namespace nsol

#endif // __NSOL_SECTION_STATS__
