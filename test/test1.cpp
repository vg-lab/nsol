#include <nsol.h>

#include <assert.h>

#include <iostream>


using namespace nsol;
using namespace std;

int main () {



  // Neurite tests

  {

    cout << "Testing neurite ops" << endl;
    Neuron neuron;

    Neurite * neurite = neuron.addNeurite();
    assert(neurite != NULL);
    assert(neurite->neuriteType() == Neurite::DENDRITE);
    
    Neurite * neurite2 = neuron.addNeurite(Neurite::AXON);
    assert(neurite2 != NULL);
    assert(neurite2->neuriteType() == Neurite::AXON);

    assert(neuron.numNeurites() ==  2);
    assert(neuron.numDendrites() ==  1);

  }

  {
    Neuron neuron;
    
    cout << "Testing dendrite ops" << endl;
    Neurite * neurite = neuron.addNeurite();
    assert(neurite != NULL);
    assert(neurite->neuriteType() == Neurite::DENDRITE);
    assert(neurite->asDendrite() != NULL);
    assert(neurite->asDendrite()->dendriteType() == Dendrite::BASAL);
    assert(neuron.apicalDendrite() == NULL);

    assert(neuron.numNeurites() ==  1);
    assert(neuron.numDendrites() ==  1);

    Dendrite * dendrite = neuron.addDendrite();
    assert(dendrite->dendriteType() == Dendrite::BASAL);

    assert(neuron.numNeurites() ==  2);
    assert(neuron.numDendrites() ==  2);
    
    Dendrite * dendrite2 = neuron.addDendrite(Dendrite::APICAL);
    assert(dendrite2->dendriteType() == Dendrite::APICAL);

    assert(neuron.apicalDendrite() != NULL);

    assert(neuron.numNeurites() ==  3);
    assert(neuron.numDendrites() ==  3);

    
  }


  // Soma tests

  {

    cout << "Testing soma ops" << endl;
    Neuron neuron;

    neuron.soma().center() = Vec3f(3.5,4.6,5.7);
    assert(neuron.soma().center()[0] == 3.5f);
    assert(neuron.soma().center()[1] == 4.6f);
    assert(neuron.soma().center()[2] == 5.7f);
    
    Vec3f & centerRef = neuron.soma().center();
    assert(centerRef[0] == 3.5f);
    assert(centerRef[1] == 4.6f);
    assert(centerRef[2] == 5.7f);

    neuron.soma().center() = Vec3f(1.2,2.3,3.4);
    assert(neuron.soma().center()[0] == 1.2f);
    assert(neuron.soma().center()[1] == 2.3f);
    assert(neuron.soma().center()[2] == 3.4f);
    assert(centerRef[0] == 1.2f);
    assert(centerRef[1] == 2.3f);
    assert(centerRef[2] == 3.4f);

    Vec3f newCenter(2.5,3.6,4.7);
    neuron.soma().center() = newCenter;
    assert(neuron.soma().center() == newCenter);
    assert(centerRef == newCenter);
    assert(neuron.soma().center()[0] == 2.5f);
    assert(neuron.soma().center()[1] == 3.6f);
    assert(neuron.soma().center()[2] == 4.7f);
    
    {
      Vec3f newCenter(5.6,6.7,7.8);
      neuron.soma().center() = newCenter;
    }
    assert(neuron.soma().center() == Vec3f(5.6,6.7,7.8));
    

  }

  return 0;

}
