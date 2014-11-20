/*
 * Example to show how to use stats
 */

#include <nsol/nsol.h>


int main ( int /* argc */, char ** argv )
{

  nsol::SwcReader< > readerWithoutStats;
  nsol::SwcReader< nsol::Node,  nsol::SectionStats > readerWithStats;

  nsol::NeuronPtr neuron = readerWithoutStats.readNeuron( argv[1] );
  nsol::NeuronPtr neuronWithStats = readerWithStats.readNeuron( argv[2] );

  neuron->morphology()->neurites()[0]->firstSection()->stats();

  neuronWithStats->morphology()->neurites()[0]->firstSection()->stats();

  return 0;

}
