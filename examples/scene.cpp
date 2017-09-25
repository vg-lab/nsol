/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Author <author@urjc.es>
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


#ifdef NSOL_USE_QT5CORE

int main ( int argc, char ** argv )
{
  if ( argc < 2 )
  {
    std::cerr << "Usage: " << argv[ 0 ] << " xml_scene_file " << std::endl;
    return -1;
  }

  nsol::DataSet ds;

  try
  {
    ds.loadXmlScene( argv[ 1 ] );
  }
  catch ( std::exception& ex )
  {
    std::cerr << "Error loading scene: " << ex.what( ) << std::endl;
    return -1;
  }

  for( auto const& col : ds.columns() )
  {
    std::cout << "Column: " << col->id() << std::endl;

    for( auto const& miniCol : col->miniColumns( ))
    {
      std::cout << "    MiniColumn: " << miniCol->id( ) << std::endl;

      for( auto const& neuron : miniCol->neurons( ))
      {
        std::cout << "        Neuron: " << neuron->gid( ) << " Layer: "
                  << neuron->layer( ) << " Type: "
                  << (int)neuron->morphologicalType( ) << std::endl;
        std::cout << "            Transform" << std::endl;
        std::cout << "                "
                  << neuron->transform( )(0,0) << " "
                  << neuron->transform( )(0,1) << " "
                  << neuron->transform( )(0,2) << " "
                  << neuron->transform( )(0,3) << " "
                  << std::endl;
        std::cout << "                "
                  << neuron->transform( )(1,0) << " "
                  << neuron->transform( )(1,1) << " "
                  << neuron->transform( )(1,2) << " "
                  << neuron->transform( )(1,3) << " "
                  << std::endl;
        std::cout << "                "
                  << neuron->transform( )(2,0) << " "
                  << neuron->transform( )(2,1) << " "
                  << neuron->transform( )(2,2) << " "
                  << neuron->transform( )(2,3) << " "
                  << std::endl;
        std::cout << "                "
                  << neuron->transform( )(3,0) << " "
                  << neuron->transform( )(3,1) << " "
                  << neuron->transform( )(3,2) << " "
                  << neuron->transform( )(3,3) << " "
                  << std::endl;
        if ( neuron->morphology( ))
          std::cout << "            Morphology linked" << std::endl;
        else
          std::cout << "            Morphology not linked" << std::endl;
      }
    }
  }

  ds.close( );

#else
int main ( void )
{

  std::cerr << "This example needs Qt5 support." << std::endl;
#endif

  return 0;

}
