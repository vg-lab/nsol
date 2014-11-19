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

  class NSOL_API SectionStats
  {

  public:

    static float surface( SectionPtr section_, bool tryCached = false );
    // static float cachedSurface( SectionPtr cachedSection_ );
    // static float cachedSurface( CachedSectionPtr cachedSection_ );

    static float volume( SectionPtr section_ );

    static float length( SectionPtr section_ );

    static float meanRadius( SectionPtr section_ );

  }; // class SectionStats


} // namespace nsol

#endif // __NSOL_SECTION_STATS__
