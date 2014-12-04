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
		  * Copy constructor
		  * @param other circuit to be copied
		  */
		  NSOL_API
		  Circuit( const Circuit & other );

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

		/** @name Connections related methods */
		 ///@{

		// TODO:
		/**
	    * Method to add a connection.
	    * @param connection connection to add to this circuit
	    */
	    NSOL_API
	    void addConnection( NeuronPtr neuron, SynapsePtr synapse );

	    /**
		 * Method to remove a connection.
		 * @param neuron pointer to the connection to be removed
   	     * @return true if connection removed false otherwise
	     */
		 NSOL_API
		 bool removeConnection( NeuronPtr neuron );

		 /**
		  * Method to clear connections.
		  */
		 NSOL_API
		 void clearConnections( void );

		 /**
		  * Method to get connections.
		  * @return connections of the circuit
		  */
		 NSOL_API
		 Columns & connections( void );

		 /**
		 * Method to get connections as const.
		 * @return connections of the circuit
		 */
		NSOL_API
		Columns connections( void ) const;

		/**
		 * Method to get the number of connections.
		 * @return numbers of connections
		 */
		NSOL_API
		unsigned int numberOfConnections( void ) const;

		///@}

	  protected:

		  //! Identifier of the circuit
		  unsigned short _id;

		  //! Container of columns, with all the morphology
		  Columns _morphology;

		  //! Container with the all connections between neurons
		  std::map <NeuronPtr, SynapsePtr> _connections;

	  }; // namespace std
	}; // namespace nsol

}

#endif

// EOF
