#include <nsdl.h>

#include <assert.h>

#include <iostream>


using namespace nol;
using namespace std;

int main (int argc, char *argv[]) {

  SwcReader r;

  cout << "Reading file" << argv[1] << endl;

  NeuronPtr n = r.readFile(argv[1]);

  cout << "Neuron loaded with " << n->numNeurites() << " neurites" << endl;

  Neurites neurites = n->neurites();

  for (Neurites::iterator it = neurites.begin();
       it != neurites.end(); it++) 
  {
    cout << "Neurite of type : " << (((*it)->neuriteType() == Neurite::AXON) ? "axon" : "");
    
    if ((*it)->neuriteType() == Neurite::DENDRITE) {
      
      cout << "dendrite " 
	   << (((*it)->asDendrite()->dendriteType() == Dendrite::APICAL) ? "apical" : "basal");

     

    }
    cout << endl;

    //    (*it)


  }



}
