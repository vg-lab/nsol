#include <nsol/nsol.h>

#include <assert.h>

#include <iostream>

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
//  BrionReader brionReader;
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

  dataSet.loadBlueConfigHierarchy( blueConfig, target);

  return 0;
}
