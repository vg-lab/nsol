/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#ifndef __NSOL_COLUMN__
#define __NSOL_COLUMN__

#include <nsol/nsol_export.h>
#include "MiniColumn.h"
#include "NsolTypes.h"
#include "Object.h"
#include "ObjectWithProperties.h"
#include "Container/MiniColumns.h"

namespace nsol
{
  class ColumnStats;

  /*! \class Column
    \brief A class to represent columns.

    Columns provides pointers to minicolumns and methods
    for different morphological values computation.
  */
  class NSOL_EXPORT Column
    : public virtual Object
  {

  public:

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default constructor
     * @param id id of the column.
     */
    Column( unsigned short id = 0 );

    /**
     * Copy constructor
     * @param other column to be copied
     */
    Column( const Column & other );

    /**
     * Default destructur
     */
    virtual ~Column( void ) ;

    /**
     * Returns object as MiniColumnStats
     * @return pointer to MiniColumnStats object
     */
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
    unsigned short & id( void );

    /**
     * Method to get the column id.
     * @return reference to column id
     */
    unsigned short id( void ) const;


    ///@}

    /** @name MiniColumn related methods */
    ///@{

    /**
     * Method to add a mini column.
     * @param miniColumn minicolumn to add to this column
     */
    void addMiniColumn( MiniColumnPtr miniColumn );

    /**
     * Method to remove a mini column.
     * @param miniColumn pointer to the minicolumn to be removed
     * @return true if minicolumn removed false otherwise
     */
    bool removeMiniColumn( MiniColumnPtr miniColumn );

    /**
     * Method to clear mini columns.
     */
    void clearMiniColumns( void );

    /**
     * Method to get minicolumns.
     * @return minicolumns of the column
     */
    MiniColumns & miniColumns( void );

    /**
     * Method to get minicolumns as const.
     * @return minicolumns of the column
     */
    MiniColumns miniColumns( void ) const;

    /**
     * Method to get the number of minicolumns.
     * @return numbers of minicolumns
     */
    unsigned int numberOfMiniColumns( void ) const;

    ///@}


    /** @name Operators */
    ///@{

    Column & operator = ( const Column & other );

    bool operator == ( Column & other ) const;

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
    unsigned int
    numberOfNeurons( const bool all = true,
                     const Neuron::TMorphologicalType neuronType =
                     Neuron::PYRAMIDAL,
                     const unsigned int layer = 0 ) const;


    virtual ColumnPtr asColumn( void )
    {
      return this;
    }

  protected:

    //! Identifier of the column
    unsigned short _id;

    //! Container of minicolumns
    MiniColumns _miniColumns;

  }; // class Column


} // namespace nsol


#endif // __NSOL_COLUMN__
// EOF
