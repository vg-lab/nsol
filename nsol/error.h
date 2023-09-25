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
/**
 * @file    error.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks  (c) VG-Lab/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_ERROR__
#define __NSOL_ERROR__


#include "Log.h"
#include <stdexcept>


#define NSOL_THROW( msg )                                        \
  {                                                              \
    nsol::Log::log( std::string( msg ), nsol::LOG_LEVEL_ERROR ); \
    throw std::runtime_error( msg );                             \
  }

#define NSOL_CHECK_THROW( cond, errorMsg )                       \
    {                                                            \
      if ( ! (cond) ) NSOL_THROW( errorMsg );                    \
    }

#ifdef DEBUG
  #define NSOL_DEBUG_CHECK( cond, errorMsg )                     \
{                                                                \
  NSOL_CHECK_THROW( cond, errorMsg )                             \
}
#else
  #define NSOL_DEBUG_CHECK( cond, errorMsg )
#endif


#endif // __NSOL_ERROR__
