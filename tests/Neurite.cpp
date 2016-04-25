/**
 * @file    Neurite.cpp
 * @brief   Test for class nsol::Neurite
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( neurite_constructor )
{

  Neurite neurite;

  BOOST_CHECK_EQUAL( neurite.neuriteType( ), 0 );
  BOOST_CHECK( !neurite.morphology( ));
  BOOST_CHECK( !neurite.firstSection( ));
  BOOST_CHECK_EQUAL( neurite.numBranches( ), 0 );
  BOOST_CHECK_EQUAL( neurite.numBifurcations( ), 0 );

}

BOOST_AUTO_TEST_CASE( neurite_clone )
{

  Section section;
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float radius = 1.0f;
  NodePtr node;
  for( unsigned int i = 0; i < 10; i++ )
  {
    node = new Node( Vec3f( x, y, z ), i+1, radius );
    section.addNode( node );
    x += 0.1f;
    y += 0.1f;
    z += 0.1f;
    radius += 0.1f;
  }
  node = new Node( Vec3f( x, y, z ), 0, radius );
  section.firstNode( node );
  Section section1 = *(section.clone( ));
  section1.parent( &section );

  Neurite neurite;
  section.neurite( &neurite );
  section1.neurite( &neurite );
  neurite.firstSection( &section );
  Neurite neurite1 = *( neurite.clone( ));

  Sections originalSecs = neurite.sections( );
  Sections cloneSecs = neurite1.sections( );
  for ( unsigned int i = 0; i < originalSecs.size( ); i++ )
  {
    Nodes originalNodes = originalSecs[i]->nodes( );
    Nodes cloneNodes = cloneSecs[i]->nodes( );
    for ( unsigned int j = 0; j < originalNodes.size( ); j++ )
    {
      BOOST_CHECK( originalNodes[j] != cloneNodes[j] );
      BOOST_CHECK( *originalNodes[j] == *cloneNodes[j] );
    }
  }

}

BOOST_AUTO_TEST_CASE( neurite_operators )
{

  Section section;
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float radius = 1.0f;
  NodePtr node;
  for( unsigned int i = 0; i < 10; i++ )
  {
    node = new Node( Vec3f( x, y, z ), i+1, radius );
    section.addNode( node );
    x += 0.1f;
    y += 0.1f;
    z += 0.1f;
    radius += 0.1f;
  }
  node = new Node( Vec3f( x, y, z ), 0, radius );
  section.firstNode( node );
  Section section1 = *(section.clone( ));
  section1.parent( &section );
  Section section2 = *(section.clone( ));

  Neurite neurite;
  section.neurite( &neurite );
  section1.neurite( &neurite );
  section2.neurite( &neurite );
  neurite.firstSection( &section );

  Neurite neurite1 = *( neurite.clone( ));

  section2.parent( &section1 );

  BOOST_CHECK( neurite == neurite );
  BOOST_CHECK( neurite1 == neurite1 );
  BOOST_CHECK( neurite != neurite1);
}
