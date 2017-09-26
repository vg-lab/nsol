/**
 * @file    NGVMorphology.h
 * @brief
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NGV_MORPHOLOGY__
#define __NSOL_NGV_MORPHOLOGY__

#include <nsol/api.h>

#include "NsolTypes.h"
#include "Node.h"
#include "NGVSection.h"

namespace nsol
{

  /*! \class NGVMorphology
   \brief A class to represent Neuro-Glia-Vasculature morphology.

   TODO: extend long description
   */
  class NGVMorphology
    : public virtual Object
  {

  public:

    /**
     * Default NGVMorphology class constructor.
     * TODO: construct protected objects
     */
    NSOL_API
    NGVMorphology( void );

    NSOL_API
    virtual ~NGVMorphology( void );

    NSOL_API
    NGVSections& sections( void );

    NSOL_API
    virtual NGVMorphologyPtr asNGVMorphology( void )
    {
      return this;
    }

  protected:

    NGVSections _sections;

  };
}

#endif
