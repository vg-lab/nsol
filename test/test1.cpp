#include <nsdl.h>

#include <assert.h>

#include <iostream>


using namespace nsdl;
using namespace std;

int main () {



  {

    Neuron neuron;

    Neurite * neurite = neuron.addNeurite();
    assert(neurite != NULL);
    assert(neurite->NeuriteType() == Neurite::DENDRITE);
    
    Neurite * neurite2 = neuron.addNeurite(Neurite::AXON);
    assert(neurite2 != NULL);
    assert(neurite2->NeuriteType() == Neurite::AXON);

  }

  {
    Neuron neuron;
    
    Neurite * neurite = neuron.addNeurite();
    assert(neurite != NULL);
    assert(neurite->NeuriteType() == Neurite::DENDRITE);
    assert(neurite->asDendrite() != NULL);
    assert(neurite->asDendrite()->DendriteType() == Dendrite::BASAL);
    
    Dendrite * dendrite = neuron.addDendrite();
    assert(dendrite->DendriteType() == Dendrite::BASAL);
    
    Dendrite * dendrite2 = neuron.addDendrite(Dendrite::APICAL);
    assert(dendrite2->DendriteType() == Dendrite::APICAL);
    
  }

  return 0;

}
