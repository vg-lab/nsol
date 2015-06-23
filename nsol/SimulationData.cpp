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

  /**
   * class iterator. method implementations.
   */

  SimulationData::iterator::iterator( void )
  {
  }

  SimulationData::iterator::iterator
  ( const iterator& extIterator )
  {
    *this = extIterator;
  }

  SimulationData::iterator::~iterator( void )
  {
  }

//  SimulationData::iterator::iterator
//  ( SimulationData::MultiIndexByTimestamp::iterator itByTimestamp )
//  {
//    _usedIterator = IT_TIMESTAMP;
//    _itByTimestamp = itByTimestamp;
//  }
//
//  SimulationData::iterator::iterator
//  ( SimulationData::MultiIndexByLabel::iterator itByLabel )
//  {
//    _usedIterator = IT_LABEL;
//    _itByLabel = itByLabel;
//  }
//
//  SimulationData::iterator::iterator
//  ( SimulationData::MultiIndexByNsobject::iterator itByNsobject )
//  {
//    _usedIterator = IT_OBJECT;
//    _itByNsobject = itByNsobject;
//  }

  SimulationData::MultiIndexByTimestamp::iterator
  SimulationData::iterator::getItByTimestamp() const
  {
  return _itByTimestamp;
  }

  SimulationData::MultiIndexByLabel::iterator
  SimulationData::iterator::getItByLabel() const
  {
    return _itByLabel;
  }

  SimulationData::MultiIndexByNsobject::iterator
  SimulationData::iterator::getItByNsobject() const
  {
  return _itByNsobject;
  }

  SimulationData::iterator::TMultiIndexIterator
  SimulationData::iterator::getUsedIterator() const
  {
  return _usedIterator;
  }

  void SimulationData::iterator::setItByTimestamp(
      const MultiIndexByTimestamp::iterator& itByTimestamp)
  {
    _itByTimestamp = itByTimestamp;
    _usedIterator = IT_TIMESTAMP;
  }

  void SimulationData::iterator::setItByLabel(
      const MultiIndexByLabel::iterator& itByLabel)
  {
    _itByLabel = itByLabel;
    _usedIterator = IT_LABEL;
  }

  void SimulationData::iterator::setItByNsobject(
      const MultiIndexByNsobject::iterator& itByNsobject)
  {
    _itByNsobject = itByNsobject;
    _usedIterator = IT_OBJECT;
  }

  SimulationData::iterator& SimulationData::iterator::operator++()
  {
    switch(_usedIterator)
    {
      case IT_TIMESTAMP:
        ++_itByTimestamp;
      break;
      case IT_LABEL:
        ++_itByLabel;
      break;
      case IT_OBJECT:
        ++_itByNsobject;
      break;
      default:
        // Lanzar excepción
      break;
    }
    return *this;
  }

  void SimulationData::iterator::operator=
  ( const SimulationData::iterator& extIterator )
  {
    _usedIterator = extIterator.getUsedIterator();
    _itByTimestamp = extIterator.getItByTimestamp();
    _itByLabel = extIterator.getItByLabel();
    _itByNsobject = extIterator.getItByNsobject();
  }

  bool SimulationData::iterator::operator==
  ( const SimulationData::iterator& extIterator ) const
  {
    if(_usedIterator != extIterator.getUsedIterator())
    {
      //Se devolvería algún tipo de excepción?
      return false;
    }
    switch(_usedIterator)
    {
      case IT_TIMESTAMP:
        return _itByTimestamp == extIterator.getItByTimestamp();
      break;
      case IT_LABEL:
        return _itByLabel == extIterator.getItByLabel();
      break;
      case IT_OBJECT:
        return _itByNsobject == extIterator.getItByNsobject();
      break;
      default:
        // Que devolver aquí?
        return false;
      break;
    }
  }

  bool SimulationData::iterator::operator!=
  ( const SimulationData::iterator& extIterator ) const
  {
    if(_usedIterator != extIterator.getUsedIterator())
    {
      //Se devolvería algún tipo de excepción?
      return true;
    }
    switch(_usedIterator)
    {
      case IT_TIMESTAMP:
        return _itByTimestamp != extIterator.getItByTimestamp();
      break;
      case IT_LABEL:
        return _itByLabel != extIterator.getItByLabel();
      break;
      case IT_OBJECT:
        return _itByNsobject != extIterator.getItByNsobject();
      break;
      default:
        // Que devolver aquí?
        return true;
      break;
    }
  }

  const SimulationData::Record& SimulationData::iterator::operator*() const
  {
    switch(_usedIterator)
    {
      case IT_TIMESTAMP:
        return *_itByTimestamp;
      break;
      case IT_LABEL:
        return *_itByLabel;
      break;
      case IT_OBJECT:
        return *_itByNsobject;
      break;
      default:
        // Lanzar excepción
        return *_itByTimestamp;
      break;
    }
  }

  /**
   * class SimulationData. method implementations.
   */

  SimulationData::SimulationData( void )
  {
  }

  SimulationData::~SimulationData( void )
  {
  }

  std::size_t SimulationData::numberOfRecords() const
  {
    return _multiIndexByTimestamp.size();
  }

  void SimulationData::insert( Record& record )
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

  /*
  void SimulationData::remove( const Record& record )
  {
    _multiIndexByTimestamp.remove(record);
    _multiIndexByLabel.remove(record);
    _multiIndexByNsobject.remove(record);
  }
  */

  void SimulationData::clear( void )
  {
    _multiIndexByTimestamp.clear();
    _multiIndexByLabel.clear();
    _multiIndexByNsobject.clear();
  }

  SimulationData::iterator
  SimulationData::find( float timestamp,
                        std::string label,
                        int nsobject ) const
  {
    SimulationData::MultiIndexByTimestamp::iterator recordToFind =
      _multiIndexByTimestamp.find(boost::make_tuple(timestamp,
                                                    label,
                                                    nsobject));
    SimulationData::iterator toReturn;
    toReturn.setItByTimestamp(recordToFind);

    //Devolver excepción si no encuentra el elemento?
    return toReturn;
  }

  std::pair<SimulationData::iterator,
            SimulationData::iterator>
  SimulationData::find( float timestamp, std::string label ) const
  {
    std::pair<SimulationData::MultiIndexByTimestamp::iterator,
              SimulationData::MultiIndexByTimestamp::iterator>
    recordsToFind =
      _multiIndexByTimestamp.equal_range(boost::make_tuple(timestamp,
                                                           label));
    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByTimestamp(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByTimestamp(recordsToFind.second);

    std::pair<SimulationData::iterator,
              SimulationData::iterator>
    toReturn(toReturnFirst, toReturnSecond);

    return toReturn;
  }

  std::pair<SimulationData::iterator,
            SimulationData::iterator>
  SimulationData::find( std::string label, int nsobject ) const
  {
    std::pair<SimulationData::MultiIndexByLabel::iterator,
              SimulationData::MultiIndexByLabel::iterator>
    recordsToFind =
      _multiIndexByLabel.equal_range(boost::make_tuple(label,
                                                       nsobject));

    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByLabel(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByLabel(recordsToFind.second);

    std::pair<SimulationData::iterator,
              SimulationData::iterator>
    toReturn(toReturnFirst, toReturnSecond);

    return toReturn;
  }

  std::pair<SimulationData::iterator,
            SimulationData::iterator>
  SimulationData::find( float timestamp, int nsobject ) const
  {
    std::pair<SimulationData::MultiIndexByNsobject::iterator,
              SimulationData::MultiIndexByNsobject::iterator>
    recordsToFind =
      _multiIndexByNsobject.equal_range(boost::make_tuple(nsobject,
                                                          timestamp));

    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByNsobject(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByNsobject(recordsToFind.second);

    std::pair<SimulationData::iterator,
              SimulationData::iterator>
    toReturn(toReturnFirst, toReturnSecond);

    return toReturn;
  }

  std::pair<SimulationData::iterator,
            SimulationData::iterator>
  SimulationData::find( float timestamp ) const
  {
    std::pair<SimulationData::MultiIndexByTimestamp::iterator,
              SimulationData::MultiIndexByTimestamp::iterator>
    recordsToFind =
      _multiIndexByTimestamp.equal_range(timestamp);

    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByTimestamp(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByTimestamp(recordsToFind.second);

    std::pair<SimulationData::iterator,
              SimulationData::iterator>
    toReturn(toReturnFirst, toReturnSecond);

    return toReturn;
  }

  std::pair<SimulationData::iterator,
            SimulationData::iterator>
  SimulationData::find( std::string label ) const
  {
    std::pair<SimulationData::MultiIndexByLabel::iterator,
              SimulationData::MultiIndexByLabel::iterator>
    recordsToFind =
      _multiIndexByLabel.equal_range(label);

    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByLabel(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByLabel(recordsToFind.second);

    std::pair<SimulationData::iterator,
              SimulationData::iterator>
    toReturn(toReturnFirst, toReturnSecond);

    return toReturn;
  }

  std::pair<SimulationData::iterator,
            SimulationData::iterator>
  SimulationData::find( int nsobject ) const
  {
    std::pair<SimulationData::MultiIndexByNsobject::iterator,
              SimulationData::MultiIndexByNsobject::iterator>
    recordsToFind =
      _multiIndexByNsobject.equal_range(nsobject);

    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByNsobject(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByNsobject(recordsToFind.second);

    std::pair<SimulationData::iterator,
              SimulationData::iterator>
    toReturn(toReturnFirst, toReturnSecond);

    return toReturn;
  }

} // namespace nsol


