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
    NeuronMorphology( void );

    ~NeuronMorphology( void );

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
    Dendrite * addDendrite( Dendrite::TDendriteType dendriteType = 
			    Dendrite::BASAL );

    /**
     * Method to add a new axon to the neuron.
     * @return pointer to the added axon
     */
    Axon * addAxon( void );

    unsigned int numNeurites( void ) const;

    unsigned int numDendrites( void ) const;

    unsigned int numNeuriteBranches( void ) const;

    unsigned int numDendriteBranches( void ) const ;

    unsigned int numAxonBranches( void ) const;

    unsigned int numNeuriteBifurcations( void ) const;

    unsigned int numDendriteBifurcations( void ) const;

    unsigned int numAxonBifurcations( void ) const;

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
    Dendrites * dendrites( void ) const;

    /**
     * Method to get all the basal dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites * basalDendrites( void ) const;

    /**
     * Method to get all the apical dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites * apicalDendrites( void ) const;

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType  .
     * @see Neurite::TNeuriteType
     * @return pointer to the added dendrite
     */
    Dendrite * apicalDendrite( void ) const;

    Neurites & neurites( void );

    Soma & soma( void );

  protected:

    Soma _soma;
    Neurites _neurites;

  };


} // namespace nsol

#endif

// EOF
