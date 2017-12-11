/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Juan Guerrero Martín <juan.guerrero@urjc.es>
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
#include "Segmentation.h"

namespace nsol
{

Segmentation::Segmentation( void )
: _uuid( std::string( ) )
, _name( std::string( ) )
, _classification( std::string( ) )
, _skeleton( nullptr )
{
}

Segmentation::~Segmentation( void )
{
  delete _skeleton;
}

const std::string& Segmentation::getUuid( void ) const
{
  return _uuid;
}

void Segmentation::setUuid( const std::string& uuid )
{
  _uuid = uuid;
}

const std::string& Segmentation::getName( void ) const
{
  return _name;
}

void Segmentation::setName( const std::string& name )
{
  _name = name;
}

const std::string& Segmentation::getClassification( void ) const
{
  return _classification;
}

SegmentationClassification Segmentation::getClassificationAsEnum( void ) const
{
  SegmentationClassification classification;
  if( _classification.compare( "Axon" ) == 0 )
  {
    classification = SegmentationClassification::AXON;
  }
  else if( _classification.compare( "Dendrite" ) == 0 )
  {
    classification = SegmentationClassification::DENDRITE;
  }
  else
  {
    classification = SegmentationClassification::OTHER;
  }
  return classification;
}

void Segmentation::setClassification( const std::string& classification )
{
  _classification = classification;
}

SkeletonPtr Segmentation::getSkeleton( void ) const
{
  return _skeleton;
}

void Segmentation::setSkeleton( SkeletonPtr skeleton )
{
  _skeleton = skeleton;
}

void Segmentation::loadFromXML( const std::string& filename_ )
{
  // Feedback.
  std::cout << "Segmentation::loadFromXML = " << filename_ << std::endl;

  QString qFilename = QString::fromStdString( filename_ );

  QFile file( qFilename );
  if( !file.open( QFile::ReadOnly | QFile::Text ) )
  {
    throw std::runtime_error( "Cannot read segmentation XML." );
  }

  QXmlStreamReader reader( &file );

  if( reader.readNextStartElement( ) )
  {
    if( reader.name() == "Segmentation" )
    {
      QXmlStreamAttributes segmentationAttributes =
        reader.attributes( );
      setUuid( segmentationAttributes.value(
        QString( ), QString( "Uuid" ) ).toString( ).toStdString( ) );
      setName( segmentationAttributes.value(
        QString( ), QString( "Name" ) ).toString( ).toStdString( ) );
      setClassification( segmentationAttributes.value(
        QString( ), QString( "Classification" ) ).toString( ).toStdString( ) );

      while(reader.readNextStartElement())
      {
        /** Section: Skeleton. **/
        if(reader.name() == "Skeleton")
        {
          SkeletonPtr skeleton = new Skeleton( );

          while(reader.readNextStartElement())
          {
            /** Subsection: Strokes. **/
            if(reader.name() == "Strokes")
            {
              while(reader.readNextStartElement())
              {
                if(reader.name() == "Stroke")
                {
                  SkeletonStrokePtr stroke = new SkeletonStroke( );
                  QXmlStreamAttributes strokeAttributes =
                    reader.attributes( );
                  stroke->setId( strokeAttributes.value(
                    QString( ), QString( "Id" ) ).toString( ).toUInt( ) );
                  stroke->setName( strokeAttributes.value(
                    QString( ), QString( "Name" ) ).toString( ).toStdString( ) );
                  stroke->setColorHue( strokeAttributes.value(
                    QString( ), QString( "ColorHue" ) ).toString( ).toUInt( ) );
                  unsigned int type = strokeAttributes.value(
                    QString( ), QString( "Type" ) ).toString( ).toUInt( );
                  SkeletonStrokeType strokeType =
                    static_cast< SkeletonStrokeType >( type );
                  stroke->setType( strokeType );
                  QString qUseMeasure = strokeAttributes.value(
                    QString( ), QString( "UseMeasure" ) ).toString( );
                  stroke->setUseMeasure( qStringToBool( qUseMeasure ) );
                  skeleton->addStroke( stroke->getId( ), stroke );
                } // Stroke.
                reader.skipCurrentElement();
              } // while Stroke.
            } // Strokes.
            /** Subsection: Edges. **/
            else if(reader.name() == "Edges")
            {
              while(reader.readNextStartElement())
              {
                if(reader.name() == "Edge")
                {
                  SkeletonEdgePtr edge = new SkeletonEdge( );
                  QXmlStreamAttributes edgeAttributes =
                    reader.attributes( );
                  edge->setId( edgeAttributes.value(
                    QString( ), QString( "Id" ) ).toString( ).toUInt( ) );
                  edge->setStrokeId( edgeAttributes.value(
                    QString( ), QString( "StrokeId" ) ).toString( ).toUInt( ) );
                  edge->setStrokeNumber( edgeAttributes.value(
                    QString( ), QString( "StrokeNumber" ) ).toString( ).toUInt( ) );
                  skeleton->addEdge( edge->getId( ), edge );
                } // Edge.
                reader.skipCurrentElement();
              } // while Edge.
            } // Edges.
            /** Subsection: Nodes. **/
            else if(reader.name() == "Nodes")
            {
              while(reader.readNextStartElement())
              {
                if(reader.name() == "Node")
                {
                  SkeletonNodePtr node = new SkeletonNode( );
                  QXmlStreamAttributes nodeAttributes =
                    reader.attributes( );
                  node->setId( nodeAttributes.value(
                    QString( ), QString( "Id" ) ).toString( ).toUInt( ) );

                  reader.readNextStartElement();
                  if(reader.name() == "Position")
                  {
                    QXmlStreamAttributes positionAttributes =
                      reader.attributes( );
                    std::vector< double > position =
                      node->getPosition( );
                    position.push_back( positionAttributes.value(
                      QString( ), QString( "x" ) ).toString( ).toDouble( ) );
                    position.push_back( positionAttributes.value(
                      QString( ), QString( "y" ) ).toString( ).toDouble( ) );
                    position.push_back( positionAttributes.value(
                      QString( ), QString( "z" ) ).toString( ).toDouble( ) );
                    node->setPosition( position );
                  }
                  reader.skipCurrentElement();

                  reader.readNextStartElement();
                  if(reader.name() == "Connections")
                  {
                    while(reader.readNextStartElement())
                    {
                      if(reader.name() == "Connection")
                      {
                        QXmlStreamAttributes connectionAttributes =
                          reader.attributes( );
                        unsigned int nodeId = connectionAttributes.value(
                          QString( ), QString( "NodeId" ) ).toString( ).toUInt( );
                        unsigned int edgeId = connectionAttributes.value(
                          QString( ), QString( "EdgeId" ) ).toString( ).toUInt( );
                        node->addConnection( nodeId, edgeId );
                      } // Connection.
                      reader.skipCurrentElement();
                    } // while Connection.
                  }
                  reader.skipCurrentElement();
                  skeleton->addNode( node->getId( ), node );
                } // Node.
              } // while Node.
            } // Nodes.
            else
            {
              reader.skipCurrentElement();
            }
          }
          setSkeleton( skeleton );
        } // Skeleton.
        /** Section: Mesh. **/
        /**
        else if(reader.name() == "Mesh")
        {
          MeshPtr mesh = new Mesh( );
          while( reader.readNextStartElement( ) )
          {
            if(reader.name() == "OBJ")
            {
              QString qtObjAsString = reader.readElementText();
              std::string objAsString = qtObjAsString.toStdString();
              mesh->loadFromOBJAsString( objAsString );
              // If there are no normals, they should be computed.
              mesh->computeNormals( );
            } // OBJ.
            else
            {
              reader.skipCurrentElement();
            }
          } // while OBJ.
          setMesh( mesh );
        } // Mesh.
        **/
        // else if(reader.name() == "Volumetric")
        // {
        // }
        else
        {
          reader.skipCurrentElement();
        }
      }
    } // Segmentation.
  }
}

void Segmentation::saveAsXML( const std::string& filename_ )
{
  // Creating XML.
  QByteArray xml;
  QXmlStreamWriter stream( &xml );
  stream.setAutoFormatting( true );
  stream.writeStartDocument( );

  stream.writeStartElement( "Segmentation" );
  stream.writeAttribute( "Uuid", QString::fromStdString( _uuid ) );
  stream.writeAttribute( "Name", QString::fromStdString( _name ) );
  stream.writeAttribute( "Classification", QString::fromStdString( _classification ) );

  /** Section: Skeleton. **/
  if( _skeleton != nullptr  )
  {
    stream.writeStartElement( "Skeleton" );

    /** Subsection: Strokes. **/
    SkeletonStrokeMap strokes = _skeleton->getStrokes( );
    stream.writeStartElement( "Strokes" );
    for( const auto& mapElement : strokes )
    {
      stream.writeStartElement("Stroke");
      stream.writeAttribute("Id", QString::number( mapElement.first ));
      SkeletonStrokePtr stroke = mapElement.second;
      stream.writeAttribute("Name", QString::fromStdString( stroke->getName( ) ));
      stream.writeAttribute("ColorHue", QString::number( stroke->getColorHue( ) ));
      unsigned int type = static_cast< unsigned int >( stroke->getType( ) );
      stream.writeAttribute("Type", QString::number( type ));
      stream.writeAttribute("UseMeasure", boolToQString( stroke->isUseMeasure( ) ));
      stream.writeEndElement(); // Stroke
    }
    stream.writeEndElement( ); // Strokes


    /** Subsection: Edges. **/
    SkeletonEdgeMap edges = _skeleton->getEdges( );
    stream.writeStartElement( "Edges" );
    for( const auto& mapElement : edges )
    {
      stream.writeStartElement("Edge");
      stream.writeAttribute("Id", QString::number( mapElement.first ));
      SkeletonEdgePtr edge = mapElement.second;
      stream.writeAttribute("StrokeId", QString::number( edge->getStrokeId( ) ));
      stream.writeAttribute("StrokeNumber", QString::number( edge->getStrokeNumber( ) ));
      stream.writeEndElement(); // Edge
    }
    stream.writeEndElement( ); // Edges

    /** Subsection: Nodes. **/
    SkeletonNodeMap nodes = _skeleton->getNodes( );
    stream.writeStartElement( "Nodes" );
    for( const auto& mapElement : nodes )
    {
      stream.writeStartElement( "Node" );
      stream.writeAttribute( "Id", QString::number( mapElement.first ) );

      SkeletonNodePtr node = mapElement.second;
      stream.writeStartElement( "Position" );
      stream.writeAttribute( "x", QString::number( node->getPosition( ).at( 0 ) ) );
      stream.writeAttribute( "y", QString::number( node->getPosition( ).at( 1 ) ) );
      stream.writeAttribute( "z", QString::number( node->getPosition( ).at( 2 ) ) );
      stream.writeEndElement( ); // Position


      stream.writeStartElement( "Connections" );
      for( const auto& connectionsElement : node->getConnections( ) )
      {
        stream.writeStartElement("Connection");
        stream.writeAttribute("NodeId", QString::number( connectionsElement.first ));
        stream.writeAttribute("EdgeId", QString::number( connectionsElement.second ));
        stream.writeEndElement(); // Connection
      }
      stream.writeEndElement( ); // Connections

      stream.writeEndElement( ); // Node
    }
    stream.writeEndElement( ); // Nodes

    stream.writeEndElement( ); // Skeleton
  }

  /** Section: Mesh. **/
  /**
  if( _mesh != nullptr )
  {
    stream.writeStartElement( "Mesh" );
    stream.writeStartElement( "OBJ" );
    QString objAsQString = QString::fromStdString( _mesh->getOBJAsString( ) );
    stream.writeCharacters( objAsQString );
    stream.writeEndElement( ); // OBJ
    stream.writeEndElement( ); // Mesh
  }
  **/

  /** Section: Volumetric. **/
  // Not working with volumetric data.

  stream.writeEndElement(); // Segmentation

  stream.writeEndDocument();
  QString xmlContent( xml );

  // Writing XML to the file.
  remove( filename_.c_str( ) );
  std::ofstream ofs;
  ofs.exceptions( std::ofstream::failbit | std::ofstream::badbit );
  try
  {
    ofs.open( filename_.c_str( ), std::ofstream::out | std::ofstream::app );
  }
  catch( std::system_error& e )
  {
    std::cerr << e.code( ).message( ) << std::endl;
    exit( EXIT_FAILURE );
  }
  ofs << xmlContent.toStdString( ).c_str( );
  ofs.close( );
  std::cout << "Saved as " << filename_ << std::endl;
}

std::vector< std::string > Segmentation::split( const std::string& str, const std::string& delimiter )
{
  std::string s = str;
  std::vector< std::string > v;
  size_t pos = 0;
  std::string token;
  while ( ( pos = s.find( delimiter ) ) != std::string::npos )
  {
    token = s.substr( 0, pos );
    v.push_back( token );
    s.erase( 0, pos + delimiter.length( ) );
  }
  if (s != "")
  {
    v.push_back( s );
  }
  return v;
}

QString Segmentation::boolToQString( bool inputBool )
{
  return ( inputBool ) ? QString( "true" ) :  QString( "false" );
}

bool Segmentation::qStringToBool( QString inputQString )
{
  if( inputQString == "true" ) return true;
  if( inputQString == "false" ) return false;
  return false;
}

} // namespace nsol

