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
#ifndef __NSOL__XML_SCENE_READER__
#define __NSOL__XML_SCENE_READER__

#ifdef NSOL_USE_QT5CORE
#include <QStringList>
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QFileInfo>
#endif

#include "BrionReader.h"
#include "SwcReader.h"
#include <map>


namespace nsol
{

  /*!
    This class allows to read the structure morphologies of a given Xml file.
  */
  class XmlSceneReader
  {
  public:
    /**
     * Write structure and optinally morphologies to xml file.
     * @param fileName name of file to write to
     * @param columns container of columns to be written
     * @param morphologies morphologies to be written to SWC
     files and linked in the Xml
     * @return true if everything went ok
     */
    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
#ifdef NSOL_USE_QT5CORE
    static void loadXml(
      const std::string& xmlSceneFile,
      Columns& columns, NeuronsMap& neuronsMap,
      std::map< std::string, NeuronMorphologyPtr >& morphologies)
#else
    static void loadXml(
      const std::string& xmlSceneFile,
      Columns&, NeuronsMap&,
      std::map< std::string, NeuronMorphologyPtr >&)
#endif
    {

#ifdef NSOL_USE_QT5CORE

      QFile qFile ( xmlSceneFile.c_str( ));
      if ( ! qFile.exists( ))
        NSOL_THROW( "Scene file not found" );

      qFile.open( QIODevice::ReadOnly | QIODevice::Text );

      if ( ! qFile.isOpen( ))
        NSOL_THROW( "Scene file not readable" );

      QXmlStreamReader xml( & qFile );

      if ( xml.hasError( ) )
        NSOL_THROW( "Scene XML file has errors" );

      xml.readNextStartElement( );

      std::string version;

      // std::map< unsigned int, NeuronPtr > neuronsMap;


      if ( xml.name( ) == "scene" )
      {
        QXmlStreamAttributes attributes = xml.attributes( );

        if( attributes.hasAttribute( "version" ))
          version = attributes.value( "version" ).toString( ).toStdString( );
        else
          NSOL_THROW( "No version number present" );
      }
      else
        NSOL_THROW( "Expected <scene> root element" );

      while( !xml.atEnd( ) &&  !xml.hasError( ))
      {
        xml.readNext( );

        if ( xml.atEnd( ))
          continue;

        if ( xml.tokenType( ) != QXmlStreamReader::StartElement )
          continue;

        if ( xml.name( ) == "morphology" )
        {
          while( !xml.atEnd( ) &&  !xml.hasError( ))
          {
            xml.readNext( );

            if ( xml.atEnd( ) ||
                 xml.tokenType( ) != QXmlStreamReader::StartElement )
              continue;

            if ( !xml.atEnd( ) && xml.name( ) == "column" )
            {
              QXmlStreamAttributes attributes = xml.attributes( );
              if( attributes.hasAttribute( "id" ))
              {
                //Creating column
                unsigned int colId = attributes.value( "id" ).toUInt( );
                ColumnPtr column = ( ColumnPtr )new COLUMN( colId );
                columns.push_back( column );

                //Looking for minicolumns in column
                while( !xml.atEnd( ) && !xml.hasError( ) &&
                       !( xml.name( ) == "column" &&
                          xml.tokenType( ) == QXmlStreamReader::EndElement ))
                {
                  xml.readNext( );
                  if ( xml.atEnd( ) ||
                       xml.tokenType( ) != QXmlStreamReader::StartElement )
                    continue;

                  if ( !xml.atEnd( ) && xml.name( ) == "minicolumn" )
                  {
                    attributes = xml.attributes( );
                    if ( attributes.hasAttribute( "id" ) )
                    {
                      //Creating minicolumn
                      unsigned int miniColId =
                        attributes.value( "id" ).toUInt( );
                      MiniColumnPtr miniColumn =
                        ( MiniColumnPtr )new MINICOLUMN( column, miniColId );
                      column->addMiniColumn( miniColumn );

                      //Looking for neuronos in minicolumn
                      while( !xml.atEnd( ) && !xml.hasError( ) &&
                             !( xml.name( ) == "minicolumn" &&
                                xml.tokenType( ) ==
                                QXmlStreamReader::EndElement ))
                      {
                        xml.readNext( );
                        if ( xml.atEnd( ) ||
                             xml.tokenType( ) !=
                             QXmlStreamReader::StartElement )
                          continue;

                        if ( !xml.atEnd( ) && xml.name( ) == "neuron" )
                        {
                          attributes = xml.attributes( );
                          if ( attributes.hasAttribute( "gid" ))
                          {
                            //Creating neuron
                            unsigned int gid =
                              attributes.value( "gid" ).toUInt( );
                            unsigned int layer = 1;
                            nsol::Neuron::TMorphologicalType morphologicalType =
                              nsol::Neuron::UNDEFINED;
                            nsol::Neuron::TFunctionalType functionalType =
                              nsol::Neuron::UNDEFINED_FUNCTIONAL_TYPE;
                            Matrix4_4f transform = Matrix4_4fIdentity;

                            //GET Layer
                            if ( attributes.hasAttribute( "layer" ))
                              layer = attributes.value( "layer" ).toUInt( );

                            //GET Mophological Type
                            if ( attributes.hasAttribute(
                                   "morphologicalType" ))
                            {
                              std::string typeString(
                                attributes.value(
                                  "morphologicalType" ).toString(
                                    ).toStdString( ));
                              if ( typeString == "INTERNEURON" )
                              {
                                morphologicalType = nsol::Neuron::INTERNEURON;
                              }
                              else if( typeString == "PYRAMIDAL" )
                              {
                                morphologicalType = nsol::Neuron::PYRAMIDAL;
                              }
                              else
                              {
                                Log::log(
                                  std::string(
                                    "nsol warning (XmlSceneReader): " ) +
                                  std::string( "Neuron " ) +
                                  std::to_string( gid ) +
                                  std::string(
                                    " undefined morphological type." ),
                                  LOG_LEVEL_WARNING );
                              }
                            }

                            //GET Functional Type
                            if ( attributes.hasAttribute( "functionalType" ) )
                            {
                              std::string typeString(
                                attributes.value(
                                  "functionalType" ).toString(
                                    ).toStdString( ));

                              if ( typeString == "EXCITATORY" )
                              {
                                functionalType = nsol::Neuron::EXCITATORY;
                              }
                              else if( typeString == "INHIBITORY" )
                              {
                                functionalType = nsol::Neuron::INHIBITORY;
                              }
                              else
                              {
                                Log::log(
                                  std::string(
                                    "nsol warning (XmlSceneReader): " ) +
                                  std::string( "Neuron " ) +
                                  std::to_string( gid ) +
                                  std::string(
                                    " undefined functional type." ),
                                  LOG_LEVEL_WARNING );
                              }
                            }

                            // Looking for transform in neuron
                            while( !xml.atEnd( ) && !xml.hasError( ) &&
                                   !( xml.name( ) == "neuron" &&
                                      xml.tokenType( ) ==
                                      QXmlStreamReader::EndElement ))
                            {
                              xml.readNext( );
                              if ( xml.atEnd( ) ||
                                   xml.tokenType( ) !=
                                   QXmlStreamReader::StartElement )
                                continue;

                              if ( !xml.atEnd( ) && xml.name( ) == "transform" )
                              {
                                QStringList mL =
                                  xml.readElementText( ).remove(' ').
                                  remove('\n').remove('\t').split(",");
                                if ( mL.size( ) == 16 )
                                {
                                  for ( unsigned int i = 0; i < 4; i ++ )
                                    for ( unsigned int j = 0; j < 4; j ++ )
                                      transform( i, j ) =
                                        mL[ i * 4 + j].toFloat( );
                                }
                              }
                            }
                            NeuronPtr neuron = ( NeuronPtr )
                              new NEURON( nullptr, layer, gid,
                                          transform, miniColumn,
                                          morphologicalType,
                                          functionalType );
                            if ( neuron )
                            {
                              if ( neuronsMap.addNeuron( neuron ))
                              {
                                miniColumn->addNeuron( neuron );
                                neuronsMap.insert(
                                  std::pair< unsigned int, NeuronPtr >(
                                    gid, neuron ));
                              }
                              else
                                delete neuron;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }

            if ( !xml.atEnd( ) && xml.name( ) == "neuronmorphologies" )
            {
              while( !xml.atEnd( ) &&  !xml.hasError( ))
              {
                xml.readNext( );
                if ( xml.atEnd( ) ||
                     xml.tokenType( ) != QXmlStreamReader::StartElement )
                  continue;

                if ( !xml.atEnd( ) && xml.name( ) == "neuronmorphology" )
                {
                  QXmlStreamAttributes attributes = xml.attributes( );
                  if( attributes.hasAttribute( "neurons" ) &&
                      attributes.hasAttribute( "swc" ))
                  {
                    std::string swc =
                      attributes.value( "swc" ).toString( ).toStdString( );

                    QFileInfo checkFile( swc.c_str( ));
                    if ( !checkFile.exists( ) || !checkFile.isFile( ))
                    {
                      // If the file does not exist then prepend xml file path
                      QFileInfo xmlSceneFileInfo( xmlSceneFile.c_str( ));
                      swc = xmlSceneFileInfo.path(
                        ).toStdString( ) + std::string( "/" ) + swc;
                    }
                    NeuronMorphologyPtr neuronMorphology = nullptr;
                    if ( morphologies.find( swc ) == morphologies.end( ))
                    {
#ifdef NSOL_USE_BRION
                    BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                                          SOMA, NEURONMORPHOLOGY, NEURON,
                                          MINICOLUMN, COLUMN > brionReader;
                     neuronMorphology = brionReader.loadMorphology( swc );
#else
                     SwcReaderTemplated< NODE, SECTION, DENDRITE, AXON, SOMA,
                                         NEURONMORPHOLOGY, NEURON> swcReader;
                     neuronMorphology = swcReader.readMorphology( swc );
#endif
                      if ( neuronMorphology )
                        morphologies[ swc ] = neuronMorphology;
                    }
                    else
                    {
                      neuronMorphology = morphologies[ swc ];
                    }

                    if ( neuronMorphology )
                    {

                      QStringList neurons_ =
                        attributes.value("neurons").toString( ).split(',');
                      for ( const auto& n : neurons_ )
                      {
                        auto neuronFind = neuronsMap.find( n .toUInt( ));
                        if( neuronFind != neuronsMap.end( ))
                        {
                          NeuronPtr neuron = neuronFind->second;
                          neuron->morphology( neuronMorphology );
                          neuronMorphology->parentNeurons( ).push_back(
                            neuron );
                        }
                      }
                    }
                    else
                    {
                      Log::log(
                        std::string(
                          "nsol warning (XmlSceneReader): morphology " ) +
                        swc + std::string( " could not be readed" ),
                        LOG_LEVEL_WARNING );
                    }
                  } // if ( neuronMorphology )
                }
              }
            }
          }
        }
        else if ( xml.name( ) == "ciruit" )
        {
          //TODO
        }
        else
          NSOL_THROW( std::string( "Element <" ) +
                      xml.name( ).toString( ).toStdString( ) +
                      std::string( "> not expected" ) );
      }

#else // NSOL_USE_QT5CORE
      NSOL_THROW( std::string("Can't load ") + xmlSceneFile +
                  std::string( ". QT5CORE not supported" ));
#endif // NSOL_USE_QT5CORE

    }


  }; // class XmlSceneReader

} // namespace nsol

#endif // __NSOL__XML_SCENE_READER__
