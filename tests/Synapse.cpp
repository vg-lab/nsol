/**
 * @file    Synapse.cpp
 * @brief   Test for class nsol::Column
 * @author  Raquel Jarillo <raquel.jarillo@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
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
