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

  Neuron::Neuron( bool initCreateMorphology,
                  const unsigned short initLayer,
                  const unsigned int initGid,
                  const Matrix4_4f initTransform,
                  const MiniColumnPtr initMiniColumn,
                  const Neuron::TNeuronType initType )
    : _morphology( nullptr )
    , _miniColumn( initMiniColumn )
    , _transform( initTransform )
    , _layer( initLayer )
    , _gid( initGid )
    , _type( initType )
  {
    if ( initCreateMorphology )
      _morphology = NeuronMorphologyPtr( new NeuronMorphology );
  }

  Neuron::Neuron( const NeuronMorphologyPtr initNeuronMorphology,
                  const unsigned short initLayer,
                  const unsigned int initGid,
                  const Matrix4_4f initTransform,
                  const MiniColumnPtr initMiniColumn,
                  const Neuron::TNeuronType initType )
      : _morphology( initNeuronMorphology )
      , _miniColumn( initMiniColumn )
      , _transform( initTransform )
      , _layer( initLayer )
      , _gid( initGid )
      , _type( initType )
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

  void Neuron::morphology( NeuronMorphologyPtr newMorphology )
  {
    _morphology = newMorphology;
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

  void Neuron::miniColumn(MiniColumnPtr newMiniColumn)
  {
    _miniColumn = newMiniColumn;
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
