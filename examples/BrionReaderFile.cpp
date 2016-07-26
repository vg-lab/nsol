#include <nsol/nsol.h>

#include <assert.h>

#include <iostream>

using namespace nsol;
using namespace std;

int main( int argc, char* argv[ ])
{
  BrionReader r;

  if( argc < 2 )
  {
    std::cerr << "Error: swc/hdf5 file parameter needed" << std::endl;
    return -1;
  }
  cout << "Reading file " << argv[1] << endl;

  NeuronPtr neuron = r.loadNeuron( std::string( argv[1] ), 1 );

  if( !neuron->morphology( ))
  {
    std::cerr << "Error: morphology not loaded " << std::endl;
    return -1;
  }

  std::cout << "Soma center: " << neuron->morphology( )->soma( )->center( )
            << std::endl;
  std::cout << "Soma nodes: " << neuron->morphology( )->soma( )->
    nodes( ).size( ) << std::endl;
  std::cout << "Soma max radius: " << neuron->morphology( )->soma( )->
    maxRadius( ) << std::endl;

  std::cout << "Num neurites: " << neuron->morphology( )->neurites( ).size( )
            << std::endl;

  unsigned int neuriteId = 0;
  for( auto neurite: neuron->morphology( )->neurites( ))
  {
    std::cout << "\n**Neurite " << neuriteId << std::endl;
    neuriteId++;
    unsigned int sectionId = 0;
    for( auto section: neurite->sections( ))
    {
      std::cout << "\n****Section " << sectionId << std::endl;
      sectionId++;
      for ( auto node: section->nodes( ))
      {
        std::cout << "******Node " << node->id( ) << "Position: "
                  << node->point( ).x( ) << " " << node->point( ).y( )
                  << " " << node->point( ).z( ) << std::endl;
      }
    }
  }

  return 0;
}
