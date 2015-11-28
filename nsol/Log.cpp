#include "Log.h"

#include <string>
#include <iostream>

namespace nsol
{

  std::string logLevelToString( TLogLevel level )
  {
    switch ( level )
    {
    case NSOL_LOG_WARNING:
      return std::string( "WARNING" );
    case NSOL_LOG_VERBOSE:
      return std::string( "VERBOSE" );
    case NSOL_LOG_ERROR:
    default:
      return std::string( "ERROR" );
    }
    return std::string( "" );
  }



  void Log::log( const std::string& msg,
                 TLogLevel level,
                 std::ostream& stream )
  {

#ifdef _DEBUG
    std::string logLevel( "NSOL_LOG_VERBOSE" );
#else
    std::string logLevel( "NSOL_LOG_ERROR" );
#endif

    char *envLogLevel = getenv ("NSOL_LOG_LEVEL");

    if ( envLogLevel )
      logLevel = std::string( envLogLevel );

    if ( logLevelToString( level ) < logLevel )
    {
      stream << std::boolalpha
             << msg << std::endl;
    }

  }

}
