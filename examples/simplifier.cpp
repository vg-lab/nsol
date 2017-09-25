/*
 * Minimal example of how to use morphology simplifier
 */
#include <nsol/nsol.h>

#include <assert.h>

#include <iostream>

using namespace nsol;

void printMorpho( NeuronMorphologyPtr morpho )
{
  for ( auto neurite: morpho->neurites( ))
  {
    std::cout << "=== Neurite ===" << std::endl;
    for ( auto section: neurite->sections( ))
    {
      std::cout << "==== Section ===" << std::endl;
      for ( auto node: section->nodes( ))
      {
        std::cout << "Node: " << node->id( );
        std::cout << "      (" <<  node->point( ).transpose( ) << ")"
                  << std::endl;
      }
    }
  }
}

int main( int argc, char* argv[ ])
{
  if( argc < 2 )
  {
    std::cerr << "Error: morphology file parameters needed" << std::endl;
    return -1;
  }

  NeuronMorphologyPtr morpho;

#ifdef NSOL_USE_BRION
  BrionReader r;
  morpho = r.loadMorphology( std::string( argv[1]) );
#else
  SwcReader r;
  morpho = r.readMorphology( std::string(argv[1]) );
#endif

  printMorpho( morpho );

  std::cout << "Simplificada" << std::endl;

  morpho = Simplifier::Instance( )->simplify( morpho, Simplifier::DIST_NODES, 5, true );

  printMorpho( morpho );

  return 0;
}
