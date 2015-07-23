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
		 //
		 // Constructors and destructors
		 //
		 Circuit::Circuit( const unsigned short identifier )
		 {
			 _id = identifier;
		 }

		 Circuit::Circuit( const Circuit & other )
		 : _id (other.id())
		  ,_connections( other.connections())
		 {
		 }

		 Circuit::~Circuit()
		 {
			 _connections.clear( );
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

	    //
	    // Operators
	    //
	    Circuit & Circuit::operator = (const Circuit & other)
	    {
	    	if (this != &other)
			{
	    	  this->id( ) = other.id( );
			  this->connections( ) = other.connections( );
			}

			return *this;

	    }

		bool Circuit::operator == (Circuit & other ) const
		{
			return ( ( this->id( ) == other.id( ) ) &&
				     ( this->connections( ) == other.connections( )));
		}

		bool Circuit::operator != (Circuit & other ) const
		{
			return !( ( this->id( ) == other.id( ) ) &&
				      ( this->connections( ) == other.connections( )));
		}


		//
		// Connections methods
		//
		void Circuit::addConnection(SynapsePtr synapse )
		{

			_connections.insert(synapse);

		}

		bool Circuit::removeConnection(SynapsePtr synapse )
		{
			std::set<SynapsePtr>::iterator cIt = _connections.find(synapse);

			if( cIt == _connections.end())
				return false;

			_connections.erase(cIt);
			return true;

		}

		void Circuit::clearConnections( void )
		{

			_connections.clear();
		}

		std::set<SynapsePtr> & Circuit::connections( void )
		{

			return _connections;
		}

		std::set<SynapsePtr> Circuit::connections( void ) const
		{

			return _connections;
		}

		 unsigned int Circuit::numberOfConnections( ) const
		{

			return ( unsigned int ) _connections.size();
		}



} // namespace nsol
