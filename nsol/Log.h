#ifndef __NSOL_LOG__
#define __NSOL_LOG__

#include <iostream>

namespace nsol
{
  typedef enum
  {
    NSOL_LOG_ERROR,
    NSOL_LOG_WARNING,
    NSOL_LOG_VERBOSE
  } TLogLevel;

#define NSOL_LOG_HEADER                                           \
  std::string( "nsol: " +                                         \
               std::string( __FILE__ ) + std::string( "(" ) +     \
               std::to_string( __LINE__ ) +                       \
               std::string( "): " ))


  class Log
  {
  public:

    static void log( const std::string& msg,
                     TLogLevel level = NSOL_LOG_VERBOSE,
                     std::ostream& stream = std::cerr );
  };
}

#endif
