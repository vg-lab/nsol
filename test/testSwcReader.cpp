#include <nsdl.h>

#include <assert.h>

#include <iostream>

#include <stack>

using namespace nol;
using namespace std;

int main(int argc, char *argv[])
{

  SwcReader r;

  cout << "Reading file " << argv[1] << endl;

  NeuronPtr n = r.readFile(argv[1]);

  cout << "Neuron loaded with " << n->numNeurites() << " neurites" << endl;

  Neurites neurites = n->neurites();

  for (Neurites::iterator it = neurites.begin(); it != neurites.end(); it++)
  {
    cout << "Neurite of type : "
         << (((*it)->neuriteType() == Neurite::AXON) ? "axon" : "");

    if ((*it)->neuriteType() == Neurite::DENDRITE)
    {

      cout
          << "dendrite "
          << (((*it)->asDendrite()->dendriteType() == Dendrite::APICAL) ?
              "apical" : "basal");

    }
    cout << endl;

    //    (*it)

  }

  for (Neurites::iterator it = neurites.begin(); it != neurites.end(); it++)
  {
    NeuritePtr neurite = (*it);

    cout << "######################################################" << endl;

    if (neurite->hasNeuron())
      cout << "Neurite has neuron" << endl;
    else
      cout << "Neurite does not have neuron" << endl;

    //    SectionPtr section = neurite->firstSection();

    if (!neurite->firstSection())
    {
      cout << "Neurite has no sections" << endl;
      continue;
    }
    cout << "First section " << neurite->firstSection() << endl;

    stack<SectionPtr> stack;
    stack.push(neurite->firstSection());

    while (!stack.empty())
    {

      SectionPtr section = stack.top();

      cout << "Section " << section << endl;

      assert(section);
      stack.pop();

      cout << "Section " << section << " parent " << section->parent()
           << " childs: ";

      for (Sections::iterator itSect = section->childs().begin();
          itSect != section->childs().end(); itSect++)
      {
        SectionPtr child = (*itSect);
        cout << child << " ";
        stack.push(child);
      };

      cout << endl;

      SegmentPtr segment = section->firstSegment();
      while (segment)
      {
        cout << "Segment" << endl;
        segment = segment->next();
      }
    }

    // while (section) {
    //   cout << "Section " << section << " parent " << section->parent() 
    // 	   << " childs: ";
    //   for (Sections::iterator itSect = section->childs().begin();
    // 	   itSect != section->childs().end(); itSect++) {
    // 	SectionPtr child = (*itSect);
    // 	cout << child << " ";
    //   };
    //   if (section->childs().size() > 0)
    // 	section = section->childs()[0];
    //   cout << endl;
    // }

  }

  std::cout << "Number neurite branchs:" << n->numNeuriteBranches() << std::endl;
  std::cout << "Number neurite bifurcations:" << n->numNeuriteBifurcations() << std::endl;
  std::cout << "Number axon branchs:" << n->numAxonBranches() << std::endl;
  std::cout << "Number dentrite branchs:" << n->numDendriteBranches() << std::endl;
  std::cout << "Volume:" << n->volume() << std::endl;
  std::cout << "Volume neurites:" << n->neuritesVolume() << std::endl;
  std::cout << "Volume dendrites:" << n->dendritesVolume() << std::endl;
  std::cout << "Volume axon:" << n->axonVolume() << std::endl;
}
