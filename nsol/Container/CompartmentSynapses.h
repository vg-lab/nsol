/**
 * @file    CompartmentSynapses.h
 * @brief   Container for class nsol::CompartmentSynapsePtr
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_COMPARTMENTSYNAPSES_H_
#define __NSOL_COMPARTMENTSYNAPSES_H_

#include <nsol/NsolTypes.h>
#include <nsol/CompartmentSynapse.h>
#include <map>

namespace nsol
{

  typedef NsolVector< CompartmentSynapsePtr > CompartmentSynapses;

  class CompartmentSynapsesMap : public std::map< unsigned int,
                                                  CompartmentSynapsePtr >
  {
  public:

    NSOL_API
    bool addCompartmentSynapse( CompartmentSynapsePtr compartmentSynapse );

  };

}

#endif // __NSOL_COMPARTMENTSYNAPSES_H_

