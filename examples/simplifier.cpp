#include <nsol/nsol.h>

#include <assert.h>

#include <iostream>

using namespace nsol;

void printMorpho( NeuronMorphologyPtr morpho )
{
  for ( auto neurite: morpho->neurites( ))
  {
    std::cout << "****Neurite****" << std::endl;
    for ( auto section: neurite->sections( ))
    {
      std::cout << "Section********" << std::endl;
      for ( auto node: section->nodes( ))
      {
        std::cout << "Node: " << node->id( ) << std::endl;
        std::cout << "      " <<  node->point( ) << std::endl;
      }
    }
  }
}

int main( int argc, char* argv[ ])
{
  BrionReader r;

  if( argc < 2 )
  {
    std::cerr << "Error: swc/hdf5 file parameters needed" << std::endl;
    return -1;
  }

  NeuronMorphologyPtr morpho = r.loadMorphology( std::string( argv[1]) );

  printMorpho( morpho );

  std::cout << "Simplificada" << std::endl;

  morpho = Simplifier::Instance( )->simplify( morpho, Simplifier::DIST_NODES, 5, true );

  printMorpho( morpho );
}
