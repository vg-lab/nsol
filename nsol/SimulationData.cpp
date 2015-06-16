/**
 * @file    SimulationData.cpp
 * @brief
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#include "SimulationData.h"

namespace nsol
{

  SimulationData::SimulationData( void )
  {
  }

  SimulationData::~SimulationData( void )
  {
  }

  std::size_t SimulationData::numberOfRecords()
  {
    return _multiIndexByTimestamp.size();
  }

  void SimulationData::insert( Record record )
  {
    /**
     * Lo ideal aquí sería usar el find nuestro pero para ello
     * tambien necesitaríamos un replace nuestro
     */
    MultiIndexByTimestamp::iterator oldRecordByTimestamp =
      _multiIndexByTimestamp.find(boost::make_tuple(record.timestamp,
                                                    record.label,
                                                    record.nsobject));

    if ( oldRecordByTimestamp == _multiIndexByTimestamp.end() )
    {
      _multiIndexByTimestamp.insert(record);
      _multiIndexByLabel.insert(record);
      _multiIndexByNsobject.insert(record);
    }
    else
    {
      MultiIndexByLabel::iterator oldRecordByLabel =
        _multiIndexByLabel.find(boost::make_tuple(record.label,
                                                  record.nsobject,
                                                  record.timestamp));

      MultiIndexByNsobject::iterator oldRecordByNsobject =
        _multiIndexByNsobject.find(boost::make_tuple(record.nsobject,
                                                     record.timestamp,
                                                     record.label));

      _multiIndexByTimestamp.replace(oldRecordByTimestamp, record);
      _multiIndexByLabel.replace(oldRecordByLabel, record);
      _multiIndexByNsobject.replace(oldRecordByNsobject, record);
    }
  }

  void SimulationData::erase( float timestamp,
                              std::string label,
                              int nsobject )
  {
    MultiIndexByTimestamp::iterator recordToEraseByTimestamp =
      _multiIndexByTimestamp.find(boost::make_tuple(timestamp,
                                                    label,
                                                    nsobject));

    if ( recordToEraseByTimestamp != _multiIndexByTimestamp.end() )
    {
      MultiIndexByLabel::iterator recordToEraseByLabel =
        _multiIndexByLabel.find(boost::make_tuple(label,
                                                  nsobject,
                                                  timestamp));

      MultiIndexByNsobject::iterator recordToEraseNsobject =
        _multiIndexByNsobject.find(boost::make_tuple(nsobject,
                                                     timestamp,
                                                     label));

      _multiIndexByTimestamp.erase(recordToEraseByTimestamp);
      _multiIndexByLabel.erase(recordToEraseByLabel);
      _multiIndexByNsobject.erase(recordToEraseNsobject);
    }
  }

  void SimulationData::clear( void )
  {
    _multiIndexByTimestamp.clear();
    _multiIndexByLabel.clear();
    _multiIndexByNsobject.clear();
  }

  SimulationData::MultiIndexByTimestamp::iterator
  SimulationData::find( float timestamp,
                        std::string label,
                        int nsobject ) const
  {
    SimulationData::MultiIndexByTimestamp::iterator recordToFind =
      _multiIndexByTimestamp.find(boost::make_tuple(timestamp,
                                                    label,
                                                    nsobject));

    //Que pasa si no encuentra el elemento?
    return recordToFind;
  }

  std::pair<SimulationData::MultiIndexByTimestamp::iterator,
            SimulationData::MultiIndexByTimestamp::iterator>
  SimulationData::find( float timestamp, std::string label ) const
  {
    std::pair<SimulationData::MultiIndexByTimestamp::iterator,
              SimulationData::MultiIndexByTimestamp::iterator>
    recordsToFind =
      _multiIndexByTimestamp.equal_range(boost::make_tuple(timestamp,
                                                           label));

    return recordsToFind;
  }

  std::pair<SimulationData::MultiIndexByLabel::iterator,
            SimulationData::MultiIndexByLabel::iterator>
  SimulationData::find( std::string label, int nsobject ) const
  {
    std::pair<SimulationData::MultiIndexByLabel::iterator,
              SimulationData::MultiIndexByLabel::iterator>
    recordsToFind =
      _multiIndexByLabel.equal_range(boost::make_tuple(label,
                                                       nsobject));

    return recordsToFind;
  }

  std::pair<SimulationData::MultiIndexByNsobject::iterator,
            SimulationData::MultiIndexByNsobject::iterator>
  SimulationData::find( float timestamp, int nsobject ) const
  {
    std::pair<SimulationData::MultiIndexByNsobject::iterator,
              SimulationData::MultiIndexByNsobject::iterator>
    recordsToFind =
      _multiIndexByNsobject.equal_range(boost::make_tuple(nsobject,
                                                          timestamp));

    return recordsToFind;
  }

  std::pair<SimulationData::MultiIndexByTimestamp::iterator,
            SimulationData::MultiIndexByTimestamp::iterator>
  SimulationData::find( float timestamp ) const
  {
    std::pair<SimulationData::MultiIndexByTimestamp::iterator,
              SimulationData::MultiIndexByTimestamp::iterator>
    recordsToFind =
      _multiIndexByTimestamp.equal_range(timestamp);

    return recordsToFind;
  }

  std::pair<SimulationData::MultiIndexByLabel::iterator,
            SimulationData::MultiIndexByLabel::iterator>
  SimulationData::find( std::string label ) const
  {
    std::pair<SimulationData::MultiIndexByLabel::iterator,
              SimulationData::MultiIndexByLabel::iterator>
    recordsToFind =
      _multiIndexByLabel.equal_range(label);

    return recordsToFind;
  }

  std::pair<SimulationData::MultiIndexByNsobject::iterator,
            SimulationData::MultiIndexByNsobject::iterator>
  SimulationData::find( int nsobject ) const
  {
    std::pair<SimulationData::MultiIndexByNsobject::iterator,
              SimulationData::MultiIndexByNsobject::iterator>
    recordsToFind =
      _multiIndexByNsobject.equal_range(nsobject);

    return recordsToFind;
  }

} // namespace nsol



