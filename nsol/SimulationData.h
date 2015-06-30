/**
 * @file    SimulationData.h
 * @brief
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SIMULATIONDATA__
#define __NSOL_SIMULATIONDATA__

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/tuple/tuple.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

#include "Object.h"

namespace nsol
{

  //!  Interface to simulation data.
    /*!
      This class contains simulation data: timestamps, labels,
      nsol objects and values.
    */
  class SimulationData
  {

  public:

    /**
     * Record with simulation data.
     */
    struct Record
    {
      float timestamp;
      std::string label;
      ObjectPtr object;

      int value;

      //Is it necessary?
      Record();

      Record( float timestamp_,
              std::string label_,
              ObjectPtr object_,
              int value_ )
      : timestamp( timestamp_ )
      , label( label_ )
      , object( object_ )
      , value( value_ )
      {}

      friend std::ostream& operator<<( std::ostream& os, const Record& e )
      {
        os<<"<"<<e.timestamp<<", "<<e.label<<", "<<e.object<<">"
          <<" = "<<e.value;
      return os;
      }
    };

  private:

    /**
     * Record multi-index indexed by a composite key with three elements.
     * First key: timestamp.
     */
    typedef boost::multi_index::multi_index_container<
      Record,
      boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
          boost::multi_index::composite_key<
            Record,
            boost::multi_index::member<Record,float,&Record::timestamp>,
            boost::multi_index::member<Record,std::string,&Record::label>,
            boost::multi_index::member<Record,ObjectPtr,&Record::object>
          >
        >
      >
    > MultiIndexByTimestamp;

    /**
     * Record multi-index indexed by a composite key with three elements.
     * First key: label.
     */
    typedef boost::multi_index::multi_index_container<
      Record,
      boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
          boost::multi_index::composite_key<
            Record,
            boost::multi_index::member<Record,std::string,&Record::label>,
            boost::multi_index::member<Record,ObjectPtr,&Record::object>,
            boost::multi_index::member<Record,float,&Record::timestamp>
          >
        >
      >
    > MultiIndexByLabel;

    /**
     * Record multi-index indexed by a composite key with three elements.
     * First key: object.
     */
    typedef boost::multi_index::multi_index_container<
      Record,
      boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
          boost::multi_index::composite_key<
            Record,
            boost::multi_index::member<Record,ObjectPtr,&Record::object>,
            boost::multi_index::member<Record,float,&Record::timestamp>,
            boost::multi_index::member<Record,std::string,&Record::label>
          >
        >
      >
    > MultiIndexByObject;

  public:

    /**
     * Record iterator.
     */
    class iterator
    {
    public:
      /**
       * Iterator type:
       *  - multi index by timestamp iterator
       *  - multi index by label iterator
       *  - multi index by nsol object iterator
       */
      enum TMultiIndexIterator
      {
        IT_TIMESTAMP = 0,
        IT_LABEL,
        IT_OBJECT
      };

      /**
       * Constructors & destructor.
       */
      iterator( void );
      iterator( const iterator& extIterator );

      ~iterator( void );

      /**
       * Getters.
       */
      MultiIndexByTimestamp::iterator getItByTimestamp() const;
      MultiIndexByLabel::iterator getItByLabel() const;
      MultiIndexByObject::iterator getItByObject() const;
      TMultiIndexIterator getUsedIterator() const;
      
      /**
       * Setters.
       */
      void setItByTimestamp
      ( const MultiIndexByTimestamp::iterator& itByTimestamp );
      void setItByLabel
      ( const MultiIndexByLabel::iterator& itByLabel );
      void setItByObject
      ( const MultiIndexByObject::iterator& itByObject );

      /**
       * Operators.
       */
      iterator& operator++();
      void operator=( const iterator& extIterator );
      bool operator==( const iterator& extIterator ) const;
      bool operator!=( const iterator& extIterator ) const;
      const Record& operator*() const;

    private:
      /**
       * Attributes.
       */
      MultiIndexByTimestamp::iterator _itByTimestamp;
      MultiIndexByLabel::iterator _itByLabel;
      MultiIndexByObject::iterator _itByObject;
      TMultiIndexIterator _usedIterator;
    };

    /**
     * Default consructor.
     */
    SimulationData( void );

    /**
     * Destructor.
     */
    virtual ~SimulationData( void );

    /**
     * This method returns the number of records.
     */
    std::size_t numberOfRecords() const;

    /**
     * If the record does not exist, it will be added to the collection.
     * If the record exist, this will be overwritten.
     */
    void insert( Record& record );

    /**
     * Erase a record by its timestamp, label and nsol object.
     */
    void erase( float timestamp,
                std::string label,
                ObjectPtr object );

    /**
     * Remove a specific record.
     */
    //void remove ( const Record& record );

    /**
     * Erase all records from the collection.
     */
    void clear( void );

    /**
     * SimulationData iterator to first record.
     */
    iterator begin();

    /**
     * SimulationData iterator to last record.
     */
    iterator end();

    /**
     * This method looks for a record filtered by:
     *  - timestamp
     *  - label
     *  - nsol object
     */
    iterator
    find( float timestamp, std::string label, ObjectPtr object ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     *  - label
     */
    std::pair<iterator, iterator>
    find( float timestamp, std::string label ) const;

    /**
     * This method looks for records filtered by:
     *  - label
     *  - nsol object
     */
    std::pair<iterator, iterator>
    find( std::string label, ObjectPtr object ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     *  - nsol object
     */
    std::pair<iterator, iterator>
    find( float timestamp, ObjectPtr object ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     */
    std::pair<iterator, iterator>
    find( float timestamp ) const;

    /**
     * TThis method looks for records filtered by:
     *  - label
     */
    std::pair<iterator, iterator>
    find( std::string label ) const;

    /**
     * This method looks for records filtered by:
     *  - nsol object
     */
    std::pair<iterator, iterator>
    find( ObjectPtr object ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     * These records must have its timestamps between a
     * lower bound and an upper bound.
     */
    std::pair<iterator, iterator>
    findByRange( float lowerTimestamp,
                 float upperTimestamp ) const;

    /**
     * Get all timestamp values.
     */
    std::set<float> getTimestamps() const;

    /**
     * Get all label values.
     */
    std::set<std::string> getLabels() const;

    /**
     * Get all nsol objects.
     */
    //std::set<ObjectPtr> getObjects();

    /**
     * Get all records.
     */
    //std::set<Record> getRecords();

    /**
     * Nota: Tiene sentido hacer un getValues?
     * Devolveríamos un std::set<boost::any>?
     */

  private:

    MultiIndexByTimestamp _multiIndexByTimestamp;
    MultiIndexByLabel _multiIndexByLabel;
    MultiIndexByObject _multiIndexByObject;

  };

} // namespace nsol

#endif // SIMULATIONDATA_H_
