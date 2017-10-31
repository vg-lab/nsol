/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Ricardo Suarez <ricardo.suarez@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
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

    bool writeMorphology(const char *fileName, NeuronMorphologyPtr morphology)
    {
      return this->writeMorphology(std::string(fileName), morphology);
    }

    bool writeMorphology(const std::string& fileName, NeuronMorphologyPtr morphology)
    {

      if (!morphology)
      {
        std::cerr << "Error neuron " << std::endl;
        return false;
      }

      std::ofstream outFile;
      outFile.open(fileName, std::ios::out);

      //Opening file checking
      if ((outFile.rdstate() & std::ofstream::failbit) != 0)
      {
        std::cerr << "Error opening file " << fileName << std::endl;
        return false;
      }

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

        NeuronMorphologySectionPtr fSection = (*it)->firstSection();

        std::stack<SectionPtr> sPS;
        sPS.push(fSection);

        std::map<unsigned int, NodePtr> nodePtrMap;
        std::map<unsigned int, int> nodeParentId;

        nodePtrMap[ fSection->firstNode( )->id( ) ] = fSection->firstNode( );
        nodeParentId[ fSection->firstNode( )->id( ) ] = 1;

        while (!sPS.empty())
        {
          NeuronMorphologySectionPtr lS =
            dynamic_cast< NeuronMorphologySectionPtr >( sPS.top( ));
          sPS.pop();

          NSOL_FOREACH( node, lS->nodes() )
          {
            if ( (*node) != lS->firstNode( ) )
            {
              nodePtrMap[( *node )->id( )] = *node;
              nodeParentId[( *node )->id( )] = parent;
            }
            parent = ( *node )->id( );
          }

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

     return true;

    }
  };
}

#endif
