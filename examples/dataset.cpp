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


#ifdef NSOL_USE_BRION
int main ( int argc, char ** argv )
{
  if ( argc < 3 )
  {
    std::cerr << "Usage: " << argv[ 0 ]
              << " blueconfig_path target" << std::endl;
    return -1;
  }

  std::string target( argv[2] );

  nsol::DataSet ds;

  std::cout << "Opening dataset with CORTICAL_HIERARCHY "
            << argv[ 1 ] << std::endl;
  ds.loadBlueConfigHierarchy( argv[ 1 ], target );
  unsigned int numPyr = 0;
  unsigned int numInt = 0;
  unsigned int numExc = 0;
  unsigned int numInh = 0;
  unsigned int numMiniCol = 0;
  unsigned int numNeurons = 0;

  nsol::Columns columns = ds.columns( );
  for( auto col: columns )
  {
    for( auto miniCol: col->miniColumns( ))
    {
      numMiniCol++;
      for( auto neuron: miniCol->neurons( ))
      {
        numNeurons++;
        if( neuron->morphologicalType( ) == nsol::Neuron::PYRAMIDAL )
          numPyr++;
        if( neuron->morphologicalType( ) == nsol::Neuron::INTERNEURON )
          numInt++;
        if( neuron->functionalType( ) == nsol::Neuron::INHIBITORY )
          numInh++;
        if( neuron->functionalType( ) == nsol::Neuron::EXCITATORY )
          numExc++;
      }
    }
  }


  std::cout << "Loaded:\n " << std::endl;
  std::cout << ds.columns( ).size( ) << " columns " << std::endl;
  std::cout << numMiniCol << " minicolumns " << std::endl;
  std::cout << numNeurons << " neurons " << std::endl;
  std::cout << numPyr << " pyramidal neurons " << std::endl;
  std::cout << numInt << " interneurons " << std::endl;
  std::cout << numExc << " exitatory neurons " << std::endl;
  std::cout << numInh << " inhibitory neurons " << std::endl;


  std::cout << "Loading morphologies" << std::endl;

  ds.loadAllMorphologies( );

  for ( const auto& pair: ds.neurons( ))
  {
    nsol::NeuronPtr neuron = pair.second;

    nsol::NeuronMorphologyPtr morpho = neuron->morphology( );
    if( !morpho )
    {
      std::cout << "Neuron " << neuron->gid( ) << "hasn't morphology"
                << std::endl;
    }
    else
    {
      std::cout << neuron->gid( ) << "\t" << "Soma center: "
                << neuron->transform( ).col( 3 ).transpose( )
                << std::endl;
    }
  }


  std::cout << "Closing dataset " << std::endl;
  ds.close( );



#else
int main ( void )
{
  std::cerr << "This example needs Brion support." << std::endl;
#endif

  return 0;

}
