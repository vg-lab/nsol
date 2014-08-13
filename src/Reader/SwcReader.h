/**
 * @file    SwcReader.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SWC_READER__
#define __NSOL_SWC_READER__

#include <NsolTypes.h>
#include "Dendrite.h"
#include "NeuronMorphology.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <map>
#include <stack>
#include <queue>

namespace nsol
{

  class SwcReader
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
      std::vector<unsigned int> childs;
    } TSwcLine;

    NeuronMorphologyPtr readFile(const char *fileName)
    {
      return this->readFile(std::string(fileName));
    }

    NeuronMorphologyPtr readFile(const std::string fileName)
    {

      std::ifstream inFile;
      inFile.open(fileName, std::ios::in);

      //Opening file checking
      if ((inFile.rdstate() & std::ifstream::failbit) != 0)
      {
        std::cerr << "Error opening file " << fileName << std::endl;

        return nullptr;
      }

      std::string line;
      std::getline(inFile, line);

      NeuronMorphologyPtr neuronMorphology = new NeuronMorphology;

      std::map<unsigned int, TSwcLine> lines;

      /* // Padding for skkiping line 0 */
      /* TSwcLine padding; */
      /* linespush_back(padding); */

      while (std::getline(inFile, line))
      {

        // TODO: this does not cover the case the # char is not the first char
        if (line[0] != '#')
        {
          std::istringstream iss(line);

          TSwcLine swcLine;
          iss >> swcLine.id;
          iss >> swcLine.type;
          iss >> swcLine.xyz[0] >> swcLine.xyz[1] >> swcLine.xyz[2];
          iss >> swcLine.radius;
          iss >> swcLine.parent;

          /* swcLine.childs[0] = -1; */
          /* swcLine.childs[1] = -1; */

          lines[swcLine.id] = swcLine;

          //      assert(swcLine.id == lines.back().id);

          //std::cout << "Id: " << swcLine.id << std::endl;

        }
      }

      for (std::map<unsigned int, TSwcLine>::iterator it = lines.begin();
          it != lines.end(); it++)
      {

        if (it->second.parent != -1)
        {
          lines[it->second.parent].childs.push_back(it->first);
        }

      }

      /* for (std::map<unsigned int, TSwcLine>::iterator it = lines.begin(); */
      /*           it != lines.end(); it++) { */
      /*        std::cout << it->second.id << " " */
      /*                  << it->second.type << " " */
      /*                  << it->second.xyz[0] << " " */
      /*                  << it->second.xyz[1] << " " */
      /*                  << it->second.xyz[2] << " " */
      /*                  << it->second.radius << " " */
      /*                  << it->second.parent << " " */
      /*                  << it->second.childs.size() << " ( "; */

      /*        for (unsigned int i = 0; i < it->second.childs.size(); i++)  */
      /*          std::cout << it->second.childs[i] << " "; */

      /*        std::cout << ")" << std::endl; */

      /* } */

      std::vector<unsigned int> somaChilds;
      std::map<unsigned int, NodePtr> nodeSomaPtr;

      for (std::map<unsigned int, TSwcLine>::iterator it = lines.begin();
          it != lines.end(); it++)
      {
        if (it->second.type == SWC_SOMA)
        {
          NodePtr node = new Node(it->second.xyz, it->second.id, it->second.radius);
          neuronMorphology->soma().addNode(node);

          nodeSomaPtr[it->second.id] = node;

          for (unsigned int i = 0; i < it->second.childs.size(); i++)
            if (lines[it->second.childs[i]].type != SWC_SOMA)
              somaChilds.push_back(it->second.childs[i]);
        }
      }

      DendritePtr d;

      for (unsigned int i = 0; i < somaChilds.size(); i++)
      {

//        std::cout << "New neurite starting in " << somaChilds[i]
//                  << lines[somaChilds[i]].type << std::endl;

        switch (lines[somaChilds[i]].type)
        {
          case SWC_SOMA:
            // TODO: handle error
            assert(false);

          case SWC_DENDRITE:
          {
//            std::cout << "New basal dendrite" << std::endl;

            d = neuronMorphology->addDendrite(Dendrite::BASAL);
            d->morphology(neuronMorphology);
            _ReadDendrite(d, lines, somaChilds[i],
                          nodeSomaPtr[lines[somaChilds[i]].parent]);

            break;
          }

          case SWC_APICAL:
//            std::cout << "New apical dendrite" << std::endl;

            d = neuronMorphology->addDendrite(Dendrite::APICAL);
            d->morphology(neuronMorphology);
            _ReadDendrite(d, lines, somaChilds[i],
                          nodeSomaPtr[lines[somaChilds[i]].parent]);

            break;

          case SWC_AXON:
          {
//            std::cout << "New axon" << std::endl;

//            neuron->addNeurite(Neurite::AXON);

            NeuritePtr nP = neuronMorphology->addNeurite(Neurite::AXON);
            nP->morphology(neuronMorphology);
            _ReadAxon(nP, lines, somaChilds[i],
                      nodeSomaPtr[lines[somaChilds[i]].parent]);

            break;
          }

          default:
            break;
        }

      }

      /* for (unsigned int i = 1; i < lines.size(); i++) { */
      /*        if (lines[i].type == SWC_SOMA) */
      /*        std::cout << lines[i].id << " " */
      /*                  << lines[i].type << " " */
      /*                  << lines[i].xyz[0] << " " */
      /*                  << lines[i].xyz[1] << " " */
      /*                  << lines[i].xyz[2] << " " */
      /*                  << lines[i].radius << " " */
      /*                  << lines[i].parent << " " */
      /*                  << std::endl; */
      /* } */

      /* for (unsigned int i = 1; i < lines.size(); i++) { */

      /*        std::cerr << "SwcReader: processing id " << lines[i].id  */
      /*                  << " type: " << lines[i].type << std::endl; */

      /*        switch (lines[i].type) { */
      /*        case SWC_SOMA: */
      /*          std::cout << "SwcReader: adding node to soma" << std::endl; */
      /*          neuron->soma().addNode(new Node(lines[i].xyz,lines[i].radius));  */
      /*          break; */
      /*        case SWC_DENDRITE: */
      /*          std::cout << "SwcReader: adding node to dendrite" << std::endl; */

      /*          /\* neuron->().addNode(new Node(xyz,radius)); *\/ */
      /*          break; */
      /*        case SWC_APICAL: */
      /*          break; */
      /*        case SWC_AXON: */
      /*          break; */
      /*        default: */
      /*          std::cerr << "Swc Reader: skkiping id " << lines[i].id << std::endl; */
      /*          break; */
      /*        } */

      /* } */

      inFile.close();

      return neuronMorphology;

    }

  private:
    void _ReadDendrite(DendritePtr d, std::map<unsigned int, TSwcLine> &lines,
                       unsigned int initId, NodePtr nodeSomaPtr)
    {

      typedef struct
      {
        unsigned int id;
        SectionPtr parent;
      } TStackElem;

      std::stack<TStackElem> ids;
      //ids.push(TStackElem { initId, NULL });	  
	  TStackElem tmp = {initId, NULL};
      ids.push(tmp);


      SectionPtr s = nullptr, parentSection;
      NodePtr nP = nullptr;
      bool first = true;

      while (!ids.empty())
      {

        unsigned int id = ids.top().id;
        parentSection = ids.top().parent;
        ids.pop();

        /* parentSection = s; */
        s = new Section;

        if (!d->firstSection())
          d->firstSection(s);  //->addSection();

        s->neurite(d);
        s->parent(parentSection);

        SegmentPtr sgPre = s->addSegment();

        //Segment begin node
        if (first)
        {
          sgPre->begin(nodeSomaPtr);
          first = false;
        }
        else
          sgPre->begin(s->parent()->_lastSegment->end());

        //Segment end node
        sgPre->end(new Node(lines[id].xyz, id, lines[id].radius));

//        std::cout << "Add segment begin node radius: " << sgPre->begin()->radius()
//                  << std::endl;
//        std::cout << "Add segment end node radius: " << lines[id].radius
//                  << std::endl;

        //std::cout << "New section at id " << id << " ( ";

        if (parentSection)
          //      parentSection->_childs.push_back(s);
          parentSection->addChild(s);

//        for (unsigned int i = 0; i < lines[id].childs.size(); i++)
//          std::cout << lines[id].childs[i] << " ";
//
//        std::cout << ") " << std::endl;

        nP = sgPre->end();

        // While same section create the segments
        while (lines[id].childs.size() == 1)
        {

          //std::cout << "New segment at id " << id << std::endl;
          SegmentPtr sg = s->addSegment();
          sg->parentSection(s);

          //Segmenet begin node
          sg->begin(nP);

          id = lines[id].childs[0];
//          std::cout << "Move to id " << id << " whith "
//                    << lines[id].childs.size() << " childs ";

          //Segment end node
          sg->end(new Node(lines[id].xyz, id, lines[id].radius));

//          std::cout << "\nAdd segment begin node radius dentro: "
//                    << sg->begin()->radius() << std::endl;
//
//          std::cout << "\nAdd segment end node radius dentro: "
//                    << sg->end()->radius() << std::endl;

//          for (unsigned int i = 0; i < lines[id].childs.size(); i++)
//            std::cout << lines[id].childs[i] << " ";
//
//          std::cout << std::endl;

          nP = sg->end();

        }

        // New branching point
        if (lines[id].childs.size() > 1)
        {
          //Plus new branch
          d->addBranchCount(lines[id].childs.size());
          //Plus new bifurcation
          d->addBifurcationCount(1);

          /* for (std::vector<unsigned int>::reverse_iterator it = lines[id].childs.rbegin(); */
          /*      it != lines[id].childs.rend(); it++) */
          for (std::vector<unsigned int>::iterator it =
              lines[id].childs.begin(); it != lines[id].childs.end(); it++)
          {
			  TStackElem tmp = { (*it), s };
			   ids.push(tmp);
           // ids.push(TStackElem { (*it), s });
          }
        }

      }

    }

    void _ReadAxon(NeuritePtr d, std::map<unsigned int, TSwcLine> &lines,
                   unsigned int initId, NodePtr nodeSomaPtr)
    {

      typedef struct
      {
        unsigned int id;
        SectionPtr parent;
      } TStackElem;

      std::stack<TStackElem> ids;
	  TStackElem tmp = { initId, NULL };
	  ids.push(tmp);

      SectionPtr s = NULL, parentSection;
      NodePtr nP = nullptr;
      bool first = true;

      while (!ids.empty())
      {

        unsigned int id = ids.top().id;
        parentSection = ids.top().parent;
        ids.pop();

        /* parentSection = s; */
        s = new Section;

        if (!d->firstSection())
          d->firstSection(s);  //->addSection();

        s->neurite(d);
        s->parent(parentSection);

        SegmentPtr sgPre = s->addSegment();

//        std::cout << "id: " << id << std::endl;

        //Segment begin node
        if (first)
        {
          sgPre->begin(nodeSomaPtr);
          first = false;
        }
        else
          sgPre->begin(s->parent()->_lastSegment->end());

        //Segment end node
        sgPre->end(new Node(lines[id].xyz, id, lines[id].radius));

//        std::cout << "Add segment begin node radius: " << sgPre->begin()->radius()
//                  << std::endl;
//        std::cout << "Add segment end node radius: " << lines[id].radius
//                  << std::endl;

        //std::cout << "New section at id " << id << " ( ";

        if (parentSection)
          //      parentSection->_childs.push_back(s);
          parentSection->addChild(s);

//        for (unsigned int i = 0; i < lines[id].childs.size(); i++)
//          std::cout << lines[id].childs[i] << " ";
//
//        std::cout << ") " << std::endl;

        nP = sgPre->end();

        // While same section create the segments
        while (lines[id].childs.size() == 1)
        {

          //std::cout << "New segment at id " << id << std::endl;
          SegmentPtr sg = s->addSegment();
          sg->parentSection(s);

          //Segmenet begin node
          sg->begin(nP);

          id = lines[id].childs[0];
//          std::cout << "Move to id " << id << " whith "
//                    << lines[id].childs.size() << " childs ";

          //Segment end node
          sg->end(new Node(lines[id].xyz, id, lines[id].radius));

//          std::cout << "\nAdd segment begin node radius dentro: "
//                    << sg->begin()->radius() << std::endl;
//
//          std::cout << "\nAdd segment end node radius dentro: "
//                    << sg->end()->radius() << std::endl;

//          for (unsigned int i = 0; i < lines[id].childs.size(); i++)
//            std::cout << lines[id].childs[i] << " ";
//
//          std::cout << std::endl;

          nP = sg->end();

        }

        // New branching point
        if (lines[id].childs.size() > 1)
        {
          //Plus new branch
          d->addBranchCount(lines[id].childs.size());
          //Plus new bifurcation
          d->addBifurcationCount(1);

          /* for (std::vector<unsigned int>::reverse_iterator it = lines[id].childs.rbegin(); */
          /*      it != lines[id].childs.rend(); it++) */
          for (std::vector<unsigned int>::iterator it =
              lines[id].childs.begin(); it != lines[id].childs.end(); it++)
          {
			TStackElem tmp = { (*it), s };
            ids.push(tmp);
          }
        }

      }

    }

  };

}

#endif
