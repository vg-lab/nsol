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
#ifndef __NSOL_LOG__
#define __NSOL_LOG__

#include <nsol/api.h>
#include <iostream>

namespace nsol
{

  //! Log levels suported
  typedef enum
  {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_UNKNOWN
  } TLogLevel;

  /**
   * Static class to log output
   *
   */
  class Log
  {
  public:

    /**
     * Set current log level
     * @param logLevel level to be set
     */
    NSOL_API
    static void setLogLevel( const TLogLevel logLevel );

    /**
     * Get current log level
     * @return current log level
     */
    NSOL_API
    static TLogLevel logLevel( void );

    /**
     * Set current output stream
     * @param stream output stream to be set
     */
    NSOL_API
    static void setStream( std::ostream& stream );

    /**
     * Get current output stream
     * @return current output stream
     */
    NSOL_API
    static const std::ostream& stream( void );

    /**
     * Method to log out a message in a specific level
     * @param msg message to log
     * @param level level of the message
     */
    NSOL_API
    static void log( const std::string& msg,
                     const TLogLevel level = LOG_LEVEL_VERBOSE );

    /**
     * Method to log out a message in a specific level to a specific stream
     * @param msg message to log
     * @param level level of the message
     * @param stream stream where log will be written
     */
    NSOL_API
    static void log( const std::string& msg,
                     std::ostream& stream,
                     const TLogLevel level = LOG_LEVEL_VERBOSE );

    NSOL_API
    static TLogLevel stringToLogLevel( std::string logLevelString );
  protected:

    //! Current log level. This can be overwritten with proper value
    //! assigned to environment variable NSOL_LOG_LEVEL
    static TLogLevel _logLevel;

    //! Current stream to write log to
    static std::ostream* _stream;

  };
}

#endif
