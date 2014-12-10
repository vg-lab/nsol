/**
 * @file    Circuit.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_CIRCUIT__
#define __NSOL_CIRCUIT__

#include <iostream.h>
#include <nsol/Container/Columns.h>


namespace nsol
{
	namespace std{

		/*! \class Circuit
		  \brief A class to represent connections between neurons.
		  TODO: extend long description
		*/
	  class Circuit
	  {

	  public:

		  /** @name Constructors and destructors  */
		  ///@{

		  /**
		   * Default constructor
		   * @param id id of the circuit.
		   */
		  NSOL_API
		  Circuit( unsigned short id = 0 );

		  /**
		  * Default destructor
		  * @param id id of the circuit.
		  */
		 NSOL_API
		 ~Circuit( void ) ;

		 ///@}

		 /** @name Id related methods */
		 ///@{

		 /**
		  * Method to get-set the circuit id.
		  * @return circuit id
		  */
		 NSOL_API
		 unsigned short & id( void );

		 /**
		  * Method to get the circuit id.
		  * @return reference to circuit id
		  */
		 NSOL_API
		 unsigned short id( void ) const;

		 ///@}

		 /** @name Column related methods */
		 ///@{

		 /**
		  * Method to add a column.
		  * @param column column to add to this circuit
		  */
		 NSOL_API
		 void addColumn( ColumnPtr column );

		 /**
		  * Method to remove a column.
		  * @param column pointer to the column to be removed
		  * @return true if column removed false otherwise
		  */
		 NSOL_API
		 bool removeColumn( ColumnPtr column );

		 /**
		  * Method to clear columns.
		  */
		 NSOL_API
		 void clearColumns( void );

		 /**
		  * Method to get columns.
		  * @return columns of the circuit
		  */
		 NSOL_API
		 Columns & columns( void );

		 /**
		 * Method to get columns as const.
		 * @return columns of the circuit
		 */
		NSOL_API
		Columns columns( void ) const;

		/**
		 * Method to get the number of columns.
		 * @return numbers of columns
		 */
		NSOL_API
		unsigned int numberOfColumns( void ) const;

		///@}

		/** @name Operators */
		///@{

		NSOL_API
		Circuit & operator = (const Circuit & other);

		NSOL_API
		bool operator == (Circuit & other ) const;

		NSOL_API
		bool operator != (Circuit & other ) const;

		///@}

		/** @name Efferent and Afferent Connections related methods */
		 ///@{

		/**
	    * Method to add an efferent connection.
	    * @param efferent connection to add to this circuit
	    * @return true if efferent connection added false otherwise
	    */
	    NSOL_API
	    void addEfferentConnection( NeuronPtr neuron, SynapsePtr efferentSynapse );

	    /**
		* Method to add an afferent connection.
		* @param afferent connection to add to this circuit
		* @return true if afferent connection added false otherwise
		*/
		NSOL_API
		void addAfferentConnection( NeuronPtr neuron, SynapsePtr afferentSynapse );

	     /**
		 * Method to remove an efferent connection.
		 * @param neuron pointer to the efferent connection to be removed
   	     * @return true if efferent connection removed false otherwise
	     */
		 NSOL_API
		 bool removeEfferentConnection( NeuronPtr neuron, SynapsePtr efferentSynapse );

		 /**
		 * Method to remove an afferent connection.
		 * @param neuron pointer to the afferent connection to be removed
		 * @return true if afferent connection removed false otherwise
		 */
		 NSOL_API
		 bool removeAfferentConnection( NeuronPtr neuron, SynapsePtr afferentSynapse );

		 /**
		  * Method to clear efferent connections of the one neuron.
		  */
		 NSOL_API
		 void clearEfferentConnections( NeuronPtr neuron );

		 /**
		  * Method to clear afferent connections of the  neuron.
		  */
		 NSOL_API
		 void clearAfferentConnections( NeuronPtr neuron );

		 /**
		  * Method to clear all the connections (efferents and afferents)
		  * of a neuron.
		  */
		 NSOL_API
		 void clearConnections( NeuronPtr neuron );

		 /**
		  * Method to clear all the connections (efferents and afferents)
		  * of all the circuit.
		  */
		 NSOL_API
		 void clearAllConnections( void );

		 /**
		  * Method to get efferent connections.
		  * @return efferent connections of the circuit
		  */
		 std::map <NeuronPtr, std::Vector<SynapsePtr>> &efferentConnections( void );

		 /**
		  * Method to get afferent connections.
		  * @return afferent connections of the circuit
		  */
		 std::map <NeuronPtr, std::Vector<SynapsePtr>> &afferentConnections( void );
		 /**
		  * Method to get efferent connections as const.
		  * @return efferent connections of the circuit
		  */
		 std::map <NeuronPtr, std::Vector<SynapsePtr>> &efferentConnections( void ) const;

		 /**
		  * Method to get afferent connections as const.
		  * @return afferent connections of the circuit
		  */
		 std::map <NeuronPtr, std::Vector<SynapsePtr>> &afferentConnections( void ) const;

		 /**
		  * Method to get efferent connections.
		  * @return efferent connections of a neuron
		  */
		 NSOL_API
		 std::Vector<SynapsePtr> & efferentConnectionsOfANeuron( NeuronPtr neuron );

		 /**
		  * Method to get afferent connections.
		  * @return afferent connections of a neuron
		  */
		 NSOL_API
		 std::Vector<SynapsePtr> & afferentConnectionsOfANeuron( NeuronPtr neuron );

		 /**
		 * Method to get efferent connections as const.
		 * @return efferent connections of a neuron
		 */
		NSOL_API
		std::Vector<SynapsePtr> efferentConnectionsOfANeuron( NeuronPtr neuron ) const;

		/**
		 * Method to get afferent connections as const.
		 * @return afferent connections of a neuron
		 */
		NSOL_API
		std::Vector<SynapsePtr> afferentConnectionsOfANeuron( NeuronPtr neuron ) const;

		/**
		 * Method to get the number of efferent connections of a neuron.
		 * @return numbers of efferent connections
		 */
		NSOL_API
		unsigned int numberOfEfferentConnections( NeuronPtr neuron ) const;

		/**
		 * Method to get the number of afferent connections of a neuron.
		 * @return numbers of afferent connections
		 */
		NSOL_API
		unsigned int numberOfAfferentConnections( NeuronPtr neuron ) const;

		/**
		 * Method to get the total number of connections of a neuron.
		 * @return total numbers of connections
		 */
		NSOL_API
		unsigned int numberOfConnections( NeuronPtr neuron ) const;

		///@}

	  protected:

		  //! Identifier of the circuit
		  unsigned short _id;

		  //! Container of columns, with all the morphology
		  Columns _morphology;

		  //! Container with the all efferent connections between neurons
		  std::map <NeuronPtr, std::Vector<SynapsePtr>> _efferentConnections;

		  //! Container with the all afferent connections between neurons
		  std::map <NeuronPtr, std::Vector<SynapsePtr>> _afferentConnections;

	  }; // namespace std
	}; // namespace nsol

}

#endif

// EOF
