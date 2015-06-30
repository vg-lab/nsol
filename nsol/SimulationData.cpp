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

  SimulationData::MultiIndexByObject::iterator
  SimulationData::iterator::getItByObject() const
  {
    return _itByObject;
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

  void SimulationData::iterator::setItByObject(
      const MultiIndexByObject::iterator& itByObject)
  {
    _itByObject = itByObject;
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
        ++_itByObject;
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
    _itByObject = extIterator.getItByObject();
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
        return _itByObject == extIterator.getItByObject();
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
        return _itByObject != extIterator.getItByObject();
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
        return *_itByObject;
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
                                                    record.object));

    if ( oldRecordByTimestamp == _multiIndexByTimestamp.end() )
    {
      _multiIndexByTimestamp.insert(record);
      _multiIndexByLabel.insert(record);
      _multiIndexByObject.insert(record);
    }
    else
    {
      MultiIndexByLabel::iterator oldRecordByLabel =
        _multiIndexByLabel.find(boost::make_tuple(record.label,
                                                  record.object,
                                                  record.timestamp));

      MultiIndexByObject::iterator oldRecordByObject =
        _multiIndexByObject.find(boost::make_tuple(record.object,
                                                     record.timestamp,
                                                     record.label));

      _multiIndexByTimestamp.replace(oldRecordByTimestamp, record);
      _multiIndexByLabel.replace(oldRecordByLabel, record);
      _multiIndexByObject.replace(oldRecordByObject, record);
    }
  }

  void SimulationData::erase( float timestamp,
                              std::string label,
                              ObjectPtr object )
  {
    MultiIndexByTimestamp::iterator recordToEraseByTimestamp =
      _multiIndexByTimestamp.find(boost::make_tuple(timestamp,
                                                    label,
                                                    object));

    if ( recordToEraseByTimestamp != _multiIndexByTimestamp.end() )
    {
      MultiIndexByLabel::iterator recordToEraseByLabel =
        _multiIndexByLabel.find(boost::make_tuple(label,
                                                  object,
                                                  timestamp));

      MultiIndexByObject::iterator recordToEraseObject =
        _multiIndexByObject.find(boost::make_tuple(object,
                                                   timestamp,
                                                   label));

      _multiIndexByTimestamp.erase(recordToEraseByTimestamp);
      _multiIndexByLabel.erase(recordToEraseByLabel);
      _multiIndexByObject.erase(recordToEraseObject);
    }
  }

  /*
  void SimulationData::remove( const Record& record )
  {
    _multiIndexByTimestamp.remove(record);
    _multiIndexByLabel.remove(record);
    _multiIndexByObject.remove(record);
  }
  */

  void SimulationData::clear( void )
  {
    _multiIndexByTimestamp.clear();
    _multiIndexByLabel.clear();
    _multiIndexByObject.clear();
  }

  SimulationData::iterator SimulationData::begin()
  {
    SimulationData::iterator toReturn;
    toReturn.setItByTimestamp(_multiIndexByTimestamp.begin());

    return toReturn;
  }

  SimulationData::iterator SimulationData::end()
  {
    SimulationData::iterator toReturn;
    toReturn.setItByTimestamp(_multiIndexByTimestamp.end());

    return toReturn;
  }


  SimulationData::iterator
  SimulationData::find( float timestamp,
                        std::string label,
                        ObjectPtr object ) const
  {
    SimulationData::MultiIndexByTimestamp::iterator recordToFind =
      _multiIndexByTimestamp.find(boost::make_tuple(timestamp,
                                                    label,
                                                    object));
    SimulationData::iterator toReturn;
    toReturn.setItByTimestamp(recordToFind);

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
  SimulationData::find( std::string label, ObjectPtr object ) const
  {
    std::pair<SimulationData::MultiIndexByLabel::iterator,
              SimulationData::MultiIndexByLabel::iterator>
    recordsToFind =
      _multiIndexByLabel.equal_range(boost::make_tuple(label,
                                                       object));

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
  SimulationData::find( float timestamp, ObjectPtr object ) const
  {
    std::pair<SimulationData::MultiIndexByObject::iterator,
              SimulationData::MultiIndexByObject::iterator>
    recordsToFind =
      _multiIndexByObject.equal_range(boost::make_tuple(object,
                                                        timestamp));

    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByObject(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByObject(recordsToFind.second);

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
  SimulationData::find( ObjectPtr object ) const
  {
    std::pair<SimulationData::MultiIndexByObject::iterator,
              SimulationData::MultiIndexByObject::iterator>
    recordsToFind =
        _multiIndexByObject.equal_range(object);

    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByObject(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByObject(recordsToFind.second);

    std::pair<SimulationData::iterator,
              SimulationData::iterator>
    toReturn(toReturnFirst, toReturnSecond);

    return toReturn;
  }

  std::pair<SimulationData::iterator,
            SimulationData::iterator>
  SimulationData::findByRange( float lowerTimestamp,
                               float upperTimestamp ) const
  {
    std::pair<SimulationData::MultiIndexByTimestamp::iterator,
              SimulationData::MultiIndexByTimestamp::iterator>
    recordsToFind =
      std::make_pair(_multiIndexByTimestamp.lower_bound(lowerTimestamp),
                     _multiIndexByTimestamp.upper_bound(upperTimestamp));

    SimulationData::iterator toReturnFirst;
    toReturnFirst.setItByTimestamp(recordsToFind.first);

    SimulationData::iterator toReturnSecond;
    toReturnSecond.setItByTimestamp(recordsToFind.second);

    std::pair<SimulationData::iterator,
              SimulationData::iterator>
    toReturn(toReturnFirst, toReturnSecond);

    return toReturn;
  }

  std::set<float> SimulationData::getTimestamps() const
  {
    std::set<float> toReturn;

    for( SimulationData::MultiIndexByTimestamp::iterator
         it = _multiIndexByTimestamp.begin();
         it != _multiIndexByTimestamp.end();
         ++it )
    {
      toReturn.insert(it->timestamp);
    }

    return toReturn;
  }

  std::set<std::string> SimulationData::getLabels() const
  {
    std::set<std::string> toReturn;

    for( SimulationData::MultiIndexByLabel::iterator
         it = _multiIndexByLabel.begin();
         it != _multiIndexByLabel.end();
         ++it )
    {
      toReturn.insert(it->label);
    }

    return toReturn;
  }

} // namespace nsol


