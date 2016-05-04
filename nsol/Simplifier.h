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

  class Simplifier
  {

  public:

    //! Methods of simplification
    typedef enum
    {
      DELETE_ALL = 0,
      DIST_NODES,
    } TSimplificationMethod;

    NSOL_API
    static Simplifier* Instance( );

    NSOL_API
    NeuronMorphologyPtr simplify(
      NeuronMorphologyPtr morpho_,
      TSimplificationMethod simplMethod_ = DELETE_ALL,
      float tolerance_ = 0.1,
      bool clone = false );

    NSOL_API
    NeuronMorphologyPtr adaptSoma(
      NeuronMorphologyPtr morpho_,
      bool clone = false );

    NSOL_API
    Simplifier( Simplifier const& ) = delete;

    NSOL_API
    void operator = ( Simplifier const& ) = delete;

  private:

    Simplifier( void ){ };

    static void _simplSecDeleteAll( SectionPtr section_,
                                    float tolerance_ );

    static void _simplSecDistNodes( SectionPtr section_,
                                    float tolerance_ );

    static Simplifier* m_pInstance;
  };

} // namespace nsol

#endif // __NSOL_SIMPLIFIER__

// EOF
