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
		 : _id (identifier)
		  , _morphology( )
		  , _connections( )
		 {
		 }

		 Circuit::~Circuit()
		 {
			 _morphology.clear( );
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
	    Circuit & Circuit::operator = (const Circuit & other)
	    {
	    	if (this != &other)
			{
	    	  this->id( ) = other.id( );
			  this->columns( ) = other.columns( );
			  this->connections( ) = other.connections( );
			}

			return *this;

	    }

		bool Circuit::operator == (Circuit & other ) const
		{
			return ( ( this->id( ) == other.id( ) ) &&
					 ( this->columns( ) == other.columns( ) ) &&
				     ( this->connections( ) == other.connections( )));
		}

		bool Circuit::operator != (Circuit & other ) const
		{
			return !( ( this->id( ) == other.id( ) ) &&
					  ( this->columns( ) == other.columns( ) ) &&
				      ( this->connections( ) == other.connections( )));
		}


		//
		// Connections methods
		//
		virtual void Circuit::addConnection(SynapsePtr synapse )
		{

			_connections.insert(synapse);

		}

		virtual bool Circuit::removeConnection(SynapsePtr synapse )
		{
			std::set<SynapsePtr>::iterator cIt = _connections.find(synapse);

			if( cIt == _connections.end())
				return false;

			_connections.erase(cIt);
			return true;

		}

		virtual void Circuit::clearConnections( void )
		{

			_connections.clear();
		}

		virtual std::set<SynapsePtr> & Circuit::connections( void )
		{

			return _connections;
		}

		virtual std::set<SynapsePtr> Circuit::connections( void ) const
		{

			return _connections;
		}

		virtual unsigned int Circuit::numberOfConnections( ) const
		{

			return ( unsigned int ) _connections.size();
		}



} // namespace nsol
