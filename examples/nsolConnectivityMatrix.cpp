/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo Pellon <raquel.jarillo@urjc.es>
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
#include <nsol/DataSet.h>
#include <nsol/Circuit.h>

#include <Eigen/Sparse>
#include <assert.h>

#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace nsol;
using namespace std;

void usageMessage( char* programName )
{
  std::cerr << std::endl
            << "Usage: "
            << programName << "\t"
            << " -bc file_name -target target_name -pathfile path_file"
            << std::endl << std::endl << std::endl;
  exit(-1);
}

bool contactsNeurons( const NeuronsMap& neurons_, Circuit& circuit_,
                      Eigen::SparseMatrix< unsigned int >& contacts_ )
{
  std::set<SynapsePtr> synapses = circuit_.synapses( Circuit::ALL );

  unsigned int dim = neurons_.size();

  contacts_.resize(dim, dim);
  contacts_.setZero();

  Eigen::SparseMatrix< unsigned int > contactsMatrix = contacts_;

  for( const auto& synapse: synapses )
  {
    NeuronsMap::const_iterator itNeuronPre  = neurons_.
                                           find( synapse->preSynapticNeuron( ));
    NeuronsMap::const_iterator itNeuronPost = neurons_.
                                          find( synapse->postSynapticNeuron( ));

    if( itNeuronPre == neurons_.end() || itNeuronPost == neurons_.end() )
    {
      return false;
    }

    unsigned int v = contactsMatrix.coeff( synapse->preSynapticNeuron( )-1,
                              synapse->postSynapticNeuron( )-1 ) + 1;

    contactsMatrix.coeffRef( synapse->preSynapticNeuron( )-1,
                                  synapse->postSynapticNeuron( )-1 ) = v;
  }

  contacts_.swap( contactsMatrix );

  return true;
}


int main( int argc, char* argv[ ])
{
  std::string blueConfig;
  std::string target = std::string( "" );
  std::string infoPath;

  for( int i = 1; i < argc; i++ )
  {
    if( std::strcmp( argv[ i ], "-bc" ) == 0 )
    {
      if( ++i < argc )
      {
        blueConfig = std::string( argv[ i ]);
      }
      else
        usageMessage( argv[0] );
    }
    if( std::strcmp( argv[ i ], "-target" ) == 0 )
    {
      if( ++i < argc )
      {
        target = std::string( argv[ i ] );
      }
      else
        usageMessage( argv[0] );
    }

    if( std::strcmp( argv[ i ], "-pathfile" ) == 0 )
    {
      if( ++i < argc )
      {
        infoPath = std::string( argv[ i ] );
      }
      else
        usageMessage( argv[0] );
    }
  }

  if ( blueConfig.empty( ) | target.empty( ) | infoPath.empty( ))
  {
    usageMessage( argv[0] );
  }

  DataSet dataSet;

  dataSet.loadBlueConfigHierarchy( blueConfig, target );
  dataSet.loadAllMorphologies( );
  dataSet.loadBlueConfigConnectivity( );

  const NeuronsMap& neuronsMap = dataSet.neurons();
  Circuit circuit = dataSet.circuit();

  Eigen::SparseMatrix< unsigned int > contactsMatrix;

  bool success = contactsNeurons( neuronsMap, circuit, contactsMatrix );

  if( !success ) return -1;

  std::ofstream ofs;
  ofs.open( infoPath, std::ofstream::out | std::ofstream::trunc );

  unsigned int count = 1;

  ofs << '"' << " X " << '"' << ";";
  for( int col=0; col < contactsMatrix.cols(); ++col )
  {
    ofs << '"' << " Post " << count << '"' << ";";

    count++;
  }
  ofs << std::endl;

  count = 1;
  for( int row=0; row < contactsMatrix.rows(); ++row )
  {
    ofs << '"' << "Pre " << count << '"' << ";";
    for( int col=0; col < contactsMatrix.cols(); ++col )
    {
      ofs << '"' << contactsMatrix.coeff( row, col ) << '"' << ";";
    }

    ofs << std::endl;
    count++;
  }

  ofs.flush();
  ofs.close();

  return 0;

}
