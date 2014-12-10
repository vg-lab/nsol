/**
 * @file    Cached.cpp
 * @brief   Test for class nsol::Cached
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */


#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( cached )
{

  typedef enum
  {
    TEST_CACHED_PROPERTY1 = 0,
    TEST_CACHED_PROPERTY2,
    TEST_CACHED_PROPERTY3
  } TCachedValues;

  Cached< > c;

  // Test all cached values are dirty
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), true );

  // Cache a value for TEST_CACHED_PROPERTY1
  c.cacheValue( TEST_CACHED_PROPERTY1, 3.4f );

  // Check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), true );

  // Check values
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY1 ), 3.4f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY2 ), 0.0f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY3 ), 0.0f );

  // Re-check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), true );

  // Cache a value for TEST_CACHED_PROPERTY2
  c.cacheValue( TEST_CACHED_PROPERTY2, 5.6f );

  // Check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), true );

  // Check values
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY1 ), 3.4f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY2 ), 5.6f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY3 ), 0.0f );

  // Re-check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), true );

  // Set one property to dirty state
  c.setDirty( TEST_CACHED_PROPERTY1 );

  // Check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), true );

  // Check values
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY1 ), 0.0f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY2 ), 5.6f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY3 ), 0.0f );

  // Cache value for property 3
  c.cacheValue( TEST_CACHED_PROPERTY3, 1.2f );

  // Check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), false );

  // Check values
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY1 ), 0.0f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY2 ), 5.6f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY3 ), 1.2f );

  // Re-check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), false );

  // Set all properties dirty
  c.setDirty( );

  // Check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), true );

  // Check values
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY1 ), 0.0f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY2 ), 0.0f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY3 ), 0.0f );

  // Test out of bounds properties
  BOOST_CHECK_EQUAL( c.dirty( 100 ), true );

  // Now lets dirty a property "out of bounds"
  c.cacheValue( TEST_CACHED_PROPERTY1, 2.2f );
  c.cacheValue( TEST_CACHED_PROPERTY3, 1.2f );
  c.setDirty( 100 );

  // Check dirtyness of the three cached properties
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY1 ), false );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY2 ), true );
  BOOST_CHECK_EQUAL( c.dirty( TEST_CACHED_PROPERTY3 ), false );

  // Check values
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY1 ), 2.2f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY2 ), 0.0f );
  BOOST_CHECK_EQUAL( c.getValue( TEST_CACHED_PROPERTY3 ), 1.2f );


}

// EOF