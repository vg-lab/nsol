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
	  MiniColumn(const unsigned short id = 0)
	  {
		  _column = nullptr;
		  _id = id;
	  }

	  MiniColumn(const ColumnPtr column, const unsigned short id = 0)
	  {
		  _column = column;
		  _id = id;
	  }

	  ~MiniColumn()
	  {
//	      for (Vector<Neuron *>::iterator it = _neurons.begin();
//	      it != _neurons.end(); ++it)
//	        delete *it;
//
//	      _neurons.clear();
	  }

	/**
	 * Method to add a neuron.
	 */
	  void addNeuron(NeuronPtr neuron)
	  {
		  _neurons.push_back(neuron);
	  }

	/**
	 * Method to add a new neuron.
	 * @return pointer to the added neuron
	 */
	  NeuronPtr addNeuron(void)
	  {
	      _neurons.push_back(new Neuron());
	      return _neurons.back();
	  }

	/**
	 * Method to get neurons.
	 * @return neurons of the mimi column
	 */
	  Neurons &neurons()
	  {
		  return _neurons;
	  }

	void column(ColumnPtr colummn)
	{
	  _column = colummn;
	}

	ColumnPtr &column(void)
	{
	  return _column;
	}

	/**
	 * Method to get-set mini column id.
	 * @return refenrence to mini column id
	 */
	  unsigned short &id(void)
	  {
		  return _id;
	  }

	  const unsigned int numberOfNeurons(void) const
	  {
		  return _neurons.size();
	  }


    float meanSomaVolume() const
    {
      double meanSomaVolume = 0;
      for (Neurons::const_iterator nIt = _neurons.begin();
          nIt != _neurons.end(); nIt++)
        meanSomaVolume += (*nIt)->soma().volume();
      return float(meanSomaVolume / _neurons.size());
    }

    float meanSomaSurface() const
    {
      double meanSomaSurface = 0;
      for (Neurons::const_iterator nIt = _neurons.begin();
          nIt != _neurons.end(); nIt++)
        meanSomaSurface += (*nIt)->soma().surface ();
      return float(meanSomaSurface / _neurons.size());
    }

    float meanDendriteVolume() const
    {
      double meanDendVolume = 0;
      for (Neurons::const_iterator nIt = _neurons.begin();
          nIt != _neurons.end(); nIt++)
        meanDendVolume += (*nIt)->dendritesVolume();
      return float(meanDendVolume / _neurons.size());
    }

    float meanDendriteSurface() const
    {
      double meanDendSurface = 0;
      for (Neurons::const_iterator nIt = _neurons.begin();
          nIt != _neurons.end(); nIt++)
        meanDendSurface += (*nIt)->dendritesSurface();
      return float(meanDendSurface / _neurons.size());
    }


  protected:

	unsigned short _id;
	ColumnPtr _column;					//Column
  Neurons _neurons;
    

  };
  
}


#endif
