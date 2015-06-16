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

  //using boost::multi_index_container;
  //using namespace boost::multi_index;

  //!  Interface to simulation data.
    /*!
      This class contains simulation data: timestamps, label,
      nsol objects and values.
    */
  class SimulationData {

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

      Record(float timestamp_,
             std::string label_,
             int nsobject_,
             int value_)
      : timestamp(timestamp_)
      , label(label_)
      , nsobject(nsobject_)
      , value(value_)
      {}

      friend std::ostream& operator<<(std::ostream& os,const Record& e)
      {
      //os<<"<"<<e.timestamp<<", "<<e.label<<", "<< e.nsobject <<std::endl;
      os<<"<"<<e.timestamp<<", "<<e.label<<", "<<e.nsobject<<">"
          <<" = "<<e.value;
      return os;
      }

    };

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
    std::size_t numberOfRecords();

    /**
     * If the record does not exist, it will be added to the collection.
     * If the record exist, this will be overwritten.
     */
    void insert( Record record );

    /**
     * Erase a record by its timestamp, label and nsobject.
     */
    void erase( float timestamp,
                std::string label,
                int nsobject );

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
    /**
     * Devolver Record* puede ser una buena solución para esconder
     * lo de los iteradores (o quizá no, quizá no sea posible
     * hacer un casting a Record*).
     */
    MultiIndexByTimestamp::iterator
    find( float timestamp, std::string label, int nsobject ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     *  - label
     */
    std::pair<MultiIndexByTimestamp::iterator, MultiIndexByTimestamp::iterator>
    find( float timestamp, std::string label ) const;

    /**
     * This method looks for records filtered by:
     *  - label
     *  - nsobject
     */
    std::pair<MultiIndexByLabel::iterator, MultiIndexByLabel::iterator>
    find( std::string label, int nsobject ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     *  - nsobject
     */
    std::pair<MultiIndexByNsobject::iterator, MultiIndexByNsobject::iterator>
    find( float timestamp, int nsobject ) const;

    /**
     * This method looks for records filtered by:
     *  - timestamp
     */
    std::pair<MultiIndexByTimestamp::iterator, MultiIndexByTimestamp::iterator>
    find( float timestamp ) const;

    /**
     * TThis method looks for records filtered by:
     *  - label
     */
    std::pair<MultiIndexByLabel::iterator, MultiIndexByLabel::iterator>
    find( std::string label ) const;

    /**
     * This method looks for records filtered by:
     *  - nsobject
     */
    std::pair<MultiIndexByNsobject::iterator, MultiIndexByNsobject::iterator>
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
