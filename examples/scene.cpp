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

  ds.loadScene( argv[ 1 ] );

  NSOL_FOREACH( col, ds.columns() )
  {
    std::cout << "Column: " << (*col)->id() << std::endl;

    NSOL_FOREACH( miniCol, (*col)->miniColumns( ))
    {
      std::cout << "    MiniColumn: " << (*miniCol)->id( ) << std::endl;

      NSOL_FOREACH( neuron, (*miniCol)->neurons( ))
      {
        std::cout << "        Neuron: " << (*neuron)->gid( ) << " Layer: "
                  << (*neuron)->layer( ) << " Type: "
                  << (int)(*neuron)->neuronType( ) << std::endl;
        std::cout << "            Transform" << std::endl;
        std::cout << "                "
                  << (*neuron)->transform( ).at(0,0) << " "
                  << (*neuron)->transform( ).at(0,1) << " "
                  << (*neuron)->transform( ).at(0,2) << " "
                  << (*neuron)->transform( ).at(0,3) << " "
                  << std::endl;
        std::cout << "                "
                  << (*neuron)->transform( ).at(1,0) << " "
                  << (*neuron)->transform( ).at(1,1) << " "
                  << (*neuron)->transform( ).at(1,2) << " "
                  << (*neuron)->transform( ).at(1,3) << " "
                  << std::endl;
        std::cout << "                "
                  << (*neuron)->transform( ).at(2,0) << " "
                  << (*neuron)->transform( ).at(2,1) << " "
                  << (*neuron)->transform( ).at(2,2) << " "
                  << (*neuron)->transform( ).at(2,3) << " "
                  << std::endl;
        std::cout << "                "
                  << (*neuron)->transform( ).at(3,0) << " "
                  << (*neuron)->transform( ).at(3,1) << " "
                  << (*neuron)->transform( ).at(3,2) << " "
                  << (*neuron)->transform( ).at(3,3) << " "
                  << std::endl;
        if ( (*neuron)->morphology( ))
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
