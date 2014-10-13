/**
 * @file    Neuron.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_NEURON__
#define __NSOL_NEURON__

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
    Neuron( bool createMorphology = true,
	    const unsigned short layer = 0,
	    const unsigned int gid = 0,
	    const Matrix4_4f transform = Matrix4_4f::IDENTITY,
	    const MiniColumnPtr miniColumn = nullptr,
	    const TNeuronType type = PYRAMIDAL);

    Neuron(const NeuronMorphologyPtr neuronMorphology,
           const unsigned short layer = 0,
           const unsigned int gid = 0,
           const Matrix4_4f transform = Matrix4_4f::IDENTITY,
           const MiniColumnPtr miniColumn = nullptr,
	   const TNeuronType type = PYRAMIDAL);


    ~Neuron( void );

    bool hasMorphology() const;

    NeuronMorphologyPtr createMorphology( void );

    NeuronMorphologyPtr morphology( void ) const;

    void morphology(NeuronMorphologyPtr morphology);

    /**
     * Method to add a new neurite to the neuron.
     * @param neuriteType type of Neurite.
     * @see Neurite::TNeuriteType
     * @return pointer to the added neurite
     */
    NeuritePtr addNeurite( Neurite::TNeuriteType neuriteType = 
			   Neurite::DENDRITE );
    

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType type of Dendrite
     * @see ndsl::Dendrite::TDendriteType
     * @return pointer to the added dendrite
     */
    DendritePtr addDendrite( Dendrite::TDendriteType dendriteType = 
			   Dendrite::BASAL);

    /**
     * Method to add a new axon to the neuron.
     * @return pointer to the added axon
     */
    AxonPtr addAxon( void );

    unsigned int numNeurites( void );

    unsigned int numDendrites( void );

    unsigned int numNeuriteBranches( void );

    unsigned int numDendriteBranches( void );

    unsigned int numAxonBranches( void );

    unsigned int numNeuriteBifurcations( void );

    unsigned int numDendriteBifurcations( void );

    unsigned int numAxonBifurcations( void );

    float volume( void ) const;

    float neuritesVolume( void ) const;

    float dendritesVolume( void ) const;

    float axonVolume( void ) const;

    float surface( void ) const;

    float neuritesSurface( void ) const;

    float dendritesSurface( void ) const;

    float axonSurface( void ) const;

    float length( void ) const;

    float neuritesLength( void ) const;

    float dendritesLength( void ) const;

    float axonLength( void ) const;

    /**
     * Method to get all the dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites * dendrites( void );

    /**
     * Method to get all the basal dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites * basalDendrites( void );
   
    /**
     * Method to get all the apical dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites *apicalDendrites( void );

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType  .
     * @see Neurite::TNeuriteType
     * @return pointer to the added dendrite
     */
    DendritePtr apicalDendrite( void );

    Neurites & neurites( void );

    Soma & soma( void );

    /**
     * Method to get the transformation matrix of the neuron.
     * @return transformation matrix
     */
    Matrix4_4f & transform( void );

    /**
     * Method to get-set the layer of the neuron.
     * @return layer
     */
    unsigned short & layer( void );

    /**
     * Method to get-set the layer of the neuron.
     * @return layer
     */
    unsigned int & gid( void );

    void miniColumn(MiniColumnPtr miniColumn);

    MiniColumnPtr &miniColumn( void );

    /**
     * Method to get the neuron type.
     * @return neuron type
     */
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
