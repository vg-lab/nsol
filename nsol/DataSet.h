/**
 * @file    DataSet.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_DATASET__
#define __NSOL_DATASET__

#include <nsol/api.h>
#include "error.h"
#include "NsolTypes.h"
#include "Neuron.h"
#include "Container/Columns.h"
#include "Reader/BBPSDKReader.h"
#include "Reader/SwcReader.h"

#ifdef NSOL_WITH_QT5CORE
#include <QStringList>
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <map>
#endif


namespace nsol
{

  class DataSet
  {
  public:
    DataSet( void );

#ifdef NSOL_WITH_BBPSDK

    template < class NODE = Node,
               class SEGMENT = Segment,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void openBlueConfig( const std::string& blueconfig,
                         const int loadFlags = MORPHOLOGY,
                         const std::string& targetLabel = std::string( "" ))
    {
      BBPSDKReaderTemplated< NODE, SEGMENT, SECTION, DENDRITE, AXON,
                             SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                             COLUMN > reader;
      reader.readFromBlueConfig( _columns,
                                 blueconfig,
                                 loadFlags,
                                 targetLabel );

      // NSOL_FOREACH( column, columnsMap )
      //   _columns.push_back( column->second );

    }
#endif

    NSOL_API
    void close( void );

    NSOL_API
    Columns& columns( void );

    template < class NODE = Node,
               class SEGMENT = Segment,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void addNeuron( const std::string& swc, const unsigned int gid_,
        const unsigned int columnId_ = 0, const unsigned int miniColumnId_ = 0,
        const unsigned int layer_ = 0,
        const Matrix4_4f transform_ = Matrix4_4f::IDENTITY,
        const Neuron::TNeuronType type_ = Neuron::PYRAMIDAL )
    {
      SwcReaderTemplated< NODE, SEGMENT, SECTION, DENDRITE, AXON, SOMA,
          NEURONMORPHOLOGY, NEURON > swcReader;
      NeuronMorphologyPtr neuronMorphology = swcReader.readMorphology( swc );

      if( neuronMorphology )
      {

        COLUMN* column = nullptr;
        NSOL_FOREACH( col, _columns )
        {
          if (( *col )->id( ) == columnId_ )
          {
            column = *col;
          }
        }
        if( !column )
        {
          column = new COLUMN( columnId_ );
          _columns.push_back( column );
        }

        MINICOLUMN* miniColumn = nullptr;
        NSOL_FOREACH( miniCol, column->miniColumns() )
        {
          if(( *miniCol )->id( ) == miniColumnId_ )
          {
            miniColumn = *miniCol;
          }
        }
        if( !miniColumn )
        {
          miniColumn = ( MiniColumnPtr )new MINICOLUMN( column, miniColumnId_ );
          column->addMiniColumn( miniColumn );
        }

        NEURON* neuron = new NEURON( neuronMorphology, layer_, gid_, transform_,
                    nullptr, type_ );
        neuron->miniColumn( miniColumn );
        miniColumn->addNeuron( neuron );
      }

    }


    template < class NODE = Node,
	       class SEGMENT = Segment,
	       class SECTION = Section,
	       class DENDRITE = Dendrite,
	       class AXON = Axon,
	       class SOMA = Soma,
	       class NEURONMORPHOLOGY = NeuronMorphology,
	       class NEURON = Neuron,
	       class MINICOLUMN = MiniColumn,
	       class COLUMN = Column >
    void loadScene( const std::string& xmlSceneFile )
    {
#ifdef NSOL_WITH_QT5CORE
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

      std::map< unsigned int, NeuronPtr > neuronsMap;


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
                _columns.push_back( column );

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
                      unsigned int miniColId = attributes.value( "id" ).toUInt( );
                      MiniColumnPtr miniColumn =
                          ( MiniColumnPtr )new MINICOLUMN( column, miniColId );
                      column->addMiniColumn( miniColumn );

                      //Looking for neuronos in minicolumn
                      while( !xml.atEnd( ) && !xml.hasError( ) &&
                             !( xml.name( ) == "minicolumn" &&
                             xml.tokenType( ) == QXmlStreamReader::EndElement ))
                      {
                        xml.readNext( );
                        if ( xml.atEnd( ) ||
                             xml.tokenType( ) != QXmlStreamReader::StartElement )
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
                            nsol::Neuron::TNeuronType type =
                                nsol::Neuron::UNDEFINED;
                            Matrix4_4f transform = Matrix4_4f::IDENTITY;

                            if ( attributes.hasAttribute( "layer" ))
                                layer = attributes.value( "layer" ).toUInt( );

                            if ( attributes.hasAttribute( "type" ) )
                            {
                              std::string typeString(
                                  attributes.value( "type" ).toString( ).toStdString( ));

                              if ( typeString == "INTERNEURON" )
                              {
                                type = nsol::Neuron::INTER;
                              }
                              else if( typeString == "PYRAMIDAL" )
                              {
                                type = nsol::Neuron::PYRAMIDAL;
                              }
                              else
                              {
                                NSOL_LOG( std::string( "Neuron " ) +
                                    std::to_string( gid ) +
                                    std::string( " undefined type." ));
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
                                      transform.at( i, j ) = mL[ i * 4 + j].toFloat( );
                                }
                              }
                            }
                            NeuronPtr neuron = ( NeuronPtr )
                                new NEURON( nullptr, layer, gid,
                                            transform, miniColumn,
                                            type );
                            miniColumn->addNeuron( neuron );
                            neuronsMap.insert(
                                std::pair< unsigned int, NeuronPtr>( gid,
                                                                     neuron ));
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
                      attributes.hasAttribute( "swc" ) )
                  {
                    std::string swc =
                        attributes.value( "swc" ).toString( ).toStdString( );

                    SwcReaderTemplated< NODE, SEGMENT, SECTION, DENDRITE, AXON,
                        SOMA, NEURONMORPHOLOGY, NEURON > swcReader;
                     NeuronMorphologyPtr neuronMorphology =
                         swcReader.readMorphology( swc );
                     if ( neuronMorphology )
                     {
                       QStringList neurons =
                           attributes.value("neurons").toString( ).split(',');
                       NSOL_FOREACH( n, neurons )
                       {
                         std::map<unsigned int, NeuronPtr>::iterator neuronFind =
                             neuronsMap.find(( *n ).toUInt( ));
                         if( neuronFind != neuronsMap.end( ))
                         {
                           NeuronPtr neuron = neuronFind->second;
                           neuron->morphology( neuronMorphology );
                         }
                       }
                     }

                  }
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
          NSOL_THROW ( std::string( "Element <" ) +
              xml.name( ).toString( ).toStdString( ) +
              std::string( "> not expected" ) );
      }
#else
      NSOL_THROW( std::string("Can't load ") + xmlSceneFile +
                  std::string( ". QT5CORE not supported" ));
#endif

    }


  protected:

    Columns _columns;

  }; // class DataSet

} // namespace nsol

#endif // __NSOL_DATASET__
