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
		 : _id (identifier)
		  , _morphology( nullptr )
		  , _efferentConnections( nullptr )
		  , _afferentConnections( nullptr )
		 {
		 }

		 Circuit::~Circuit()
		 {
			 _morphology.clear( );
			 _efferentConnections.clear( );
			 _afferentConnections.clear( );
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
	    	  this->id( ) = other.id( );
			  this->columns( ) = other->columns( );
			  this->efferentConnections( ) = other.efferentConnections( );
			  this->afferentConnections( ) = other.afferentConnections( );
			}

			return *this;

	    }

		bool operator == (Circuit & other ) const
		{
			return ( ( this->id( ) = other.id( ) )
					 ( this->columns( ) == other.columns( ) ) &&
				     ( this->efferentConnections( ) == other.efferentConnections( )) &&
				     ( this->afferentConnections( ) == other.afferentConnections( )));
		}

		bool operator != (Circuit & other ) const
		{
			return !( ( this->id( ) = other.id( ) )
					 ( this->columns( ) == other.columns( ) ) &&
				     ( this->efferentConnections( ) == other.efferentConnections( )) &&
				     ( this->afferentConnections( ) == other.afferentConnections( )));
		}
	    //

	    //
	    // Efferent and Afferent connections methods
	    //
	    bool addEfferentConnection( NeuronPtr neuron, SynapsePtr efferentSynapse )
	    {
	    	std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
	    									_efferentConnections.find(neuron);

			if(it == _efferentConnections.end())
				return false;

			(_efferentConnections[ neuron ]).push_back( efferentSynapse );
			return true;
	    }

	    bool addAfferentConnection( NeuronPtr neuron, SynapsePtr afferentSynapse )
		{
	    	std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_afferentConnections.find(neuron);

			if(it == _afferentConnections.end())
				return false;

			(_afferentConnections[ neuron ]).push_back( afferentSynapse );
			return true;
		}

	    bool removeEfferentConnection( NeuronPtr neuron, SynapsePtr efferentSynapse )
	    {
	    	std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_efferentConnections.find(neuron);

			if(it == _efferentConnections.end())
				return false;

			(_efferentConnections[ neuron ]).erase( efferentSynapse );
	    	return true;

	    }

	    bool removeAfferentConnection( NeuronPtr neuron, SynapsePtr afferentSynapse )
		{
			std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_afferentConnections.find(neuron);

			if(it == _afferentConnections.end())
				return false;

			(_afferentConnections[ neuron ]).erase( afferentSynapse );
			return true;

		}

	    void clearEfferentConnections( NeuronPtr neuron )
	    {
	    	std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_efferentConnections.find(neuron);

			if(it == _efferentConnections.end())
				throw std::runtime_error("No efferent connections in neuron object");

			_efferentConnections.clear();
	    }

	    void clearAfferentConnections( NeuronPtr neuron )
		{
			std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_afferentConnections.find(neuron);

			if(it == _afferentConnections.end())
				throw std::runtime_error("No afferent connections in neuron object");

			_afferentConnections.clear();
		}

	    void  clearConnections( NeuronPtr neuron )
	    {
	    	clearEfferentConnections( neuron );
			clearAfferentConnections( neuron );
	    }

	    std::Vector<SynapsePtr> & efferentConnections( NeuronPtr neuron )
		{
	    	std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_efferentConnections.find(neuron);

			if(it == _efferentConnections.end())
				throw std::runtime_error("No efferent connections in neuron object");

			return _efferentConnections[ neuron ];
		}

	    std::Vector<SynapsePtr> & afferentConnections( NeuronPtr neuron )
		{
			std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_afferentConnections.find(neuron);

			if(it == _afferentConnections.end())
				throw std::runtime_error("No afferent connections in neuron object");

			return _afferentConnections[ neuron ];
		}

	    std::Vector<SynapsePtr> efferentConnections( NeuronPtr neuron ) const
		{
	    	std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_efferentConnections.find(neuron);

			if(it == _efferentConnections.end())
				throw std::runtime_error("No efferent connections in neuron object");

			return _efferentConnections[ neuron ];
		}

	    std::Vector<SynapsePtr> afferentConnections( NeuronPtr neuron ) const
		{
	    	std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_afferentConnections.find(neuron);

			if(it == _afferentConnections.end())
				throw std::runtime_error("No afferent connections in neuron object");

			return _afferentConnections[ neuron ];
		}

	    unsigned int numberOfEfferentConnections( NeuronPtr neuron ) const
	    {
	    	std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_efferentConnections.find(neuron);

			if(it == _efferentConnections.end())
				throw std::runtime_error("Don't found the neuron object");

			return ( unsigned int ) _efferentConnections[ neuron ].size();
	    }

	    unsigned int numberOfAfferentConnections( NeuronPtr neuron ) const
		{
			std::map <NeuronPtr, std::Vector<SynapsePtr>>::iterator it =
											_afferentConnections.find(neuron);

			if(it == _afferentConnections.end())
				throw std::runtime_error("Don't found the neuron object");

			return ( unsigned int ) _afferentConnections[ neuron ].size();
		}


	    /*Columns & connections( void )
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
	    }*/
	    //


	 } // namespace std
} // namespace nsol
