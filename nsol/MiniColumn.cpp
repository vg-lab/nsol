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

    if ( neuron )
      _neurons.push_back(neuron);
    else 
      _neurons.push_back(NeuronPtr(new Neuron()));

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
    if (all)
      return (unsigned int) _neurons.size( );
    else 
    {
      unsigned int nNeurons = 0;
      for ( Neurons::const_iterator nIt = _neurons.begin( );
	    nIt != _neurons.end(); nIt++ ) 
      {
	if ( (*nIt)->neuronType( ) == neuronType && 
	    ( layer == 0 || layer == (*nIt)->layer( )))
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


  //
  // Morphological measures methods
  //  

  float MiniColumn::meanSomaVolume( void ) const 
  {
    if ( _neurons.size() == 0 ) 
      return 0.0f;

    float totalSomaVolume = 0;

    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      totalSomaVolume += (*nIt)->soma( ).volume( );

    return totalSomaVolume / float(_neurons.size( ));
  }

  float MiniColumn::meanSomaSurface( ) const 
  {
    if ( _neurons.size() == 0 ) 
      return 0.0f;

    float totalSomaSurface = 0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      totalSomaSurface += (*nIt)->soma( ).surface( );
    return totalSomaSurface / float( _neurons.size( ));
  }

  float MiniColumn::meanDendriteVolume( void ) const 
  {
    if ( _neurons.size() == 0 ) 
      return 0.0f;

    float totalDendVolume = 0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      totalDendVolume += (*nIt)->dendritesVolume( );
    return totalDendVolume / float( _neurons.size( ));
  }

  float MiniColumn::meanDendriteSurface( void ) const 
  {
    if ( _neurons.size() == 0 ) 
      return 0.0f;

    double meanDendSurface = 0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      meanDendSurface += (*nIt)->dendritesSurface( );
    return float(meanDendSurface / _neurons.size( ));
  }

  float MiniColumn::maxSomaVolume( void ) const 
  {
    double tmpMaxSomaVolume = 0.0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      if ((*nIt)->soma().volume() > tmpMaxSomaVolume)
	tmpMaxSomaVolume = (*nIt)->soma().volume( );
    return (float) tmpMaxSomaVolume;
  }

  float MiniColumn::maxSomaSurface( void) const 
  {
    float tmpMaxSomaSurface = 0.0;
    for (Neurons::const_iterator nIt = _neurons.begin();
	 nIt != _neurons.end( ); nIt++)
      if ((*nIt)->soma().surface( ) > tmpMaxSomaSurface)
	tmpMaxSomaSurface = (*nIt)->soma( ).surface();
    return tmpMaxSomaSurface;
  }

  float MiniColumn::maxDendriteVolume( void ) const 
  {
    float tmpMaxDendVolume = 0;
    for (Neurons::const_iterator nIt = _neurons.begin();
	 nIt != _neurons.end(); nIt++)
      if ((*nIt)->dendritesVolume() > tmpMaxDendVolume)
	tmpMaxDendVolume = (*nIt)->dendritesVolume();
    return tmpMaxDendVolume;
  }

  float MiniColumn::maxDendriteSurface( void ) const 
  {
    double maxDendSurface = 0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      if ((*nIt)->dendritesSurface() > maxDendSurface)
	maxDendSurface = (*nIt)->dendritesSurface( );
    return (float) maxDendSurface;
  }

  unsigned int MiniColumn::numDendriteBranches( void ) 
  {   
    unsigned int numBranches = 0;
    
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      numBranches += (*nIt)->numDendriteBranches( );

    return numBranches;
  }

} // namespace nsol

// EOF
