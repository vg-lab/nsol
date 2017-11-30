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
#include "Skeleton.h"

namespace nsol
{

Skeleton::Skeleton( void )
{
}

Skeleton::~Skeleton( void )
{
}

const SkeletonNodeMap& Skeleton::getNodes( void ) const
{
  return _nodes;
}

void Skeleton::setNodes( const SkeletonNodeMap& nodes )
{
  _nodes = nodes;
}

void Skeleton::addNode( const unsigned int& nodeId,
                        SkeletonNodePtr nodePtr )
{
  _nodes.insert( std::pair< unsigned int, SkeletonNodePtr >
                 ( nodeId, nodePtr ) );
}

const SkeletonEdgeMap& Skeleton::getEdges( void ) const
{
  return _edges;
}

void Skeleton::setEdges( const SkeletonEdgeMap& edges )
{
  _edges = edges;
}

void Skeleton::addEdge( const unsigned int& edgeId,
                        SkeletonEdgePtr edgePtr )
{
  _edges.insert( std::pair< unsigned int, SkeletonEdgePtr >
                 ( edgeId, edgePtr ) );
}

const SkeletonStrokeMap& Skeleton::getStrokes( void ) const
{
  return _strokes;
}

void Skeleton::setStrokes( const SkeletonStrokeMap& strokes )
{
  _strokes = strokes;
}

void Skeleton::addStroke( const unsigned int& strokeId,
                          SkeletonStrokePtr strokePtr )
{
  _strokes.insert( std::pair< unsigned int, SkeletonStrokePtr >
                   ( strokeId, strokePtr ) );
}

void Skeleton::print( void )
{
  std::cout << "Skeleton." << std::endl;

  std::cout << "Strokes" << std::endl;
  for( const auto& mapElement : getStrokes( ) )
  {
    std::cout << "Stroke id: " << mapElement.first << std::endl;
    SkeletonStrokePtr stroke = mapElement.second;
    std::cout << "Stroke name: " << stroke->getName( ) << std::endl;
    std::cout << "Stroke color hue: " << stroke->getColorHue( ) << std::endl;
    std::cout << "Stroke type: ";
    switch( stroke->getType( ) )
    {
      case SkeletonStrokeType::SOLID :
      {
        std::cout << "solid";
      }
      break;
      case SkeletonStrokeType::DASHED :
      {
        std::cout << "dashed";
      }
      break;
      default : std::cout << "unknown";
    }
    std::cout << std::endl;
    std::cout << "Stroke use measure: "
              << boolToQString( stroke->isUseMeasure( ) ).toStdString( ) << std::endl;
    std::cout << std::endl;
  }

  std::cout << "Edges." << std::endl;
  for( const auto& mapElement : getEdges( ) )
  {
    std::cout << "Edge id: " << mapElement.first << std::endl;
    SkeletonEdgePtr edge = mapElement.second;
    std::cout << "Edge stroke id: " << edge->getStrokeId( ) << std::endl;
    std::cout << "Edge stroke number: " << edge->getStrokeNumber( ) << std::endl;
    std::cout << std::endl;
  }

  std::cout << "Nodes." << std::endl;
  for( const auto& mapElement : getNodes( ) )
  {
    std::cout << "Node id: " << mapElement.first << std::endl;
    SkeletonNodePtr node = mapElement.second;
    std::cout << "Node position: ("
              << node->getPosition( ).at( 0 ) << ","
              << node->getPosition( ).at( 1 ) << ","
              << node->getPosition( ).at( 2 ) << ")" << std::endl;
    std::cout << "Node connections: " << std::endl;
    std::cout << "< nodeId, edgeId >" << std::endl;
    for( const auto& connectionsElement : node->getConnections( ) )
    {
      std::cout << "< " << connectionsElement.first << ", "
                        << connectionsElement.second << " >" << std::endl;
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

QString Skeleton::boolToQString( bool inputBool )
{
  return ( inputBool ) ? QString( "true" ) :  QString( "false" );
}

} // namespace nsol
