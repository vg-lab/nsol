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

  Neuron::Neuron( const NeuronMorphologyPtr initNeuronMorphology,
                  const unsigned short initLayer,
                  const unsigned int initGid,
                  const Matrix4_4f initTransform,
                  const MiniColumnPtr initMiniColumn,
                  const Neuron::TMorphologicalType initMorphologicalType,
                  const Neuron::TFunctionalType initFunctionalType )
      : _morphology( initNeuronMorphology )
      , _miniColumn( initMiniColumn )
      , _transform( initTransform )
      , _layer( initLayer )
      , _gid( initGid )
      , _morphologicalType( initMorphologicalType )
      , _functionalType( initFunctionalType )

    {
    }


  Neuron::~Neuron( void )
  {
  }

  bool Neuron::hasMorphology( void ) const
  {
    return ( _morphology != NULL );
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

  Neuron::TMorphologicalType & Neuron::morphologicalType( void )
  {
    return _morphologicalType;
  };

  Neuron::TFunctionalType & Neuron::functionalType( void )
  {
    return _functionalType;
  };

  bool Neuron::isPyramidal( void )
  {
    return _morphologicalType == Neuron::PYRAMIDAL;
  }

  bool Neuron::isInterneuron( void )
  {
    return _morphologicalType == Neuron::INTERNEURON;
  }

  bool Neuron::isExcitatory( void )
  {
    return _functionalType == Neuron::EXCITATORY;
  }

  bool Neuron::isInhibitory( void )
  {
    return _functionalType == Neuron::INHIBITORY;
  }




} // namespace nsol

// EOF
