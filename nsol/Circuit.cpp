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



	 } // namespace std
} // namespace nsol
