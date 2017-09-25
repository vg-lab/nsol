/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Author <author@urjc.es>
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

//
// Example of how to use the factory class
//

#include <nsol/nsol.h>


int main ( int /* argc */, char ** /* argv */ )
{

  nsol::NeuronPtr neuron = nsol::Factory::newNeuron( );
  NSOL_CHECK_THROW( neuron->morphology( ), "no morphology" );

  nsol::NeuronMorphologyPtr nm = nsol::Factory::newNeuronMorphology( );
  NSOL_CHECK_THROW( nm->soma( ), "no soma" );

  return 0;

}
