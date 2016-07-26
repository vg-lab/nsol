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

BOOST_AUTO_TEST_CASE( neuronMorphology_clone )
{
  NeuronMorphologyPtr neuronMorphology;
#ifdef NSOL_USE_BRION
  BrionReader brionReader;
  neuronMorphology = brionReader.loadMorphology( "ExampleNeuron.swc" );
#else
  SwcReader swcReader;
  neuronMorphology = swcReader.readMorphology( "ExampleNeuron.swc" );
#endif

  NeuronMorphologyPtr neuronMorphology1 = neuronMorphology->clone( );

  BOOST_CHECK( *neuronMorphology->soma( ) != *neuronMorphology1->soma( ));
}

BOOST_AUTO_TEST_CASE( neuronMorphology_operators )
{
  NeuronMorphologyPtr neuronMorphology1;
  NeuronMorphologyPtr neuronMorphology2;

#ifdef NSOL_USE_BRION
  BrionReader brionReader;
  neuronMorphology1 = brionReader.loadMorphology( "ExampleNeuron.swc" );
  neuronMorphology2 = brionReader.loadMorphology( "mini.swc" );
#else
  SwcReader swcReader;
  neuronMorphology1 = swcReader.readMorphology( "ExampleNeuron.swc" );
  neuronMorphology2 = swcReader.readMorphology( "mini.swc" );
#endif

  BOOST_CHECK( neuronMorphology1 == neuronMorphology1 );
  BOOST_CHECK( neuronMorphology2 == neuronMorphology2 );
  BOOST_CHECK( neuronMorphology1 != neuronMorphology2 );
}
