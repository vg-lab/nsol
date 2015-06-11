/**
 * @file    SimulationData.cpp
 * @brief
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include "SimulationData.h"

SimulationData::SimulationData()
{
}

SimulationData::~SimulationData()
{
}

void SimulationData::insert(Record record)
{
  /**
   * Lo ideal aquí sería usar el find nuestro pero para ello
   * tambien necesitaríamos un replace nuestro
   */
  MultiIndexByTimestamp::iterator oldRecord =
    _multiIndexByTimestamp.find(boost::make_tuple(record.timestamp,
                                                  record.label,
                                                  record.nsobject));

  if (oldRecord == _multiIndexByTimestamp.end())
  {
    _multiIndexByTimestamp.insert(record);
    _multiIndexByLabel.insert(record);
    _multiIndexByNsobject.insert(record);
  }
  else
  {
    _multiIndexByTimestamp.replace(oldRecord, record);
    _multiIndexByLabel.replace(oldRecord, record);
    _multiIndexByNsobject.replace(oldRecord, record);
  }
}

void SimulationData::erase(float timestamp,
                           std::string label,
                           int nsobject)
{
  MultiIndexByTimestamp::iterator recordToErase =
    _multiIndexByTimestamp.find(boost::make_tuple(timestamp,
                                                  label,
                                                  nsobject));

  if (recordToErase != _multiIndexByTimestamp.end())
  {
    _multiIndexByTimestamp.erase(recordToErase);
    _multiIndexByLabel.erase(recordToErase);
    _multiIndexByNsobject.erase(recordToErase);
  }
}

void SimulationData::clear()
{
  _multiIndexByTimestamp.clear();
  _multiIndexByLabel.clear();
  _multiIndexByNsobject.clear();
}
