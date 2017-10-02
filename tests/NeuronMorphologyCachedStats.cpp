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

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( neuronMorphologyCachedStats_constructors )
{
   {
      NeuronMorphologyCachedStats* neuronMorphologyCachedStats =
                                             new NeuronMorphologyCachedStats( );

      BOOST_CHECK( neuronMorphologyCachedStats->soma() == nullptr );
      BOOST_CHECK_EQUAL( neuronMorphologyCachedStats->neurites().size(), 0 );
      BOOST_CHECK_EQUAL( neuronMorphologyCachedStats->parentNeurons().size(), 0 );

      // Free dymanic memory used
      NSOL_DELETE_PTR( neuronMorphologyCachedStats );
   }
   {
      SomaPtr soma( new Soma );
      NeuronMorphologyCachedStats* neuronMorphologyCachedStats1 =
                                          new NeuronMorphologyCachedStats( soma );

      BOOST_CHECK( neuronMorphologyCachedStats1->soma() != nullptr );

      // Free dymanic memory used
      NSOL_DELETE_PTR( neuronMorphologyCachedStats1 );
   }
}


BOOST_AUTO_TEST_CASE( neuronMorphologyCachedStats_setAndPropagateDirty )
{
   NeuronMorphologyCachedStats* neuronMorphologyCachedStats =
                                            new NeuronMorphologyCachedStats( );

   neuronMorphologyCachedStats->setAndPropagateDirty(1);
   BOOST_CHECK_EQUAL( neuronMorphologyCachedStats->dirty(2), true );

   neuronMorphologyCachedStats->setAndPropagateDirty();
   BOOST_CHECK_EQUAL( neuronMorphologyCachedStats->dirty(2), true );

   // Free dymanic memory used
   NSOL_DELETE_PTR( neuronMorphologyCachedStats );

}

