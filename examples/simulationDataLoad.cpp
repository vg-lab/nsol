/**
 * @file    simulationDataLoad.cpp
 * @brief   Stress test for class nsol::SimulationData
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include <nsol/nsol.h>

using namespace nsol;

int main (int argc, char ** argv)
{
  std::cout << std::endl;

  if ( argc < 2 )
  {
    std::cerr << "Error. Usage: " << argv[0]
              << " blue_config_input_file" << std::endl;
    return -1;
  }

  BBPSDKReader bbpReader;
  Columns columns;
  SimulationData simulationData;

  bbpReader.readFromBlueConfig( columns,
                                simulationData,
                                argv[1],
                                LoadFlags::SIMULATION_DATA,
                                "Layer1",
                                "voltage" );

  std::pair<SimulationData::iterator, SimulationData::iterator>
    simDataIteratorPair = simulationData.findByRange(0.0f, 80.0f);

  std::cout << std::endl;

  std::cout << "BEGIN simulationDataLoad" << std::endl << std::endl;

  int positiveVoltage = 0;
  int negativeVoltage = 0;
  while ( simDataIteratorPair.first != simDataIteratorPair.second )
  {
    std::cout << *simDataIteratorPair.first << std::endl << std::endl;
    if ( (*simDataIteratorPair.first).value < 0 )
      negativeVoltage++;
    else
      positiveVoltage++;
    ++simDataIteratorPair.first;
  }

  std::cout << std::endl;

  std::cout << "Positives: " << positiveVoltage << std::endl;
  std::cout << "Negatives: " << negativeVoltage << std::endl;

  std::cout << std::endl;

  std::cout << "END simulationDataLoad" << std::endl;

  /*
  // Entire multi index printed
  for ( SimulationData::iterator
        recordIterator = simulationData.begin();
        recordIterator != simulationData.end();
        ++recordIterator )
  {
    std::cout << *recordIterator << std::endl << std::endl;
  }
  */

  return 0;
}
