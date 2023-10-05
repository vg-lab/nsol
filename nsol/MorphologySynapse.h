/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Raquel Jarillo Pellon <raquel.jarillo@urjc.es>
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
#ifndef __NSOL_COMPARTMENTSYNAPSE__
#define __NSOL_COMPARTMENTSYNAPSE__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Neuron.h>
#include <nsol/Synapse.h>


namespace nsol
{

  class MorphologySynapse : public Synapse
  {

  public:

    //! Possible types of synapse
    typedef enum
    {
      UNDEFINED = 0,
      DENDRODENDRITIC,
      AXODENDRITIC,
      AXOAXONIC,
      SOMATOSOMATIC,
      AXOSOMATIC,
      DENDROSOMATIC
    }TSynapseType;

    //! Possible types of synaptic section
    typedef enum
    {
      PRESYNAPTICSECTION = 0,
      POSTSYNAPTICSECTION
    } TSynapticSectionType;

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default MorphologySynapse constructor
     */
    NSOL_API
    MorphologySynapse( void );

    /**
     * Copy constructor
     * @param other_ MorphologySynapseto be copied
     */
    NSOL_API
    MorphologySynapse( const MorphologySynapse& other_ );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~MorphologySynapse( void );

    ///@}

    /** @name getters and setters methods */
    ///@{

    /**
     * GID getter
     */
    NSOL_API unsigned int gid( void ) const;

    /**
     * GID setter
     *
     * Note: Zero as default value.
     */
    NSOL_API void gid( unsigned int gid_ );

    /**
     * Method to get the type of the synapse.
     */
    NSOL_API
    TSynapseType synapseType( void ) const;

    /**
     * Method to get the presynaptic surface position.
     * @return presynaptic surface position.
     */
    NSOL_API
    Vec3f preSynapticSurfacePosition( void ) const;

    /**
     * Method to set presynaptic surface position to the synapse.
     * @param presynaptic_surface_position_ presynaptic surface position.
     */
    NSOL_API
    void
    preSynapticSurfacePosition( const Vec3f& presynaptic_surface_position_ );

    /**
     * Method to get the postsynaptic surface position.
     * @return postsynaptic surface position.
     */
    NSOL_API
    Vec3f postSynapticSurfacePosition( void ) const;

    /**
     * Method to set postsynaptic surface position to the synapse.
     * @param position_ postsynaptic surface position.
     */
    NSOL_API
    void
    postSynapticSurfacePosition( const Vec3f& position_ );

    /**
     * Method to add a presynaptic section to the synapse.
     * @param preSynapticSection_ presynaptic section.
     * @see Synapse
     */
    NSOL_API
    void preSynapticSection(
        const NeuronMorphologySectionPtr preSynapticSection_ );

    /**
     * Method to get the presynaptic section.
     * @return pointer to the presynaptic section.
     */
    NSOL_API
    NeuronMorphologySectionPtr preSynapticSection( void ) const;

    /**
     * Method to add a postsynaptic section to the synapse.
     * @param section_ postsynaptic section.
     * @see Synapse
     */
    NSOL_API
    void postSynapticSection( const NeuronMorphologySectionPtr section_ );

    /**
     * Method to get the postsynaptic section.
     * @return pointer to the postsynaptic section.
     */
    NSOL_API
    NeuronMorphologySectionPtr postSynapticSection( void ) const;

    /** \brief Operator =. Included to avoid warning in modern gcc versions.
     *
     */
    MorphologySynapse& operator=(const nsol::MorphologySynapse&) = default;

    ///@}

  protected:

    //! Synapse GID (default value zero)
    unsigned int _gid;

    //! Presynaptic surface position
    Vec3f _preSynapticSurfacePosition;

    //! Postsynaptic surface position
    Vec3f _postSynapticSurfacePosition;

    //! Section of a presynaptic neuron (neurite)
    NeuronMorphologySectionPtr _preSynapticSection;

    //! Section of a postsynaptic neuron (neurite)
    NeuronMorphologySectionPtr _postSynapticSection;

  };

} // namespace nsol

#endif // __NSOL_COMPARTMENTSYNAPSE__
