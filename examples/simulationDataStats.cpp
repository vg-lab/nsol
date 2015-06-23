/**
 * @file    simulationDataStats.cpp
 * @brief   Stress test for class nsol::SimulationData
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include <nsol/nsol.h>
#include <chrono>

using namespace nsol;

void generateRandomString(char* s, const int len) {
  const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
}

int main ( /*int argc, char ** argv*/ )
{

  const int NUMBER_OF_RECORDS = 100000;

  const int NUMBER_OF_TIMESTAMPS = 30000;

  const int NUMBER_OF_LABELS = 10;
  const int LABEL_SIZE = 10;

  const int NUMBER_OF_NSOBJECTS = 1000;

  const int NUMBER_OF_TESTS = 25;

  SimulationData simData;

  std::vector<std::string> randomLabels;

  for(int i = 0; i < NUMBER_OF_LABELS; i++)
  {
    char randomString[LABEL_SIZE];
    generateRandomString(randomString, LABEL_SIZE);
    std::string str(randomString);
    randomLabels.push_back(str);
  }

  for(int r = 0; r < NUMBER_OF_RECORDS; r++)
  {
    float randomTimestamp =
      (float) (rand()%NUMBER_OF_TIMESTAMPS);

    std::string randomLabel =
      randomLabels.at(rand()%NUMBER_OF_LABELS);

    int randomNsobject =
      rand()%NUMBER_OF_NSOBJECTS;

    SimulationData::Record* randomRecord =
      new SimulationData::Record(randomTimestamp,
                                 randomLabel,
                                 randomNsobject,
                                 r);

    simData.insert(*randomRecord);
  }

  std::cout << "simData size: " << simData.numberOfRecords() << std::endl;

  std::cout << std::endl;

  for(int f = 0; f < NUMBER_OF_TESTS; f++)
  {
    float randomTimestamp =
          (float) (rand()%NUMBER_OF_TIMESTAMPS);

    std::string randomLabel =
          randomLabels.at(rand()%NUMBER_OF_LABELS);

    int randomNsobject =
          rand()%NUMBER_OF_NSOBJECTS;

    std::cout << "Test " << f << "." << std::endl;

    std::cout << "ts = " << randomTimestamp << ". "
              << "lb = " << randomLabel << ". "
              << "ns = " << randomNsobject << "."
              << std::endl;

    /**
     * Looking for a record by its timestamp, label and nsobject
     */
    std::chrono::high_resolution_clock::time_point tBegin1 =
      std::chrono::high_resolution_clock::now();
    //SimulationData::iterator
      //wantedRecord1 =
        simData.find(randomTimestamp,
                     randomLabel,
                     randomNsobject);
    std::chrono::high_resolution_clock::time_point tEnd1 =
      std::chrono::high_resolution_clock::now();

    auto duration1 =
      std::chrono::duration_cast<std::chrono::nanoseconds>
      ( tEnd1 - tBegin1 ).count();

    std::cout << "Test " << f
      << ". ts-lb-ns: " << duration1 << " nanoseconds." << std::endl;

    /**
     * Looking for records by their timestamps and labels
     */
    std::chrono::high_resolution_clock::time_point tBegin2 =
      std::chrono::high_resolution_clock::now();
    //std::pair<SimulationData::iterator,
      //        SimulationData::iterator>
      //wantedRecord2 =
        simData.find(randomTimestamp,
                     randomLabel);
    std::chrono::high_resolution_clock::time_point tEnd2 =
      std::chrono::high_resolution_clock::now();

    auto duration2 =
      std::chrono::duration_cast<std::chrono::nanoseconds>
      ( tEnd2 - tBegin2 ).count();

    std::cout << "Test " << f
      << ". ts-lb: " << duration2 << " nanoseconds." << std::endl;

    /**
     * Looking for records by their labels and nsobjects
     */
    std::chrono::high_resolution_clock::time_point tBegin3 =
      std::chrono::high_resolution_clock::now();
    //std::pair<SimulationData::iterator,
      //        SimulationData::iterator>
      //wantedRecord3 =
        simData.find(randomLabel,
                     randomNsobject);
    std::chrono::high_resolution_clock::time_point tEnd3 =
      std::chrono::high_resolution_clock::now();

    auto duration3 =
      std::chrono::duration_cast<std::chrono::nanoseconds>
      ( tEnd3 - tBegin3 ).count();

    std::cout << "Test " << f
      << ". lb-ns: " << duration3 << " nanoseconds." << std::endl;

    /**
     * Looking for records by their timestamps and nsobjects
     */
    std::chrono::high_resolution_clock::time_point tBegin4 =
      std::chrono::high_resolution_clock::now();
    //std::pair<SimulationData::iterator,
      //        SimulationData::iterator>
      //wantedRecord4 =
        simData.find(randomTimestamp,
                     randomNsobject);
    std::chrono::high_resolution_clock::time_point tEnd4 =
      std::chrono::high_resolution_clock::now();

    auto duration4 =
      std::chrono::duration_cast<std::chrono::nanoseconds>
      ( tEnd4 - tBegin4 ).count();

    std::cout << "Test " << f
      << ". ts-ns: " << duration4 << " nanoseconds." << std::endl;

    /**
     * Looking for records by their timestamps
     */
    std::chrono::high_resolution_clock::time_point tBegin5 =
      std::chrono::high_resolution_clock::now();
    //std::pair<SimulationData::iterator,
      //        SimulationData::iterator>
      //wantedRecord5 =
        simData.find(randomTimestamp);
    std::chrono::high_resolution_clock::time_point tEnd5 =
      std::chrono::high_resolution_clock::now();

    auto duration5 =
      std::chrono::duration_cast<std::chrono::nanoseconds>
      ( tEnd5 - tBegin5 ).count();

    std::cout << "Test " << f
      << ". ts: " << duration5 << " nanoseconds." << std::endl;

    /**
     * Looking for records by their labels
     */
    std::chrono::high_resolution_clock::time_point tBegin6 =
      std::chrono::high_resolution_clock::now();
    //std::pair<SimulationData::iterator,
      //        SimulationData::iterator>
      //wantedRecord6 =
        simData.find(randomLabel);
    std::chrono::high_resolution_clock::time_point tEnd6 =
      std::chrono::high_resolution_clock::now();

    auto duration6 =
      std::chrono::duration_cast<std::chrono::nanoseconds>
      ( tEnd6 - tBegin6 ).count();

    std::cout << "Test " << f
      << ". lb: " << duration6 << " nanoseconds." << std::endl;

    /**
     * Looking for records by their nsobjects
     */
    std::chrono::high_resolution_clock::time_point tBegin7 =
      std::chrono::high_resolution_clock::now();
    //std::pair<SimulationData::iterator,
      //        SimulationData::iterator>
      //wantedRecord7 =
        simData.find(randomNsobject);
    std::chrono::high_resolution_clock::time_point tEnd7 =
      std::chrono::high_resolution_clock::now();

    auto duration7 =
      std::chrono::duration_cast<std::chrono::nanoseconds>
      ( tEnd7 - tBegin7 ).count();

    std::cout << "Test " << f
      << ". ns: " << duration7 << " nanoseconds." << std::endl;

    std::cout << std::endl;
  }

  return 0;
}
