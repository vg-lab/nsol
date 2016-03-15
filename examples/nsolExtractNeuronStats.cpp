/*
 * Example to show how to use stats and cached stats
 */

#include <nsol/nsol.h>

void usageMessage( char* programName )
{
  std::cerr << std::endl
            << "Usage: "
            << programName << "\t"
            << "( -bc file_name [ -target target_name ] | " << std::endl
            << "\t\t\t\t\t  -swc swc_file | -xml scene_file ) " << std::endl
            << "\t\t\t\t\t  [ -o output_file_name ] " << std::endl
            << std::endl << std::endl;
  exit(-1);
}

bool atLeastTwo( bool a, bool b, bool c )
{
  return a ^ b ? c : a;
}

  std::string NeuronMorphologyToLabel(
    nsol::NeuronMorphologyStats::TNeuronMorphologyStat stat )
  {
    switch( stat )
    {
    // Volume
    case nsol::NeuronMorphologyStats::DENDRITIC_VOLUME:
      return std::string("Dendritic Volume");
      break;
    case nsol::NeuronMorphologyStats::AXON_VOLUME:
      return std::string("Axon Volume");
      break;
    case nsol::NeuronMorphologyStats::NEURITIC_VOLUME:
      return std::string("Neuritic Volume");
      break;
    case nsol::NeuronMorphologyStats::SOMA_VOLUME:
      return std::string("Soma Volume");
      break;
    case nsol::NeuronMorphologyStats::VOLUME:
      return std::string("Volume");
      break;

    // Surface
    case nsol::NeuronMorphologyStats::DENDRITIC_SURFACE:
      return std::string("Dendritic Surface");
      break;
    case nsol::NeuronMorphologyStats::AXON_SURFACE:
      return std::string("Axon Surface");
      break;
    case nsol::NeuronMorphologyStats::NEURITIC_SURFACE:
      return std::string("Neuritic Surface");
      break;
    case nsol::NeuronMorphologyStats::SOMA_SURFACE:
      return std::string("Soma Surface");
      break;
    case nsol::NeuronMorphologyStats::SURFACE:
      return std::string("Surface");
      break;

    // Length
    case nsol::NeuronMorphologyStats::DENDRITIC_LENGTH:
      return std::string("Dendritic Length");
      break;
    case nsol::NeuronMorphologyStats::AXON_LENGTH:
      return std::string("Axon Length");
      break;
    case nsol::NeuronMorphologyStats::NEURITIC_LENGTH:
      return std::string("Neuritic Length");
      break;

    // Bifurcations
    case nsol::NeuronMorphologyStats::DENDRITIC_BIFURCATIONS:
      return std::string("Dendritic Bifurcations");
      break;
    case nsol::NeuronMorphologyStats::AXON_BIFURCATIONS:
      return std::string("Axon Bifurcations");
      break;
    case nsol::NeuronMorphologyStats::NEURITIC_BIFURCATIONS:
      return std::string("Neuritic Bifurcations");
      break;

    default:
      break;
    }
    return std::string("");
  }


