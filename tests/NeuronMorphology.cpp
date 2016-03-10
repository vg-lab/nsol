/**
 * @file    NeuronMorphology.cpp
 * @brief   Test for class nsol::NeuronMorphology
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( neuronMorphology_constructor )
{
  {
    NeuronMorphology neuronMorphology;
    BOOST_CHECK( neuronMorphology.soma() == nullptr );
    BOOST_CHECK_EQUAL( neuronMorphology.neurites( ).size( ), 0 );
  }
  {
    NeuronMorphology neuronMorphology( nullptr );
    BOOST_CHECK( neuronMorphology.soma() ==  nullptr );
    BOOST_CHECK_EQUAL( neuronMorphology.neurites( ).size( ), 0 );
  }
}
