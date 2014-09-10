/**
 * @file    MiniColumn.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_MINICOLUMN__
#define __NSOL_MINICOLUMN__

#include <Neuron.h>
#include <Container/Neurons.h>

namespace nsol {

class MiniColumn {

public:
	MiniColumn(const unsigned short id = 0) {
		_column = nullptr;
		_id = id;
	}

	MiniColumn(const ColumnPtr column, const unsigned short id = 0) {
		_column = column;
		_id = id;
	}

	~MiniColumn() {
//	      for (Vector<Neuron *>::iterator it = _neurons.begin();
//	      it != _neurons.end(); ++it)
//	        delete *it;
//
//	      _neurons.clear();
	}

	/**
	 * Method to add a neuron.
	 */
	void addNeuron(NeuronPtr neuron) {
		_neurons.push_back(neuron);
	}

	/**
	 * Method to add a new neuron.
	 * @return pointer to the added neuron
	 */
	NeuronPtr addNeuron(void) {
		_neurons.push_back(new Neuron());
		return _neurons.back();
	}

	/**
	 * Method to get neurons.
	 * @return neurons of the mimi column
	 */
	Neurons &neurons() {
		return _neurons;
	}

	void column(ColumnPtr colummn) {
		_column = colummn;
	}

	ColumnPtr &column(void) {
		return _column;
	}

	/**
	 * Method to get-set mini column id.
	 * @return refenrence to mini column id
	 */
	unsigned short &id(void) {
		return _id;
	}

    /**
     * Method to get the number of neuron in te mini column.
     * @param all all neuron o filtered group of neurons
     * @oaram neuronType type of neuron
     * @return neuron that macth the type
     */
	const unsigned int numberOfNeurons(bool all = true, Neuron::TNeuronType neuronType =
			Neuron::PYRAMIDAL) const {
		if (all)
			return _neurons.size();
		else {
			unsigned int nNeurons = 0;
			for (Neurons::const_iterator nIt = _neurons.begin();
					nIt != _neurons.end(); nIt++) {
				if ((*nIt)->neuronType() == neuronType)
					nNeurons++;
			}

			return nNeurons;
		}
	}

	/**
	 * Method to get the mean soma volume.
	 * @return the mean soma volume
	 */
	float meanSomaVolume() const {
		double meanSomaVolume = 0;
		for (Neurons::const_iterator nIt = _neurons.begin();
				nIt != _neurons.end(); nIt++)
			meanSomaVolume += (*nIt)->soma().volume();
		return float(meanSomaVolume / _neurons.size());
	}

	/**
	 * Method to get the mean soma surface.
	 * @return the mean soma surface
	 */
	float meanSomaSurface() const {
		double meanSomaSurface = 0;
		for (Neurons::const_iterator nIt = _neurons.begin();
				nIt != _neurons.end(); nIt++)
			meanSomaSurface += (*nIt)->soma().surface();
		return float(meanSomaSurface / _neurons.size());
	}

	/**
	 * Method to get the mean dendrite volume.
	 * @return the mean dendrite volume
	 */
	float meanDendriteVolume() const {
		double meanDendVolume = 0;
		for (Neurons::const_iterator nIt = _neurons.begin();
				nIt != _neurons.end(); nIt++)
			meanDendVolume += (*nIt)->dendritesVolume();
		return float(meanDendVolume / _neurons.size());
	}

	/**
	 * Method to get the mean dendrite.
	 * @return the mean dendrite surface
	 */
	float meanDendriteSurface() const {
		double meanDendSurface = 0;
		for (Neurons::const_iterator nIt = _neurons.begin();
				nIt != _neurons.end(); nIt++)
			meanDendSurface += (*nIt)->dendritesSurface();
		return float(meanDendSurface / _neurons.size());
	}

	/**
	 * Method to get the max soma volume.
	 * @return the max soma volume
	 */
	float maxSomaVolume() const {
		double maxSomaVolume = 0.0;
		for (Neurons::const_iterator nIt = _neurons.begin();
				nIt != _neurons.end(); nIt++)
			if ((*nIt)->soma().volume() > maxSomaVolume)
				maxSomaVolume = (*nIt)->soma().volume();
		return (float) maxSomaVolume;
	}

	/**
	 * Method to get the max soma surface.
	 * @return the max soma surface
	 */
	float maxSomaSurface() const {
		double maxSomaSurface = 0.0;
		for (Neurons::const_iterator nIt = _neurons.begin();
				nIt != _neurons.end(); nIt++)
			if ((*nIt)->soma().surface() > maxSomaSurface)
				maxSomaSurface = (*nIt)->soma().surface();
		return (float) maxSomaSurface;
	}

	/**
	 * Method to get the max dendrite volume.
	 * @return the max dendrite volume
	 */
	float maxDendriteVolume() const {
		double maxDendVolume = 0;
		for (Neurons::const_iterator nIt = _neurons.begin();
				nIt != _neurons.end(); nIt++)
			if ((*nIt)->dendritesVolume() > maxDendVolume)
				maxDendVolume = (*nIt)->dendritesVolume();
		return (float) maxDendVolume;
	}

	/**
	 * Method to get the max dendrite surface.
	 * @return the max dendrite surface
	 */
	float maxDendriteSurface() const {
		double maxDendSurface = 0;
		for (Neurons::const_iterator nIt = _neurons.begin();
				nIt != _neurons.end(); nIt++)
			if ((*nIt)->dendritesSurface() > maxDendSurface)
				maxDendSurface = (*nIt)->dendritesSurface();
		return (float) maxDendSurface;
	}

protected:

	unsigned short _id;
	ColumnPtr _column;					//Column
	Neurons _neurons;

};

}

#endif
