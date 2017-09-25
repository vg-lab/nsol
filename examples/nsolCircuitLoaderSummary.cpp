/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo Pellon <raquel.jarillo@urjc.es>
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

#include <nsol/nsol.h>
#include <nsol/DataSet.h>
#include <nsol/Circuit.h>

#include <Eigen/Sparse>
#include <assert.h>

#include <iostream>
#include <stdio.h>

using namespace nsol;
using namespace std;

void usageMessage( char* programName )
{
  std::cerr << std::endl
            << "Usage: "
            << programName << "\t"
            << " -bc file_name -target target_name" << std::endl
            << std::endl << std::endl;
  exit(-1);
}

int main( int argc, char* argv[ ])
{
  std::string blueConfig;
  std::string target = std::string( "" );

  for( int i = 1; i < argc; i++ )
  {
    if( std::strcmp( argv[ i ], "-bc" ) == 0 )
    {
      if( ++i < argc )
      {
        blueConfig = std::string( argv[ i ]);
      }
      else
        usageMessage( argv[0] );
    }
    if( std::strcmp( argv[ i ], "-target" ) == 0 )
    {
      if( ++i < argc )
      {
        target = std::string( argv[ i ] );
      }
      else
        usageMessage( argv[0] );
    }
  }

  if ( blueConfig.empty( ) || target.empty( ))
  {
    usageMessage( argv[0] );
  }

  DataSet dataSet;

  cout << "Open BlueConfig ..." << endl;

  dataSet.loadBlueConfigHierarchy( blueConfig, target );
  dataSet.loadAllMorphologies( );
  dataSet.loadBlueConfigConnectivity( );

  cout << " EXECUTING CircuitLoader... " << endl;
  cout << endl; cout << endl; cout << endl;

  NeuronsMap neuronsMap = dataSet.neurons();
  Circuit circuit = dataSet.circuit();

  std::set<SynapsePtr> synapses = std::move(circuit.synapses
                                           ( Circuit::PRESYNAPTICCONNECTIONS ));

  std::cout << "-     SUMMARY OF CONNECTIVITY DATA     -"<< std::endl;
  std::cout << "  - Number of synapses: "<< synapses.size() << std::endl;
  std::cout << "  - Number of neurons: "<< neuronsMap.size() << std::endl;

  unsigned int totalSynapsesPerNeuron = 0;
  unsigned int maxSynapsesPerNeurons = 0;
  float meanSynapsesPerNeuron = 0.0f;

  for( const auto& pair: neuronsMap )
  {
    std::set<SynapsePtr> preSynapses = std::move(circuit.synapses
                               ( pair.first, Circuit::PRESYNAPTICCONNECTIONS ));
    std::set<SynapsePtr> postSynapses = std::move(circuit.synapses
                              ( pair.first, Circuit::POSTSYNAPTICCONNECTIONS ));

    unsigned int numSynapses = preSynapses.size() + postSynapses.size();

    if( numSynapses >  maxSynapsesPerNeurons)
     maxSynapsesPerNeurons = numSynapses;

    totalSynapsesPerNeuron += numSynapses;
  }

  meanSynapsesPerNeuron = std::roundf
                                 ( totalSynapsesPerNeuron / neuronsMap.size() );

  std::cout << "  - Maximun number of synapses per neuron: "
            << maxSynapsesPerNeurons << std::endl;

  std::cout << "  - Mean of number of synapses per neuron: "
            << meanSynapsesPerNeuron
            << std::endl;

  return 0;

}
