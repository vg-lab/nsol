/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
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
#ifndef __NSOL_VECTORS_READER__
#define __NSOL_VECTORS_READER__

#include "../Morphology.h"

#include "../NsolTypes.h"


namespace nsol
{

#define VECTORS_READER_TEMPLATE_CLASSES   \
  class NODE,                                 \
    class SECTION,                            \
    class MORPHOLOGY

#define VECTORS_READER_TEMPLATE_CLASS_NAMES \
  NODE,                                         \
    SECTION,                                    \
    MORPHOLOGY

  template < VECTORS_READER_TEMPLATE_CLASSES >
  class VectorsReaderTemplated
  {

  public:

    /**
     * Creates a generic morphology using a vector of points and segments.
     * @param points_ each point or node is represented by four floats
     * (position {x,y,z} and radius).
     * @param segments_ each segment is represented by two unsigned integers
     * (indices of the two nodes belonging to the segment). Indices must have
     * values from 0 to (#points-1).
     * @return MorphologyPtr a generic morphology.
     */
    MorphologyPtr loadMorphology(
      const std::vector< float >& points_,
      const std::vector< unsigned int >& segments_ );

  protected:

    void _groupSections( const SectionPtr section_,
                         std::set< SectionPtr >& uniqueSections_ );
  };

  typedef VectorsReaderTemplated<
    Node,
    Section,
    Morphology > VectorsReader;

  template < VECTORS_READER_TEMPLATE_CLASSES >
  MorphologyPtr
  VectorsReaderTemplated< VECTORS_READER_TEMPLATE_CLASS_NAMES>::
  loadMorphology( const std::vector< float >& points_,
                  const std::vector< unsigned int >& segments_ )
  {
    MorphologyPtr morpho = nullptr;

    if ( points_.size( )%4 != 0 || segments_.size( )%2 != 0 )
      return morpho;

    morpho = new MORPHOLOGY( );

    Nodes nodes;
    NodePtr node;
    unsigned int nodeId = 0;

    for( size_t i = 0, len = points_.size( ) / 4;
         i < len; ++i )
    {
      size_t index = i*4;
      node = new NODE( Vec3f( points_[index], points_[index+1],
                              points_[index+2]), nodeId, points_[index+3] );
      nodes.push_back( node );
      ++nodeId;
    }

    std::vector< unsigned int > nodesOccurrences( nodes.size( ), 0 );

    for ( size_t i = 0, len = segments_.size( ) / 2;
          i < len; ++i )
    {
      size_t index = i*2;
      nodesOccurrences[ segments_[index]] =
        nodesOccurrences[ segments_[index]] + 1;
      nodesOccurrences[ segments_[index+1]] =
        nodesOccurrences[ segments_[index+1]] + 1;
    }

    Sections sections;
    SectionPtr section;
    int previousIDx = -1;
    int previousIDy = -1;

    for( size_t i = 0, len = segments_.size( ) / 2;
         i < len; ++i )
    {
      size_t index = i*2;
      int x = ( int )segments_[index];
      int y = ( int )segments_[index+1];
      int occuX = nodesOccurrences[ x ];
      int occuY = nodesOccurrences[ y ];
      if ( previousIDy == x )
      {
        section->addForwardNode( nodes[ y ]);
        previousIDx = -1;
        if ( occuY < 2 || occuY > 2 )
          previousIDy = -1;
        else
          previousIDy = y;
      }
      else if ( previousIDx == y )
      {
        section->addBackwardNode( nodes[ x ]);
        if ( occuY < 2 || occuY > 2 )
          previousIDx = -1;
        else
          previousIDx = x;
        previousIDy = -1;
      }
      else
      {
        section = new SECTION( );
        sections.push_back( section );
        section->addForwardNode( nodes[ x ]);
        section->addForwardNode( nodes[ y ]);
        if (( occuX < 2 || occuX > 2 ) && ( occuY < 2 || occuY > 2 ))
        {
          previousIDx = -1;
          previousIDy = -1;
        }
        else
        {
          previousIDx = x;
          previousIDy = y;
        }
      }
    }

    std::unordered_map< NodePtr, Sections > nodeSections;
    NodePtr currentNode;
    for ( auto currentSection: sections )
    {
      if ( currentSection->nodes( ).size( ) > 1 )
      {
        currentNode = currentSection->nodes( ).front( );
        auto nodeSectionsIt = nodeSections.find( currentNode );
        if ( nodeSectionsIt != nodeSections.end( ))
        {
          auto neighbourSections = nodeSectionsIt->second;
          for ( auto neighbourSection: neighbourSections )
          {
            neighbourSection->addNeighbour( currentSection, currentNode );
            currentSection->addNeighbour( neighbourSection, currentNode );
          }
          nodeSections[currentNode].push_back( currentSection );
        }
        else
        {
          Sections* neighbors = new Sections( );
          neighbors->push_back( currentSection );
          nodeSections[ currentNode ] = *neighbors;
        }

        currentNode = currentSection->nodes( ).back( );
        nodeSectionsIt = nodeSections.find( currentNode );
        if ( nodeSectionsIt != nodeSections.end( ))
        {
          auto neighbourSections = nodeSectionsIt->second;
          for ( auto neighbourSection: neighbourSections )
          {
            neighbourSection->addNeighbour( currentSection, currentNode );
            currentSection->addNeighbour( neighbourSection, currentNode );
          }
          nodeSections[currentNode].push_back( currentSection );
        }
        else
        {
          Sections* neighbors = new Sections( );
          neighbors->push_back( currentSection );
          nodeSections[ currentNode ] = *neighbors;
        }
      }
    }

    nodeSections.clear( );

    std::set< SectionPtr > uniqueSections;
    Sections sectionsGrouped;
    for ( auto currentSection: sections )
    {
      if ( uniqueSections.find( currentSection ) == uniqueSections.end( ))
      {
        sectionsGrouped.push_back( currentSection );
        _groupSections( currentSection, uniqueSections );
      }
    }
    uniqueSections.clear( );

    morpho->sections( ) = sectionsGrouped;

    return morpho;
  }

  template < VECTORS_READER_TEMPLATE_CLASSES >
  void VectorsReaderTemplated< VECTORS_READER_TEMPLATE_CLASS_NAMES>::
  _groupSections( const SectionPtr section_,
                  std::set< SectionPtr >& uniqueSections_ )
  {
    if ( uniqueSections_.find( section_ ) == uniqueSections_.end( ))
    {
      uniqueSections_.insert( section_ );
      for ( auto neighbourSection: section_->backwardNeighbors( ))
        _groupSections( neighbourSection, uniqueSections_ );
      for ( auto neighbourSection: section_->forwardNeighbors( ))
        _groupSections( neighbourSection, uniqueSections_ );
    }
  }

} // end namespace nsol

#endif
