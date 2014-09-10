/**
 * @file    Column.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_COLUMN__
#define __NSOL_COLUMN__

#include <MiniColumn.h>
#include <NsolTypes.h>
#include <Container/MiniColumns.h>

namespace nsol {

class Column {

public:
	Column(unsigned short id = 0) {
		_id = id;
	}

	~Column() {
		for (Vector<MiniColumn *>::iterator it = _miniColumns.begin();
		it != _miniColumns.end(); ++it)
		delete *it;

		_miniColumns.clear();
	}

	/**
	 * Method to add a mini column.
	 */
	void addMiniColumn(MiniColumnPtr miniColumn)
	{
		_miniColumns.push_back(miniColumn);
	}

	/**
	 * Method to add a new mini column.
	 * @return pointer to the added mini column
	 */
	MiniColumnPtr addMiniColumn(unsigned short id = 0)
	{
		_miniColumns.push_back(new MiniColumn(this, id));
		return _miniColumns.back();
	}

	/**
	 * Method to get-set the column id.
	 * @return reference to column id
	 */
	unsigned short &id(void)
	{
		return _id;
	}

	/**
	 * Method to get minicolumns.
	 * @return minicolumns of the column
	 */
	MiniColumns &miniColumns()
	{
		return _miniColumns;
	}

	/**
	 * Method to get the number of minicolumns.
	 * @return numbers of minicolumns
	 */
	const unsigned int numberOfMiniColumns(void) const
	{
		return _miniColumns.size();
	}

	/**
	 * Method to get the mean soma volume.
	 * @return the mean soma volume
	 */
	float meanSomaVolume() const
	{
		double meanSomaVolume = 0;
		for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
				mcIt != _miniColumns.end(); mcIt++)
		meanSomaVolume += (*mcIt)->meanSomaVolume();
		return float(meanSomaVolume / _miniColumns.size());
	}

	/**
	 * Method to get the mean soma surface.
	 * @return the mean soma surface
	 */
	float meanSomaSurface() const
	{
		double meanSomaSurface = 0;
		for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
				mcIt != _miniColumns.end(); mcIt++)
		meanSomaSurface += (*mcIt)->meanSomaSurface();
		return float(meanSomaSurface / _miniColumns.size());
	}

	/**
	 * Method to get the mean dendrite volume.
	 * @return the mean dendrite volume
	 */
	float meanDendriteVolume() const
	{
		double meanDendVolume = 0;
		for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
				mcIt != _miniColumns.end(); mcIt++)
		meanDendVolume += (*mcIt)->meanDendriteVolume();
		return float(meanDendVolume / _miniColumns.size());
	}

	/**
	 * Method to get the mean dendrite surface.
	 * @return the mean dendrite surface
	 */
	float meanDendriteSurface() const
	{
		double meanDendSurface = 0;
		for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
				mcIt != _miniColumns.end(); mcIt++)
		meanDendSurface += (*mcIt)->meanDendriteSurface();
		return float(meanDendSurface / _miniColumns.size());
	}

	/**
	 * Method to get the max soma volume.
	 * @return the max soma volume
	 */
	float maxSomaVolume() const
	{
		double maxSomaVolume = 0.0;
		for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
				mcIt != _miniColumns.end(); mcIt++)
			if ((*mcIt)->maxSomaVolume() > maxSomaVolume)
				maxSomaVolume = (*mcIt)->maxSomaVolume();
		return (float)maxSomaVolume;
	}

	/**
	 * Method to get the max soma surface.
	 * @return the max soma surface
	 */
	float maxSomaSurface() const
	{
		double maxSomaSurface = 0.0;
		for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
				mcIt != _miniColumns.end(); mcIt++)
			if ((*mcIt)->maxSomaSurface() > maxSomaSurface)
		maxSomaSurface = (*mcIt)->maxSomaSurface();
		return (float)maxSomaSurface;
	}

	/**
	 * Method to get the max dendrite volume.
	 * @return the max dendrite volume
	 */
	float maxDendriteVolume() const
	{
		double maxDendVolume = 0;
		for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
				mcIt != _miniColumns.end(); mcIt++)
			if ((*mcIt)->maxDendriteVolume() > maxDendVolume)
				maxDendVolume = (*mcIt)->maxDendriteVolume();
		return (float)maxDendVolume;
	}

	/**
	 * Method to get the max dendrite surface.
	 * @return the max dendrite surface
	 */
	float maxDendriteSurface() const
	{
		double maxDendSurface = 0;
		for (MiniColumns::const_iterator mcIt = _miniColumns.begin();
				mcIt != _miniColumns.end(); mcIt++)
			if ((*mcIt)->maxDendriteSurface())
				maxDendSurface = (*mcIt)->maxDendriteSurface();
		return (float)maxDendSurface;
	}

protected:

	unsigned short _id;
	MiniColumns _miniColumns;
};

}

#endif
