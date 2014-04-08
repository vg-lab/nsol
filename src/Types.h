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

#include <boost/geometry/geometries/point.hpp>


namespace nsdl {


  #if __GNUC__ == 4
    #if  __GNUC_MINOR__ < 7
  //! Vector container redefinition for gcc 4.6 and previous
      #define Vector std::vector
  //! List container redefinition for gcc 4.6 and previous
      #define List std::list
    #else
  //! Vector container template alias (gcc 4.7 min required)
  template<typename T>
    using Vector = std::vector<T, MyCustomAllocator<T>>;

  //! List container template alias (gcc 4.7 min required)
  template<typename T>
    using List = std::list<T, MyCustomAllocator<T>>;


    #endif
  #endif

  




}


#endif
