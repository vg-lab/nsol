/**
 * @file    Sections.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_SWC_READER__
#define __NOL_SWC_READER__

#include <Types.h>


#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <map>
#include <stack>
#include <queue>


namespace nol
{
  class SwcReader
  {

    public:

<<<<<<< HEAD
  class SwcReader {

  public:
    
    typedef enum {SWC_SOMA = 1, 
		  SWC_AXON = 2, 
		  SWC_DENDRITE = 3, 
		  SWC_APICAL = 4} TSwcNodeType;

    typedef struct {
      unsigned int id;
      unsigned int type;
      Vec3f xyz;
      float radius;
	int parent;
      std::vector<unsigned int> childs;
    } TSwcLine;
    

    NeuronPtr readFile(const char * fileName) {
      return this->readFile(std::string(fileName));
    }

    NeuronPtr readFile(const std::string fileName) {

      std::ifstream inFile;
      inFile.open(fileName, std::ios::in);

      //Opening file checking
      if ( (inFile.rdstate() & std::ifstream::failbit ) != 0 )
      {
        std::cerr << "Error opening file " << fileName << "\n";

        return nullptr;
      }

      std::string line;
      std::getline(inFile, line);

      NeuronPtr neuron = new Neuron;


      std::map<unsigned int, TSwcLine> lines;

      /* // Padding for skkiping line 0 */
      /* TSwcLine padding; */
      /* linespush_back(padding); */

      while (std::getline(inFile, line)) {
	
	// TODO: this does not cover the case the # char is not the first char
	if (line[0] != '#' ) {
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

	  //	  assert(swcLine.id == lines.back().id);
=======
      typedef enum
      {
        SWC_SOMA = 1,
        SWC_AXON = 2,
        SWC_DENDRITE = 3,
        SWC_APICAL = 4
      } TSwcNodeType;
>>>>>>> 7348a8e567b976ac12367ae74f7b82c28354bd74

      typedef struct
      {
        unsigned int id;
        unsigned int type;
        Vec3f xyz;
        float radius;
        int parent;
        std::vector<unsigned int> childs;
      } TSwcLine;


      NeuronPtr readFile(const char *fileName)
      {
        return this->readFile(std::string(fileName));
      }

<<<<<<< HEAD
      /* for (std::map<unsigned int, TSwcLine>::iterator it = lines.begin(); */
      /* 	   it != lines.end(); it++) { */
      /* 	std::cout << it->second.id << " " */
      /* 		  << it->second.type << " " */
      /* 		  << it->second.xyz[0] << " " */
      /* 		  << it->second.xyz[1] << " " */
      /* 		  << it->second.xyz[2] << " " */
      /* 		  << it->second.radius << " " */
      /* 		  << it->second.parent << " " */
      /* 		  << it->second.childs.size() << " ( "; */
	
      /* 	for (unsigned int i = 0; i < it->second.childs.size(); i++)  */
      /* 	  std::cout << it->second.childs[i] << " "; */
      	
      /* 	std::cout << ")" << std::endl; */
	
      /* } */
      
      
      std::vector<unsigned int> somaChilds;

      for (std::map<unsigned int, TSwcLine>::iterator it = lines.begin();
	   it != lines.end(); it++) {

	

	if (it->second.type == SWC_SOMA) {
		neuron->soma().addNode(new Node(it->second.xyz,it->second.radius));
	  for (unsigned int i = 0; i < it->second.childs.size(); i++) 
	    if (lines[it->second.childs[i]].type != SWC_SOMA) 
	      somaChilds.push_back(it->second.childs[i]);
	}
=======
      NeuronPtr readFile(const std::string fileName)
      {
        std::ifstream inFile;
        inFile.open(fileName, std::ios::in);
        // TODO: file opening error checking
        std::string line;
        std::getline(inFile, line);
        NeuronPtr neuron = new Neuron;
        std::map<unsigned int, TSwcLine> lines;

        /* // Padding for skkiping line 0 */
        /* TSwcLine padding; */
        /* linespush_back(padding); */

        while (std::getline(inFile, line))
        {
          // TODO: this does not cover the case the # char is not the first char
          if (line[0] != '#' )
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
            //    assert(swcLine.id == lines.back().id);
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
        /*     it != lines.end(); it++) { */
        /*  std::cout << it->second.id << " " */
        /*      << it->second.type << " " */
        /*      << it->second.xyz[0] << " " */
        /*      << it->second.xyz[1] << " " */
        /*      << it->second.xyz[2] << " " */
        /*      << it->second.radius << " " */
        /*      << it->second.parent << " " */
        /*      << it->second.childs.size() << " ( "; */
        /*  for (unsigned int i = 0; i < it->second.childs.size(); i++)  */
        /*    std::cout << it->second.childs[i] << " "; */
        /*  std::cout << ")" << std::endl; */
        /* } */
        std::vector<unsigned int> somaChilds;

        for (std::map<unsigned int, TSwcLine>::iterator it = lines.begin();
             it != lines.end(); it++)
        {
          neuron->soma().addNode(new Node(it->second.xyz,it->second.radius));

          if (it->second.type == SWC_SOMA)
          {
            for (unsigned int i = 0; i < it->second.childs.size(); i++)
              if (lines[it->second.childs[i]].type != SWC_SOMA)
                somaChilds.push_back(it->second.childs[i]);
          }
        }

        DendritePtr d;

        for (unsigned int i = 0; i < somaChilds.size(); i++)
        {
          std::cout << "New neurite starting in " << somaChilds[i]
                    << lines[somaChilds[i]].type << std::endl;

          switch (lines[somaChilds[i]].type)
          {
          case SWC_SOMA:
            // TODO: handle error
            assert(false);

          case SWC_DENDRITE:
            std::cout << "New dendrite" << std::endl;
            d = neuron->addDendrite(Dendrite::BASAL);
            d->neuron(neuron);
            _ReadDendrite(d, lines, somaChilds[i]);
            break;

          case SWC_APICAL:
            std::cout << "New apical" << std::endl;
            d = neuron->addDendrite(Dendrite::APICAL);
            d->neuron(neuron);
            _ReadDendrite(d, lines, somaChilds[i]);
            break;

          case SWC_AXON:
            neuron->addNeurite(Neurite::AXON);
            std::cout << "New axon" << std::endl;
            break;

          default:
            break;
          }
        }

        /* for (unsigned int i = 1; i < lines.size(); i++) { */
        /*  if (lines[i].type == SWC_SOMA) */
        /*  std::cout << lines[i].id << " " */
        /*      << lines[i].type << " " */
        /*      << lines[i].xyz[0] << " " */
        /*      << lines[i].xyz[1] << " " */
        /*      << lines[i].xyz[2] << " " */
        /*      << lines[i].radius << " " */
        /*      << lines[i].parent << " " */
        /*      << std::endl; */
        /* } */
        /* for (unsigned int i = 1; i < lines.size(); i++) { */
        /*  std::cerr << "SwcReader: processing id " << lines[i].id  */
        /*      << " type: " << lines[i].type << std::endl; */
        /*  switch (lines[i].type) { */
        /*  case SWC_SOMA: */
        /*    std::cout << "SwcReader: adding node to soma" << std::endl; */
        /*    neuron->soma().addNode(new Node(lines[i].xyz,lines[i].radius));  */
        /*    break; */
        /*  case SWC_DENDRITE: */
        /*    std::cout << "SwcReader: adding node to dendrite" << std::endl; */
        /*    /\* neuron->().addNode(new Node(xyz,radius)); *\/ */
        /*    break; */
        /*  case SWC_APICAL: */
        /*    break; */
        /*  case SWC_AXON: */
        /*    break; */
        /*  default: */
        /*    std::cerr << "Swc Reader: skkiping id " << lines[i].id << std::endl; */
        /*    break; */
        /*  } */
        /* } */
        return neuron;
>>>>>>> 7348a8e567b976ac12367ae74f7b82c28354bd74
      }

    private:
      void _ReadDendrite(DendritePtr d, std::map<unsigned int,
                         TSwcLine> & lines,
                         unsigned int initId)
      {
<<<<<<< HEAD
	
	unsigned int id = ids.top().id;
	parentSection = ids.top().parent;;
	ids.pop();
	
	/* parentSection = s; */
	s = new Section; 
	SegmentPtr sg = s->addSegment();

	std::cout << "New section at id " << id << " ( ";

	if (!d->firstSection())
	  d->firstSection(s); //->addSection();
	s->neurite(d);
	s->parent(parentSection);
	if (parentSection)
	  //	  parentSection->_childs.push_back(s);
	  parentSection->addChild(s);

       	for (unsigned int i = 0; i < lines[id].childs.size(); i++)  
	  std::cout << lines[id].childs[i] << " "; 
	
	std::cout << ") " << std::endl;
	
	// While same section create the segments
	while (lines[id].childs.size() == 1) {

	  std::cout << "New segment at id " << id <<  std::endl;
	  SegmentPtr sg = s->addSegment();
	  sg->parentSection(s);

	  id  = lines[id].childs[0];
	  std::cout << "Move to id " << id << " whith " 
		    << lines[id].childs.size() << " childs ";
	    for (unsigned int i = 0; i < lines[id].childs.size(); i++)  
	      std::cout << lines[id].childs[i] << " "; 
	  std::cout << std::endl;
	  
	}

	// New branching point
	if (lines[id].childs.size() > 1) {

	  /* for (std::vector<unsigned int>::reverse_iterator it = lines[id].childs.rbegin(); */
	  /*      it != lines[id].childs.rend(); it++) */
	  for (std::vector<unsigned int>::iterator it = lines[id].childs.begin();
	       it != lines[id].childs.end(); it++)
	  {
	      ids.push(TStackElem{(*it),s});
	  }
	}

	
=======
        typedef struct
        {
          unsigned int id;
          SectionPtr parent;
        } TStackElem;

        std::stack<TStackElem> ids;
        ids.push(TStackElem {initId,NULL});
        SectionPtr s = NULL, parentSection;

        while (!ids.empty())
        {
          unsigned int id = ids.top().id;
          parentSection = ids.top().parent;;
          ids.pop();
          /* parentSection = s; */
          s = new Section;
          std::cout << "New section at id " << id << " ( ";

          if (!d->firstSection())
            d->firstSection(s); //->addSection();

          s->neurite(d);
          s->parent(parentSection);

          if (parentSection)
            //    parentSection->_childs.push_back(s);
            parentSection->addChild(s);

          for (unsigned int i = 0; i < lines[id].childs.size(); i++)
            std::cout << lines[id].childs[i] << " ";

          std::cout << ") " << std::endl;

          // While same section create the segments
          while (lines[id].childs.size() == 1)
          {
            std::cout << "New segment at id " << id <<  std::endl;
            SegmentPtr sg = s->addSegment();
            sg->parentSection(s);
            id  = lines[id].childs[0];
            std::cout << "Move to id " << id << " whith "
                      << lines[id].childs.size() << " childs ";

            for (unsigned int i = 0; i < lines[id].childs.size(); i++)
              std::cout << lines[id].childs[i] << " ";

            std::cout << std::endl;
          }

          // New branching point
          if (lines[id].childs.size() > 1)
          {
            /* for (std::vector<unsigned int>::reverse_iterator it = lines[id].childs.rbegin(); */
            /*      it != lines[id].childs.rend(); it++) */
            for (std::vector<unsigned int>::iterator it = lines[id].childs.begin();
                 it != lines[id].childs.end(); it++)
            {
              ids.push(TStackElem {(*it),s});
            }
          }
        }
>>>>>>> 7348a8e567b976ac12367ae74f7b82c28354bd74
      }



  };

}

#endif
