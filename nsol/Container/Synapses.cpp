/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
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
#include "Synapses.h"
#include "../Synapse.h"


namespace nsol
{

  bool SynapsesMap::_checkSynapseRepeated( unsigned int neuronGID_,
                                           Synapse* synapse_ )
  {
    auto values = this->equal_range( neuronGID_ );
    for( auto value = values.first; value != values.second; ++value )
    {
      if( value->second == synapse_ )
      {
        NSOL_THROW( std::string( "Warning: synapse with neuron gid " ) +
                    std::to_string( neuronGID_ ) +
                    std::string( "already exists in the dataset" ) );
        return false;
      }
    }

    return true;
  }

  void SynapsesMap::addSynapse( unsigned int neuronGID_, Synapse* synapse_ )
  {

    NSOL_DEBUG_CHECK( _checkSynapseRepeated( neuronGID_, synapse_ ),
                      "The synapse already exists into the dataset." );

    this->insert( std::make_pair( neuronGID_, synapse_ ));

  }

} // namespace nsol
