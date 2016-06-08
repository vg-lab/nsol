/**
 * @file Simplifier.h
 * @brief
 * @author Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#ifndef __NSOL_SIMPLIFIER__
#define __NSOL_SIMPLIFIER__

#include <nsol/api.h>

#include "NsolTypes.h"

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
     * @param clone if true the morphology is clone before the simplification
     *        if false the simplification is made over the orignal morphology
     */
    NSOL_API
    NeuronMorphologyPtr simplify(
      NeuronMorphologyPtr morpho_,
      TSimplificationMethod simplMethod_ = DELETE_ALL,
      float tolerance_ = 0.1,
      bool clone = false );


    /**
     * Mehod to correct the neuronal morphology to avoid errors in the
     * generation of the neuronal soma mesh
     * @param morpho_ neuronal morphology to correct
     * @param clone if true the morphology is clone before the correction
     *        if false the correction is made over the orignal morphology
     */
    NSOL_API
    NeuronMorphologyPtr adaptSoma(
      NeuronMorphologyPtr morpho_,
      bool clone = false );


    /**
     * Mehod to cutout the neuronal morphology based in the nodes importances
     * @param morpho_ neuronal morphology to cutout
     * @param clone if true the morphology is clone before the cutout
     *        if false the cutout is made over the orignal morphology
     */
    NSOL_API
    NeuronMorphologyPtr cutout(
      NeuronMorphologyPtr morpho_,
      bool clone = false );

    NSOL_API
    Simplifier( Simplifier const& ) = delete;

    NSOL_API
    void operator = ( Simplifier const& ) = delete;

  private:

    Simplifier( void ){ };

    void _cutoutAnalizeSection( SectionPtr section_ );

    void _cutoutSection( SectionPtr section_ );


    /** @name Simplification functions */
    ///@{

    static void _simplSecDeleteAll( SectionPtr section_,
                                    float tolerance_ );

    static void _simplSecDistNodes( SectionPtr section_,
                                    float tolerance_ );
    ///@}

    //! Static instance of Simplifier singleton class
    static Simplifier* _mpInstance;
  };

} // namespace nsol

#endif // __NSOL_SIMPLIFIER__

// EOF
