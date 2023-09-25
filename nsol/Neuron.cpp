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
    return ( _morphologicalType == Neuron::INTERNEURON ||
             _morphologicalType == Neuron::BASKET ||
             _morphologicalType == Neuron::STELLATE ||
             _morphologicalType == Neuron::GOLGI ||
             _morphologicalType == Neuron::GRANULE ||
             _morphologicalType == Neuron::LUGARO ||
             _morphologicalType == Neuron::UNIPOLAR_BRUSH );
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
