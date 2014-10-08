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

  class MiniColumn 
  {

  public:
    MiniColumn( const ColumnPtr column = nullptr, 
		const unsigned short id = 0 ); 

    ~MiniColumn();

    /**
     * Method to add a neuron. If null value passed a new neuron is created
     * @param neuron pointer to neuron to add. If null new neuron is created
     * @return pointer to the added neuron
     */
    NeuronPtr addNeuron( NeuronPtr neuron = nullptr );

    /**
     * Method to get neurons.
     * @return neurons of the mimi column
     */
    Neurons & neurons( void );

    /**
     * Method to set the column of this minicolumn
     * @param column pointer to the column
     */
    void column( ColumnPtr colummn );

    /**
     * Method to get the column of this minicolumn
     * @return pointer to the column
     */
    ColumnPtr column(void) const;

    /**
     * Method to get-set mini column id.
     * @return refenrence to mini column id
     */
    unsigned short & id( void );

    /**
     * Method to get the number of neuron in te mini column.
     * @param all all neuron o filtered group of neurons
     * @param neuronType type of neuron
     * @param layer count neurons in that layer. If 0 all layers counter.
     * @return neuron that macth the type
     */
    unsigned int numberOfNeurons(bool all = true, 
				 Neuron::TNeuronType neuronType =
				 Neuron::PYRAMIDAL,
				 unsigned int layer = 0 ) const;
  

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
