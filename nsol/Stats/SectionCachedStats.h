/**
 * @file    SectionCachedStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SECTION_CACHED_STATS__
#define __NSOL_SECTION_CACHED_STATS__

#include <nsol/api.h>

#include "Cached.h"
#include "SectionStats.h"

namespace nsol
{


  /** \class SectionCachedStats
   *  \brief This class allows to cache the stats for sections
   *
   *  Using this class instead of Section or SectionStats when constructing
   *  the hierarchy allows to call the method stats from base Section
   *  class and get the corresponding volume, surface and length. If the cached
   *  value is dirty then the actual computation process is done. In case is
   *  clean the cached value is returned directly.
   *
   *  Example: @include examples/stats.cpp
   */
  class SectionCachedStats
    : public SectionStats
    , public Cached<>
  {


  public:

    //! Stats that can be cached for SectionStats
    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      LENGTH,
      SECTION_NUM_CACHED_VALUES
    } TSectionCachedValues;

    /**
     * Default constructor
     */
    NSOL_API
    SectionCachedStats( void );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~SectionCachedStats( void );

    /**
     * Set dirty a cached stat and propagates dirty to parent neurite
     * @param id identifier of the property to set dirty. It also propagates
     * dirty state to parent neurite. id value has to be one from
     * TSectionCachedValues (checked only on debug compiling).
     */
    NSOL_API
    virtual void setAndPropagateDirty( unsigned int id );

    /**
     * Set dirty all cached stats and propagates dirty to parent neurite
     */
    NSOL_API
    virtual void setAndPropagateDirty( void );

    /**
     * Adds a segment at the end of the section. This method does the same as
     * Section::addSegment but it also sets diry all stats of parent neurite.
     * @param segment pointer to the segment to add.
     *        Precondition: pointer is not null.
     * @return pointer to the segment added
     *         (for compatibility with older nsol versions)
     */
    NSOL_API
    virtual SegmentPtr addSegment( SegmentPtr segment = nullptr );

    NSOL_API
    virtual void firstSegment( SegmentPtr firstSegment_ );

    NSOL_API
    virtual void lastSegment( SegmentPtr lastSegment_ );

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


  }; // class SectionCachedStats

} // namespace nsol

#endif // __NSOL_SECTION_CACHED_STATS__
