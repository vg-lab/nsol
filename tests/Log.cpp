/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Cristian Rodríguez <cristian.rodriguez@urjc.es>
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

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

#include <sstream>

using namespace nsol;

BOOST_AUTO_TEST_CASE( logger_levels )
{
	Log::setLogLevel( TLogLevel::LOG_LEVEL_ERROR );

	BOOST_CHECK_EQUAL( Log::logLevel( ), TLogLevel::LOG_LEVEL_ERROR );

	BOOST_CHECK_EQUAL( TLogLevel::LOG_LEVEL_ERROR, 
		Log::stringToLogLevel( "ERROR" ) );

	BOOST_CHECK_EQUAL( TLogLevel::LOG_LEVEL_WARNING, 
		Log::stringToLogLevel( "WARNING" ) );

	BOOST_CHECK_EQUAL( TLogLevel::LOG_LEVEL_VERBOSE, 
		Log::stringToLogLevel( "VERBOSE" ) );

	BOOST_CHECK_EQUAL( TLogLevel::LOG_LEVEL_UNKNOWN, 
		Log::stringToLogLevel( "" ) );
}

std::string toString( const std::ostream& str )
{
    std::ostringstream ss;
    ss << str.rdbuf();
    return ss.str();
}

BOOST_AUTO_TEST_CASE( logger_stream )
{
	#define LOG_FOO_MESSAGE "Hello from Nsol"
	std::ostringstream os;
	os.flush( );
	Log::setStream( os );

	Log::log( LOG_FOO_MESSAGE, TLogLevel::LOG_LEVEL_ERROR );
	std::string str = toString( Log::stream( ) );

	/*std::stringstream ss;
	ss.flush( );
	ss << LOG_FOO_MESSAGE << std::endl;

	std::string str2 = ss.str( );

	BOOST_CHECK_EQUAL( str, str2 );

	// TODO: BOOST_CHECK_EQUAL( str, std::string( LOG_FOO_MESSAGE ) );*/
}

// EOF