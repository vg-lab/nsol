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
#ifdef NSOL_USE_HDF5

#ifndef __NSOL_VASCULATURE_READER__
#define __NSOL_VASCULATURE_READER__

#include "../Morphology.h"

#include "../NsolTypes.h"

#include <H5Cpp.h>
#include <stdexcept>
#include <iostream>
#include <string>

namespace nsol
{

#define VASCULATURE_READER_TEMPLATE_CLASSES   \
  class NODE,                                 \
    class SECTION,                            \
    class MORPHOLOGY

#define VASCULATURE_READER_TEMPLATE_CLASS_NAMES \
  NODE,                                         \
    SECTION,                                    \
    MORPHOLOGY

  template < VASCULATURE_READER_TEMPLATE_CLASSES >
  class VasculatureReaderTemplated
  {

  public:

    MorphologyPtr loadMorphology( const std::string& file_ );

  protected:

    void _groupSections( SectionPtr section_,
                         std::set< SectionPtr >& uniqueSections_ );
  };

  typedef VasculatureReaderTemplated<
    Node,
    Section,
    Morphology > VasculatureReader;

  template < VASCULATURE_READER_TEMPLATE_CLASSES >
  MorphologyPtr
  VasculatureReaderTemplated< VASCULATURE_READER_TEMPLATE_CLASS_NAMES>::
  loadMorphology( const std::string& file_ )
  {
    MorphologyPtr morpho = nullptr;
    H5::H5File file;
    try
    {
      file.openFile( file_, H5F_ACC_RDONLY );
    }
    catch ( const std::exception& exc )
    {
      throw( std::runtime_error( "Could not open morphology file " + file_
                                 + ": " + exc.what( )));
    }

    hsize_t dims[2];
    H5::DataSet dataset;

    dataset = file.openDataSet( "/points" );
    dataset.getSpace( ).getSimpleExtentDims( dims );
    Vec4fsPtr pointsData( new Vec4fs( dims[0] ));
    dataset.read( pointsData->data( ), H5::PredType::NATIVE_FLOAT );

    dataset = file.openDataSet("/edges" );
    dataset.getSpace( ).getSimpleExtentDims( dims );
    Vec3isPtr edgesData( new Vec3is( dims[0] ));
    dataset.read( edgesData->data( ), H5::PredType::NATIVE_INT );

    morpho = new MORPHOLOGY( );

    Nodes nodes;
    NodePtr node;
    unsigned int nodeId = 0;

    for ( const auto& point: *pointsData )
    {
      node = new NODE( Vec3f( point.x( ), point.y( ), point.z( )), nodeId,
                       point.w( ));
      nodes.push_back( node );
      ++nodeId;
    }

    pointsData->clear( );
    delete pointsData;

    std::vector< unsigned int > nodesOccurrences( nodes.size( ), 0 );

    for ( const auto& edge: *edgesData )
    {
      nodesOccurrences[ edge.x( )] = nodesOccurrences[ edge.x( )] + 1;
      nodesOccurrences[ edge.y( )] = nodesOccurrences[ edge.y( )] + 1;
    }

    Sections sections;
    SectionPtr section;
    int previousIDx = -1;
    int previousIDy = -1;

    for( const auto& edge: *edgesData )
    {
      int occuX = nodesOccurrences[ edge.x( )];
      int occuY = nodesOccurrences[ edge.y( )];
      if ( previousIDy == edge.x( ))
      {
        section->addForwardNode( nodes[ edge.y( )]);
        previousIDx = -1;
        if ( occuY < 2 || occuY > 2 )
          previousIDy = -1;
        else
          previousIDy = edge.y( );
      }
      else if ( previousIDx == edge.y( ))
      {
        section->addBackwardNode( nodes[ edge.x( )]);
        if ( occuY < 2 || occuY > 2 )
          previousIDx = -1;
        else
          previousIDx = edge.x( );
        previousIDy = -1;
      }
      else
      {
        section = new SECTION( );
        sections.push_back( section );
        section->addForwardNode( nodes[ edge.x( )]);
        section->addForwardNode( nodes[ edge.y( )]);
        if (( occuX < 2 || occuX > 2 ) && ( occuY < 2 || occuY > 2 ))
        {
          previousIDx = -1;
          previousIDy = -1;
        }
        else
        {
          previousIDx = edge.x( );
          previousIDy = edge.y( );
        }
      }
    }
    edgesData->clear( );
    delete edgesData;

    std::unordered_map< NodePtr, Sections > nodeSections;
    NodePtr currentNode;
    for ( auto currentSection: sections )
    {
      if ( currentSection->nodes( ).size( ) > 1 )
      {
        currentNode =  currentSection->nodes( ).front( );
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

    if ( file.getId( ))
      file.close( );

    return morpho;
  }

  template < VASCULATURE_READER_TEMPLATE_CLASSES >
  void VasculatureReaderTemplated< VASCULATURE_READER_TEMPLATE_CLASS_NAMES>::
  _groupSections( SectionPtr section_, std::set< SectionPtr >& uniqueSections_ )
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

#endif // NSOL_USE_HDF5
