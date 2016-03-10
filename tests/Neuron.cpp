/**
 * @file    Neuron.cpp
 * @brief   Test for class nsol::Neuron
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
    BOOST_CHECK_EQUAL( neuron.transform(), Matrix4_4f::IDENTITY );
    BOOST_CHECK_EQUAL( neuron.morphologicalType( ), Neuron::UNDEFINED );
    BOOST_CHECK_EQUAL( neuron.functionalType( ),
        Neuron::UNDEFINED_FUNCTIONAL_TYPE );
  }
  {
    Neuron neuron( nullptr, 1, 1, Matrix4_4f::IDENTITY, nullptr,
        Neuron::PYRAMIDAL, Neuron::INHIBITORY );
    BOOST_CHECK_EQUAL( neuron.hasMorphology(), false );
    BOOST_CHECK_EQUAL( neuron.layer( ), 1 );
    BOOST_CHECK_EQUAL( neuron.gid( ), 1 );
    BOOST_CHECK_EQUAL( neuron.transform(), Matrix4_4f::IDENTITY );
    BOOST_CHECK_EQUAL( neuron.morphologicalType( ), Neuron::PYRAMIDAL );
    BOOST_CHECK_EQUAL( neuron.functionalType( ),
        Neuron::INHIBITORY );
  }
}

BOOST_AUTO_TEST_CASE( neuron_type )
{
  {
    Neuron neuron( nullptr, 1, 1, Matrix4_4f::IDENTITY, nullptr,
                   Neuron::PYRAMIDAL, Neuron::INHIBITORY );
    BOOST_CHECK_EQUAL( neuron.isPyramidal(), true );
    BOOST_CHECK_EQUAL( neuron.isInterneuron(), false );
    BOOST_CHECK_EQUAL( neuron.isExcitatory(), false );
    BOOST_CHECK_EQUAL( neuron.isInhibitory(), true );
  }
  {
    Neuron neuron( nullptr, 1, 1, Matrix4_4f::IDENTITY, nullptr,
                   Neuron::INTERNEURON, Neuron::EXCITATORY );
    BOOST_CHECK_EQUAL( neuron.isPyramidal(), false );
    BOOST_CHECK_EQUAL( neuron.isInterneuron(), true );
    BOOST_CHECK_EQUAL( neuron.isExcitatory(), true );
    BOOST_CHECK_EQUAL( neuron.isInhibitory(), false );
  }
}
