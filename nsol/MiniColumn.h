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
#ifndef __NSOL_MINICOLUMN__
#define __NSOL_MINICOLUMN__

#include <nsol/nsol_export.h>
#include "Object.h"
#include "Neuron.h"
#include "Container/Neurons.h"

namespace nsol
{

  class MiniColumnStats;

  /*! \class MiniColumn
    \brief A class to represent minicolumns.

    Columns provides pointers to neurons and methods
    for different morphological values computation.
  */
  class NSOL_EXPORT MiniColumn
    : public virtual Object
  {

  public:

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default constructor
     * @param column pointer to parent column.
     * @param id id of the minicolumn.
     */
    MiniColumn( const ColumnPtr column = nullptr,
                const unsigned short id = 0 );

    /**
     * Copy constructor
     * @param other column to be copied
     */
    MiniColumn( const MiniColumn & other );

    /**
     * Default destructur
     */
    virtual ~MiniColumn();

    ///@}

    /** @name Id related methods */
    ///@{

    /**
     * Method to get-set mini column id.
     * @return refenrence to mini column id
     */
    unsigned short & id( void );

    /**
     * Method to get the column id as const.
     * @return id of the minicolumn
     */
    unsigned short id( void ) const;

    ///@}

    /** @name Column related methods */
    ///@{

    /**
     * Method to set the column of this minicolumn
     * @param column pointer to the column
     */
    void column( ColumnPtr column );

    /**
     * Method to get the column of this minicolumn
     * @return pointer to the column
     */
    ColumnPtr column( void ) const;

    ///@}


    /** @name Neuron related methods */
    ///@{

    /**
     * Method to add a neuron. If null value passed a new neuron is created
     * @param neuron pointer to neuron to add. If null new neuron is created
     * @return pointer to the added neuron
     */
    NeuronPtr addNeuron( NeuronPtr neuron );

    /**
     * Method to remove a neuron.
     * @param neuron pointer to the neuron to be removed
     * @return true if neuron removed false otherwise
     */
    bool removeNeuron( NeuronPtr neuron );

    /**
     * Method to get neurons.
     * @return neurons of the mimi column
     */
    Neurons & neurons( void );

    /**
     * Method to get neurons.
     * @return neurons of the mimi column
     */
    Neurons neurons( void ) const;

    /**
     * Method to clear the neurons container.
     */
    void clearNeurons( void );


    /**
     * Method to get the number of neurons in the minicolumn.
     * @param all if this is true all neurons are counted
     * @param neuronType if "all" is false neurons of the
     *        passed type will be counted
     * @param layer if "all" is false neurons of the
     *        layer will be counted. If layer is 0 then all
     *        neurons of all layers will be counted.
     * @return number of neurons that match the criteria
     */
    unsigned int numberOfNeurons(bool all = true,
                                 Neuron::TMorphologicalType neuronType =
                                 Neuron::PYRAMIDAL,
                                 unsigned int layer = 0 ) const;


    ///@}

    /** @name Operators */
    ///@{

    MiniColumn & operator = (const MiniColumn & other);

    bool operator == (MiniColumn & other ) const;

    bool operator != (MiniColumn & other ) const;

    ///@}

    /**
     * Returns object as MiniColumnStats
     * @return pointer to MiniColumnStats object
     */
    virtual MiniColumnStats * stats( void )
    {
      return nullptr;
    }

    virtual MiniColumnPtr asMiniColumn( void )
    {
      return this;
    }


  protected:

    //! id of this minicolumn
    unsigned short _id;

    //! Pointer to the column this minicolumn belogns to
    ColumnPtr _column;

    //!! Container of the neurons of this minicolumn
    Neurons _neurons;

  };

} // namespace nsol

#endif
