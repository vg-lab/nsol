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
#ifndef __NSOL_NEURON_MORPHOLOGY__
#define __NSOL_NEURON_MORPHOLOGY__

#include <nsol/api.h>

#include "Morphology.h"
#include "Node.h"
#include "Soma.h"
#include "Axon.h"
#include "Neurite.h"
#include "Dendrite.h"
#include "Container/Dendrites.h"
#include "Container/Neurites.h"
#include "Container/Neurons.h"

#include <string>

namespace nsol
{

  class NeuronMorphologyStats;

  /*! \class NeuronMorphology
   \brief A class to represent morphology of neurons.

   TODO: extend long description
   */
  class NeuronMorphology
    : public Morphology
  {

  public:

    /**
     * Default Neuron class constructor.
     * TODO: construct protected objects
     */
    NSOL_API
    NeuronMorphology( void );

    NSOL_API
    NeuronMorphology( SomaPtr soma );

    NSOL_API
    virtual ~NeuronMorphology( void );

    /**
     * Method to set the neuronal soma.
     * @param soma pointer to the soma to be setted.
     * @return pointer to the setted soma
     */
    NSOL_API
    SomaPtr soma( SomaPtr soma );

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

    /**
     * Returns axon if exists
     * @return pointer to the axon or nullptr in case it doens't exist
     */
    NSOL_API
    AxonPtr axon( void ) const;


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

    NSOL_API
    virtual NeuronMorphologyPtr clone( void ) const;

    NSOL_API
    bool operator == ( NeuronMorphology & other );

    NSOL_API
    bool operator != ( NeuronMorphology & other );

  protected:

    SomaPtr _soma;
    Neurites _neurites;
    Neurons _parentNeurons;
  };


} // namespace nsol

#endif

// EOF
