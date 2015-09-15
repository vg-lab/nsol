/**
 * @file    SwcWriter.h
 * @brief
 * @author  Ricardo Suarez <ricardo.suarez@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
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
      Vec3f xyz;
      float radius;
    } TSwcLine;

    void writeMorphology(const char *fileName, NeuronMorphologyPtr morphology)
    {
      return this->writeMorphology(std::string(fileName), morphology);
    }

    void writeMorphology(const std::string& fileName, NeuronMorphologyPtr morphology)
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
      for (NsolVector<NodePtr>::iterator it =
             morphology->soma()->nodes().begin();
           it != morphology->soma()->nodes().end(); ++it)
      {
        outFile << " "
                << (*it)->id()
                << " "
                << int( SWC_SOMA )
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
      for (Neurites::iterator it = neurites.begin();
           it != neurites.end(); ++it)
      {
        if (NSOL_DYNAMIC_CAST( Dendrite, *it ))
        {
          if (NSOL_DYNAMIC_CAST( Dendrite, *it )->dendriteType() == Dendrite::APICAL)
            type = SWC_APICAL;
          else if (NSOL_DYNAMIC_CAST( Dendrite, *it )->dendriteType() == Dendrite::BASAL)
            type = SWC_DENDRITE;
        }
        else if (NSOL_DYNAMIC_CAST( Axon, *it ))
          type = SWC_AXON;

        SectionPtr fSection = (*it)->firstSection();

        std::stack<SectionPtr> sPS;
        sPS.push(fSection);

        std::map<unsigned int, NodePtr> nodePtrMap;
        std::map<unsigned int, int> nodeParentId;

        nodePtrMap[ fSection->firstNode( )->id( ) ] = fSection->firstNode( );
        nodeParentId[ fSection->firstNode( )->id( ) ] = 1;

        while (!sPS.empty())
        {
          SectionPtr lS = sPS.top();
          sPS.pop();

          parent = lS->firstNode( )->id();
          NSOL_FOREACH( node, lS->middleNodes() )
          {

            nodePtrMap[( *node )->id( )] = *node;
            nodeParentId[( *node )->id( )] = parent;

            parent = ( *node )->id( );
          }
          nodePtrMap[ lS->lastNode( )->id( )] = lS->lastNode( );
          nodeParentId[ lS->lastNode( )->id( ) ] = parent;

          if (lS->children().size() > 0)
            for (unsigned int i = 0; i < lS->children().size(); ++i)
              sPS.push(lS->children()[i]);
        }

        for (std::map<unsigned int, NodePtr>::iterator nodeIt =
               nodePtrMap.begin(); nodeIt != nodePtrMap.end(); ++nodeIt)
        {

          outFile << " "
                  << nodeIt->second->id()
                  << " "
                  << type
                  << " "
                  << nodeIt->second->point()[0]
                  << " "
                  << nodeIt->second->point()[1]
                  << " "
                  << nodeIt->second->point()[2]
                  << " "
                  << nodeIt->second->radius()
                  << " "
                  << nodeParentId[nodeIt->second->id()]
                  << std::endl;

          parent = nodeParentId[nodeIt->second->id()];
        }

      }

     outFile.close();

    }
  };
}

#endif
