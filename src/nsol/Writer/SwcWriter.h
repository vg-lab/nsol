/**
 * @file    SwcWriter.h
 * @brief
 * @author  Ricardo Suarez <ricardo.suarez@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SWC_WRITER__
#define __NSOL_SWC_WRITER__

#include <nsol/NsolTypes.h>
#include <nsol/Dendrite.h>
#include <nsol/NeuronMorphology.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <map>
#include <stack>
#include <queue>

namespace nsol
{

  class SwcWriter
  {

  public:

    typedef enum
    {
      SWC_SOMA = 1, SWC_AXON = 2, SWC_DENDRITE = 3, SWC_APICAL = 4
    } TSwcNodeType;

    typedef struct
    {
      unsigned int id;
      unsigned int type;
      Vec3f xyz;
      float radius;
      int parent;
    } TSwcLine;

    void writeFile(const char *fileName, NeuronMorphologyPtr morphology)
    {
      return this->writeFile(std::string(fileName), morphology);
    }

    void writeFile(const std::string fileName, NeuronMorphologyPtr morphology)
    {

      if (!morphology)
        std::cerr << "Error neuron " << std::endl;

      std::ofstream outFile;
      outFile.open(fileName, std::ios::out);

      //Opening file checking
      if ((outFile.rdstate() & std::ofstream::failbit) != 0)
        std::cerr << "Error opening file " << fileName << std::endl;

      int parent = -1;

//      TODO: remove this initial line restriction
      outFile << "#File exporter" << std::endl;

      //Writing soma
      for (Vector<NodePtr>::iterator it = morphology->soma().nodes().begin();
      it != morphology->soma().nodes().end(); ++it)
      {
        outFile << " "
                << (*it)->id()
                << " "
                << SWC_SOMA
                << " "
                << (*it)->point()[0]
                << " "
                << (*it)->point()[1]
                << " "
                << (*it)->point()[2]
                << " "
                << (*it)->radius()
                << " "
                << parent
                << std::endl;

        parent = (*it)->id();
      }

      Neurites neurites = morphology->neurites();
      unsigned int type;

      //Writing neurites
      for (Vector<Neurite *>::iterator it = neurites.begin();
      it != neurites.end(); ++it)
      {
        if ((*it)->asDendrite())
        {
          if ((*it)->asDendrite()->dendriteType() == Dendrite::APICAL)
            type = SWC_APICAL;
          else if ((*it)->asDendrite()->dendriteType() == Dendrite::BASAL)
            type = SWC_DENDRITE;
        }
        else if ((*it)->asAxon())
          type = SWC_AXON;

        SectionPtr fSection = (*it)->firstSection();

        std::stack<SectionPtr> sPS;
        sPS.push(fSection);

        std::map<unsigned int, NodePtr> nodePtrMap;
        std::map<unsigned int, int> nodeParentId;

        while (!sPS.empty())
        {
          SectionPtr lS = sPS.top();
          sPS.pop();

          SegmentPtr segment = lS->firstSegment();

          parent = segment->begin()->id();
          while(segment)
          {

        	  nodePtrMap[segment->end()->id()] = segment->end();
        	  nodeParentId[segment->end()->id()] = parent;

            parent = segment->end()->id();
            segment = segment->next();
          }

          if (lS->childs().size() > 0)
            for (unsigned int i = 0; i < lS->childs().size(); ++i)
              sPS.push(lS->childs()[i]);
        }

        for (std::map<unsigned int, NodePtr>::iterator it = nodePtrMap.begin(); it != nodePtrMap.end(); it++)
        {

          outFile << " "
                  << it->second->id()
                  << " "
                  << type
                  << " "
                  << it->second->point()[0]
                  << " "
                  << it->second->point()[1]
                  << " "
                  << it->second->point()[2]
                  << " "
                  << it->second->radius()
                  << " "
                  << nodeParentId[it->second->id()]
                  << std::endl;

          parent = nodeParentId[it->second->id()];
        }

      }

     outFile.close();

    }
  };
}

#endif
