/**
 * @file    Synapses.h
 * @brief   Container for class nsol::SynapsePtr
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_SYNAPSES__
#define __NSOL_SYNAPSES__

#include <nsol/NsolTypes.h>
#include <nsol/Synapse.h>
#include <map>

namespace nsol
{

  typedef NsolVector< SynapsePtr > Synapses;

  class SynapsesMap : public std::unordered_multimap< unsigned int, SynapsePtr >
  {
  public:

    NSOL_API
    void addSynapse( unsigned int neuronGID_, SynapsePtr synapse_ );

  private:

    bool _checkSynapseRepeated( unsigned int neuronGID_, Synapse* synapse_ );

  };
}

#endif // __NSOL_SYNAPSES_H_

