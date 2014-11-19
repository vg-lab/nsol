/**
 * @file    Cached.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
            Do not distribute without further notice.
 */
#ifndef __NSOL_STATS_CACHED__
#define __NSOL_STATS_CACHED__

#include "../error.h"

#include <vector>

namespace nsol
{ 
  /*! \class Cached
    \brief This class allows to cache values
   

  */
  template < typename TYPE = float > class Cached
  {

  public:
    
    Cached( unsigned int numValues_ = 0 )
      : _dirty( true )
    {
      _values.reserve( numValues_ );
    }

    virtual ~Cached( void )
    {
    }

    bool & dirty( void )
    {
      return _dirty;
    }

    void setDirty( void )
    {
      _dirty = true;
    }

    void setClean( void )
    {
      _dirty = false;
    }

    virtual void setAndPropagateDirty( void ) 
    {
      NSOL_THROW( "setAndPropagateDirty not reimplemented" );
    }


    TYPE & value( unsigned int idx_ )
    {
      #ifdef DEBUG
      if ( idx_ >= _values.size( ))
	NSOL_THROW( std::string( "value index " ) + 
		    std::to_string( idx_) +  
		    std::string( "not valid" );		    
      #endif

      return _values[ idx_ ];

    }

  protected:

    //! Indicates if the values are updated
    bool _dirty;

    //! Container of the cached values
    std::vector < TYPE > _values;

  };

} // namespace nsol

#endif // __NSOL_STATS_CACHED__
