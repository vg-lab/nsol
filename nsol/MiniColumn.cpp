/**
 * @file    MiniColumn.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
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
                               Neuron::TNeuronType neuronType,
                               unsigned int layer) const
  {
    if ( all )
      return ( unsigned int ) _neurons.size( );
    else
    {
      unsigned int nNeurons = 0;

      NSOL_CONST_FOREACH( nIt, _neurons )
      {
        if ( ( * nIt )->neuronType( ) == neuronType &&
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
