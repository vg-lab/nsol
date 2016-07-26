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

  for ( auto par: ds.neurons( ))
  {
    nsol::NeuronPtr neuron = par.second;

    nsol::NeuronMorphologyPtr morpho = neuron->morphology( );
    if( !morpho )
    {
      std::cout << "Neuron " << neuron->gid( ) << "hasn't morphology"
                << std::endl;
    }
    else
    {
      std::cout << "Soma center: " << morpho->soma( )->center( )
                << std::endl;
    }
  }


  std::cout << "Closing dataset " << std::endl;
  ds.close( );

  // std::cout << "Opening dataset with MORPHOLOGY " << argv[ 1 ] << std::endl;
  // ds.loadFromBlueConfig( argv[ 1 ], nsol::MORPHOLOGY, target );
  // std::cout << "Loaded " << ds.columns( ).size( ) << " columns " << std::endl;
  // std::cout << "Closing dataset " << std::endl;
  // ds.close( );


#else
int main ( void )
{
  std::cerr << "This example needs BBPSDK support." << std::endl;
#endif

  return 0;

}
