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

#include <nsol/api.h>
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
      NSOL_API
      iterator( void );
      NSOL_API
      iterator( const iterator& extIterator );

      NSOL_API
      ~iterator( void );

      /**
       * Getters.
       */
      NSOL_API
      MultiIndexByTimestamp::iterator getItByTimestamp() const;
      NSOL_API
      MultiIndexByLabel::iterator getItByLabel() const;
      NSOL_API
      MultiIndexByObject::iterator getItByObject() const;
      NSOL_API
      TMultiIndexIterator getUsedIterator() const;

      /**
       * Setters.
       */
      NSOL_API
      void setItByTimestamp(
        const MultiIndexByTimestamp::iterator& itByTimestamp );
      NSOL_API
      void setItByLabel(
        const MultiIndexByLabel::iterator& itByLabel );
      NSOL_API
      void setItByObject(
        const MultiIndexByObject::iterator& itByObject );

      /**
       * Operators.
       */
      NSOL_API
      iterator& operator++();
      NSOL_API
      void operator=( const iterator& extIterator );
      NSOL_API
      bool operator==( const iterator& extIterator ) const;
      NSOL_API
      bool operator!=( const iterator& extIterator ) const;
      NSOL_API
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
    NSOL_API
    SimulationData( void );

    /**
     * Destructor.
     */
    NSOL_API
    virtual ~SimulationData( void );

    /**
     * This method returns the number of records.
     */
    NSOL_API
    std::size_t numberOfRecords() const;

    /**
     * If the record does not exist, it will be added to the collection.
     * If the record exist, this will be overwritten.
     */
    NSOL_API
    void insert( Record& record );

    /**
     * Erase a record by its timestamp, label and nsol object.
     */
    NSOL_API
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
    NSOL_API
    void clear( void );

    /**
     * SimulationData iterator to first record.
     */
    NSOL_API
    iterator begin();

    /**
     * SimulationData iterator to last record.
     */
    NSOL_API
    iterator end();

    /**
     * This method looks for a record filtered by:
     *  - timestamp
     *  - label
     *  - nsol object
     */
    NSOL_API
    iterator find( float timestamp,
                   std::string label, ObjectPtr object ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     *  - label
     */
    NSOL_API
    std::pair<iterator, iterator> find( float timestamp,
                                        std::string label ) const;

    /**
     * This method looks for records filtered by:
     *  - label
     *  - nsol object
     */
    NSOL_API
    std::pair<iterator, iterator> find( std::string label,
                                        ObjectPtr object ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     *  - nsol object
     */
    NSOL_API
    std::pair<iterator, iterator> find( float timestamp,
                                        ObjectPtr object ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     */
    NSOL_API
    std::pair<iterator, iterator> find( float timestamp ) const;

    /**
     * TThis method looks for records filtered by:
     *  - label
     */
    NSOL_API
    std::pair<iterator, iterator> find( std::string label ) const;

    /**
     * This method looks for records filtered by:
     *  - nsol object
     */
    NSOL_API
    std::pair<iterator, iterator> find( ObjectPtr object ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     * These records must have its timestamps between a
     * lower bound and an upper bound.
     */
    NSOL_API
    std::pair<iterator, iterator> findByRange( float lowerTimestamp,
                                               float upperTimestamp ) const;

    /**
     * Get all timestamp values.
     */
    NSOL_API
    std::set<float> getTimestamps( void ) const;

    /**
     * Get all label values.
     */
    NSOL_API
    std::set<std::string> getLabels( void ) const;

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
