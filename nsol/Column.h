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

  /*! \class Column
    \brief A class to represent columns.

    Columns provides pointers to minicolumns and methods 
    for different morphological values computation.
  */
  class Column 
  {

  public:
    
    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default constructor 
     * @param id id of the column. 
     */
    Column( unsigned short id = 0 );

    /**
     * Default destructur
     * @param id id of the column. 
     */
    ~Column( void ) ;

    ///@}

    /** @name Id related methods */
    ///@{

    /**
     * Method to get-set the column id.
     * @return reference to column id
     */
    unsigned short & id( void );

    ///@}

    /** @name MiniColumn related methods */
    ///@{

    /**
     * Method to add a mini column.
     * @param miniColumn minicolumn to add to this column
     */
    void addMiniColumn( MiniColumnPtr miniColumn );

    /**
     * Method to add a mini column.
     */
    bool removeMiniColumn( MiniColumnPtr miniColumn );

    /**
     * Method to clear mini columns.
     */
    void clearMiniColumns( void );

    /**
     * Method to get minicolumns.
     * @return minicolumns of the column
     */
    MiniColumns & miniColumns( void );

    /**
     * Method to get the number of minicolumns.
     * @return numbers of minicolumns
     */
    const unsigned int numberOfMiniColumns( void ) const;

    ///@}

    /** @name Morphological measures */
    ///@{

    /**
     * Method to get the number of neurons in the column.
     * @param all if this is true all neurons are counted
     * @param neuronType if "all" is false neurons of the 
     *        passed type will be counted
     * @param layer if "all" is false neurons of the 
     *        layer will be counted. If later is 0 then all 
     *        neurons of all layers will be counted.
     * @return number of neurons that match the criteria
     */
    const unsigned int 
    numberOfNeurons( const bool all = true, 
		     const Neuron::TNeuronType neuronType =
		     Neuron::PYRAMIDAL,
		     const unsigned int layer = 0 ) const;


    /**
     * Method to get the mean soma volume.
     * @return the mean soma volume
     */
    float meanSomaVolume( void ) const;

    /**
     * Method to get the mean soma surface.
     * @return the mean soma surface
     */
    float meanSomaSurface( void ) const;

    /**
     * Method to get the mean dendrite volume.
     * @return the mean dendrite volume
     */
    float meanDendriteVolume( void ) const;

    /**
     * Method to get the mean dendrite surface.
     * @return the mean dendrite surface
     */
    float meanDendriteSurface( void ) const;

    /**
     * Method to get the max soma volume.
     * @return the max soma volume
     */
    float maxSomaVolume( void ) const;

    /**
     * Method to get the max soma surface.
     * @return the max soma surface
     */
    float maxSomaSurface( void ) const;

    /**
     * Method to get the max dendrite volume.
     * @return the max dendrite volume
     */
    float maxDendriteVolume( void ) const;

    /**
     * Method to get the max dendrite surface.
     * @return the max dendrite surface
     */
    float maxDendriteSurface( void ) const;

    /**
     * Method to get the number of branches in dendrites.
     * @return number of branches in dendrites
     */    
    unsigned int numDendriteBranches( void ) const;

    ///@}

  protected:

    //! Identifier of the column
    unsigned short _id;

    //! Container of minicolumns
    MiniColumns _miniColumns;

  }; // class Column
} // namespace nsol

#endif // __NSOL_COLUMN__
// EOF
