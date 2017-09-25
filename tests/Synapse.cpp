/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
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

using namespace nsol;

BOOST_AUTO_TEST_CASE( synapse_constructors )
{
  {
    Synapse synapse;
    BOOST_CHECK_EQUAL( synapse.weight( ), 0.0f );
    BOOST_CHECK_EQUAL( synapse.preSynapticNeuron( ), 0 );
    BOOST_CHECK_EQUAL( synapse.postSynapticNeuron( ), 0 );
  }
  {
    Synapse synapse1;
    synapse1.weight( 1.0f );
    synapse1.preSynapticNeuron( 1 );
    synapse1.postSynapticNeuron( 2 );

    Synapse synapse2( synapse1 );
    BOOST_CHECK_EQUAL( synapse2.weight( ), 1.0f );
    BOOST_CHECK_EQUAL( synapse2.preSynapticNeuron( ), 1 );
    BOOST_CHECK_EQUAL( synapse2.postSynapticNeuron( ), 2 );
  }
}

BOOST_AUTO_TEST_CASE( synapse_operators )
{
  {
    Synapse synapse;
    synapse.weight( 2.f );
    synapse.preSynapticNeuron( 1 );
    synapse.postSynapticNeuron( 2 );

    Synapse synapse1 = synapse;
    BOOST_CHECK_EQUAL( synapse1.weight( ), 2.f );
    BOOST_CHECK_EQUAL( synapse1.preSynapticNeuron( ), 1 );
    BOOST_CHECK_EQUAL( synapse1.postSynapticNeuron( ), 2 );
  }
}
