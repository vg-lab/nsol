/*
 * Copyright (c) 2014-2017 GMRV/URJC.
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

#include <nsol/nsol.h>
#include <assert.h>
#include <iostream>


using namespace nsol;
using namespace std;

int main () {



  // Neurite tests

  {

    cout << "Testing neurite ops" << endl;
    Neuron neuron;

    Neurite * neurite = neuron.morphology( )->addNeurite( new Neurite );
    assert(neurite != NULL);
    assert(neurite->neuriteType() == Neurite::DENDRITE);

    Neurite * neurite2 = neuron.morphology( )->addNeurite(
      new Neurite( Neurite::AXON ));
    assert(neurite2 != NULL);
    assert(neurite2->neuriteType() == Neurite::AXON);

    // assert(neuron.numNeurites() ==  2);
    // assert(neuron.numDendrites() ==  1);

    // To avoid warnings for unused in release mode
    ( ( void )( neurite ));
    ( ( void )( neurite2 ));
  }

  {
    Neuron neuron;

    cout << "Testing dendrite ops" << endl;
    Neurite * neurite = neuron.morphology( )->addNeurite( new Neurite );
    assert(neurite != NULL);
    assert(neurite->neuriteType() == Neurite::DENDRITE);
    assert(neuron.morphology( )->apicalDendrite() == NULL);

    // assert(neuron.numNeurites() ==  1);
    // assert(neuron.numDendrites() ==  1);

    Dendrite * dendrite = new Dendrite;
    neuron.morphology( )->addNeurite( dendrite );
    assert(dendrite->dendriteType() == Dendrite::BASAL);

    // assert(neuron.numNeurites() ==  2);
    // assert(neuron.numDendrites() ==  2);

    Dendrite * dendrite2 = new Dendrite( Dendrite::APICAL );
    neuron.morphology( )->addNeurite( dendrite2 );
    assert(dendrite2->dendriteType() == Dendrite::APICAL);

    assert(neuron.morphology( )->apicalDendrite() != NULL);
    // assert(neuron.numNeurites() ==  3);
    // assert(neuron.numDendrites() ==  3);

    // To avoid warnings for unused in release mode
    ( ( void )( neurite ));


  }


  // Soma tests

  {

    cout << "Testing soma ops" << endl;
    Neuron neuron;

    // neuron.soma().center() = Vec3f(3.5,4.6,5.7);
    // std::cout << neuron.soma().center()[0] << std::endl;
    // assert(neuron.soma().center()[0] == 3.5f);
    // assert(neuron.soma().center()[1] == 4.6f);
    // assert(neuron.soma().center()[2] == 5.7f);

    // const Vec3f & centerRef = neuron.soma().center();
    // assert(centerRef[0] == 3.5f);
    // assert(centerRef[1] == 4.6f);
    // assert(centerRef[2] == 5.7f);

    // neuron.soma().center() = Vec3f(1.2,2.3,3.4);
    // assert(neuron.soma().center()[0] == 1.2f);
    // assert(neuron.soma().center()[1] == 2.3f);
    // assert(neuron.soma().center()[2] == 3.4f);
    // assert(centerRef[0] == 1.2f);
    // assert(centerRef[1] == 2.3f);
    // assert(centerRef[2] == 3.4f);

    // Vec3f newCenter2(2.5,3.6,4.7);
    // neuron.soma().center() = newCenter2;
    // assert(neuron.soma().center() == newCenter2);
    // assert(centerRef == newCenter2);
    // assert(neuron.soma().center()[0] == 2.5f);
    // assert(neuron.soma().center()[1] == 3.6f);
    // assert(neuron.soma().center()[2] == 4.7f);

    // {
    //   Vec3f newCenter3(5.6,6.7,7.8);
    //   neuron.soma().center() = newCenter3;
    // }
    // assert(neuron.soma().center() == Vec3f(5.6,6.7,7.8));


  }

  return 0;

}
