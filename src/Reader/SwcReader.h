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


namespace nol {


  class SwcReader {

  public:
    
    typedef enum {SWC_SOMA = 1, SWC_APICAL = 2, SWC_BASAL = 3} TSwcNodeType;

    NeuronPtr readFile(std::string fileName) {

      std::ifstream inFile;
      inFile.open(fileName, std::ios::in);

      // TODO: file opening error checking
      
      std::string line;
      std::getline(inFile, line);

      NeuronPtr neuron = new Neuron;

      while (std::getline(inFile, line)) {
	
	// TODO: this does not cover the case the # char is not the first char
	if (line[0] != '#' ) {
	  std::istringstream iss(line);
	  
	  unsigned int id;
	  unsigned int type;
	  Vec3f xyz;
	  float radius;
	  unsigned int parent;
	  iss >> id;
	  iss >> type;
	  iss >> xyz[0] >> xyz[1] >> xyz[2];
	  iss >> radius;
	  iss >> parent;

	  if (id == SWC_SOMA) {

	    neuron->soma().addNode(new Node(xyz,radius));

	  }


	}

      }



      return neuron;

    }


  };

}

#endif
