#include "Column.h"

namespace nsol {


  Column::Column(unsigned short id) 
  {
    _id = id;
  }

  Column::~Column() 
  {
    for (Vector<MiniColumn *>::iterator it = _miniColumns.begin();
	 it != _miniColumns.end(); ++it)
      delete *it;

    _miniColumns.clear();
  }

  void Column::addMiniColumn(MiniColumnPtr miniColumn)
  {
    _miniColumns.push_back(miniColumn);
  }

  MiniColumnPtr Column::addMiniColumn(unsigned short id)
  {
    _miniColumns.push_back(new MiniColumn(this, id));
    return _miniColumns.back();
  }

  unsigned short & Column::id(void)
  {
    return _id;
  }

  MiniColumns & Column::miniColumns()
  {
    return _miniColumns;
  }

  const unsigned int Column::numberOfMiniColumns(void) const
  {
    return _miniColumns.size();
  }

  float Column::meanSomaVolume () const
  {
    double meanSomaVolume = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      meanSomaVolume += (*mcIt)->meanSomaVolume();
    return float(meanSomaVolume / _miniColumns.size());
  }

  float Column::meanSomaSurface() const
  {
    double meanSomaSurface = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      meanSomaSurface += (*mcIt)->meanSomaSurface();
    return float(meanSomaSurface / _miniColumns.size());
  }

  float Column::meanDendriteVolume() const
  {
    double meanDendVolume = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      meanDendVolume += (*mcIt)->meanDendriteVolume();
    return float(meanDendVolume / _miniColumns.size());
  }

  float Column::meanDendriteSurface() const
  {
    double meanDendSurface = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      meanDendSurface += (*mcIt)->meanDendriteSurface();
    return float(meanDendSurface / _miniColumns.size());
  }

  float Column::maxSomaVolume() const
  {
    double maxSomaVolume = 0.0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      if ((*mcIt)->maxSomaVolume() > maxSomaVolume)
	maxSomaVolume = (*mcIt)->maxSomaVolume();
    return (float)maxSomaVolume;
  }

  float Column::maxSomaSurface() const
  {
    double maxSomaSurface = 0.0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      if ((*mcIt)->maxSomaSurface() > maxSomaSurface)
	maxSomaSurface = (*mcIt)->maxSomaSurface();
    return (float)maxSomaSurface;
  }

  float Column::maxDendriteVolume() const
  {
    double maxDendVolume = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      if ((*mcIt)->maxDendriteVolume() > maxDendVolume)
	maxDendVolume = (*mcIt)->maxDendriteVolume();
    return (float)maxDendVolume;
  }

  float Column::maxDendriteSurface() const
  {
    double maxDendSurface = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      if ((*mcIt)->maxDendriteSurface())
	maxDendSurface = (*mcIt)->maxDendriteSurface();
    return (float)maxDendSurface;
  }



  const unsigned int Column::numberOfNeurons(bool all, 
					     Neuron::TNeuronType neuronType,
					     unsigned int layer) 
    const 
  {
    unsigned int nNeurons = 0;
    
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      nNeurons += (*mcIt)->numberOfNeurons(all, neuronType, layer);

    return nNeurons;
  
  }

  unsigned int Column::numDendriteBranches( void ) const 
  {

    unsigned int numBranches = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      numBranches += (*mcIt)->numDendriteBranches();

    return numBranches;

  }

} // namespace nsol
