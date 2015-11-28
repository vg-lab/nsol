/*
 * Neurons.h
 *
 *  Created on: 31/07/2014
 *      Author: richard
 */

#ifndef _NSOL_NEURONS_H_
#define _NSOL_NEURONS_H_

#include <nsol/NsolTypes.h>
#include <nsol/Neuron.h>
#include <unordered_map>

namespace nsol {

  typedef NsolVector< NeuronPtr > Neurons;
  typedef std::unordered_map< unsigned int, NeuronPtr > NeuronsMap;

}

#endif /* _NSOL_NEURONS_H_ */
