/**
 * @file    Column.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_COLUMN__
#define __NSOL_COLUMN__

#include <MiniColumn.h>
#include <Container/MiniColumns.h>

namespace nsol {
  
  class Column {

  public:
	  Column(unsigned short id = 0)
	  {
		  _id = id;
	  }

	  ~Column()
	  {
	      for (Vector<MiniColumn *>::iterator it = _miniColumns.begin();
	      it != _miniColumns.end(); ++it)
	        delete *it;

	      _miniColumns.clear();
	  }

	/**
	 * Method to add a mini column.
	 */
	  void addMiniColumn(MiniColumnPtr miniColumn)
	  {
		  _miniColumns.push_back(miniColumn);
	  }

	/**
	 * Method to add a new mini column.
	 * @return pointer to the added mini column
	 */
	  MiniColumnPtr addMiniColumn(unsigned short id = 0)
	  {
		  _miniColumns.push_back(new MiniColumn(id));
		  return _miniColumns.back();
	  }

	/**
	 * Method to set the column id.
	 */
	  void id(const unsigned short id)
	  {
		  _id = id;
	  }

	/**
	 * Method to get the column id.
	 * @return column id
	 */
	  unsigned short &id(void)
	  {
		  return _id;
	  }

	/**
	 * Method to get minicolumns.
	 * @return minicolumns of the column
	 */
	  MiniColumns &miniColumns()
	  {
		  return _miniColumns;
	  }
 
  protected:

	  unsigned short _id;
	  MiniColumns _miniColumns;
  };
  
}


#endif
