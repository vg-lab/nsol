/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
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
#ifndef __NSOL_NEURON_MORPHOLOGY_SECTION__
#define __NSOL_NEURON_MORPHOLOGY_SECTION__

#include <nsol/api.h>
#include "Section.h"

namespace nsol
{

  class NeuronMorphologySectionStats;

  class NeuronMorphologySection
    : public Section
  {

  public:

    /**
     * Default constructor
     */
    NSOL_API
    NeuronMorphologySection( void );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~NeuronMorphologySection( );

    /**
     * Method to get the gid of the neuron morphology section.
     * @return gid
     */
    NSOL_API
    unsigned int id( void );

    /**
     * Method to set the gid of the neuron morphology section.
     * @param gid
     */
    NSOL_API
    void id (unsigned int id_ );

    /**
     * Gets the parent Neurite of the Neuron Morphology Section
     * @return pointer to the parent Neurite
     */
    NSOL_API
    NeuritePtr neurite( void );

    /**
     * Sets the parent neurite of this Neuron Morphology Section
     * @param neurite pointer to parent neurite
     */
    NSOL_API
    void neurite( NeuritePtr neurite );

    /**
     * Returns object as SectionStats
     * @return pointer to SectionStats object
     */
    NSOL_API
    virtual NeuronMorphologySectionStats * stats( void );

    NSOL_API
    virtual SectionPtr clone( void ) const;

    NSOL_API
    virtual SectionPtr asNeuronMorphologySection( void )
    {
      return this;
    }

  protected:

    //! Unique id
    unsigned int _id;

    //! Parent neurite of the section
    NeuritePtr _neurite;

  }; // class Neuron Morphology Section

} // namespace nsol

#endif
