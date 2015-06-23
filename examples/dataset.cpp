#include <nsol/nsol.h>


int main ( int argc, char ** argv )
{

  if ( argc < 2 )
  {
    std::cerr << "Usage: " << argv[ 0 ] << " blueconfig_path " << std::endl;
    return -1;
  }

  nsol::DataSet ds;

  std::cout << "Opening dataset " << argv[ 1 ] << std::endl;
  ds.openBlueConfig( argv[ 1 ], bbp::MICROCIRCUIT );

  std::cout << "Loaded " << ds.columns( ).size( ) << " columns " << std::endl;

  std::cout << "Closing dataset " << std::endl;
  ds.close( );

  return 0;

}
