/**
 * @file    Node.cpp
 * @brief   Test for class nsol::Node
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
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
