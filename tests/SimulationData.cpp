/**
 * @file    SimulationData.cpp
 * @brief   Unit test for class nsol::SimulationData
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

/**
 * define section
 */
//#define EXAMPLE 4

/*
BOOST_AUTO_TEST_CASE( simulation_data_constructor )
{
}
*/

BOOST_AUTO_TEST_CASE( simulation_data_insert )
{
  SimulationData simData1;
  SimulationData simData2;
  SimulationData simData3;

  SimulationData::Record r1(0.0f, "Voltaje", 3, 11);
  SimulationData::Record r2(1.0f, "Plasticidad", 2, 22);
  SimulationData::Record r3(2.0f, "Calcio", 1, 33);

  simData1.insert(r1);
  simData1.insert(r2);
  simData1.insert(r3);

  simData2.insert(r1);
  simData2.insert(r2);

  simData3.insert(r2);
  simData3.insert(r3);

  /* Size checking */
  BOOST_CHECK_EQUAL(simData1.numberOfRecords(), 3);
  BOOST_CHECK_EQUAL(simData2.numberOfRecords(), 2);
  BOOST_CHECK_EQUAL(simData3.numberOfRecords(), 2);

  /* Size comparing */
  BOOST_CHECK(simData1.numberOfRecords() != simData2.numberOfRecords());
  BOOST_CHECK_EQUAL(simData2.numberOfRecords(), simData3.numberOfRecords());

  SimulationData::iterator
  wantedRecord =
    simData1.find(1.0f, "Plasticidad", 2);

  /* Looking for the value of an inserted record */
  BOOST_CHECK_EQUAL((*wantedRecord).value, 22);

  r2.value = 44;

  simData1.insert(r2);

  SimulationData::iterator
    replacedRecord =
      simData1.find(1.0f, "Plasticidad", 2);

  /* Looking for the replaced value of a specific record */
  BOOST_CHECK_EQUAL((*replacedRecord).value, 44);
  /* It is not necessary to find twice */
  BOOST_CHECK_EQUAL((*wantedRecord).value, 44);
}

BOOST_AUTO_TEST_CASE( simulation_data_erase )
{
  SimulationData simData;

  SimulationData::Record r1(0.0f, "Voltaje", 3, 11);
  SimulationData::Record r2(1.0f, "Plasticidad", 2, 22);
  SimulationData::Record r3(2.0f, "Calcio", 1, 33);

  simData.insert(r1);
  simData.insert(r2);
  simData.insert(r3);

  /* Trying to erase a record that does not exist */
  simData.erase(2.0f, "Calcio", 5);

  /* Checking size before erasing */
  BOOST_CHECK_EQUAL(simData.numberOfRecords(), 3);

  simData.erase(2.0f, "Calcio", 1);

  /* Checking size after erasing */
  BOOST_CHECK_EQUAL(simData.numberOfRecords(), 2);
}

BOOST_AUTO_TEST_CASE( simulation_data_clear )
{
  SimulationData simData;

  SimulationData::Record r1(0.0f, "Voltaje", 3, 11);
  SimulationData::Record r2(1.0f, "Plasticidad", 2, 22);
  SimulationData::Record r3(2.0f, "Calcio", 1, 33);

  simData.insert(r1);
  simData.insert(r2);
  simData.insert(r3);

  /* Checking size before clearing */
  BOOST_CHECK_EQUAL(simData.numberOfRecords(), 3);

  simData.clear();

  /* Checking size after clearing */
  BOOST_CHECK_EQUAL(simData.numberOfRecords(), 0);
}

