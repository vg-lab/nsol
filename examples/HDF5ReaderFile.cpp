#include <nsol/nsol.h>

#include <assert.h>

#include <iostream>

using namespace nsol;
using namespace std;

int main( int argc, char* argv[ ])
{
  HDF5Reader r;

  if( argc < 2 )
  {
    std::cerr << "Error: hdf5 file parameter needed" << std::endl;
    return -1;
  }
  cout << "Reading file " << argv[1] << endl;

  NGVMorphologyPtr ngvMorpho = r.loadHDF5File( std::string( argv[1] ));

  std::cout << "Numbre of NGVMophology sections: " << ngvMorpho->sections( ).size( )
            << std::endl;
  // NodePtr node = ngvMorpho->nodes( )[0];

  // for ( auto node: ngvMorpho->nodes( ))
  // std::cout << "=== Node " << node->id( ) << " ===\nPosition: "
  //           << node->point( ).x( ) << ", " << node->point( ).y( ) << ", "
  //           << node->point( ).z( ) << "\nRadius: " << node->radius( )
  //           << std::endl;
  return 0;
}
