/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Cristian Rodriguez <cristian.rodriguez@urjc.es>
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
#include <testData.h>

#include <sstream>

using namespace nsol;

BOOST_AUTO_TEST_CASE( swc_writer )
{
  SwcWriter sw;
  BOOST_CHECK( !sw.writeMorphology( "foo.txt", nullptr ) );

  NeuronMorphologyPtr neuronMorphology;

  SwcReader swcReader;
  neuronMorphology = swcReader.readMorphology( NSOL_EXAMPLE_NEURON_SWC );

  BOOST_CHECK( sw.writeMorphology( "foo.txt", neuronMorphology ) );
}
