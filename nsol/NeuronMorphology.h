/**
 * @file    NeuronMorphology.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NEURON_MORPHOLOGY__
#define __NSOL_NEURON_MORPHOLOGY__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Soma.h>
#include <nsol/Axon.h>
#include <nsol/Neurite.h>
#include <nsol/Dendrite.h>
#include <nsol/Container/Dendrites.h>
#include <nsol/Container/Neurites.h>

namespace nsol
{

  /*! \class NeuronMorphology
   \brief A class to represent morphology of neurons.

   TODO: extend long description
   */
  class NeuronMorphology
  {

  public:

    /**
     * Default Neuron class constructor.
     * TODO: construct protected objects
     */
    NSOL_API
    NeuronMorphology( void );

    NSOL_API
    ~NeuronMorphology( void );

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
                             Dendrite::BASAL );

    /**
     * Method to add a new axon to the neuron.
     * @return pointer to the added axon
     */
    NSOL_API
    AxonPtr addAxon( void );

    // NSOL_API
    // unsigned int numNeurites( void ) const;

    // NSOL_API
    // unsigned int numDendrites( void ) const;

    // NSOL_API
    // unsigned int numNeuriteBranches( void ) const;

    // NSOL_API
    // unsigned int numDendriteBranches( void ) const ;

    // NSOL_API
    // unsigned int numAxonBranches( void ) const;

    // NSOL_API
    // unsigned int numNeuriteBifurcations( void ) const;

    // NSOL_API
    // unsigned int numDendriteBifurcations( void ) const;

    // NSOL_API
    // unsigned int numAxonBifurcations( void ) const;

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
    Dendrites * dendrites( void ) const;

    /**
     * Method to get all the basal dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    NSOL_API
    Dendrites * basalDendrites( void ) const;

    /**
     * Method to get all the apical dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    NSOL_API
    Dendrites * apicalDendrites( void ) const;

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType  .
     * @see Neurite::TNeuriteType
     * @return pointer to the added dendrite
     */
    NSOL_API
    DendritePtr apicalDendrite( void ) const;

    NSOL_API
    Neurites & neurites( void );

    NSOL_API
    Soma & soma( void );

  protected:

    Soma _soma;
    Neurites _neurites;

  };


} // namespace nsol

#endif

// EOF
