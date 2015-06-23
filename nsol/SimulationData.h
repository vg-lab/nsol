/**
 * @file    SimulationData.h
 * @brief
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef SIMULATIONDATA_H_
#define SIMULATIONDATA_H_

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

namespace nsol
{

  //!  Interface to simulation data.
    /*!
      This class contains simulation data: timestamps, label,
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
      int nsobject;

      int value;

      //Necesario?
      Record();

      Record( float timestamp_,
              std::string label_,
              int nsobject_,
              int value_ )
      : timestamp( timestamp_ )
      , label( label_ )
      , nsobject( nsobject_ )
      , value( value_ )
      {}

      friend std::ostream& operator<<( std::ostream& os, const Record& e )
      {
        os<<"<"<<e.timestamp<<", "<<e.label<<", "<<e.nsobject<<">"
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
            boost::multi_index::member<Record,int,&Record::nsobject>
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
            boost::multi_index::member<Record,int,&Record::nsobject>,
            boost::multi_index::member<Record,float,&Record::timestamp>
          >
        >
      >
    > MultiIndexByLabel;

    /**
     * Record multi-index indexed by a composite key with three elements.
     * First key: nsobject.
     */
    typedef boost::multi_index::multi_index_container<
      Record,
      boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
          boost::multi_index::composite_key<
            Record,
            boost::multi_index::member<Record,int,&Record::nsobject>,
            boost::multi_index::member<Record,float,&Record::timestamp>,
            boost::multi_index::member<Record,std::string,&Record::label>
          >
        >
      >
    > MultiIndexByNsobject;

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
       *  - multi index by nsobject iterator
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
      //iterator( MultiIndexByTimestamp::iterator itByTimestamp );
      //iterator( MultiIndexByLabel::iterator itByLabel );
      //iterator( MultiIndexByNsobject::iterator itByNsobject );

      ~iterator( void );

      /**
       * Getters.
       */
      MultiIndexByTimestamp::iterator getItByTimestamp() const;
      MultiIndexByLabel::iterator getItByLabel() const;
      MultiIndexByNsobject::iterator getItByNsobject() const;
      TMultiIndexIterator getUsedIterator() const;
      
      /**
       * Setters.
       */
      void setItByTimestamp
      ( const MultiIndexByTimestamp::iterator& itByTimestamp );
      void setItByLabel
      ( const MultiIndexByLabel::iterator& itByLabel );
      void setItByNsobject
      ( const MultiIndexByNsobject::iterator& itByNsobject );

      /**
       * Operators.
       * url: http://www.cplusplus.com/reference/iterator/iterator/.
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
      MultiIndexByNsobject::iterator _itByNsobject;
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
     * Erase a record by its timestamp, label and nsobject.
     */
    void erase( float timestamp,
                std::string label,
                int nsobject );

    /**
     * Remove a specific record.
     */
    //void remove ( const Record& record );

    /**
     * Erase all records from the collection.
     */
    void clear( void );

    /**
     * This method looks for a record filtered by:
     *  - timestamp
     *  - label
     *  - nsobject
     */
    iterator
    find( float timestamp, std::string label, int nsobject ) const;

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
     *  - nsobject
     */
    std::pair<iterator, iterator>
    find( std::string label, int nsobject ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     *  - nsobject
     */
    std::pair<iterator, iterator>
    find( float timestamp, int nsobject ) const;

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
     *  - nsobject
     */
    std::pair<iterator, iterator>
    find( int nsobject ) const;

    /**
     * Get all timestamp values.
     */
    //std::set<float> getTimestamps();

    /**
     * Get all label values.
     */
    //std::set<std::string> getLabels();

    /**
     * Get all nsol objects.
     */
    //std::set<int> getNsobjects();

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
    MultiIndexByNsobject _multiIndexByNsobject;

  };

} // namespace nsol

#endif // SIMULATIONDATA_H_
