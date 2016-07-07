/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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
#ifndef __NSOL__NEURONS__
#define __NSOL__NEURONS__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <unordered_map>

namespace nsol
{

  typedef NsolVector< NeuronPtr > Neurons;

  class NeuronsMap : public std::unordered_map< unsigned int, NeuronPtr >
  {
  public:

    NSOL_API
    bool addNeuron( NeuronPtr neuron );
  };
}

#endif /* _NSOL_NEURONS_H_ */
