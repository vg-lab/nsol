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

  NeuronMorphology::NeuronMorphology( void )
  {
  }

  NeuronMorphology::~NeuronMorphology( void )
  {
    for (Neurites::iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      delete *it;
    
    _neurites.clear( );
  }

  NeuritePtr 
  NeuronMorphology::addNeurite( Neurite::TNeuriteType neuriteType )
  {
    if ( neuriteType == Neurite::DENDRITE )
      _neurites.push_back( new Dendrite( ));
    else if ( neuriteType == Neurite::AXON )
      _neurites.push_back( new Axon( ));
    else
      return nullptr;
    
    return _neurites.back( );
  }


  Dendrite * 
  NeuronMorphology::addDendrite( Dendrite::TDendriteType dendriteType )
  {
    _neurites.push_back( new Dendrite( dendriteType ));
    return _neurites.back( )->asDendrite( );
  }

  Axon * NeuronMorphology::addAxon( void )
  {
    _neurites.push_back(new Axon( ));
    return _neurites.back( )->asAxon( );
  }

  
  unsigned int NeuronMorphology::numNeurites( void ) const
  {
    return _neurites.size( );
  }

  unsigned int NeuronMorphology::numDendrites( void ) const
  {
    unsigned int nd = 0;
    
    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asDendrite( )) nd++;
    
    return nd;
  }

  unsigned int NeuronMorphology::numNeuriteBranches( void ) const
  {
    unsigned int nb = 0;
    
    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      nb += (*it)->numBranches( );
    
    return nb;
  }
  
  unsigned int NeuronMorphology::numDendriteBranches( void ) const
  {
    unsigned int nb = 0;
    
    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asDendrite( ))
	nb += (*it)->numBranches( );
    
    return nb;
  }

  unsigned int NeuronMorphology::numAxonBranches( void ) const
  {
    unsigned int nb = 0;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if  ((*it)->asAxon( ))
	nb += (*it)->numBranches( );

    return nb;
  }

  unsigned int NeuronMorphology::numNeuriteBifurcations( void ) const
  {
    unsigned int nb = 0;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      nb += (*it)->numBifurcations( );

    return nb;
  }

  unsigned int NeuronMorphology::numDendriteBifurcations( void ) const
  {
    unsigned int nb = 0;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asDendrite( ))
	nb += (*it)->numBifurcations( );

    return nb;
  }

  unsigned int NeuronMorphology::numAxonBifurcations( void ) const
  {
    unsigned int nb = 0;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if  ((*it)->asAxon( ))
	nb += (*it)->numBifurcations( );

    return nb;
  }

  float NeuronMorphology::volume( void ) const
  {
    return this->neuritesVolume( ) + _soma.volume( );
  }

  float NeuronMorphology::neuritesVolume( void ) const
  {
    return this->dendritesVolume( ) + this->axonVolume( );
  }

  float NeuronMorphology::dendritesVolume( void ) const
  {
    float volume = 0.0f;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asDendrite( ))
	volume += (*it)->volume( );

    return volume;
  }

  float NeuronMorphology::axonVolume( void ) const
  {
    float volume = 0.0f;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asAxon( ))
	volume += (*it)->volume( );

    return volume;
  }

  float NeuronMorphology::surface( void ) const
  {
    return this->neuritesSurface( ) + _soma.surface( );
  }

  float NeuronMorphology::neuritesSurface( void ) const
  {
    return this->dendritesSurface( ) + this->axonSurface( );
  }

  float NeuronMorphology::dendritesSurface( void ) const
  {
    float surface = 0.0f;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asDendrite( ))
	surface += (*it)->surface( );

    return surface;
  }

  float NeuronMorphology::axonSurface( void ) const
  {
    float surface = 0.0f;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asAxon( ))
	surface += (*it)->surface( );

    return surface;
  }

  float NeuronMorphology::length( void ) const
  {
    return this->neuritesLength( );
  }

  float NeuronMorphology::neuritesLength( void ) const
  {
    return this->dendritesLength( ) + this->axonLength( );
  }

  float NeuronMorphology::dendritesLength( void ) const
  {
    float length = 0;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asDendrite( ))
	length += (*it)->length( );

    return length;
  }

  float NeuronMorphology::axonLength( void ) const
  {
    float length = 0.0f;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asAxon( ))
	length += (*it)->length( );

    return length;
  }

  Dendrites * NeuronMorphology::dendrites( void ) const
  {
    Dendrites *dendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
      if ((*it)->asDendrite( ))
	dendrites->push_back((*it)->asDendrite( ));

    return dendrites;
  }

  Dendrites * NeuronMorphology::basalDendrites(void) const
  {

    Dendrites *dendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
    {
      if ((*it)->asDendrite( ) &&
	  ((*it)->asDendrite( )->dendriteType( ) == Dendrite::BASAL))
	dendrites->push_back((*it)->asDendrite( ));
    }

    return dendrites;
  }

  Dendrites * NeuronMorphology::apicalDendrites( void ) const
  {
    Dendrites * dendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
    {
      if ((*it)->asDendrite( ) &&
	  ((*it)->asDendrite( )->dendriteType( ) == Dendrite::APICAL))
	dendrites->push_back((*it)->asDendrite( ));
    }

    return dendrites;
  }

  Dendrite * NeuronMorphology::apicalDendrite( void ) const
  {
    for (Neurites::const_iterator it = _neurites.begin( );
	 it != _neurites.end( ); ++it)
    {
      if ((*it)->asDendrite( ) &&
	  ((*it)->asDendrite( )->dendriteType( ) == Dendrite::APICAL))
        return (*it)->asDendrite( );
    }

    return NULL;
  }

  Neurites & NeuronMorphology::neurites( void )
  {
    return _neurites;
  }

  Soma & NeuronMorphology::soma( void )
  {
    return _soma;
  }


} // namespace nsol

// EOF
