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

#include <nsol/nsol_export.h>
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
    NSOL_EXPORT
    NeuronMorphologySection( void );

    /**
     * Default destructor
     */
    NSOL_EXPORT
    virtual ~NeuronMorphologySection( );

    /**
     * Method to get the gid of the neuron morphology section.
     * @return gid
     */
    NSOL_EXPORT
    unsigned int id( void ) const;

    /**
     * Method to set the gid of the neuron morphology section.
     * @param id
     */
    NSOL_EXPORT
    void id ( unsigned int id );

    /**
     * Gets the parent Neurite of the Neuron Morphology Section
     * @return pointer to the parent Neurite
     */
    NSOL_EXPORT
    NeuritePtr neurite( void );

    /**
     * Sets the parent neurite of this Neuron Morphology Section
     * @param neurite pointer to parent neurite
     */
    NSOL_EXPORT
    void neurite( NeuritePtr neurite );

     /**
     * Gets the parent Section of this Section
     * @return pointer to the parent Section
     */
    NSOL_EXPORT
    SectionPtr parent( void );

    /**
     * Sets the parent Section of this Section
     * @param parent pointer to parent Section
     */
    NSOL_EXPORT
    void parent( SectionPtr parent );

    /**
     * Adds child Section to this Section
     * @param section pointer to the section to be added
     */
    NSOL_EXPORT
    void addChild( SectionPtr section );

    /**
     * Return the children sections
     * @return container of children sections
     */
    NSOL_EXPORT
    Sections& children( void );

    NSOL_EXPORT
    const Sections& children( void ) const;

    /**
     * Adds a Node at the end of Section
     * @param node pointer to the Node to add.
     *        Precondition: pointer is not null.
     */
    NSOL_EXPORT
    virtual void addNode( NodePtr node );

    /**
     * Gets the first Node of the Section.
     * @return pointer to the first Node, null in case it doesn't have any
     */
    NSOL_EXPORT
    NodePtr firstNode( void );

    /**
     * Sets first Node of the Section. This method is virtual to allow
     * reimplementation for cached objects and dirty state propagation
     * @param firstNode pointer to the Node.
     */
    NSOL_EXPORT
    virtual void firstNode( NodePtr firstNode );

    /**
     * Gets the last Node of the Section.
     * @return pointer to the last Node, null in case it doesn't have any
     */
    NSOL_EXPORT
    NodePtr lastNode( void );


    /**
     * Returns object as SectionStats
     * @return pointer to SectionStats object
     */
    NSOL_EXPORT
    virtual NeuronMorphologySectionStats* stats( void );

    NSOL_EXPORT
    virtual SectionPtr clone( void ) const;

    NSOL_EXPORT
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
