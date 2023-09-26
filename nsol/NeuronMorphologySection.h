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
    unsigned int id( void ) const;

    /**
     * Method to set the gid of the neuron morphology section.
     * @param id
     */
    NSOL_API
    void id ( unsigned int id );

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
     * Gets the parent Section of this Section
     * @return pointer to the parent Section
     */
    NSOL_API
    SectionPtr parent( void );

    /**
     * Sets the parent Section of this Section
     * @param parent pointer to parent Section
     */
    NSOL_API
    void parent( SectionPtr parent );

    /**
     * Adds child Section to this Section
     * @param section pointer to the section to be added
     */
    NSOL_API
    void addChild( SectionPtr section );

    /**
     * Return the children sections
     * @return container of children sections
     */
    NSOL_API
    Sections& children( void );

    NSOL_API
    const Sections& children( void ) const;

    /**
     * Adds a Node at the end of Section
     * @param node pointer to the Node to add.
     *        Precondition: pointer is not null.
     */
    NSOL_API
    virtual void addNode( NodePtr node );

    /**
     * Gets the first Node of the Section.
     * @return pointer to the first Node, null in case it doesn't have any
     */
    NSOL_API
    NodePtr firstNode( void );

    /**
     * Sets first Node of the Section. This method is virtual to allow
     * reimplementation for cached objects and dirty state propagation
     * @param firstNode pointer to the Node.
     */
    NSOL_API
    virtual void firstNode( NodePtr firstNode );

    /**
     * Gets the last Node of the Section.
     * @return pointer to the last Node, null in case it doesn't have any
     */
    NSOL_API
    NodePtr lastNode( void );


    /**
     * Returns object as SectionStats
     * @return pointer to SectionStats object
     */
    NSOL_API
    virtual NeuronMorphologySectionStats* stats( void );

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
