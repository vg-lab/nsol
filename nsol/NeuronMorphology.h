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

#include <nsol/nsol_export.h>

#include "Morphology.h"
#include "Node.h"
#include "Soma.h"
#include "Axon.h"
#include "Neurite.h"
#include "Dendrite.h"
#include "Container/Dendrites.h"
#include "Container/Neurites.h"
#include "Container/Neurons.h"
#include "Container/Axons.h"

#include <string>

namespace nsol
{

    class NeuronMorphologyStats;

    /*! \class NeuronMorphology
     \brief A class to represent morphology of neurons.

     TODO: extend long description
     */
    class NeuronMorphology : public Morphology
    {
      public:
        /**
         * Default Neuron class constructor.
         * TODO: construct protected objects
         */
        NSOL_EXPORT
        NeuronMorphology(void);

        NSOL_EXPORT
        NeuronMorphology(SomaPtr soma);

        NSOL_EXPORT
        virtual ~NeuronMorphology(void);

        /**
         * Method to set the neuronal soma.
         * @param soma pointer to the soma to be setted.
         * @return pointer to the setted soma
         */
        NSOL_EXPORT
        SomaPtr soma(SomaPtr soma);

        /**
         * Method to add a new neurite to the neuron.
         * @param neurite pointer to the neurite to be added.
         * @return pointer to the added neurite.
         */
        NSOL_EXPORT
        NeuritePtr addNeurite(NeuritePtr neurite);

        /**
         * Method to get all the dendrites in a container.
         * Memory for the container is allocated.
         * @return pointer to the container of Dendrites
         */
        NSOL_EXPORT
        Dendrites* dendrites(void) const;

        /**
         * Method to get all the basal dendrites in a container.
         * Memory for the container is allocated.
         * @return pointer to the container of Dendrites
         */
        NSOL_EXPORT
        Dendrites* basalDendrites(void) const;

        /**
         * Method to get all the apical dendrites in a container.
         * Memory for the container is allocated.
         * @return pointer to the container of Dendrites
         */
        NSOL_EXPORT
        Dendrites* apicalDendrites(void) const;

        /**
         * Method to get the first apical dendrite.
         * @return pointer to the apical dendrite.
         */
        NSOL_EXPORT
        DendritePtr apicalDendrite(void) const;

        /**
         * Method to get all the axons in a container.
         * Memory for the container is allocated.
         * @return pointer to the container of Axons.
         */
        NSOL_EXPORT
        Axons* axons() const;

        NSOL_EXPORT
        virtual Neurites& neurites(void);

        NSOL_EXPORT
        const Neurites& neurites(void) const;

        NSOL_EXPORT
        virtual Neurons& parentNeurons(void);

        NSOL_EXPORT
        const Neurons& parentNeurons(void) const;

        NSOL_EXPORT
        SomaPtr soma(void);

        NSOL_EXPORT
        virtual NeuronMorphologyStats* stats(void)
        {
            return nullptr;
        }

        NSOL_EXPORT
        void addParentNeuron(NeuronPtr neuron);

        NSOL_EXPORT
        virtual NeuronMorphologyPtr asNeuronMorphology(void)
        {
            return this;
        }

        NSOL_EXPORT
        virtual NeuronMorphologyPtr clone(void) const;

        NSOL_EXPORT
        bool operator==(NeuronMorphology& other);

        NSOL_EXPORT
        bool operator!=(NeuronMorphology& other);

      protected:
        SomaPtr _soma;
        Neurites _neurites;
        Neurons _parentNeurons;
    };

} // namespace nsol

#endif

// EOF
