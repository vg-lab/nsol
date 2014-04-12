/**
 * @file    Types.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NS_DATA_LIB_TYPES__
#define __NS_DATA_LIB_TYPES__


#include <list>
#include <vector>

#include <iostream>

#include <vmmlib/vector.hpp>


/* #include <boost/geometry/geometries/point.hpp> */


namespace nsdl {


#if __GNUC__ == 4
#if  __GNUC_MINOR__ > 6
  //! Vector container template alias (gcc 4.7 min required)
  template<typename T>
    using Vector = std::vector<T>;
  
  //! List container template alias (gcc 4.7 min required)
  template<typename T>
    using List = std::list<T>;
#else
  //! Vector container redefinition for gcc 4.6 and previous
#define Vector std::vector
  //! List container redefinition for gcc 4.6 and previous
#define List std::list
  
#endif
#endif


typedef vmml::vector< 3, float > Vec3f;

  




}


#endif
