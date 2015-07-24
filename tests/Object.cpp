/*
 * @brief   Test for class nsol::Object
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

#define CHECK_AS( OBJ, C, MC, N, NM, SEC, SEG, NOD )    \
  BOOST_CHECK( OBJ->properties( ) ==  nullptr );        \
  BOOST_CHECK( OBJ->asColumn( ) ==  C );                \
  BOOST_CHECK( OBJ->asMiniColumn( ) ==  MC );           \
  BOOST_CHECK( OBJ->asNeuron( ) ==  N );                \
  BOOST_CHECK( OBJ->asNeuronMorphology( ) ==  NM );     \
  BOOST_CHECK( OBJ->asSection( ) ==  SEC );             \
  BOOST_CHECK( OBJ->asSegment( ) ==  SEG );             \
  BOOST_CHECK( OBJ->asNode( ) ==  NOD );                \

BOOST_AUTO_TEST_CASE( test_object )
{
  nsol::ObjectPtr obj = new nsol::Object;
  CHECK_AS( obj, 0, 0, 0, 0, 0, 0, 0 );
  delete obj;

  obj = new nsol::Column;
  CHECK_AS( obj, obj, 0, 0, 0, 0, 0, 0 );
  delete obj;

  obj = new nsol::MiniColumn;
  CHECK_AS( obj, 0, obj, 0, 0, 0, 0, 0 );
  delete obj;

  obj = new nsol::Neuron;
  CHECK_AS( obj, 0, 0, obj, 0, 0, 0, 0 );
  delete obj;

  obj = new nsol::NeuronMorphology( new nsol::Soma );
  CHECK_AS( obj, 0, 0, 0, obj, 0, 0, 0 );
  delete obj;

  obj = new nsol::Section;
  CHECK_AS( obj, 0, 0, 0, 0, obj, 0, 0 );
  delete obj;

  obj = new nsol::Segment;
  CHECK_AS( obj, 0, 0, 0, 0, 0, obj, 0 );
  delete obj;

  obj = new nsol::Node;
  CHECK_AS( obj, 0, 0, 0, 0, 0, 0, obj );
  delete obj;


}
