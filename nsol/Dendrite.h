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
#ifndef __NSOL_DENDRITE__
#define __NSOL_DENDRITE__

#include <nsol/api.h>
#include "Neurite.h"

namespace nsol
{

  class Dendrite : public virtual Neurite
  {

  public:

    //! Type of dendrite
    typedef enum TDendriteType
    {
      BASAL = 0,
      APICAL
    } TDendriteType;

    friend std::ostream & operator<< ( std::ostream & os,
                                       const TDendriteType & rhs)
    {
      switch ( rhs )
      {
      case BASAL:
        return os << "BASAL";
        break;
      case APICAL:
        return os << "APICAL";
        break;
      default:
        return os << "UNDEFINED";
      }
      return os;
    }

    NSOL_API
    Dendrite ( TDendriteType dendriteType = BASAL );

    //! Get the type of neurite
    NSOL_API
    TDendriteType & dendriteType( void );

    NSOL_API
    virtual NeuritePtr clone( void ) const final;

  protected:

    //! Type of dendrite
    TDendriteType _dendriteType;

  }; // class Dendrite


} // namespace nsol


#endif

// EOF
