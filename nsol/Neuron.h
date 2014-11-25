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
#include <nsol/NsolTypes.h>
#include <nsol/NeuronMorphology.h>
#include <nsol/Soma.h>
#include <nsol/Neurite.h>
#include <nsol/Dendrite.h>
#include <nsol/Container/Dendrites.h>
#include <nsol/Container/Neurites.h>

namespace nsol
{

  /*! \class Neuron
    \brief A class to represent neurons.

    TODO: extend long description
  */
  class Neuron
  {

  public:

    //! Type of dendrite
    typedef enum {
      PYRAMIDAL = 0,
      INTER
    } TNeuronType;

    /**
     * Default Neuron class constructor.
     * TODO: construct protected objects
     */
    NSOL_API
    Neuron( bool createMorphology = true,
            const unsigned short layer = 0,
            const unsigned int gid = 0,
            const Matrix4_4f transform = Matrix4_4f::IDENTITY,
            const MiniColumnPtr miniColumn = nullptr,
            const TNeuronType type = PYRAMIDAL);

    NSOL_API
    Neuron(const NeuronMorphologyPtr neuronMorphology,
           const unsigned short layer = 0,
           const unsigned int gid = 0,
           const Matrix4_4f transform = Matrix4_4f::IDENTITY,
           const MiniColumnPtr miniColumn = nullptr,
           const TNeuronType type = PYRAMIDAL);

    NSOL_API
    ~Neuron( void );

    NSOL_API
    bool hasMorphology() const;

    NSOL_API
    NeuronMorphologyPtr createMorphology( void );

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

    NeuronMorphologyPtr _morphology; //> Morphology

    MiniColumnPtr _miniColumn;	//> Minicolumn

    Matrix4_4f _transform; //> Matrix of global transformation

    unsigned short _layer; //> Layer

    unsigned int _gid; //> Neuron id

    TNeuronType _type;

  };


}

#endif
