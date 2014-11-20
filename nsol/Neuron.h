/**
 * @file    Neuron.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
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
    typedef enum {PYRAMIDAL = 0, INTER} TNeuronType;

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
    void morphology(NeuronMorphologyPtr morphology);

    /**
     * Method to add a new neurite to the neuron.
     * @param neuriteType type of Neurite.
     * @see Neurite::TNeuriteType
     * @return pointer to the added neurite
     */
    NSOL_API
    NeuritePtr addNeurite( Neurite::TNeuriteType neuriteType =
                           Neurite::DENDRITE );


    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType type of Dendrite
     * @see ndsl::Dendrite::TDendriteType
     * @return pointer to the added dendrite
     */
    NSOL_API
    DendritePtr addDendrite( Dendrite::TDendriteType dendriteType =
                             Dendrite::BASAL);

    /**
     * Method to add a new axon to the neuron.
     * @return pointer to the added axon
     */
    NSOL_API
    AxonPtr addAxon( void );

    // NSOL_API
    // unsigned int numNeurites( void );

    // NSOL_API
    // unsigned int numDendrites( void );

    // NSOL_API
    // unsigned int numNeuriteBranches( void );

    // NSOL_API
    // unsigned int numDendriteBranches( void );

    // NSOL_API
    // unsigned int numAxonBranches( void );

    // NSOL_API
    // unsigned int numNeuriteBifurcations( void );

    // NSOL_API
    // unsigned int numDendriteBifurcations( void );

    // NSOL_API
    // unsigned int numAxonBifurcations( void );

    // NSOL_API
    // float volume( void ) const;

    // NSOL_API
    // float neuritesVolume( void ) const;

    // NSOL_API
    // float dendritesVolume( void ) const;

    // NSOL_API
    // float axonVolume( void ) const;

    // NSOL_API
    // float surface( void ) const;

    // NSOL_API
    // float neuritesSurface( void ) const;

    // NSOL_API
    // float dendritesSurface( void ) const;

    // NSOL_API
    // float axonSurface( void ) const;

    // NSOL_API
    // float length( void ) const;

    // NSOL_API
    // float neuritesLength( void ) const;

    // NSOL_API
    // float dendritesLength( void ) const;

    // NSOL_API
    // float axonLength( void ) const;

    /**
     * Method to get all the dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    NSOL_API
    Dendrites * dendrites( void );

    /**
     * Method to get all the basal dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    NSOL_API
    Dendrites * basalDendrites( void );

    /**
     * Method to get all the apical dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    NSOL_API
    Dendrites *apicalDendrites( void );

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType  .
     * @see Neurite::TNeuriteType
     * @return pointer to the added dendrite
     */
    NSOL_API
    DendritePtr apicalDendrite( void );

    NSOL_API
    Neurites & neurites( void );

    NSOL_API
    Soma & soma( void );

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
