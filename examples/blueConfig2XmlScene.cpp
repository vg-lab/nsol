/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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
/*
 * Tool that convertes from BlueConfig to nsol XML scene
 */
#include <nsol/nsol.h>

void usageMessage( char* programName )
{
  std::cerr << std::endl
            << "Usage: "
            << programName << "\t"
            << " -bc file_name -target target_name" << std::endl
            << "\t\t\t\t\t  -o output_file_name ] " << std::endl
            << std::endl << std::endl;
  exit(-1);
}

int main ( int argc, char ** argv )
{

  std::string blueConfig;
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

    if ( blueConfig.empty( ) |
         target.empty( ) ||
         outFile.empty( ))
    {
      usageMessage( argv[0] );
    }

    nsol::DataSet dataSet;

    dataSet.loadBlueConfigHierarchy( blueConfig, target );
    dataSet.loadAllMorphologies( );
    dataSet.writeXmlScene( outFile );
    return 0;

}
