/**
 * @file    SynapsesNeuriteToNeurite.h
 * @brief   Test for class nsol::SynapsesNeutireToNeuritePtr
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_SYNAPSES_NEURITE_TO_NEURITE__
#define __NSOL_SYNAPSES_NEURITE_TO_NEURITE__

#include <nsol/NsolTypes.h>
#include <nsol/SynapseNeuriteToNeurite.h>

namespace nsol {

  class SynapsesNeuriteToNeurite : public Vector<SynapseNeuriteToNeuritePtr> {
  };

}

#endif