BOOST_AUTO_TEST_CASE( simulation_data_find )
{
  SimulationData simData;

  SimulationData::Record r1(0.0f, "Voltaje", 5, 11);
  SimulationData::Record r2(1.0f, "Plasticidad", 2, 22);
  SimulationData::Record r3(2.0f, "Calcio", 1, 33);
  SimulationData::Record r4(2.0f, "Calcio", 3, 44);
  SimulationData::Record r5(2.0f, "Voltaje", 5, 55);
  SimulationData::Record r6(2.0f, "Plasticidad", 1, 66);

  simData.insert(r1);
  simData.insert(r2);
  simData.insert(r3);
  simData.insert(r4);
  simData.insert(r5);
  simData.insert(r6);

  /**
   * Looking for a record by its timestamp, label and nsobject
   */
  SimulationData::iterator
    wantedRecord1 =
      simData.find(2.0f, "Calcio", 1);
  /* Checking by record value */
  BOOST_CHECK_EQUAL((*wantedRecord1).value, 33);

  /**
   * Looking for records by their timestamps and labels
   */
  std::pair<SimulationData::iterator,
            SimulationData::iterator>
    wantedRecord2 =
      simData.find(2.0f, "Calcio");
  /* Checking by record values */
  int wantedValue2 = 33;
  while ( wantedRecord2.first != wantedRecord2.second)
  {
    BOOST_CHECK_EQUAL((*wantedRecord2.first).value, wantedValue2);
    ++wantedRecord2.first;
    wantedValue2 += 11;
  }

  /**
   * Looking for records by their labels and nsobjects
   */
  std::pair<SimulationData::iterator,
            SimulationData::iterator>
    wantedRecord3 =
      simData.find("Voltaje", 5);
  /* Checking by record values */
  int wantedValue3 = 11;
  while ( wantedRecord3.first != wantedRecord3.second)
  {
    BOOST_CHECK_EQUAL((*wantedRecord3.first).value, wantedValue3);
    ++wantedRecord3.first;
    wantedValue3 += 44;
  }

  /**
   * Looking for records by their timestamps and nsobjects
   */
  std::pair<SimulationData::iterator,
            SimulationData::iterator>
    wantedRecord4 =
      simData.find(2.0f, 1);
  /* Checking by record values */
  int wantedValue4 = 33;
  while ( wantedRecord4.first != wantedRecord4.second)
  {
    BOOST_CHECK_EQUAL((*wantedRecord4.first).value, wantedValue4);
    ++wantedRecord4.first;
    wantedValue4 += 33;
  }

  /**
   * Looking for records by their timestamps
   */
  std::pair<SimulationData::iterator,
            SimulationData::iterator>
    wantedRecord5 =
      simData.find(2.0f);
  /* Checking by record values */
  int wantedValues5 [4] = {33, 44, 66, 55};
  int wantedValues5_index = 0;
  while ( wantedRecord5.first != wantedRecord5.second)
  {
    BOOST_CHECK_EQUAL((*wantedRecord5.first).value,
                      wantedValues5[wantedValues5_index]);
    ++wantedRecord5.first;
    wantedValues5_index++;
  }

  /**
   * Looking for records by their labels
   */
  std::pair<SimulationData::iterator,
            SimulationData::iterator>
    wantedRecord6 =
      simData.find("Voltaje");
  /* Checking by record values */
  int wantedValue6 = 11;
  while ( wantedRecord6.first != wantedRecord6.second)
  {
    BOOST_CHECK_EQUAL((*wantedRecord6.first).value, wantedValue6);
    ++wantedRecord6.first;
    wantedValue6 += 44;
  }

  /**
   * Looking for records by their nsobjects
   */
  std::pair<SimulationData::iterator,
            SimulationData::iterator>
    wantedRecord7 =
      simData.find(1);
  /* Checking by record values */
  int wantedValue7 = 33;
  while ( wantedRecord7.first != wantedRecord7.second)
  {
    BOOST_CHECK_EQUAL((*wantedRecord7.first).value, wantedValue7);
    ++wantedRecord7.first;
    wantedValue7 += 33;
  }
}

