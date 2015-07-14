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

#include <QXmlStreamReader>

#ifdef NSOL_WITH_QT5CORE
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
      NeuronMorphologyPtr neuronMorphology = swcReader.readFile( swc );

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
          miniColumn = new MINICOLUMN( miniColumnId_ );
          column->addMiniColumn( miniColumn );
        }

        NEURON* neuron = new NEURON( neuronMorphology, layer_, gid_, transform_,
                    nullptr, type_ );
        neuron->miniColumn( miniColumn );
        miniColumn->addNeuron( neuron );
      }

    }

#ifdef NSOL_WITH_QT5CORE
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

      std::map< unsigned int, ColumnPtr > columnsMap;
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

		  QXmlStreamAttributes attributes = xml.attributes( );
		  if( attributes.hasAttribute( "id" ))
		  {
		    unsigned int id = attributes.value( "id" ).toUInt( );
		    ColumnPtr column = ( ColumnPtr )new COLUMN( id );
		    _columns.push_back( column );
		    columnsMap.insert(
			std::pair<unsigned int, ColumnPtr>( id, column ));
		  }
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
		  QXmlStreamAttributes attributes = xml.attributes( );
		  if( attributes.hasAttribute( "column" ))
		  {
		    unsigned int columnId = attributes.value( "column" ).toUInt( );
		    ColumnPtr column = ( ColumnPtr )columnsMap.find( columnId );
		    if ( attributes.hasAttribute( "id" ) &&
			 column != (ColumnPtr)columnsMap.end( ))
		    {
			unsigned int id = attributes.value( "id" ).toUInt( );
			MiniColumnPtr miniColumn = ( MiniColumnPtr )new MINICOLUMN( column );
			column->addMiniColumn( miniColumn );
		    }
		  }
		}
	      }
	    }
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

#endif
  protected:

    Columns _columns;

  }; // class DataSet

} // namespace nsol

#endif // __NSOL_DATASET__
