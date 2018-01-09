/*
 * Copyright (c) 2017 GMRV/URJC.
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
#include "EspINASkeletonReader.h"

namespace nsol
{

  VectorsReaderInput* EspINASkeletonReader::read( const std::string& fileName )
  {
    VectorsReaderInput* vectorsReaderInput =
      new VectorsReaderInput( );

    SkeletonPtr skeleton =
      new Skeleton( );

    try
    {
      skeleton->loadFromJSON( fileName );
    }
    catch( const std::runtime_error& e  )
    {
      Log::log( std::string( e.what() ), LOG_LEVEL_WARNING );
      return vectorsReaderInput;
    }

    // Feedback.
    skeleton->print();

    SkeletonNodeMap nodes =
      skeleton->getNodes( );

    // First pass: getting the nodes belonging to the shaft.
    SkeletonNodes filteredNodes;
    unsigned int vectorsReaderIndex = 0;
    std::map< unsigned int, unsigned int >
      indexCorrespondence;
    for( const auto& nodeMapElem : nodes )
    {
      SkeletonNodePtr node =
        nodeMapElem.second;

      // We are only interested in nodes belonging to the neurite shaft.
      std::map< unsigned int,
                unsigned int > connections =
        node->getConnections( );

      bool shaftNode = false;
      for( const auto& connection : connections )
      {
        unsigned int edgeId = connection.second;
        SkeletonEdgePtr edge = skeleton->getEdges( ).at( edgeId );
        unsigned int strokeId = edge->getStrokeId( );
        SkeletonStrokePtr stroke = skeleton->getStrokes( ).at( strokeId );
        if( stroke->getName( ).compare( "Shaft" ) == 0 )
        {
          shaftNode = true;
          break;
        }
      }

      if( shaftNode )
      {
        filteredNodes.push_back( node );
        indexCorrespondence.insert(
          std::pair< unsigned int, unsigned int >
          ( node->getId( ), vectorsReaderIndex++ ) );
      }
    }

    // Second pass: inserting these nodes into VectorsReaderInput.
    std::unordered_set< Segment*,
                        std::hash< Segment* >,
                        SegmentPtrEqual > segmentSet;
    for( SkeletonNodePtr filteredNode : filteredNodes )
    {
      std::map< unsigned int,
                unsigned int > connections =
        filteredNode->getConnections( );

      // Point = ( X Y Z Radius ). Radius is considered 1.0f.
      vectorsReaderInput->points.push_back( filteredNode->getPosition( ).at( 0 ) );
      vectorsReaderInput->points.push_back( filteredNode->getPosition( ).at( 1 ) );
      vectorsReaderInput->points.push_back( filteredNode->getPosition( ).at( 2 ) );
      vectorsReaderInput->points.push_back( 1.0f );

      for( const auto& connection : connections )
      {
        unsigned int edgeId = connection.second;
        SkeletonEdgePtr edge = skeleton->getEdges( ).at( edgeId );
        unsigned int strokeId = edge->getStrokeId( );
        SkeletonStrokePtr stroke = skeleton->getStrokes( ).at( strokeId );
        if( stroke->getName( ).compare( "Shaft" ) == 0 )
        {
          Segment* segment =
            new Segment( indexCorrespondence[ filteredNode->getId( ) ],
                         indexCorrespondence[ connection.first ] );
          segmentSet.insert( segment );
        }
      }
    }

    for( Segment* segment : segmentSet )
    {
      vectorsReaderInput->segments.push_back( segment->a );
      vectorsReaderInput->segments.push_back( segment->b );
    }

    return vectorsReaderInput;
  }

}
