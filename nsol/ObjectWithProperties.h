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
#ifndef __NSOL_OBJECT_USE_PROPERTIES__
#define __NSOL_OBJECT_USE_PROPERTIES__

#include <nsol/api.h>
#include "Object.h"
#include "NsolTypes.h"

#ifdef NSOL_USE_FIRES
#include <fires/fires.h>
#endif

namespace nsol
{

  class ObjectWithProperties
    : public virtual Object
#ifdef NSOL_USE_FIRES
    , public fires::Object
#endif
  {
  public:

    NSOL_API
    ObjectWithProperties( void );

    NSOL_API
    virtual ~ObjectWithProperties( void );

    NSOL_API
    virtual ObjectWithPropertiesPtr properties( void );

    virtual ObjectPtr create( void )
    {
      return new ObjectWithProperties;
    }
  };


} // namespace nsol


#endif
