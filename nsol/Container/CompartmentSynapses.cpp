/*
 * Copyright (c) 2016-2017 GMRV/URJC.
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
#include "CompartmentSynapses.h"
#include "../CompartmentSynapse.h"


namespace nsol
{

  bool CompartmentSynapsesMap::addCompartmentSynapse( Neuron* neuron,
                                        CompartmentSynapse* compartmentSynapse )
  {
    if( this->find( neuron->gid( )) != this->end( ))
    {
      Log::log( std::string("Warning: compartmentSynapse with neuron gid ") +
                std::to_string( neuron->gid( )) +
                std::string("already exists in the dataset"),
                LOG_LEVEL_WARNING );
      return false;
    }

    std::pair< unsigned int, CompartmentSynapsePtr > pair ( neuron->gid(),
                                                           compartmentSynapse );

    ( *this ).insert( pair );
    return true;
  }

} // namespace nsol
