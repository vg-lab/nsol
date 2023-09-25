/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
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

#ifndef __NSOL_SIMPLIFIER__
#define __NSOL_SIMPLIFIER__

#include <nsol/api.h>

#include "NsolTypes.h"

#include <set>

namespace nsol
{

  /*! \class Simplifier
    \brief A singleton class to operate over morphologies

    Provides functionality to the simplification, the adaptation
    and the cutout of neuronal morphologies
  */
  class Simplifier
  {

  public:

    //! Methods of simplification
    typedef enum
    {
      DELETE_ALL = 0,
      DIST_NODES,
      DIST_NODES_RADIUS,
      ANGLE_MIN
    } TSimplificationMethod;

    /**
     * Returns the instance of the singelton class
     * @return the Simplifier instance
     */
    NSOL_API
    static Simplifier* Instance( );

    /**
     * Method to simplify the morphology given by the simplification function
     * selected, the simplification can be made over the original given
     * morphology or over a clone of this morphology
     * @param morpho_ neuronal morphology to simplify
     * @param simplMethod_ to select the function used to simplify
     * @param tolerance_ used for different simplification function
     * @param clone_ if true the morphology is clone before the simplification
     *        if false the simplification is made over the orignal morphology
     */
    NSOL_API
    NeuronMorphologyPtr simplify(
      NeuronMorphologyPtr morpho_,
      TSimplificationMethod simplMethod_ = DELETE_ALL,
      float tolerance_ = 0.1,
      bool clone_ = false );

    NSOL_API
    MorphologyPtr simplify(
      MorphologyPtr morpho_,
      TSimplificationMethod simplMethod_ = DELETE_ALL,
      float tolerance_ = 0.1 );


    /**
     * Method to correct the neuronal morphology to avoid errors in the
     * generation of the neuronal soma mesh
     * @param morpho_ neuronal morphology to correct
     * @param clone_ if true the morphology is clone before the correction
     *        if false the correction is made over the orignal morphology
     */
    NSOL_API
    NeuronMorphologyPtr adaptSoma(
      NeuronMorphologyPtr morpho_,
      bool clone_ = false );

    /**
     * Method to correct the neuronal morphology to fix the intersecting
     * bifurcations
     * @param morpho_ neuronal morphology to correct
     * @param tolerance_ used to determine the maximum opening angle of a
     *        bifurcation
     * @param clone_ if true the morphology is clone before the correction
     *        if false the correction is made over the orignal morphology
     */
    NSOL_API
    NeuronMorphologyPtr adaptBifurcations(
      NeuronMorphologyPtr morpho_,
      float tolerance_ = 0.9f,
      bool clone_ = false );

    /**
     * Method to cutout the neuronal morphology based in the nodes importances
     * @param morpho_ neuronal morphology to cutout
     * @param clone_ if true the morphology is clone before the cutout
     *        if false the cutout is made over the orignal morphology
     */
    NSOL_API
    NeuronMorphologyPtr cutout(
      NeuronMorphologyPtr morpho_,
      bool clone_ = false );

    /**
     * Method to repair morphological traces, deleting sections composed only by
     * two nodes and whose distance between nodes is less than the radius of the
     * segment that they represent
     * @param morpho_ neuronal morphology to unify sections
     */
    NSOL_API
    MorphologyPtr repairSections(
      MorphologyPtr morpho_ );

    NSOL_API
    Simplifier( Simplifier const& ) = delete;

    NSOL_API
    void operator = ( Simplifier const& ) = delete;

  private:

    Simplifier( void ){ };

    void _cutoutAnalizeSection( SectionPtr section_ );

    void _cutoutSection( SectionPtr section_ );

    void _groupSections( SectionPtr section_,
                         std::set< SectionPtr >& uniqueSections_ );

    void _removeSectionFromNeighbors( SectionPtr section_ );

    /** @name Simplification functions */
    ///@{

    static void _simplSecDeleteAll( SectionPtr section_,
                                    float tolerance_ );

    static void _simplSecDistNodes( SectionPtr section_,
                                    float tolerance_ );

    static void _simplSecDistNodesRadius( SectionPtr section_,
                                    float tolerance_ );

    static void _simplSecMinAngle( SectionPtr section_,
                                   float tolerance_ );

    ///@}

    //! Static instance of Simplifier singleton class
    static Simplifier* _mpInstance;
  };

} // namespace nsol

#endif // __NSOL_SIMPLIFIER__

// EOF
