 /**
 * @brief
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#ifndef __NSOL_HDF5_READER__
#define __NSOL_HDF5_READER__

#include "../NGVMorphology.h"

#include "../NsolTypes.h"

#include <H5Cpp.h>

#include <iostream>
#include <string>
#include <stdexcept>


namespace nsol
{

#define HDF5_READER_TEMPLATE_CLASSES            \
  class NODE,                                   \
    class NGVSECTION,                           \
    class NGVMORPHOLOGY

#define HDF5_READER_TEMPLATE_CLASS_NAMES         \
  NODE,                                          \
    NGVSECTION,                                  \
    NGVMORPHOLOGY

  template < HDF5_READER_TEMPLATE_CLASSES >
  class HDF5ReaderTemplated
  {

  public:

    NGVMorphologyPtr loadHDF5File( const std::string& file_ );

  private:

    void _groupSections( NGVSectionPtr section,
                        std::set<NGVSectionPtr>& uniqueSections );
  };

  typedef HDF5ReaderTemplated<
    Node,
    NGVSection,
    NGVMorphology > HDF5Reader;


  template < HDF5_READER_TEMPLATE_CLASSES >
  NGVMorphologyPtr
  HDF5ReaderTemplated< HDF5_READER_TEMPLATE_CLASS_NAMES >::loadHDF5File(
    const std::string& file_ )
  {
    NGVMorphologyPtr ngvMorpho = nullptr;
    std::cout << "HDF5 Reader: Loading file: " << file_ << std::endl;
    H5::H5File file;
    try
    {
      file.openFile( file_, H5F_ACC_RDONLY );
    }
    catch ( const std::exception& exc)
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

    dataset = file.openDataSet( "/edges" );
    dataset.getSpace( ).getSimpleExtentDims( dims );
    Vec3isPtr edgesData( new Vec3is( dims[0]));
    dataset.read( edgesData->data( ), H5::PredType::NATIVE_INT );

    ngvMorpho = new NGVMORPHOLOGY( );

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

    std::vector<unsigned int> nodesOccurrences( nodes.size( ), 0 );

    for ( const auto edge: *edgesData )
    {
      nodesOccurrences[ edge.x( )] = nodesOccurrences[ edge.x( )] + 1;
      nodesOccurrences[ edge.y( )] = nodesOccurrences[ edge.y( )] + 1;
    }

    NGVSections sections;
    NGVSectionPtr section;
    int previousIDx = -1;
    int previousIDy = -1;
    for( const auto edge: *edgesData )
    {
      int occuX = nodesOccurrences[ edge.x( )];
      int occuY = nodesOccurrences[ edge.y( )];
      if ( previousIDy == edge.x( ))
      {
        section->addFrontNode( nodes[ edge.y( )]);
        previousIDx = -1;
        if ( occuY < 2 || occuY > 2 )
          previousIDy = -1;
        else
          previousIDy = edge.y( );
      }
      else if ( previousIDx == edge.y(  ))
      {
        section->addBackNode( nodes[ edge.x( )]);
        if ( occuY < 2 || occuY > 2 )
          previousIDx = -1;
        else
          previousIDx = edge.x( );
        previousIDy = -1;
      }
      else
      {
        section = new NGVSECTION( );
        sections.push_back( section );
        section->addFrontNode( nodes[ edge.x( )]);
        section->addFrontNode( nodes[ edge.y( )]);
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

    std::unordered_map< NodePtr, std::vector< NGVSectionPtr >> nodeSections;
    NodePtr actualNode;
    for ( auto actualSection: sections )
    {
      if (  actualSection->nodes( ).size( ) > 1 )
      {
        actualNode = (actualSection->nodes( ).at( 0 ));
        if ( nodeSections.find( actualNode ) != nodeSections.end( ))
        {
          for ( auto neighbourSection: nodeSections[actualNode] )
          {
            neighbourSection->addNeighbour( actualSection, actualNode );
            actualSection->addNeighbour( neighbourSection, actualNode );
          }
          nodeSections[actualNode].push_back( actualSection );
        }
        else
        {
          std::vector< NGVSectionPtr >* neighbors =
            new std::vector< NGVSectionPtr >( );
          nodeSections[actualNode] = *neighbors;
          nodeSections[actualNode].push_back( actualSection );
        }

        actualNode = (actualSection->nodes( ).at( actualSection->nodes( ).size( ) - 1 ));
        if ( nodeSections.find( actualNode ) != nodeSections.end( ))
        {
          for ( auto neighbourSection: nodeSections[actualNode] )
          {
            neighbourSection->addNeighbour( actualSection, actualNode );
            actualSection->addNeighbour( neighbourSection, actualNode );
          }
          nodeSections[actualNode].push_back( actualSection );
        }
        else
        {
          std::vector< NGVSectionPtr >* neighbors =
            new std::vector< NGVSectionPtr >( );
          nodeSections[actualNode] = *neighbors;
          nodeSections[actualNode].push_back( actualSection );
        }
      }
    }
    nodeSections.clear( );

    std::set<NGVSectionPtr> uniqueSections;
    std::vector< NGVSectionPtr > sectionsGrouped;
    for( auto actualSection: sections  )
    {
      if ( uniqueSections.find( actualSection ) == uniqueSections.end( ))
      {
        sectionsGrouped.push_back( actualSection );
        _groupSections( actualSection, uniqueSections );
      }
    }
    uniqueSections.clear( );

    ngvMorpho->sections( ) = sectionsGrouped;

    if ( file.getId( ))
      file.close( );

    return ngvMorpho;

  }


  template < HDF5_READER_TEMPLATE_CLASSES >
  void
  HDF5ReaderTemplated< HDF5_READER_TEMPLATE_CLASS_NAMES >::_groupSections(
    NGVSectionPtr section, std::set<NGVSectionPtr>& uniqueSections )
  {
    if ( uniqueSections.find( section ) == uniqueSections.end( ))
    {
      uniqueSections.insert( section );
      for ( auto neighbourSection: section->backwardNeighbors( ))
        _groupSections( neighbourSection, uniqueSections );
      for ( auto neighbourSection: section->forwardNeighbors( ))
        _groupSections( neighbourSection, uniqueSections );
    }
  }

}

#endif // __NSOL_HDF5_READER__
