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
#ifndef __NSOL_NEURON_MORPHOLOGY_SECTION_CACHED_STATS__
#define __NSOL_NEURON_MORPHOLOGY_SECTION_CACHED_STATS__

#include <nsol/api.h>

#include "Cached.h"
#include "NeuronMorphologySectionStats.h"

namespace nsol
{


  /** \class SectionCachedStats
   *  \brief This class allows to cache the stats for sections
   *
   *  Using this class instead of Section or NeuronMorphologySectionStats when
   *  constructing the hierarchy allows to call the method stats from base
   *  NeuronMorphologySection class and get the corresponding volume, surface
   *  and length. If the cached value is dirty then the actual computation
   *  process is done. In case is clean the cached value is returned directly.
   *
   *  Example: @include examples/sectionStats.cpp
   */
  class NeuronMorphologySectionCachedStats
    : public NeuronMorphologySectionStats
    , public Cached<>
  {


  public:

    //! Stats that can be cached for NeuronMorphologySectionStats
    // typedef enum
    // {
    //   SURFACE = 0,
    //   VOLUME,
    //   LENGTH,
    //   SECTION_NUM_CACHED_VALUES
    // } TNeuronMorphologySectionCachedValues;

    /**
     * Default constructor
     */
    NSOL_API
    NeuronMorphologySectionCachedStats( void );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~NeuronMorphologySectionCachedStats( void );

    /**
     * Set dirty a cached stat and propagates dirty to parent neurite
     * @param id_ identifier of the property to set dirty. It also propagates
     * dirty state to parent neurite. id value has to be one from
     * TNeuronMorphologySectionCachedValues (checked only on debug compiling).
     */
    NSOL_API
    virtual void setAndPropagateDirty(unsigned int id_ );

    /**
     * Set dirty all cached stats and propagates dirty to parent neurite
     */
    NSOL_API
    virtual void setAndPropagateDirty( void );

    /**
     * Adds a node at the end of the section. This method does the same as
     * Section::addNode but it also sets dirty all stats of parent neurite.
     * @param node pointer to the node to add.
     *        Precondition: pointer is not null.
     * @return pointer to the node added
     *         (for compatibility with older nsol versions)
     */
    NSOL_API
    virtual void addNode( NodePtr node = nullptr );

    NSOL_API
    virtual void firstNode( NodePtr firstNode_ );

    NSOL_API
    virtual float getStat( TNeuronMorphologySectionStat stat ) const;

    // /**
    //  * Computes volume of the section
    //  * @return volume of section
    //  */
    // NSOL_API
    // virtual float volume( void ) const;

    // /**
    //  * Computes surface of the section
    //  * @return surface of section
    //  */
    // NSOL_API
    // virtual float surface( void ) const;

    // /**
    //  * Computes length of the section
    //  * @return length of section
    //  */
    // NSOL_API
    // virtual float length( void ) const;


  }; // class NeuronMorphologySectionCachedStats

} // namespace nsol

#endif // __NSOL_NEURON_MORPHOLOGY_SECTION_CACHED_STATS__
