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

using namespace nsol;

BOOST_AUTO_TEST_CASE( neuron_constructor )
{
  {
    Neuron neuron;
    BOOST_CHECK_EQUAL( neuron.hasMorphology(), false );
    BOOST_CHECK_EQUAL( neuron.layer( ), 0 );
    BOOST_CHECK_EQUAL( neuron.gid( ), 0 );
    BOOST_CHECK_EQUAL( neuron.transform(), Matrix4_4fIdentity );
    BOOST_CHECK_EQUAL( neuron.morphologicalType( ), Neuron::UNDEFINED );
    BOOST_CHECK_EQUAL( neuron.functionalType( ),
        Neuron::UNDEFINED_FUNCTIONAL_TYPE );
  }
  {
    Neuron neuron( nullptr, 1, 1, Matrix4_4fIdentity, nullptr,
        Neuron::PYRAMIDAL, Neuron::INHIBITORY );
    BOOST_CHECK_EQUAL( neuron.hasMorphology(), false );
    BOOST_CHECK_EQUAL( neuron.layer( ), 1 );
    BOOST_CHECK_EQUAL( neuron.gid( ), 1 );
    BOOST_CHECK_EQUAL( neuron.transform(), Matrix4_4fIdentity );
    BOOST_CHECK_EQUAL( neuron.morphologicalType( ), Neuron::PYRAMIDAL );
    BOOST_CHECK_EQUAL( neuron.functionalType( ),
        Neuron::INHIBITORY );
  }
}

BOOST_AUTO_TEST_CASE( neuron_type )
{
  {
    Neuron neuron( nullptr, 1, 1, Matrix4_4fIdentity, nullptr,
                   Neuron::PYRAMIDAL, Neuron::INHIBITORY );
    BOOST_CHECK_EQUAL( neuron.isPyramidal(), true );
    BOOST_CHECK_EQUAL( neuron.isInterneuron(), false );
    BOOST_CHECK_EQUAL( neuron.isExcitatory(), false );
    BOOST_CHECK_EQUAL( neuron.isInhibitory(), true );
  }
  {
    Neuron neuron( nullptr, 1, 1, Matrix4_4fIdentity, nullptr,
                   Neuron::INTERNEURON, Neuron::EXCITATORY );
    BOOST_CHECK_EQUAL( neuron.isPyramidal(), false );
    BOOST_CHECK_EQUAL( neuron.isInterneuron(), true );
    BOOST_CHECK_EQUAL( neuron.isExcitatory(), true );
    BOOST_CHECK_EQUAL( neuron.isInhibitory(), false );
  }
}
