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

    /** \brief Returns the string of the given morphological type.
     * \param[in] type Morphological type.
     *
     */
    static std::string typeToString(const TMorphologicalType type)
    {
      std::string typeStr = "Undefined";

      switch(type)
      {
        case PYRAMIDAL:
          typeStr = "Pyramidal";
          break;
        case INTERNEURON:
          typeStr = "Interneuron";
          break;
        case BASKET:
          typeStr = "Basket";
          break;
        case STELLATE:
          typeStr = "Stellate";
          break;
        case GOLGI:
          typeStr = "Golgi";
          break;
        case GRANULE:
          typeStr = "Granule";
          break;
        case LUGARO:
          typeStr = "Lugaro";
          break;
        case UNIPOLAR_BRUSH:
          typeStr = "Unipolar brush";
          break;
        case PURKINJE:
          typeStr = "Purkinje";
          break;
        case CHANDELIER:
          typeStr = "Chandelier";
          break;
        case INFERIOR_OLIVE:
          typeStr = "Inferior olive";
          break;
        case DEEP_CEREBELLAR_NUCLEI:
          typeStr = "Deep cerebellar nuclei";
          break;
        case UNDEFINED:
          // fall through
        default:
          break;
      }

      return typeStr;
    }

    /** \brief Returns the color assigned to the type. Colors are now
     * "random", should use the ones defined in other HDF5 activity
     * file. TODO: change colors.
     * \param[in] type Morphological type.
     *
     */
    static Eigen::Vector3f typeToColor(const TMorphologicalType type)
    {
      Eigen::Vector3f color{0,0,0};

      auto hex2float = [](int v){ return static_cast<float>(v)/255.f; };

      switch(type)
      {
        case PYRAMIDAL:
          color = { 1,0,0 };
          break;
        case INTERNEURON:
          color = { 0,1,0 };
          break;
        case BASKET: // F37735
          color = { hex2float(0xF3), hex2float(0x77), hex2float(0x35) };
          break;
        case STELLATE: // FFC425
          color = { hex2float(0xFF), hex2float(0xC4), hex2float(0x25) };
          break;
        case GOLGI: // 332EBC
          color = { hex2float(0x33), hex2float(0x2E), hex2float(0xBC) };
          break;
        case GRANULE: // E62214
          color = { hex2float(0xE6), hex2float(0x22), hex2float(0x14) };
          break;
        case LUGARO:
          color = { 0,1,1 };
          break;
        case UNIPOLAR_BRUSH:
          color = { 1,0,0.5 };
          break;
        case PURKINJE: // 0F8944
          color = { hex2float(0x0F), hex2float(0x89), hex2float(0x44) };
          break;
        case CHANDELIER:
          color = { 1,0.5,0.5 };
          break;
        case INFERIOR_OLIVE:
          color = { 0.5,0,0 };
          break;
        case DEEP_CEREBELLAR_NUCLEI:
          color = { 0,0.5,0 };
          break;
        case UNDEFINED:
          // fall through
        default:
          break;
      }

      return color;
    }

    static Eigen::Vector3f layerToColor(const unsigned short layer)
    {
      Eigen::Vector3f color{0,0,0};

      switch(layer)
      {
        case 1:
          color = { 1,0,0 };
          break;
        case 2:
          color = { 1,1,0 };
          break;
        case 3:
          color = { 0,1,0 };
          break;
        case 4:
          color = { 0,1,1 };
          break;
        case 5:
          color = { 0,0,1 };
          break;
        case 6:
          color = { 1,0,1 };
          break;
        default:
          break;
      }

      return color;
    }

    //! Type of neuron based in neuron functionality
    typedef enum : uint8_t
    {
      UNDEFINED_FUNCTIONAL_TYPE = 0,
      INHIBITORY,
      EXCITATORY
    } TFunctionalType;

    static std::string functionToString(const TFunctionalType type)
    {
      std::string typeStr = "Undefined";

      switch(type)
      {
        case INHIBITORY: typeStr = "Inhibitory"; break;
        case EXCITATORY: typeStr = "Excitatory"; break;
        default:
        case UNDEFINED_FUNCTIONAL_TYPE:
          break;
      }

      return typeStr;
    }

    static Eigen::Vector3f functionToColor(const TFunctionalType type)
    {
      Eigen::Vector3f color{0,0,0};

      switch(type)
      {
        case INHIBITORY:
          color = { 1,0,0 };
          break;
        case EXCITATORY:
          color = { 0,0,1 };
          break;
        case UNDEFINED_FUNCTIONAL_TYPE:
        default:
          break;
      }

      return color;
    }

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
