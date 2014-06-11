/**
 * @file    Neurite.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_NEURITE_
#define __NOL_NEURITE_

#include <stack>
#include <Types.h>
#include <Section.h>

namespace nol {

  class Dendrite;
  class Axon;

  class Neurite {

    friend class SwcReader;

  public:

    //! Pssible types of neurite
    typedef enum {DENDRITE = 0, AXON} TNeuriteType;

    //! Default constructor
    Neurite(TNeuriteType neuriteType = DENDRITE) {
      _neuriteType = neuriteType;
      _firstSection = NULL;
      _neuron = NULL;
      _numBranches = 0;
      _numBifurcations = 0;
    };

    virtual ~Neurite()
    {
      if (_firstSection)
      {
        std::stack<SectionPtr> sPS;
        sPS.push(_firstSection);

        while (!sPS.empty())
        {
          SectionPtr lS = sPS.top();
          sPS.pop();

          if (lS->childs().size() > 0)
          {
            for (unsigned int i = 0; i < lS->childs().size(); ++i)
              sPS.push(lS->childs()[i]);
          }

          delete lS;
        }
      }
    }

    //! Get the type of neurite
    TNeuriteType & neuriteType() {
      return _neuriteType;
    };

    NeuronPtr neuron() const {
      return  _neuron;
    }

    NeuronPtr neuron(NeuronPtr neuron)  {
      return  _neuron = neuron;
    }

    bool hasNeuron() {
      return _neuron;
    }

    /* SectionPtr addSection() { */
    /*   _sections.push_back(new Section); */
    /*   return _sections.back(); */
    /* }; */

    SectionPtr firstSection()
    {
      return _firstSection;
    }

    void firstSection(SectionPtr section)
    {
      _firstSection = section;
    }

    /* Sections sections() { */
    /*   return _sections; */
    /* } */


    unsigned int numBranches ()
    {
      //Plus 1 branch for the first soma branch of each neurite
    	return _numBranches + 1;
    }

    unsigned int numBifurcations ()
    {
      return _numBifurcations;
    }

    float volume()
    {
      float volume = 0.0f;

      if (_firstSection)
      {
        std::stack<SectionPtr> sPS;
        sPS.push(_firstSection);

        while (!sPS.empty())
        {
          SectionPtr lS = sPS.top();
          sPS.pop();

          volume += lS->volume();

          if (lS->childs().size() > 0)
            for (unsigned int i = 0; i < lS->childs().size(); ++i)
              sPS.push(lS->childs()[i]);
        }
      }

      return volume;
    }

    float surface()
    {
      float surface = 0.0f;

      if (_firstSection)
      {
        std::stack<SectionPtr> sPS;
        sPS.push(_firstSection);

        while (!sPS.empty())
        {
          SectionPtr lS = sPS.top();
          sPS.pop();

          surface += lS->surface();

          if (lS->childs().size() > 0)
            for (unsigned int i = 0; i < lS->childs().size(); ++i)
              sPS.push(lS->childs()[i]);
        }
      }

      return surface;
    }

    float length()
    {
      float length = 0.0f;

      if (_firstSection)
      {
        std::stack<SectionPtr> sPS;
        sPS.push(_firstSection);

        while (!sPS.empty())
        {
          SectionPtr lS = sPS.top();
          sPS.pop();

          length += lS->length();

          if (lS->childs().size() > 0)
            for (unsigned int i = 0; i < lS->childs().size(); ++i)
              sPS.push(lS->childs()[i]);
        }
      }

      return length;
    }

    // Casting virtual functions
    
    //! Return pointer to Dendrite objetc
    virtual Dendrite * asDendrite() { return 0; }

    //! Return pointer to Dendrite objetc
    virtual Axon * asAxon() { return 0; }

  protected:
    
    void addBifurcationCount (unsigned int numBifurcations)
    {
      _numBifurcations += numBifurcations;
    }

    void addBranchCount (unsigned int numBranches)
    {
      _numBranches += numBranches;
    }

    TNeuriteType _neuriteType;

    //    Vector <Section> 
    /* Sections _sections; */

    SectionPtr _firstSection;

    NeuronPtr _neuron;
    
    unsigned int _numBranches;

    unsigned int _numBifurcations;
  };


}

#endif
