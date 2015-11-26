#include <nsol/nsol.h>


#ifdef NSOL_USE_BBPSDK
int main ( int argc, char ** argv )
{
  if ( argc < 2 )
  {
    std::cerr << "Usage: " << argv[ 0 ]
              << " blueconfig_path [target]" << std::endl;
    return -1;
  }

  std::string target("");
  if ( argc > 2  )
  {
    target = std::string( argv[ 2 ] );
  }

  nsol::DataSet ds;

  std::cout << "Opening dataset with CORTICAL_HIERARCHY "
            << argv[ 1 ] << std::endl;
  ds.loadFromBlueConfig( argv[ 1 ], nsol::CORTICAL_HIERARCHY, target );
  std::cout << "Loaded " << ds.columns( ).size( ) << " columns " << std::endl;
  std::cout << "Closing dataset " << std::endl;
  ds.close( );

  std::cout << "Opening dataset with MORPHOLOGY " << argv[ 1 ] << std::endl;
  ds.loadFromBlueConfig( argv[ 1 ], nsol::MORPHOLOGY, target );
  std::cout << "Loaded " << ds.columns( ).size( ) << " columns " << std::endl;
  std::cout << "Closing dataset " << std::endl;
  ds.close( );


#else
int main ( void )
{
  std::cerr << "This example needs BBPSDK support." << std::endl;
#endif

  return 0;

}