BOOST_AUTO_TEST_CASE( simulation_data_findByRange )
{
  SimulationData simData;

  SimulationData::Record r1(0.0f, "Voltaje", 5, 11);
  SimulationData::Record r2(1.0f, "Plasticidad", 2, 22);
  SimulationData::Record r3(2.0f, "Calcio", 1, 33);
  SimulationData::Record r4(3.0f, "Calcio", 3, 44);
  SimulationData::Record r5(4.0f, "Voltaje", 5, 55);
  SimulationData::Record r6(5.0f, "Plasticidad", 1, 66);

  simData.insert(r1);
  simData.insert(r2);
  simData.insert(r3);
  simData.insert(r4);
  simData.insert(r5);
  simData.insert(r6);

  /**
   * Looking for records by their timestamps delimited by
   * a lower bound and an upper bound.
   */
  std::pair<SimulationData::iterator,
            SimulationData::iterator>
    wantedRecord1 =
      simData.findByRange(2.0f, 4.0f);
  /* Checking by record values */
  int wantedValue1 = 33;
  int numberOfElements = 0;
  while ( wantedRecord1.first != wantedRecord1.second)
  {
    BOOST_CHECK_EQUAL((*wantedRecord1.first).value, wantedValue1);
    ++wantedRecord1.first;
    wantedValue1 += 11;
    ++numberOfElements;
  }
  BOOST_CHECK_EQUAL(numberOfElements, 3);
}

BOOST_AUTO_TEST_CASE( simulation_data_getTimestamps )
{
  SimulationData simData;

  SimulationData::Record r1(0.0f, "Voltaje", 5, 11);
  SimulationData::Record r2(1.0f, "Plasticidad", 2, 22);
  SimulationData::Record r3(2.0f, "Calcio", 1, 33);
  SimulationData::Record r4(2.0f, "Calcio", 3, 44);
  SimulationData::Record r5(4.0f, "Voltaje", 5, 55);
  SimulationData::Record r6(5.0f, "Plasticidad", 1, 66);
  SimulationData::Record r7(5.0f, "Voltaje", 2, 77);

  simData.insert(r1);
  simData.insert(r2);
  simData.insert(r3);
  simData.insert(r4);
  simData.insert(r5);
  simData.insert(r6);
  simData.insert(r7);

  std::set<float> timestampSet =
    simData.getTimestamps();

  float wantedValues [5] = {0.0f, 1.0f, 2.0f, 4.0f, 5.0f};

  int index = 0;

  for( std::set<float>::iterator
      it = timestampSet.begin();
      it != timestampSet.end();
      ++it)
  {
    BOOST_CHECK_EQUAL(*it, wantedValues[index]);
    index++;
  }
}

BOOST_AUTO_TEST_CASE( simulation_data_getLabels )
{
  SimulationData simData;

  SimulationData::Record r1(0.0f, "Voltaje", 5, 11);
  SimulationData::Record r2(1.0f, "Plasticidad", 2, 22);
  SimulationData::Record r3(2.0f, "Calcio", 1, 33);
  SimulationData::Record r4(2.0f, "Calcio", 3, 44);
  SimulationData::Record r5(4.0f, "Voltaje", 5, 55);
  SimulationData::Record r6(5.0f, "Plasticidad", 1, 66);
  SimulationData::Record r7(5.0f, "Voltaje", 2, 77);

  simData.insert(r1);
  simData.insert(r2);
  simData.insert(r3);
  simData.insert(r4);
  simData.insert(r5);
  simData.insert(r6);
  simData.insert(r7);

  std::set<std::string> labelSet =
    simData.getLabels();

  std::vector<std::string> wantedValues;

  wantedValues.push_back("Calcio");
  wantedValues.push_back("Plasticidad");
  wantedValues.push_back("Voltaje");

  int index = 0;

  for(std::set<std::string>::iterator
      it = labelSet.begin();
      it != labelSet.end();
      ++it)
  {
    BOOST_CHECK_EQUAL(*it, wantedValues.at(index));
    index++;
  }
}
