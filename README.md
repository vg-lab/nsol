[![build status](https://gitlab.vglab.es/nsviz/nsol/badges/master/build.svg)](https://gitlab.vglab.es/nsviz/nsol/commits/master)
[![coverage report](https://gitlab.vglab.es/nsviz/nsol/badges/master/coverage.svg)](https://gitlab.vglab.es/nsviz/nsol/commits/master)


# NSOL - Neuroscience Objects Library
(c) 2015. GMRV / VGLAB / URJC

www.gmrv.es
www.vglab.es
gmrv@gmrv.es

## Introduction

nsol is a library that provides data structures to handle basic neuroscientific 
data, mainly cortex morphologies and structures as Spine, Soma, Neuron, Column, etc...
It also provides some readers and writers to load and store dataset in swc 
(as used by [NeuroMorpho](http://neuromorpho.org/)) and XML file formats.   
It also reads circuits and morphologies using [Brion](https://github.com/BlueBrain/Brion),
which is an optional dependency.  
It is used in projects as
[NeuroScheme](https://hbp-hpc-platform.fz-juelich.de/?hbp_software=neuroscheme),
[ViSimpl](http://gmrv.es/visimpl/) and [NeuroLOTs](http://gmrv.es/neurotessmesh/)

## Dependencies

* Required dependencies:
    * Eigen3 (*1)
* Optional dependencies:
    * FiReS (*2)
    * Brion (*2)
    * Boost's Unit Test Framework
    * Qt5Core

(*1) Install linux package libeigen3-dev or download sources from http://eigen.tuxfamily.org/       
(*2) This dependencies can be built uncommenting theirs corresponding line in the file .gitsubprojects

## Building

nsol has been successfully built and used on Ubuntu 17.04/16.04, Mac OSX
Yosemite/Capitan/Sierra and Windows 7/8/10 (Visual Studio 2015 Win64). 
The following steps should be enough to build it under linux/Mac OSX:

~~~~~~~~~~~~~
git clone --recursive https://github.com/vg-lab/nsol
mkdir nsol/build && cd nsol/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCLONE_SUBPROJECTS=ON
make
~~~~~~~~~~~~~

## Testing

After building NSOL, you can run some examples in bin directory.
For example, to manually run a simple test that parses an input .swc 
file and dumps some statistics about it, use the command:
~~~~~~~~~~~~~
./bin/nsolScene testData/scene.xml
~~~~~~~~~~~~~

## Documentation

You can access the online API documentation generated from the source 
(using [Doxygen](http://doxygen.org/) ) in 
https://vg-lab.github.io/doc/nsol/

