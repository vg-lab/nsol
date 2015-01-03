//
// Example of how to use the factory class
//

#include <nsol/nsol.h>


int main ( int /* argc */, char ** /* argv */ )
{

  nsol::NeuronPtr neuron = nsol::Factory::newNeuron( );
  NSOL_CHECK_THROW( neuron->morphology( ), "no morphology" );

  nsol::NeuronMorphologyPtr nm = nsol::Factory::newNeuronMorphology( );
  NSOL_CHECK_THROW( nm->soma( ), "no soma" );

  return 0;

}
