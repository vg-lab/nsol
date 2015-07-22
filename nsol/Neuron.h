/**
 * @file    Neuron.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
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
    : public Object
  {

  public:

    //! Type of dendrite
    typedef enum {
      UNDEFINED = -1,
      PYRAMIDAL = 0,
      INTER
    } TNeuronType;


    NSOL_API
    Neuron( const NeuronMorphologyPtr neuronMorphology = nullptr,
            const unsigned short layer = 0,
            const unsigned int gid = 0,
            const Matrix4_4f transform = Matrix4_4f::IDENTITY,
            const MiniColumnPtr miniColumn = nullptr,
            const TNeuronType type = PYRAMIDAL );

    NSOL_API
    virtual ~Neuron( void );

    NSOL_API
    bool hasMorphology() const;

    // NSOL_API
    // NeuronMorphologyPtr createMorphology( void );

    NSOL_API
    NeuronMorphologyPtr morphology( void ) const;

    NSOL_API
    void morphology( NeuronMorphologyPtr morphology );

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
     * Method to get the neuron type.
     * @return neuron type
     */
    NSOL_API
    TNeuronType & neuronType();


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

    //! Type of neuron
    TNeuronType _type;

  };

 
}

#endif
