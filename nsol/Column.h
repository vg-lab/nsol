/**
 * @file    Column.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_COLUMN__
#define __NSOL_COLUMN__

#include <nsol/api.h>
#include "MiniColumn.h"
#include "NsolTypes.h"
#include "Container/MiniColumns.h"

namespace nsol
{
  class ColumnStats;


  /*! \class Column
    \brief A class to represent columns.

    Columns provides pointers to minicolumns and methods
    for different morphological values computation.
  */
  class Column
  {

  public:

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default constructor
     * @param id id of the column.
     */
    NSOL_API
    Column( unsigned short id = 0 );

    /**
     * Copy constructor
     * @param other column to be copied
     */
    NSOL_API
    Column( const Column & other );

    /**
     * Default destructur
     */
    NSOL_API
    virtual ~Column( void ) ;

        /**
     * Returns object as MiniColumnStats
     * @return pointer to MiniColumnStats object
     */
    NSOL_API
    virtual ColumnStats * stats( void )
    {
      return nullptr;
    }


    ///@}

    /** @name Id related methods */
    ///@{

    /**
     * Method to get-set the column id.
     * @return column id
     */
    NSOL_API
    unsigned short & id( void );

    /**
     * Method to get the column id.
     * @return reference to column id
     */
    NSOL_API
    unsigned short id( void ) const;


    ///@}

    /** @name MiniColumn related methods */
    ///@{

    /**
     * Method to add a mini column.
     * @param miniColumn minicolumn to add to this column
     */
    NSOL_API
    void addMiniColumn( MiniColumnPtr miniColumn );

    /**
     * Method to remove a mini column.
     * @param miniColumn pointer to the minicolumn to be removed
     * @return true if minicolumn removed false otherwise
     */
    NSOL_API
    bool removeMiniColumn( MiniColumnPtr miniColumn );

    /**
     * Method to clear mini columns.
     */
    NSOL_API
    void clearMiniColumns( void );

    /**
     * Method to get minicolumns.
     * @return minicolumns of the column
     */
    NSOL_API
    MiniColumns & miniColumns( void );

    /**
     * Method to get minicolumns as const.
     * @return minicolumns of the column
     */
    NSOL_API
    MiniColumns miniColumns( void ) const;

    /**
     * Method to get the number of minicolumns.
     * @return numbers of minicolumns
     */
    NSOL_API
    unsigned int numberOfMiniColumns( void ) const;

    ///@}


    /** @name Operators */
    ///@{

    NSOL_API
    Column & operator = ( const Column & other );

    NSOL_API
    bool operator == ( Column & other ) const;

    NSOL_API
    bool operator != ( Column & other ) const;

    ///@}

    /**
     * Method to get the number of neurons in the column.
     * @param all if this is true all neurons are counted
     * @param neuronType if "all" is false neurons of the
     *        passed type will be counted
     * @param layer if "all" is false neurons of the
     *        layer will be counted. If later is 0 then all
     *        neurons of all layers will be counted.
     * @return number of neurons that match the criteria
     */
    NSOL_API
    unsigned int
    numberOfNeurons( const bool all = true,
                     const Neuron::TNeuronType neuronType =
                     Neuron::PYRAMIDAL,
                     const unsigned int layer = 0 ) const;

  protected:

    //! Identifier of the column
    unsigned short _id;

    //! Container of minicolumns
    MiniColumns _miniColumns;

  }; // class Column
} // namespace nsol


#endif // __NSOL_COLUMN__
// EOF
