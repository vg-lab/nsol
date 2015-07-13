#include <set>
#include "DataSet.h"
#include "error.h"

namespace nsol
{

  DataSet::DataSet( void )
  {

  }

  void DataSet::close( void )
  {
    std::set< NeuronMorphologyPtr > morphologies;

    NSOL_FOREACH( col, _columns )
    {
      NSOL_FOREACH( miniCol, ( *col )->miniColumns( ))
      {
        NSOL_FOREACH( neuron, ( *miniCol )->neurons( ))
        {
          morphologies.insert(( *neuron )->morphology( ));
          delete *neuron;
        }
        delete *miniCol;
      }
      delete *col;
    }

    std::set< NodePtr > nodes;

    NSOL_FOREACH( morphology, morphologies )
    {
      NSOL_FOREACH( neurite, ( *morphology )->neurites( ))
      {
        Sections sections = ( *neurite )->sections( );
        NSOL_FOREACH( section, sections )
        {
          SegmentPtr segment = ( *section )->firstSegment( );
          while ( segment )
          {
            SegmentPtr tmpSegment = segment;
            segment = segment->next( );
            nodes.insert( tmpSegment->begin( ));
            nodes.insert( tmpSegment->end( ));
            delete tmpSegment;
          }
          delete *section;
        }
        delete *neurite;
      }
      delete ( *morphology )->soma( );
      delete *morphology;
    }


    NSOL_FOREACH( node, nodes )
      delete *node;

    _columns.clear( );

    return;
  }


  Columns& DataSet::columns( void )
  {
    return _columns;
  }


#ifdef NSOL_WITH_QT5CORE
  void DataSet::loadScene( const std::string& xmlSceneFile )
  {
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

    if ( xml.name( ) == "scene" )
    {
      QXmlStreamAttributes attributes = xml.attributes( );

      if( attributes.hasAttribute( "version" ))
        version = attributes.value( "version" ).toString( ).toStdString( );
      else
        NSOL_THROW( "No version number present" );
    }
    else
      NSOL_THROW(
        "Expected <scene> root element" );

    while( !xml.atEnd( ) &&  !xml.hasError( ))
    {
      xml.readNext( );

      if ( xml.atEnd( ))
        continue;

      if ( xml.tokenType( ) != QXmlStreamReader::StartElement )
        continue;

      if ( xml.name( ) == "morphology" )
      {

        std::cout << "morphology" << std::endl;

        while( !xml.atEnd( ) &&  !xml.hasError( ))
        {
          xml.readNext( );

          if ( xml.atEnd( ) ||
               xml.tokenType( ) != QXmlStreamReader::StartElement )
            continue;

          if ( !xml.atEnd( ) && xml.name( ) == "columns" )
          {
            std::cout << "columns" << std::endl;

            while( !xml.atEnd( ) && !xml.hasError( ) &&
                   !( xml.name( ) == "columns" &&
                      xml.tokenType( ) == QXmlStreamReader::EndElement ))
            {
              xml.readNext( );
              if ( xml.atEnd( ) ||
                   xml.tokenType( ) != QXmlStreamReader::StartElement )
                continue;

              if ( !xml.atEnd( ) && xml.name( ) == "column" )
              {
                std::cout << "Create column";
                QXmlStreamAttributes attributes = xml.attributes( );
                if( attributes.hasAttribute( "id" ))
                  std::cout << " "
                            << attributes.value( "id" ).toString( ).toStdString( );
                std::cout << std::endl;
              }
            }
          }

          if ( !xml.atEnd( ) && xml.name( ) == "minicolumns" )
          {
            std::cout << "minicolumns" << std::endl;

            while( !xml.atEnd( ) &&  !xml.hasError( ) &&
                   !( xml.name( ) == "minicolumns" &&
                      xml.tokenType( ) == QXmlStreamReader::EndElement ))
            {
              xml.readNext( );
              if ( xml.atEnd( ) ||
                   xml.tokenType( ) != QXmlStreamReader::StartElement )
                continue;

              if ( !xml.atEnd( ) && xml.name( ) == "minicolumn" )
              {
                std::cout << "Create minicolumn";
                QXmlStreamAttributes attributes = xml.attributes( );
                if( attributes.hasAttribute( "id" ))
                  std::cout << " "
                            << attributes.value( "id" ).toString( ).toStdString( );
                if( attributes.hasAttribute( "column" ))
                  std::cout << " column: "
                            << attributes.value( "column" ).toString( ).toStdString( );

                std::cout << std::endl;

              }
            }
          }

//          std::cout << xml.name( ).toString( ).toStdString( ) << std::endl;
          if ( !xml.atEnd( ) && xml.name( ) == "neurons" )
          {
            std::cout << "neurons" << std::endl;

            while( !xml.atEnd( ) &&  !xml.hasError( ) &&
                   !( xml.name( ) == "neurons" &&
                      xml.tokenType( ) == QXmlStreamReader::EndElement ))
            {
              xml.readNext( );
              if ( xml.atEnd( ) ||
                   xml.tokenType( ) != QXmlStreamReader::StartElement )
                continue;

              if ( !xml.atEnd( ) && xml.name( ) == "neuron" )
              {
                std::cout << "Create neuron";
                QXmlStreamAttributes attributes = xml.attributes( );
                if( attributes.hasAttribute( "gid" ))
                  std::cout << " gid: "
                            << attributes.value( "gid" ).toString( ).toStdString( );
                if( attributes.hasAttribute( "minicolumn" ))
                  std::cout << " minicolumn: "
                            << attributes.value( "minicolumn" ).toString( ).toStdString( );
                std::cout << std::endl;

              }
            }
          }

          if ( !xml.atEnd( ) && xml.name( ) == "neuronmorphologies" )
          {
            std::cout << "neuronmorphologies" << std::endl;

            while( !xml.atEnd( ) &&  !xml.hasError( ))
            {
              xml.readNext( );
              if ( xml.atEnd( ) ||
                   xml.tokenType( ) != QXmlStreamReader::StartElement )
                continue;

              if ( !xml.atEnd( ) && xml.name( ) == "neuronmorphology" )
              {
                std::cout << "Create neuron morphology";
                QXmlStreamAttributes attributes = xml.attributes( );
                if( attributes.hasAttribute( "neurons" ))
                  std::cout << " neurons: "
                            << attributes.value( "neurons" ).toString( ).toStdString( );
                if( attributes.hasAttribute( "swc" ))
                  std::cout << " swc: "
                            << attributes.value( "swc" ).toString( ).toStdString( );
                std::cout << std::endl;


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
  }

#else
  void DataSet::loadScene( const std::string&  )
  {
    NSOL_THROW( "No QT found needed to read XML files" );
  }
#endif

} // namespace nsol
