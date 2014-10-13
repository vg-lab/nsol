/**
 * @file    MiniColumn.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_MINICOLUMN__
#define __NSOL_MINICOLUMN__

#include <nsol/Neuron.h>
#include <nsol/Container/Neurons.h>

namespace nsol 
{

  /*! \class MiniColumn
    \brief A class to represent minicolumns.

    Columns provides pointers to neurons and methods 
    for different morphological values computation.
  */
  class MiniColumn 
  {

  public:

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default constructor 
     * @param column pointer to parent column. 
     * @param id id of the minicolumn. 
     */
    MiniColumn( const ColumnPtr column = nullptr, 
		const unsigned short id = 0 ); 

    /**
     * Copy constructor 
     * @param other column to be copied
     */   
    MiniColumn( const MiniColumn & other );
    
    /**
     * Default destructur
     * @param id id of the column. 
     */
    ~MiniColumn();

    ///@}

    /** @name Id related methods */
    ///@{

    /**
     * Method to get-set mini column id.
     * @return refenrence to mini column id
     */
    unsigned short & id( void );

    /**
     * Method to get the column id as const.
     * @return id of the minicolumn
     */
    unsigned short id( void ) const;

    ///@}

    /** @name Column related methods */
    ///@{

    /**
     * Method to set the column of this minicolumn
     * @param column pointer to the column
     */
    void column( ColumnPtr colummn );

    /**
     * Method to get the column of this minicolumn
     * @return pointer to the column
     */
    ColumnPtr column( void ) const;

    ///@}


    /** @name Neuron related methods */
    ///@{

    /**
     * Method to add a neuron. If null value passed a new neuron is created
     * @param neuron pointer to neuron to add. If null new neuron is created
     * @return pointer to the added neuron
     */
    NeuronPtr addNeuron( NeuronPtr neuron = nullptr );

    /**
     * Method to remove a neuron.
     * @param neuron pointer to the neuron to be removed
     * @return true if neuron removed false otherwise
     */
    bool removeNeuron( NeuronPtr neuron );

    /**
     * Method to get neurons.
     * @return neurons of the mimi column
     */
    Neurons & neurons( void );

    /**
     * Method to get neurons.
     * @return neurons of the mimi column
     */
    Neurons neurons( void ) const;

    /**
     * Method to clear the neurons container.
     */
    void clearNeurons( void );


    /**
     * Method to get the number of neurons in the minicolumn.
     * @param all if this is true all neurons are counted
     * @param neuronType if "all" is false neurons of the 
     *        passed type will be counted
     * @param layer if "all" is false neurons of the 
     *        layer will be counted. If later is 0 then all 
     *        neurons of all layers will be counted.
     * @return number of neurons that match the criteria
     */
    unsigned int numberOfNeurons(bool all = true, 
				 Neuron::TNeuronType neuronType =
				 Neuron::PYRAMIDAL,
				 unsigned int layer = 0 ) const;
  

    ///@}

    /** @name Operators */
    ///@{

    MiniColumn & operator = (const MiniColumn & other);
    bool operator == (MiniColumn & other ) const;
    bool operator != (MiniColumn & other ) const;

    ///@}
 

    /** @name Morphological measures */
    ///@{

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
     * Method to get the mean dendrite.
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
     * Method to compute the number of branches in dendrites
     * @return number of branches
     */
    unsigned int numDendriteBranches( void );

    ///@}

  protected:

    //! id of this minicolumn
    unsigned short _id;

    //! Pointer to the column this minicolumn belogns to
    ColumnPtr _column;					

    //!! Container of the neurons of this minicolumn
    Neurons _neurons;

  };

} // namespace nsol

#endif
