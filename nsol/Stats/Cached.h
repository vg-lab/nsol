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
#ifndef __NSOL_STATS_CACHED__
#define __NSOL_STATS_CACHED__

#include "../error.h"

#include <map>

namespace nsol
{
  /*! \class Cached
    \brief This class allows to cache values


  */
  template < typename TYPE = float > class Cached
  {

  public:

    Cached( void )
    {
    }

    virtual ~Cached( void )
    {
    }

    bool dirty( unsigned int id_ ) const
    {
      return ( _values.find( id_ ) == _values.end( ));
    }

    void setDirty( unsigned int id_ )
    {
      _values.erase( id_ );
    }

    void setDirty( void )
    {
      _values.clear( );
    }

    virtual void setAndPropagateDirty( unsigned int id_ )
    {
      this->setDirty( id_ );
      // Note: propagation has to be reimplemented if needed
    }

    virtual void setAndPropagateDirty( void )
    {
      this->setDirty( );
      // Note: propagation has to be reimplemented if needed
    }

    // This method is const to be able to cache values from
    // derived const methods
    void cacheValue( const unsigned int id_, TYPE value_ ) const
    {
      _values[ id_ ] = value_;
    }

    TYPE getValue( const unsigned int id_ ) const
    {
      if ( ! dirty( id_ ))
        return _values[ id_ ];
      else
        return TYPE( 0 );
    }


  protected:

    //! Container of the cached values. Is mutable to allow const methods
    //! to modify the cache if needed.
    mutable std::map < unsigned int, TYPE > _values;

  };

} // namespace nsol

#endif // __NSOL_STATS_CACHED__
