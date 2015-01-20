/**
 * @file    Circuit.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_CIRCUIT__
#define __NSOL_CIRCUIT__

#include <iostream>
#include <set>
//#include <map>

#include <nsol/Container/Columns.h>


namespace nsol
{
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

		 /** @name Connections related methods */
		 ///@{

	     /**
		 * Method to add a connection.
		 * @param synapse to add to this circuit
		 * @return true if connection added false otherwise
		 */
		 NSOL_API
		 virtual void addConnection(SynapsePtr synapse );

	     /**
		 * Method to remove a connection.
		 * @param synapse to be removed
		 * @return true if the connection removed false otherwise
		 */
		 NSOL_API
		 virtual bool removeConnection(SynapsePtr synapse );

		 /**
		 * Method to clear all the connections
		 * of all the circuit.
		 */
		 NSOL_API
		 virtual void clearConnections( void );

		 /**
		  * Method to get all the connections (synapses of the circuit).
		  * @return synapses of the circuit
		  */
		 NSOL_API
		 virtual std::set<SynapsePtr> & connections( void );

		 /**
		 * Method to get all the connections as const.
		 * @return synapses of the circuit
		 */
		 NSOL_API
		 virtual std::set<SynapsePtr> connections( void ) const;

		 /**
		 * Method to get the total number of connections of the circuit.
		 * @return total numbers of connections
		 */
		 NSOL_API
		 virtual unsigned int numberOfConnections( ) const;

		///@}


	  protected:

		  //! Identifier of the circuit
		  unsigned short _id;

		  //! Container of columns, with all the morphology
		  Columns _morphology;

		  //! Container with the all connections between neurons
		  std::set<SynapsePtr> _connections;


	}; // namespace nsol

}

#endif

// EOF
