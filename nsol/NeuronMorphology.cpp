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

#include "NeuronMorphology.h"

namespace nsol
{

  NeuronMorphology::NeuronMorphology( void )
    : _soma( nullptr )
  {

  }

  NeuronMorphology::NeuronMorphology( SomaPtr soma_ )
    : _soma( soma_ )
  {

  }

  NeuronMorphology::~NeuronMorphology( void )
  {
    for ( auto neurite: _neurites)
    {
      delete neurite;
    }
    delete _soma;
    _neurites.clear( );
    _parentNeurons.clear( );
  }

  SomaPtr
  NeuronMorphology::soma( SomaPtr soma_ )
  {
    NSOL_DEBUG_CHECK( soma_, "soma is null" );
    _soma = soma_;
    return soma_;
  }

  NeuritePtr
  NeuronMorphology::addNeurite( NeuritePtr neurite_ )
  {
    NSOL_DEBUG_CHECK( neurite_, "neurite is null" );
    _neurites.push_back( neurite_ );
    _sections.push_back( neurite_->firstSection( ));
    return neurite_;
  }

  Dendrites * NeuronMorphology::dendrites( void ) const
  {
    Dendrites * tmpDendrites = new Dendrites;

    NSOL_CONST_FOREACH( it, _neurites )
    {

      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );

      if ( dend )
        tmpDendrites->push_back( dend );
    }
    return tmpDendrites;
  }

  Dendrites * NeuronMorphology::basalDendrites(void) const
  {

    Dendrites * tmpDendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::BASAL ))
        tmpDendrites->push_back( dend );
    }

    return tmpDendrites;
  }

  Dendrites * NeuronMorphology::apicalDendrites( void ) const
  {
    Dendrites * tmpDendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST ( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::APICAL ))
        tmpDendrites->push_back( dend );
    }

    return tmpDendrites;
  }

  DendritePtr NeuronMorphology::apicalDendrite( void ) const
  {
    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::APICAL ))
        return dend;
    }

    return nullptr;
  }

  AxonPtr NeuronMorphology::axon( void ) const
  {
    for ( const auto& neurite : _neurites )
    {
      auto axon_ = NSOL_DYNAMIC_CAST( Axon, neurite );
      if ( axon_ )
        return axon_;
    }
    return nullptr;
  }


  Neurites & NeuronMorphology::neurites( void )
  {
    return _neurites;
  }

  const Neurites & NeuronMorphology::neurites( void ) const
  {
    return _neurites;
  }

  Neurons & NeuronMorphology::parentNeurons( void )
  {
    return _parentNeurons;
  }

  const Neurons & NeuronMorphology::parentNeurons( void ) const
  {
    return _parentNeurons;
  }

  void NeuronMorphology::addParentNeuron( NeuronPtr neuron )
  {
    Neurons::iterator neuronIt =
      std::find ( _parentNeurons.begin( ),
                  _parentNeurons.end( ),
                  neuron );

    if ( neuronIt != _parentNeurons.end( ))
      _parentNeurons.push_back( neuron );


  }

  SomaPtr NeuronMorphology::soma( void )
  {
    return _soma;
  }

  NeuronMorphologyPtr NeuronMorphology::clone( void ) const
  {
    NeuronMorphologyPtr newMorpho = new NeuronMorphology( );
    newMorpho->soma( _soma->clone( ));

    for ( NeuritePtr neurite: _neurites )
    {
      NeuritePtr newNeurite = neurite->clone( );
      newNeurite->morphology( newMorpho );
      newMorpho->addNeurite( newNeurite );
    }
    return newMorpho;
  }

  bool NeuronMorphology::operator == ( NeuronMorphology & other )
  {
    if (*_soma != *other.soma( ) ||
        _neurites.size( ) != other.neurites( ).size( ))
      return false;

    for ( unsigned int i = 0; i < _neurites.size( ); i++ )
      if ( *_neurites[i] != *other.neurites( )[i] )
        return false;

    return true;
  }

  bool NeuronMorphology::operator != ( NeuronMorphology & other )
  {
    return !( *this == other );
  }
} // namespace nsol

// EOF
