/**
 * @file    Column.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_COLUMN__
#define __NSOL_COLUMN__

#include <nsol/MiniColumn.h>
#include <nsol/NsolTypes.h>
#include <nsol/Container/MiniColumns.h>

namespace nsol 
{

  class Column 
  {

  public:
    Column(unsigned short id = 0);
    ~Column() ;

    /**
     * Method to add a mini column.
     */
    void addMiniColumn(MiniColumnPtr miniColumn);

    /**
     * Method to add a new mini column.
     * @return pointer to the added mini column
     */
    MiniColumnPtr addMiniColumn(unsigned short id = 0);

    /**
     * Method to get-set the column id.
     * @return reference to column id
     */
    unsigned short & id(void);

    /**
     * Method to get minicolumns.
     * @return minicolumns of the column
     */
    MiniColumns &miniColumns();

    /**
     * Method to get the number of minicolumns.
     * @return numbers of minicolumns
     */
    const unsigned int numberOfMiniColumns(void) const;

    /**
     * Method to get the mean soma volume.
     * @return the mean soma volume
     */
    float meanSomaVolume() const;

    /**
     * Method to get the mean soma surface.
     * @return the mean soma surface
     */
    float meanSomaSurface() const;

    /**
     * Method to get the mean dendrite volume.
     * @return the mean dendrite volume
     */
    float meanDendriteVolume() const;

    /**
     * Method to get the mean dendrite surface.
     * @return the mean dendrite surface
     */
    float meanDendriteSurface() const;

    /**
     * Method to get the max soma volume.
     * @return the max soma volume
     */
    float maxSomaVolume() const;

    /**
     * Method to get the max soma surface.
     * @return the max soma surface
     */
    float maxSomaSurface() const;

    /**
     * Method to get the max dendrite volume.
     * @return the max dendrite volume
     */
    float maxDendriteVolume() const;

    /**
     * Method to get the max dendrite surface.
     * @return the max dendrite surface
     */
    float maxDendriteSurface() const;


    const unsigned int numberOfNeurons(bool all = true, 
				       Neuron::TNeuronType neuronType =
				       Neuron::PYRAMIDAL,
				       unsigned int layer = 0) const;
    
    unsigned int numDendriteBranches( void ) const;


  protected:

    unsigned short _id;
    MiniColumns _miniColumns;
  };

}

#endif
