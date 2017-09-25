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

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

#define CHECK_AS( OBJ, C, MC, N, NM, SEC, NOD )    \
  BOOST_CHECK( OBJ->properties( ) ==  nullptr );        \
  BOOST_CHECK( OBJ->asColumn( ) ==  C );                \
  BOOST_CHECK( OBJ->asMiniColumn( ) ==  MC );           \
  BOOST_CHECK( OBJ->asNeuron( ) ==  N );                \
  BOOST_CHECK( OBJ->asNeuronMorphology( ) ==  NM );     \
  BOOST_CHECK( OBJ->asSection( ) ==  SEC );             \
  BOOST_CHECK( OBJ->asNode( ) ==  NOD );                \

BOOST_AUTO_TEST_CASE( test_object )
{
  nsol::ObjectPtr obj = new nsol::Object;
  CHECK_AS( obj, 0, 0, 0, 0, 0, 0 );
  delete obj;

  obj = new nsol::Column;
  CHECK_AS( obj, obj, 0, 0, 0, 0, 0 );
  delete obj;

  obj = new nsol::MiniColumn;
  CHECK_AS( obj, 0, obj, 0, 0, 0, 0 );
  delete obj;

  obj = new nsol::Neuron;
  CHECK_AS( obj, 0, 0, obj, 0, 0, 0 );
  delete obj;

  obj = new nsol::NeuronMorphology( new nsol::Soma );
  CHECK_AS( obj, 0, 0, 0, obj, 0, 0 );
  delete obj;

  obj = new nsol::Section;
  CHECK_AS( obj, 0, 0, 0, 0, obj, 0 );
  delete obj;

  obj = new nsol::Node;
  CHECK_AS( obj, 0, 0, 0, 0, 0, obj );
  delete obj;


}
