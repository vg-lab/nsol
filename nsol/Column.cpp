#include "Column.h"

namespace nsol {

  
  Column::Column(unsigned short id) 
  {
    _id = id;
  }

  Column::~Column() 
  {
/*    for (Vector<MiniColumnPtr>::iterator it = _miniColumns.begin();
	 it != _miniColumns.end(); ++it)
      delete *it;
*/
    _miniColumns.clear();
  }

  void Column::addMiniColumn(MiniColumnPtr miniColumn)
  {
    _miniColumns.push_back(miniColumn);
  }

  bool Column::removeMiniColumn(MiniColumnPtr miniColumn)
  {
    MiniColumns::iterator mcIt = 
      find (_miniColumns.begin( ), _miniColumns.end( ), miniColumn);

    if ( mcIt == _miniColumns.end( ))
      return false;

    _miniColumns.erase( mcIt );
    return true;
  }

  void Column::clearMiniColumns( void )
  {
    _miniColumns.clear( );
  }



  // MiniColumnPtr Column::addMiniColumn(unsigned short id)
  // {
  //   {
  //     ColumnPtr col( this );
  //   }
  //   ColumnPtr col2( this );
  //   std::cout << col2.get() << " " << col2.use_count() << std::endl;
  //   _miniColumns.push_back( MiniColumnPtr( new MiniColumn( col2 , id )));
  //   return _miniColumns.back();
  // }

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

  float Column::meanSomaVolume () const
  {
    if ( _miniColumns.size() == 0 ) 
      return 0.0f;

    double meanSomaVolume = 0;

    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      meanSomaVolume += (*mcIt)->meanSomaVolume( );

    return float(meanSomaVolume / float(_miniColumns.size( )));
  }

  float Column::meanSomaSurface() const
  {
    if ( _miniColumns.size() == 0 ) 
      return 0.0f;

    double meanSomaSurface = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      meanSomaSurface += (*mcIt)->meanSomaSurface();
    return float(meanSomaSurface / _miniColumns.size());
  }

  float Column::meanDendriteVolume() const
  {
    if ( _miniColumns.size() == 0 ) 
      return 0.0f;

    double meanDendVolume = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      meanDendVolume += (*mcIt)->meanDendriteVolume();
    return float(meanDendVolume / _miniColumns.size());
  }

  float Column::meanDendriteSurface() const
  {
    if ( _miniColumns.size() == 0 ) 
      return 0.0f;

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

  unsigned int Column::numDendriteBranches( void ) const 
  {

    unsigned int numBranches = 0;
    for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
	 mcIt != _miniColumns.end(); mcIt++)
      numBranches += (*mcIt)->numDendriteBranches();

    return numBranches;

  }

} // namespace nsol
