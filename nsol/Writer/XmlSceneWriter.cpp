/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of FiReS <https://github.com/gmrvvis/FiReS>
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
#include "XmlSceneWriter.h"
#include "SwcWriter.h"
#include "../Log.h"
#include <iostream>
#include <fstream>

namespace nsol
{

  std::string morphologicalTypeToString( const Neuron::TMorphologicalType type )
  {
    switch( type )
    {
    case Neuron::UNDEFINED:
      return std::string( "UNDEFINED" );
      break;
    case Neuron::PYRAMIDAL:
      return std::string( "PYRAMIDAL" );
      break;
    case Neuron::INTERNEURON:
      return std::string( "INTERNEURON" );
      break;
    default:
      break;
    }
    Log::log( "nsol warning (XmlSceneWriter): "
              "unknown morphological type",
              LOG_LEVEL_WARNING );
    return std::string( "UNDEFINED" );
  }

  std::string functionalTypeToString( const Neuron::TFunctionalType type )
  {
    switch( type )
    {
    case Neuron::UNDEFINED_FUNCTIONAL_TYPE:
      return std::string( "UNDEFINED_FUNCTIONAL_TYPE" );
      break;
    case Neuron::INHIBITORY:
      return std::string( "INHIBITORY" );
      break;
    case Neuron::EXCITATORY:
      return std::string( "EXCITATORY" );
      break;
    default:
      break;
    }
    Log::log( "nsol warning (XmlSceneWriter): "
              "unknown functional type",
              LOG_LEVEL_WARNING );
    return std::string( "UNDEFINED_FUNCTIONAL_TYPE" );
  }

  bool XmlSceneWriter::writeToXml( const std::string& fileName,
                                   const Columns& columns,
                                   std::map< std::string, NeuronMorphologyPtr >
                                   morphologies,
                                   bool relativeToXmlMorphologyPath )
  {
    if ( columns.size( ) == 0 )
      Log::log( "Writting Xml file from an empty columns container",
                LOG_LEVEL_WARNING );

    std::ofstream file;
    file.open( fileName );

    if ( !file.is_open( ))
      NSOL_THROW( "Xml output file could not be opened for writting." );

    // Write headers
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
         << std::endl << std::endl;
    file << "<scene version=\"0.1\">" << std::endl;
    file << "  <morphology>" << std::endl;


    file << "    <columns>" << std::endl;
    for ( const auto& col : columns )
    {
      file << "      <column id=\"" << col->id( ) << "\">" << std::endl;

      for ( const auto& minicol : col->miniColumns( ))
      {
        file << "        <minicolumn id=\"" << minicol->id( )
             << "\">" << std::endl;

        for ( const auto& neuron : minicol->neurons( ))
        {
          file << "          <neuron gid=\"" << neuron->gid( ) << "\" "
               << "layer=\"" << neuron->layer( ) <<  "\" "
               << "morphologicalType=\""
               << morphologicalTypeToString( neuron->morphologicalType( ))
               <<  "\" "
               << "functionalType=\""
               << functionalTypeToString( neuron->functionalType( ))
               << "\">" << std::endl;

          const auto& xform = neuron->transform( );
          file << "            <transform>" << std::endl;
          file << "              "
               << xform( 0, 0 ) << ", " << xform( 0, 1 ) << ", "
               << xform( 0, 2 ) << ", " << xform( 0, 3 ) << ", " << std::endl;
          file << "              "
               << xform( 1, 0 ) << ", " << xform( 1, 1 ) << ", "
               << xform( 1, 2 ) << ", " << xform( 1, 3 ) << ", " << std::endl;
          file << "              "
               << xform( 2, 0 ) << ", " << xform( 2, 1 ) << ", "
               << xform( 2, 2 ) << ", " << xform( 2, 3 ) << ", " << std::endl;
          file << "              "
               << xform( 3, 0 ) << ", " << xform( 3, 1 ) << ", "
               << xform( 3, 2 ) << ", " << xform( 3, 3 ) << std::endl;
          file << "            </transform>" << std::endl;

          file << "          </neuron>" << std::endl;
        }

        file << "        </minicolumn>" << std::endl;
      }

      file << "      </column>" << std::endl;
    }

    file << "    </columns>" << std::endl << std::endl;;

    file << "    <neuronmorphologies>" << std::endl;

    unsigned int counter = 0;
    SwcWriter swcWriter;
    for ( const auto& morphology : morphologies )
    {
      file << "      <neuronmorphology neurons=\"";

      for ( const auto& neuron : morphology.second->parentNeurons( ))
      {
        file << neuron->gid( );
        if ( &neuron != &morphology.second->parentNeurons( ).back( ))
          file << ",";
      }
      file << "\" swc=\"" << std::to_string( counter )
           << ".swc\"";
      if ( relativeToXmlMorphologyPath )
        file << "pathRelativeToXml=\"true\"";
      file << " />" << std::endl;
      // file << "      </neuronmorphology>" << std::endl;

      swcWriter.writeMorphology( std::to_string( counter++ ) +
                                 std::string( ".swc" ),
                                 morphology.second );
    }

    file << "    </neuronmorphologies>" << std::endl;

    file << "  </morphology>" << std::endl;
    file << "</scene>" << std::endl;

    return true;
  }

}; // namespace nsol
