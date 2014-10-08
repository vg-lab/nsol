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

  MiniColumn::MiniColumn( const ColumnPtr column, 
			  const unsigned short id ) 
    : _id( id )
    , _column( column )
  {
    _column = column;
    _id = id;
  }

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

  Neurons & MiniColumn::neurons( void ) 
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

  unsigned int 
  MiniColumn::numberOfNeurons( bool all, 
			       Neuron::TNeuronType neuronType,
			       unsigned int layer) const 
  {
    if (all)
      return _neurons.size( );
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

  float MiniColumn::meanSomaVolume( void ) const 
  {
    double meanSomaVolume = 0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      meanSomaVolume += (*nIt)->soma( ).volume( );
    return float(meanSomaVolume / _neurons.size( ));
  }

  float MiniColumn::meanSomaSurface( ) const 
  {
    double meanSomaSurface = 0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      meanSomaSurface += (*nIt)->soma( ).surface( );
    return float(meanSomaSurface / _neurons.size( ));
  }

  float MiniColumn::meanDendriteVolume( void ) const 
  {
    double meanDendVolume = 0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      meanDendVolume += (*nIt)->dendritesVolume( );
    return float(meanDendVolume / _neurons.size( ));
  }

  float MiniColumn::meanDendriteSurface( void ) const 
  {
    double meanDendSurface = 0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      meanDendSurface += (*nIt)->dendritesSurface( );
    return float(meanDendSurface / _neurons.size( ));
  }

  float MiniColumn::maxSomaVolume( void ) const 
  {
    double maxSomaVolume = 0.0;
    for (Neurons::const_iterator nIt = _neurons.begin( );
	 nIt != _neurons.end( ); nIt++)
      if ((*nIt)->soma().volume() > maxSomaVolume)
	maxSomaVolume = (*nIt)->soma().volume( );
    return (float) maxSomaVolume;
  }

  float MiniColumn::maxSomaSurface( void) const 
  {
    double maxSomaSurface = 0.0;
    for (Neurons::const_iterator nIt = _neurons.begin();
	 nIt != _neurons.end( ); nIt++)
      if ((*nIt)->soma().surface( ) > maxSomaSurface)
	maxSomaSurface = (*nIt)->soma( ).surface();
    return (float) maxSomaSurface;
  }

  float MiniColumn::maxDendriteVolume( void ) const 
  {
    double maxDendVolume = 0;
    for (Neurons::const_iterator nIt = _neurons.begin();
	 nIt != _neurons.end(); nIt++)
      if ((*nIt)->dendritesVolume() > maxDendVolume)
	maxDendVolume = (*nIt)->dendritesVolume();
    return (float) maxDendVolume;
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
