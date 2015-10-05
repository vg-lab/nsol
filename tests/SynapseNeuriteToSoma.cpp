/**
 * @file    SynapseNeuriteToSoma.cpp
 * @brief   Test for class nsol::SynapseNeuriteToSoma
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 Do not distribute without further notice.
*/

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;


BOOST_AUTO_TEST_CASE( test_constructor_synapseNeuriteToSoma )
{
  // Create a synapse neurite to soma by default
  nsol::SynapseNeuriteToSomaPtr  snts(new nsol::SynapseNeuriteToSoma());

  // Check the type of the synapse
  BOOST_CHECK_EQUAL( snts->synapseType( ), Synapse::DENDROSOMATIC );

  // Create the type of the synapse axosomatic
  nsol::SynapseNeuriteToSomaPtr  sats(new nsol::SynapseNeuriteToSoma(Synapse::AXOSOMATIC));

  // Check the type of the synapse
  BOOST_CHECK_EQUAL( sats->synapseType( ), Synapse::AXOSOMATIC );

  // Add the presynaptic segment
  nsol::SegmentPtr presynaptic_segment(new nsol::Segment);

  sats->preSynapticSegment( presynaptic_segment );

  BOOST_CHECK_EQUAL( sats->preSynapticSegment( ), presynaptic_segment );

  // Free dymanic memory used
  NSOL_DELETE_PTR( snts );
  NSOL_DELETE_PTR( sats );

}

BOOST_AUTO_TEST_CASE( test_synapseNeuriteToSoma_operators)
{
  // Create a neuritetosoma synapse
  nsol::SynapseNeuriteToSomaPtr  s(new nsol::SynapseNeuriteToSoma());

  //Compare empty neuritetosoma synapses
  nsol::SynapseNeuriteToSomaPtr s2( new nsol::SynapseNeuriteToSoma( ));
  BOOST_CHECK_EQUAL( *s == *s2, true );
  BOOST_CHECK_EQUAL( *s != *s2, false );

  // Change the type and compare
  s2->synapseType( Synapse::AXOSOMATIC );
  BOOST_CHECK_EQUAL( *s == *s2, false );
  BOOST_CHECK_EQUAL( *s != *s2, true );

  // Assignment operator
  SynapseNeuriteToSoma s3 = *s2;
  BOOST_CHECK_EQUAL( s3 == *s2, true );
  BOOST_CHECK_EQUAL( s3 != *s2, false );

  // Add presynaptic segment and test if equal
  *s2 = *s;
  BOOST_CHECK_EQUAL( *s == *s2, true );
  BOOST_CHECK_EQUAL( *s != *s2, false );

  s->preSynapticSegment(SegmentPtr( new nsol::Segment( )));

  BOOST_CHECK_EQUAL( *s == *s2, false );
  BOOST_CHECK_EQUAL( *s != *s2, true );

  // Test assigment op with presynaptic segment
  *s2 = *s;
  BOOST_CHECK_EQUAL( *s == *s2, true );
  BOOST_CHECK_EQUAL( *s != *s2, false );

  // Test copy constructor
  nsol::SynapseNeuriteToSoma s4( s3 );
  BOOST_CHECK_EQUAL( *s == s4, false );
  BOOST_CHECK_EQUAL( *s != s4, true );

  nsol::SynapseNeuriteToSoma s5( *s );
  BOOST_CHECK_EQUAL( *s == s5, true );
  BOOST_CHECK_EQUAL( *s != s5, false );

  // Free dymanic memory used
  NSOL_DELETE_PTR( s );
  NSOL_DELETE_PTR( s2 );
}
