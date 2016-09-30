/**
* @file    brionCircuitLoader2.cpp
* @brief Test for class nsol::Circuit
* @author   Raquel Jarillo Pellon <raquel.jarillo@urjc.es>
* @date
* @remarks Copyright (c) GMRV/URJC. All rights reserved.
*          Do not distribute without further notice.
*/

#define TESTING_PRINT_LITERAL

#include <nsol/nsol.h>
#include <nsol/DataSet.h>
#include <nsol/Circuit.h>

#include <Eigen/Sparse>
#include <assert.h>

#include <iostream>
#include <stdio.h>

using namespace nsol;
using namespace std;

void usageMessage( char* programName )
{
  std::cerr << std::endl
            << "Usage: "
            << programName << "\t"
            << " -bc file_name -target target_name" << std::endl
            << std::endl << std::endl;
  exit(-1);
}

int main( int argc, char* argv[ ])
{
    std::string blueConfig;
    std::string target = std::string( "" );

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
  }

  if ( blueConfig.empty( ) | target.empty( ))
  {
    usageMessage( argv[0] );
  }

  DataSet dataSet;

  cout << "Open BlueConfig ..." << endl;

  dataSet.loadBlueConfigHierarchy( blueConfig, target );
  dataSet.loadAllMorphologies( );
  dataSet.loadBlueConfigConnectivity( );

  cout << " EXECUTING CircuitLoader... " << endl;
  cout << endl; cout << endl; cout << endl;

  NeuronsMap neuronsMap = dataSet.neurons();
  Circuit circuit = dataSet.circuit();


   Eigen::SparseMatrix< float > C = circuit.contactsNeurons( neuronsMap );
   cout << "Contacts between neurons: " << endl;
   cout << " - Matrix C [ "<< C.rows()<<" ]"
                       "[ "<< C.cols()<<" ]"<< endl;

   cout << "     - Diagonal:" << C.diagonal() << endl;


   std::set<SynapsePtr> connections = circuit.connections();


//   for(unsigned int i = 0; i < C.rows(); i++)
//       for(unsigned int j = 0; j < C.cols(); j++)
//          std::swap(C.insert(i,j), C.insert(j,i))
   Eigen::SparseMatrix<float> A  = C.triangularView<Eigen::Upper>();
   Eigen::SparseMatrix<float> Ct = C.transpose();

   if( C.isApprox( Ct ) )
       cout << "     - Is Symmetric! " << endl;

   int count = 0;
   for( std::set<SynapsePtr>::iterator it=connections.begin();
        it != connections.end(); ++it )
   {
        if( count == 10 ) break;

        SynapsePtr connection = (*it);
        NeuronPtr neuronPre = connection->preSynapticNeuron();
        NeuronPtr neuronPost = connection->postSynapticNeuron();

        cout << "---------------------------------" << endl;
        cout << "     - Synapse ID:" << connection->id() << endl;
        cout << "     - neuron pre:"  << neuronPre->gid() << endl;
        cout << "     - neuron post:" << neuronPost->gid() << endl;
        cout << "     - C( " << neuronPre->gid() << ", "
                            << neuronPost->gid() << " ) = "
                            << C.coeff(neuronPre->gid()-1,
                                        neuronPost->gid()-1) << endl;

        cout << "     - C( " << neuronPost->gid() << ", "
                            << neuronPre->gid() << " ) = "
                            <<  C.coeff(neuronPost->gid()-1,
                                         neuronPre->gid()-1) << endl;

        cout << endl;
        count ++;
   }

   cout << "------  SPARSE MATRIX  ---------" << endl;
   cout << C << endl;
   cout << "------  TRIANGULAR MATRIX  ---------" << endl;
   cout << A << endl;

  return 0;

}
