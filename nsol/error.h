/**
 * @file    error.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_ERROR__
#define __NSOL_ERROR__

#include <stdexcept>

#ifdef DEBUG
  #define NSOL_LOG( msg )                                        \
    std::cerr << "nsol "                                         \
              << __FILE__ << "("                                 \
              << __LINE__ << "): "                               \
              << msg << std::endl;
#else
  #define NSOL_LOG( msg )
#endif


#define NSOL_THROW( msg )                                        \
  {                                                              \
    NSOL_LOG( msg );                                             \
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
