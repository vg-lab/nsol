/**
 * @file    CachedSection.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_CACHED_SECTION__
#define __NSOL_CACHED_SECTION__

#include <nsol/api.h>

#include "Cached.h"
#include "../Section.h"

namespace nsol
{


  class CachedSection 
    : public Section
    , public Cached<>
  {
    
  public:

    typedef enum 
    { 
      SURFACE = 0,
      VOLUME,
      LENGTH,
      MEAN_RADIUS,
      SECTION_NUM_CACHED_VALUES
    } TSectionCachedValues;

    NSOL_API
    CachedSection( void ) 
      : Section( )
      , Cached( SECTION_NUM_CACHED_VALUES )
    {

    }

    NSOL_API
    virtual ~CachedSection( void )
    {
    }

    NSOL_API
    virtual void setAndPropagateDirty( void ) 
    {
      this->setDirty( );
      
      auto cached = dynamic_cast< Cached * >( this->parent( ));

      if ( cached )
	cached->setAndPropagateDirty( );
    }

    NSOL_API
    virtual SegmentPtr addSegment( SegmentPtr segment = nullptr )
    {
      this->setAndPropagateDirty( );      
      return this->Section::addSegment( segment );
    }

    NSOL_API
    virtual void firstSegment( SegmentPtr firstSegment_ )
    {
      return this->Section::firstSegment( firstSegment_ );
      this->setAndPropagateDirty( );      
    }

    NSOL_API
    virtual void lastSegment( SegmentPtr lastSegment_ )
    {
      return this->Section::lastSegment( lastSegment_ );
      this->setAndPropagateDirty( );      
    }


    
  };

} // namespace nsol

#endif // __NSOL_CACHED_SECTION__
