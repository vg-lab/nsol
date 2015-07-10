#include <nsol/nsol.h>


#ifdef NSOL_WITH_QT5CORE

int main ( int argc, char ** argv )
{
  if ( argc < 2 )
  {
    std::cerr << "Usage: " << argv[ 0 ] << " xml_scene_file " << std::endl;
    return -1;
  }

  nsol::DataSet ds;

  ds.loadScene( argv[ 1 ] );

  ds.close( );

#else
int main ( void )
{
  std::cerr << "This example needs Qt5 support." << std::endl;
#endif

  return 0;

}
