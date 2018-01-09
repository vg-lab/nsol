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

// std.
#include <assert.h>
#include <iostream>

using namespace nsol;
using namespace std;

int main(int argc, char *argv[])
{
  if ( argc < 2 )
  {
    std::cerr << "Usage: bin/nsolEspINASkeletonReader espina_skeleton_file" << std::endl;
    return -1;
  }

  std::string espinaSkeletonFile( argv[1] );

  cout << "Reading file: " << espinaSkeletonFile << endl;

  EspINASkeletonReader espinaSkeletonReader;

  VectorsReaderInput* vectorsReaderInput =
    espinaSkeletonReader.read( espinaSkeletonFile );

  // Feedback.
  for( float elem : vectorsReaderInput->points )
  {
    std::cout << elem << ";";
  }
  std::cout << std::endl << std::endl;

  for( float elem : vectorsReaderInput->segments )
  {
    std::cout << elem << ";";
  }
  std::cout << std::endl << std::endl;

  VectorsReader reader;
  MorphologyPtr morphology =
    reader.loadMorphology( vectorsReaderInput->points,
                           vectorsReaderInput->segments );

  if( !morphology )
  {
    std::cerr << "Error: morphology not loaded " << std::endl;
    return -1;
  }

  std::cout << "Number of sections: " << morphology->sections( ).size( )
            << std::endl;

  return 0;
}
