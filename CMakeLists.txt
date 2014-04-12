project(nsdl)

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src ${VMMLIB_INSTALL_DIR}/include) 


add_subdirectory(test)
