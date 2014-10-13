/**
 * @file    Neuron.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "Neuron.h"

namespace nsol
{

  Neuron::Neuron( bool createMorphology,
		  const unsigned short layer,
		  const unsigned int gid, 
		  const Matrix4_4f transform,
		  const MiniColumnPtr miniColumn,
    		  const Neuron::TNeuronType type )
    : _morphology( nullptr )
    , _miniColumn( miniColumn )
    , _transform( transform )
    , _layer( layer )
    , _gid( gid )
    , _type( type )
  {
    if (createMorphology)
      _morphology = NeuronMorphologyPtr( new NeuronMorphology );
  }

    Neuron::Neuron( const NeuronMorphologyPtr neuronMorphology,
		    const unsigned short layer,
		    const unsigned int gid,
		    const Matrix4_4f transform,
		    const MiniColumnPtr miniColumn,
		    const Neuron::TNeuronType type )

      : _morphology( neuronMorphology )
      , _miniColumn( miniColumn )
      , _transform( transform )
      , _layer( layer )
      , _gid( gid )
      , _type( type )
    {
    }


  Neuron::~Neuron( void )
  {
  }

  bool Neuron::hasMorphology( void ) const
  {
    return ( _morphology != NULL );
  }

  NeuronMorphologyPtr Neuron::createMorphology( void )
  {
    if ( _morphology )
      std::cerr << "nsol::Neuron::createMorphology: " 
		<< "warning, morphology already exist" 
		<< std::endl;
    
    _morphology = NeuronMorphologyPtr( new NeuronMorphology );
    
    return _morphology;
  }

  NeuronMorphologyPtr Neuron::morphology( void ) const
  {
    return _morphology;
  }

  void Neuron::morphology( NeuronMorphologyPtr morphology )
  {
    _morphology = morphology;
  }

  NeuritePtr Neuron::addNeurite( Neurite::TNeuriteType neuriteType )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return _morphology->addNeurite(neuriteType);
  }

  DendritePtr Neuron::addDendrite( Dendrite::TDendriteType dendriteType )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    if ( dendriteType == Dendrite::APICAL )
      _type = PYRAMIDAL;

    return _morphology->addDendrite(dendriteType);
  }

  AxonPtr Neuron::addAxon()
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->addAxon();
  }

  unsigned int Neuron::numNeurites( void )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->numNeurites();
  }

  unsigned int Neuron::numDendrites( void )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->numDendrites();
  }

  unsigned int Neuron::numNeuriteBranches()
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->numNeuriteBranches();
  }

  unsigned int Neuron::numDendriteBranches()
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->numDendriteBranches();
  }

  unsigned int Neuron::numAxonBranches()
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->numAxonBranches();
  }

  unsigned int Neuron::numNeuriteBifurcations()
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->numNeuriteBifurcations();
  }

  unsigned int Neuron::numDendriteBifurcations()
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->numDendriteBifurcations();
  }

  unsigned int Neuron::numAxonBifurcations()
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->numAxonBifurcations();
  }

  float Neuron::volume() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->volume();
  }

  float Neuron::neuritesVolume() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->neuritesVolume();
  }

  float Neuron::dendritesVolume() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->dendritesVolume();
  }

  float Neuron::axonVolume() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->axonVolume();
  }

  float Neuron::surface() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->surface();
  }

  float Neuron::neuritesSurface() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->neuritesSurface();
  }

  float Neuron::dendritesSurface() const
  { 
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->dendritesSurface();
  }

  float Neuron::axonSurface() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->axonSurface();
  }

  float Neuron::length() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->length();
  }

  float Neuron::neuritesLength() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->neuritesLength();
  }

  float Neuron::dendritesLength() const
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->dendritesLength();
  }

  float Neuron::axonLength() const
  {    
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return  _morphology->axonLength();
  }

  /**
   * Method to get all the dendrites in a container.
   * Memory for the container is allocated.
   * @return pointer to the container of Dendrites
   */
  Dendrites * Neuron::dendrites( void )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return _morphology->dendrites();
  }

  /**
   * Method to get all the basal dendrites in a container.
   * Memory for the container is allocated.
   * @return pointer to the container of Dendrites
   */
  Dendrites * Neuron::basalDendrites( void )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return _morphology->basalDendrites();
  }


  Dendrites * Neuron::apicalDendrites( void )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return _morphology->apicalDendrites();
  }

  DendritePtr Neuron::apicalDendrite( void )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return _morphology->apicalDendrite();
  }

  Neurites & Neuron::neurites( void )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return _morphology->neurites();
  }

  Soma & Neuron::soma( void )
  {
    if ( !this->hasMorphology( ) )
      throw std::runtime_error("No morphology in neuron object");

    return _morphology->soma();
  }

  Matrix4_4f & Neuron::transform( void ) 
  {
    return _transform;
  }

  unsigned short & Neuron::layer( void )
  {
    return _layer;
  }

  
  unsigned int & Neuron::gid( void )
  {
    return _gid;
  }

  void Neuron::miniColumn(MiniColumnPtr miniColumn)
  {
    _miniColumn = miniColumn;
  }

  MiniColumnPtr & Neuron::miniColumn( void )
  {
    return _miniColumn;
  }

  Neuron::TNeuronType & Neuron::neuronType( void )
  {
    // if (this->apicalDendrites()->size() == 0)
    //   assert( PYRAMIDAL == _type);
    // else
    //   assert( INTER == _type);

    return _type;

  };


} // namespace nsol

// EOF
