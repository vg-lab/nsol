/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <nsol/nsol.h>

#include <assert.h>

#include <nsol/nsol.h>
#include <iostream>

int main( int argc, char* argv[ ] )
{
  nsol::VasculatureReader r;

  if( argc < 2 )
  {
    std::cerr << "Error: morphology input file parameter needed" << std::endl;
    return -1;
  }

  std::cout << "Reading file " << argv[1] << std::endl;

  nsol::MorphologyPtr morphology =
    r.loadMorphology( std::string( argv[1] ));

  if( !morphology )
  {
    std::cerr << "Error: morphology not loaded " << std::endl;
    return -1;
  }
  std::cout << "Number of section: " << morphology->sections( ).size( )
            << std::endl;
  return 0;
}
