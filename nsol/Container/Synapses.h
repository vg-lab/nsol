/*
 * Copyright (c) 2014-2017 GMRV/URJC.
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

