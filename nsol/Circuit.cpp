/**
 * @file    Circuit.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include "nsol/Circuit.h"

namespace nsol
{
	 namespace std{

		 //
		 // Constructors and destructors
		 //

		 Circuit::Circuit( const unsigned short identifier )
		 {
		   _id = identifier;
		 }

		 Circuit::Circuit( const Circuit & other )
		     : _id( other.id( ))
		     , _morphology( other.columns( ))
		 	 , _connections( other.connections( ))
		   {}

		 Circuit::~Circuit()
		 {
			 _morphology.clear();
		 }

		 //
		 // Morphological measures methods
		 //

		 unsigned short & Circuit::id(void)
	     {
		   return _id;
	     }

	    unsigned short Circuit::id(void) const
	    {
		  return _id;
	    }


		void Circuit::addColumn(ColumnPtr column)
	    {
		   _morphology.push_back(column);
	    }

	    bool Circuit::removeColumn(ColumnPtr column)
	    {
	      Columns::iterator cIt =
	      find (_morphology.begin( ), _morphology.end( ), column);

	      if ( cIt == _morphology.end( ))
	    	  return false;

	      _morphology.erase( cIt );
		  return true;
		}

		void Circuit::clearColumns( void )
	    {
		 _morphology.clear( );
    	}

		Columns & Circuit::columns()
	    {
		   return _morphology;
	    }

	    Columns Circuit::columns() const
	    {
	       return _morphology;
	    }

	    unsigned int Circuit::numberOfColumns(void) const
	    {
	      return ( unsigned int ) _morphology.size();
	    }

	    //
	    // Operators
	    //
	    // TODO:
	    Circuit & operator = (const Circuit & other)
	    {
	    	if (this != &other)
			{
			  this->columns( ) = other->columns( );
			  this->connections( ) = other.connections( );
			}

			return *this;

	    }

		bool operator == (Circuit & other ) const
		{
			return ( ( this->columns( ) == other.columns( ) ) &&
				     ( this->connections( ) == other.connections( )));
		}

		bool operator != (Circuit & other ) const
		{
			return !( ( this->columns( ) == other.columns( ) ) &&
				      ( this->connections( ) == other.connections( )));
		}
	    //

	    //
	    // Connections methods
	    //
	    // TODO:
	    void addConnection( NeuronPtr neuron, SynapsePtr synapse )
	    {
	    	_connections[ neuron ] = synapse;
	    }

	    bool removeConnection( NeuronPtr neuron )
	    {
	    	std::map <NeuronPtr, SynapsePtr>::iterator it = _connections.find(neuron);

	    	if(it == _connections.end())
	    		return false;

	    	_connections.erase(neuron);
	    	return true;

	    }

	    void clearConnections( void )
	    {
	    	_connections.clear();
	    }

	    Columns & connections( void )
	    {
	    	return _connections;
	    }

	    Columns connections( void ) const
	    {
	    	return _connections;
	    }

	    unsigned int numberOfConnections( void ) const
	    {
	    	return ( unsigned int ) _connections.size();
	    }
	    //


	 } // namespace std
} // namespace nsol
