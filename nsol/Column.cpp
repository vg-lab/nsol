/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
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
#include "Column.h"

namespace nsol
{


  //
  // Constructors and destructors
  //

  Column::Column( const unsigned short identifier )
  {
    _id = identifier;
  }


  Column::Column( const Column & other )
    : _id( other.id( ))
    , _miniColumns( other.miniColumns( ))
  {}

  Column::~Column()
  {
/*    for (Vector<MiniColumnPtr>::iterator it = _miniColumns.begin();
      it != _miniColumns.end(); ++it)
      delete *it;
*/
    _miniColumns.clear();
  }

  void Column::addMiniColumn(MiniColumnPtr miniColumn)
  {
    _miniColumns.push_back(miniColumn);
  }

  bool Column::removeMiniColumn(MiniColumnPtr miniColumn)
  {
    MiniColumns::iterator mcIt =
      find (_miniColumns.begin( ), _miniColumns.end( ), miniColumn);

    if ( mcIt == _miniColumns.end( ))
      return false;

    _miniColumns.erase( mcIt );
    return true;
  }

  void Column::clearMiniColumns( void )
  {
    _miniColumns.clear( );
  }



  //
  // Operators
  //

  Column & Column::operator = (const Column & other)
  {
    if (this != &other)
    {
      this->id( ) = other.id( );
      this->miniColumns( ) = other.miniColumns( );
    }

    return *this;
  }

  bool Column::operator == (Column & other ) const
  {
    return ( ( this->id( ) == other.id( ) ) &&
             ( this->miniColumns( ) == other.miniColumns( )));
  }

  bool Column::operator != (Column & other ) const
  {
    return !( ( this->id( ) == other.id( ) ) &&
              ( this->miniColumns( ) == other.miniColumns( )));
  }


  //
  // Id related methods
  //

  unsigned short & Column::id(void)
  {
    return _id;
  }

  unsigned short Column::id(void) const
  {
    return _id;
  }

  //
  // Minicolumn related methods
  //

  MiniColumns & Column::miniColumns()
  {
    return _miniColumns;
  }

  MiniColumns Column::miniColumns() const
  {
    return _miniColumns;
  }

  unsigned int Column::numberOfMiniColumns(void) const
  {
    return ( unsigned int ) _miniColumns.size();
  }

  unsigned int Column::numberOfNeurons(bool all,
                                       Neuron::TMorphologicalType neuronType,
                                       unsigned int layer) const
  {
    unsigned int nNeurons = 0;

    NSOL_CONST_FOREACH( miniColumn, _miniColumns )
      nNeurons += ( * miniColumn )->numberOfNeurons(all, neuronType, layer);

    return nNeurons;

  }

} // namespace nsol
