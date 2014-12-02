/**
 * @file    NeuronMorphology.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "NeuronMorphology.h"

namespace nsol
{

  NeuronMorphology::NeuronMorphology( SomaPtr soma_ )
    : _soma( soma_ )
  {
  }

  NeuronMorphology::~NeuronMorphology( void )
  {
  }

  NeuritePtr
  NeuronMorphology::addNeurite( NeuritePtr neurite_ )
  //Neurite::TNeuriteType neuriteType )
  {
    // if ( neuriteType == Neurite::DENDRITE )
    //   _neurites.push_back( DendritePtr( new Dendrite( )));
    // else if ( neuriteType == Neurite::AXON )
    //   _neurites.push_back( AxonPtr( new Axon( )));
    // else
    //   return nullptr;

    // return _neurites.back( );
    NSOL_DEBUG_CHECK( neurite_, "neurite is null" );
    // DendritePtr dend( new Dendrite( dendriteType ));
    _neurites.push_back( neurite_ );
    return neurite_;
  }


  // DendritePtr
  // NeuronMorphology::addDendrite( DendritePtr dendrite_ )
  // {
  //   NSOL_DEBUG_CHECK( axon_, "dendrite is null" );
  //   // DendritePtr dend( new Dendrite( dendriteType ));
  //   _neurites.push_back( dendrite_ );
  //   return dendrite_;
  // }

  // AxonPtr NeuronMorphology::addAxon( AxonPtr axon_ )
  // {
  //   // AxonPtr axon( new Axon( ));
  //   NSOL_DEBUG_CHECK( axon_, "axon is null" );
  //   _neurites.push_back( axon_ );
  //   return axon_;
  // }


  // unsigned int NeuronMorphology::numNeurites( void ) const
  // {
  //   return ( unsigned int ) _neurites.size( );
  // }

  // unsigned int NeuronMorphology::numDendrites( void ) const
  // {
  //   unsigned int nd = 0;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if ( NSOL_DYNAMIC_CAST( Dendrite, *it ))
  //       nd++;

  //   return nd;
  // }

  // unsigned int NeuronMorphology::numNeuriteBranches( void ) const
  // {
  //   unsigned int nb = 0;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     nb += (*it)->numBranches( );

  //   return nb;
  // }

  // unsigned int NeuronMorphology::numDendriteBranches( void ) const
  // {
  //   unsigned int nb = 0;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if (NSOL_DYNAMIC_CAST( Dendrite, *it ))
  //       nb += (*it)->numBranches( );

  //   return nb;
  // }

  // unsigned int NeuronMorphology::numAxonBranches( void ) const
  // {
  //   unsigned int nb = 0;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if  (NSOL_DYNAMIC_CAST( Axon, *it ))
  //       nb += (*it)->numBranches( );

  //   return nb;
  // }

  // unsigned int NeuronMorphology::numNeuriteBifurcations( void ) const
  // {
  //   unsigned int nb = 0;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     nb += (*it)->numBifurcations( );

  //   return nb;
  // }

  // unsigned int NeuronMorphology::numDendriteBifurcations( void ) const
  // {
  //   unsigned int nb = 0;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if (NSOL_DYNAMIC_CAST( Dendrite, *it ))
  //       nb += (*it)->numBifurcations( );

  //   return nb;
  // }

  // unsigned int NeuronMorphology::numAxonBifurcations( void ) const
  // {
  //   unsigned int nb = 0;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if  (NSOL_DYNAMIC_CAST( Axon, *it ))
  //       nb += (*it)->numBifurcations( );

  //   return nb;
  // }

  // float NeuronMorphology::volume( void ) const
  // {
  //   return this->neuritesVolume( ) + _soma.volume( );
  // }

  // float NeuronMorphology::neuritesVolume( void ) const
  // {
  //   return this->dendritesVolume( ) + this->axonVolume( );
  // }

  // float NeuronMorphology::dendritesVolume( void ) const
  // {
  //   float tmpVolume = 0.0f;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //   {
  //     if ( NSOL_DYNAMIC_CAST( Dendrite, *it ) ) // std::dynamic_pointer_cast< Dendrite >( ( *it ))) // (*it)->asDendrite( ))
  //       tmpVolume += (*it)->volume( );
  //   }
  //   return tmpVolume;
  // }

  // float NeuronMorphology::axonVolume( void ) const
  // {
  //   float tmpVolume = 0.0f;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if (NSOL_DYNAMIC_CAST( Axon, *it ))
  //       tmpVolume += (*it)->volume( );

  //   return tmpVolume;
  // }

  // float NeuronMorphology::surface( void ) const
  // {
  //   return this->neuritesSurface( ) + _soma.surface( );
  // }

  // float NeuronMorphology::neuritesSurface( void ) const
  // {
  //   return this->dendritesSurface( ) + this->axonSurface( );
  // }

  // float NeuronMorphology::dendritesSurface( void ) const
  // {
  //   float tmpSurface = 0.0f;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if (NSOL_DYNAMIC_CAST( Dendrite, *it ))
  //       tmpSurface += (*it)->surface( );

  //   return tmpSurface;
  // }

  // float NeuronMorphology::axonSurface( void ) const
  // {
  //   float tmpSurface = 0.0f;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if (NSOL_DYNAMIC_CAST( Axon, *it ))
  //       tmpSurface += (*it)->surface( );

  //   return tmpSurface;
  // }

  // float NeuronMorphology::length( void ) const
  // {
  //   return this->neuritesLength( );
  // }

  // float NeuronMorphology::neuritesLength( void ) const
  // {
  //   return this->dendritesLength( ) + this->axonLength( );
  // }

  // float NeuronMorphology::dendritesLength( void ) const
  // {
  //   float tmpLength = 0;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if (NSOL_DYNAMIC_CAST( Dendrite, *it ))
  //       tmpLength += (*it)->length( );

  //   return tmpLength;
  // }

  // float NeuronMorphology::axonLength( void ) const
  // {
  //   float tmpLength = 0.0f;

  //   for (Neurites::const_iterator it = _neurites.begin( );
  //        it != _neurites.end( ); ++it)
  //     if (NSOL_DYNAMIC_CAST( Axon, *it ))
  //       tmpLength += (*it)->length( );

  //   return tmpLength;
  // }

  Dendrites * NeuronMorphology::dendrites( void ) const
  {
    Dendrites * tmpDendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
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

    return NULL;
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


} // namespace nsol

// EOF
