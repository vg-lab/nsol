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

#include "MiniColumn.h"

namespace nsol
{

  //
  // Constructors and destructors
  //

  MiniColumn::MiniColumn( const ColumnPtr initColumn,
                          const unsigned short initId )
    : _id( initId )
    , _column( initColumn )
  {
  }

  MiniColumn::MiniColumn( const MiniColumn & other )
    : _id( other.id( ))
    , _column( other.column( ))
    , _neurons( other.neurons( ))
  {}

  MiniColumn::~MiniColumn( void )
  {
//	      for (Vector<Neuron *>::iterator it = _neurons.begin();
//	      it != _neurons.end(); ++it)
//	        delete *it;
//
//	      _neurons.clear();
  }

  NeuronPtr MiniColumn::addNeuron( NeuronPtr neuron )
  {

    NSOL_DEBUG_CHECK( neuron, "neuron to be added is null" );
    _neurons.push_back( neuron );

    return _neurons.back();
  }

  bool MiniColumn::removeNeuron( NeuronPtr neuron )
  {
    Neurons::iterator nIt =
      find (_neurons.begin( ), _neurons.end( ), neuron);

    if ( nIt == _neurons.end( ))
      return false;

    _neurons.erase( nIt );
    return true;
  }

  void MiniColumn::clearNeurons( void )
  {
    _neurons.clear( );
  }

  Neurons & MiniColumn::neurons( void )
  {
    return _neurons;
  }

  Neurons MiniColumn::neurons( void ) const
  {
    return _neurons;
  }

  void MiniColumn::column( ColumnPtr colummn )
  {
    _column = colummn;
  }

  ColumnPtr MiniColumn::column( void ) const
  {
    return _column;
  }

  unsigned short & MiniColumn::id( void )
  {
    return _id;
  }

  unsigned short MiniColumn::id( void ) const
  {
    return _id;
  }


  unsigned int
  MiniColumn::numberOfNeurons( bool all,
                               Neuron::TMorphologicalType neuronType,
                               unsigned int layer) const
  {
    if ( all )
      return ( unsigned int ) _neurons.size( );
    else
    {
      unsigned int nNeurons = 0;

      NSOL_CONST_FOREACH( nIt, _neurons )
      {
        if ( ( * nIt )->morphologicalType( ) == neuronType &&
             ( layer == 0 || layer == ( * nIt )->layer( )))
          nNeurons++;
      }

      return nNeurons;
    }
  }

  //
  // Operators
  //

  MiniColumn & MiniColumn::operator = (const MiniColumn & other)
  {
    if (this != &other)
    {
      this->id( ) = other.id( );
      this->column( other.column( ) );
      this->neurons( ) = other.neurons( );
    }

    return *this;
  }

  bool MiniColumn::operator == (MiniColumn & other ) const
  {
    return  ( ( this->id( ) == other.id( ) ) &&
              ( this->column( ) == other.column( )) &&
              ( this->neurons( ) == other.neurons( )));
  }

  bool MiniColumn::operator != (MiniColumn & other ) const
  {
    return ! ( *this == other );
  }


} // namespace nsol

// EOF
