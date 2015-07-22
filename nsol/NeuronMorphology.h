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

#include "NsolTypes.h"
#include "Soma.h"
#include "Axon.h"
#include "Neurite.h"
#include "Dendrite.h"
#include "Container/Dendrites.h"
#include "Container/Neurites.h"
#include "Container/Neurons.h"

namespace nsol
{

  class NeuronMorphologyStats;

  /*! \class NeuronMorphology
   \brief A class to represent morphology of neurons.

   TODO: extend long description
   */
  class NeuronMorphology
    : public virtual Object
  {

  public:

    /**
     * Default Neuron class constructor.
     * TODO: construct protected objects
     */
    NSOL_API
    NeuronMorphology( SomaPtr soma );

    NSOL_API
    virtual ~NeuronMorphology( void );

    /**
     * Method to add a new neurite to the neuron.
     * @param neurite pointer to the neurite to be added.
     * @return pointer to the added neurite
     */
    NSOL_API
    NeuritePtr addNeurite( NeuritePtr neurite );

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
     * Method to get the first apical dendrite
     * @return pointer to the apical dendrite. nullptr in case not found.
     */
    NSOL_API
    DendritePtr apicalDendrite( void ) const;

    NSOL_API
    virtual Neurites & neurites( void );

    NSOL_API
    const Neurites & neurites( void ) const;

    NSOL_API
    virtual Neurons & parentNeurons( void );

    NSOL_API
    const Neurons & parentNeurons( void ) const;

    NSOL_API
    SomaPtr soma( void );

    NSOL_API
    virtual NeuronMorphologyStats * stats( void )
    {
      return nullptr;
    }

    NSOL_API
    void addParentNeuron( NeuronPtr neuron );

    NSOL_API
    virtual NeuronMorphologyPtr asNeuronMorphology( void )
    {
      return this;
    }


  protected:

    Soma * _soma;
    Neurites _neurites;
    Neurons _parentNeurons;

  };


} // namespace nsol

#endif

// EOF
