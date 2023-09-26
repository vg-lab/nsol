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
#ifndef __NSOL_NEURON__
#define __NSOL_NEURON__

#include <nsol/api.h>
#include "NsolTypes.h"
#include "Object.h"
#include "NeuronMorphology.h"
#include "Soma.h"
#include "Neurite.h"
#include "Dendrite.h"
#include "Container/Dendrites.h"
#include "Container/Neurites.h"

namespace nsol
{

  /*! \class Neuron
    \brief A class to represent neurons.

    TODO: extend long description
  */
  class Neuron
    : public virtual Object
  {

  public:

    //! Type of neuron based in neuron morphology
    typedef enum : uint8_t
    {
      //! Type for undefined
      UNDEFINED = 0,
      //! General pyramidal
      PYRAMIDAL,
      //! General interneuron
      INTERNEURON,
      //! Cerebellum interneurons
      BASKET,
      STELLATE,
      GOLGI,
      GRANULE,
      LUGARO,
      UNIPOLAR_BRUSH,
      //! Other Cerebellum cells
      PURKINJE,
      CHANDELIER,
      INFERIOR_OLIVE,
      DEEP_CEREBELLAR_NUCLEI
    } TMorphologicalType;

    //! Type of neuron based in neuron functionality
    typedef enum : uint8_t
    {
      UNDEFINED_FUNCTIONAL_TYPE = 0,
      INHIBITORY,
      EXCITATORY
    } TFunctionalType;



    NSOL_API
    Neuron( const NeuronMorphologyPtr neuronMorphology = nullptr,
            const unsigned short layer = 0,
            const unsigned int gid = 0,
            const Matrix4_4f transform = Matrix4_4fIdentity,
            const MiniColumnPtr miniColumn = nullptr,
            const TMorphologicalType morphologicalType = UNDEFINED,
            const TFunctionalType functionalType = UNDEFINED_FUNCTIONAL_TYPE );

    NSOL_API
    virtual ~Neuron( void );

    NSOL_API
    bool hasMorphology() const;

    NSOL_API
    bool isMorphologyLoaded( ) const;

    // NSOL_API
    // NeuronMorphologyPtr createMorphology( void );

    NSOL_API
    NeuronMorphologyPtr morphology( void ) const;

    NSOL_API
    virtual void morphology( NeuronMorphologyPtr morphology );

    /**
     * Method to get the transformation matrix of the neuron.
     * @return transformation matrix
     */
    NSOL_API
    Matrix4_4f & transform( void );

    /**
     * Method to get-set the layer of the neuron.
     * @return layer
     */
    NSOL_API
    unsigned short & layer( void );

    /**
     * Method to get-set the layer of the neuron.
     * @return layer
     */
    NSOL_API
    unsigned int & gid( void );

    NSOL_API
    void miniColumn(MiniColumnPtr miniColumn);

    NSOL_API
    MiniColumnPtr &miniColumn( void );

    /**
     * Method to get the neuron type based in morphology.
     * @return neuron type
     */
    NSOL_API
    TMorphologicalType & morphologicalType();

    /**
     * Method to get the neuron type based in functionality.
     * @return neuron type
     */
    NSOL_API
    TFunctionalType & functionalType();

    /**
     * Method to know if the neuron is pyramidal type.
     * @return bool
     */
    NSOL_API
    bool isPyramidal( void );

    /**
     * Method to know if the neuron is internuron type.
     * @return bool
     */
    NSOL_API
    bool isInterneuron( void );

    /**
     * Method to know if the neuron is excitatory type.
     * @return bool
     */
    NSOL_API
    bool isExcitatory( void );

    /**
     * Method to know if the neuron is inhibitory type.
     * @return bool
     */
    NSOL_API
    bool isInhibitory( void );

    NSOL_API
    virtual NeuronPtr asNeuron( void )
    {
      return this;
    }


  protected:

    //! Morphology pointer
    NeuronMorphologyPtr _morphology;

    //! Minicolumn pointer
    MiniColumnPtr _miniColumn;

    //! Matrix of global transformation
    Matrix4_4f _transform;

    //! Layer
    unsigned short _layer; //> Layer

    //! Unique id
    unsigned int _gid;

    //! Type of neuron based in morphology
    TMorphologicalType _morphologicalType;

    //! Type of neuron based in functionality
    TFunctionalType _functionalType;

  };
}

#endif
