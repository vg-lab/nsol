[![build status](https://gitlab.gmrv.es/nsviz/nsol/badges/master/build.svg)](https://gitlab.gmrv.es/nsviz/nsol/commits/master)
[![coverage report](https://gitlab.gmrv.es/nsviz/nsol/badges/master/coverage.svg)](https://gitlab.gmrv.es/nsviz/nsol/commits/master)


# NSOL - Neuroscience Objetcs Library
(c) 2015. GMRV / URJC

www.gmrv.es
gmrv@gmrv.es

## Introduction

nsol is a library that provides data structures to handle neuroscientific data, 
mainly cortex morphologies and cortex estructures. It also provides some readers
and writers to load dataset and to store them.

## Dependencies

Required dependencies: Eigen3
Optional dependencies: FiReS, Brion and Boost's Unit Test Framework and Qt5Core

## Building

nsol has been succesfully built and used on Ubuntu 17.04/16.04, Mac OSX
Yosemite/Capitan and Windows 7/8/10 (Visual Studio 2013 Win64). The following
steps should be enough to build it:

```bash
git clone https://gitlab.gmrv.es/nsviz/nsol.git
mkdir nsol/build && cd nsol/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