int main ( int argc, char ** argv )
{

  std::string blueConfig;
  std::string swcFile;
  std::string sceneFile;
  std::string target = std::string( "" );
  std::string outFile;

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
    if( std::strcmp( argv[ i ], "-swc" ) == 0 )
    {
      if( ++i < argc )
      {
        swcFile = std::string( argv[ i ]);
      }
      else
        usageMessage( argv[0] );

    }
    if( std::strcmp( argv[ i ], "-xml" ) == 0 )
    {
      if( ++i < argc )
      {
        sceneFile = std::string( argv[ i ] );
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
    if( std::strcmp( argv[ i ], "-o" ) == 0 )
    {
      if( ++i < argc )
      {
        outFile = std::string( argv[ i ] );
      }
      else
        usageMessage( argv[0] );
    }
  }

  if ( atLeastTwo( !blueConfig.empty( ),
                   !swcFile.empty( ),
                   !sceneFile.empty( )))
  {
    std::cerr << "Error: -swc, -xml and -bc options are exclusive" << std::endl;
    usageMessage( argv[0] );
  }

  if ( blueConfig.empty( ) & swcFile.empty( ) & sceneFile.empty( ))
  {
    std::cerr << "Error: no -swc, -xml and -bc options selected" << std::endl;
    usageMessage( argv[0] );
  }

  std::ostream* outStream = &std::cout;
  std::ofstream* outFileStream;

  if ( !outFile.empty( ))
  {
    outFileStream = new std::ofstream( outFile );
    outStream = outFileStream;
  }


  nsol::DataSet dataSet;

  if( !blueConfig.empty( ))
  {
#ifdef NSOL_USE_BBPSDK
    dataSet.loadFromBlueConfig<
      nsol::Node,
      nsol::SectionStats,
      nsol::DendriteStats,
      nsol::AxonStats,
      nsol::SomaStats,
      nsol::NeuronMorphologyCachedStats,
      nsol::Neuron,
      nsol::MiniColumnStats,
      nsol::ColumnStats >( blueConfig,
                           nsol::CORTICAL_HIERARCHY |  nsol::MORPHOLOGY,
                           target );
#else
    std::cerr << "No BBPSDK support built-in" << std::endl;
    return -1;
#endif

  }
  else if( !swcFile.empty( ))
  {

    dataSet.loadCorticalNeuronFromSwc<
      nsol::NodeCached,
      nsol::SectionCachedStats,
      nsol::DendriteCachedStats,
      nsol::AxonCachedStats,
      nsol::SomaStats,
      nsol::NeuronMorphologyCachedStats,
      nsol::Neuron,
      nsol::MiniColumn,
      nsol::Column >( swcFile, 0 );
  }
  else if ( !sceneFile.empty( ))
  {
#ifdef NSOL_USE_QT5CORE
    dataSet.loadScene<
      nsol::NodeCached,
      nsol::SectionCachedStats,
      nsol::DendriteCachedStats,
      nsol::AxonCachedStats,
      nsol::SomaStats,
      nsol::NeuronMorphologyCachedStats,
      nsol::Neuron,
      nsol::MiniColumnStats,
      nsol::ColumnStats >( sceneFile );
#else
    std::cerr << "No QT5 support built-in" << std::endl;
    return -1;
#endif

  }

  // Print out headers

  ( *outStream ) << "Gid" << ","
            << "x" << ","
            << "y" << ","
            << "z" << ","
            << "Layer" << ","
            << "Column" << ","
            << "Minicolumn" << ","
            << "Morphological Type" << ","
            << "Functional Type" << ","
            << "Soma Max. Radius";

  for ( int stat_ = 0;
        stat_ < nsol::NeuronMorphologyStats::NEURON_MORPHOLOGY_NUM_STATS;
        ++stat_ )
  {
    ( *outStream ) << ","
              <<  NeuronMorphologyToLabel(
                nsol::NeuronMorphologyStats::TNeuronMorphologyStat( stat_ ));
  }

  ( *outStream ) << std::endl;

  // Print out values for each neuron

  for( const auto& col : dataSet.columns( ))
  {
    for( const auto miniCol : col->miniColumns( ))
    {
      for( const auto neuron : miniCol->neurons( ))
      {
        ( *outStream ) << neuron->gid( ) << ","
                       << ( neuron->transform( ) *
                            neuron->morphology( )->soma( )->center( )).x( )
                       << ","
                       << ( neuron->transform( ) *
                            neuron->morphology( )->soma( )->center( )).y( )
                       << ","
                  << ( neuron->transform( ) *
                       neuron->morphology( )->soma( )->center( )).z( )
                       << ","
                  << neuron->layer( ) << ","
                  << neuron->miniColumn( )->column( )->id( ) << ","
                  << neuron->miniColumn( )->id( ) << ","
                  << neuron->morphologicalType( ) << ","
                  << neuron->functionalType( ) << ","
                  << neuron->morphology( )->soma( )->maxRadius( );

        assert( neuron->morphology( ) &&  neuron->morphology( )->stats( ));

        nsol::NeuronMorphologyStats* nms = neuron->morphology( )->stats( );

        for ( int stat_ = 0;
              stat_ < nsol::NeuronMorphologyStats::NEURON_MORPHOLOGY_NUM_STATS;
              ++stat_ )
        {
            nsol::NeuronMorphologyStats::TNeuronMorphologyStat stat =
              nsol::NeuronMorphologyStats::TNeuronMorphologyStat( stat_ );
            ( *outStream ) << "," << nms->getStat( stat );
        }
        ( *outStream )  << std::endl;
      }
    }
  }



  return 0;

}
