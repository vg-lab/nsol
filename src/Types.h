/**
 * @file    Types.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NS_DATA_LIB_TYPES__
#define __NS_DATA_LIB_TYPES__


#include<list>
#include<vector>

namespace nsdl {


  #if __GNUC__ == 4
    #if  __GNUC_MINOR__ < 7
  //! Vector container redefinition for gcc 4.6 and previous
      #define vector std::vector
  //! List container redefinition for gcc 4.6 and previous
      #define list std::list
    #else
  //! Vector container template alias (gcc 4.7 min required)
  template<typename T>
    using vector = std::vector<T, MyCustomAllocator<T>>;

  //! List container template alias (gcc 4.7 min required)
  template<typename T>
    using list = std::list<T, MyCustomAllocator<T>>;


    #endif
  #endif

  

}


#endif
