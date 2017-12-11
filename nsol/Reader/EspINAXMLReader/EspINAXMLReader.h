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
#ifndef __NSOL_ESPINAXML_READER__
#define __NSOL_ESPINAXML_READER__

#include "Segmentation.h"
#include "../../Neuron.h"
/**
#include "../Stats/NodeCached.h"
#include "../Stats/NeuronMorphologySectionCachedStats.h"
#include "../Stats/DendriteCachedStats.h"
#include "../Stats/AxonCachedStats.h"
#include "../Stats/NeuronMorphologyCachedStats.h"
**/

// std.
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

namespace nsol
{

#define ESPINAXML_READER_TEMPLATE_CLASSES      \
  class NODE,                                  \
  class NEURONMORPHOLOGYSECTION,               \
  class DENDRITE,                              \
  class AXON,                                  \
  class SOMA,                                  \
  class NEURONMORPHOLOGY,                      \
  class NEURON

#define ESPINAXML_READER_TEMPLATE_CLASS_NAMES \
  NODE,                                       \
  NEURONMORPHOLOGYSECTION,                    \
  DENDRITE,                                   \
  AXON,                                       \
  SOMA,                                       \
  NEURONMORPHOLOGY,                           \
  NEURON


  template < ESPINAXML_READER_TEMPLATE_CLASSES >
  class EspINAXMLReaderTemplated
  {

    public:

    /**
     * Creates a new Neuron that contains the NeuronMorphology described in
     * EspINA XML file
     * Calls readMorphology( 1 )
     *
     * @param fileName path to XML file to read
     * @return pointer to the Neuron created; nullptr if failure on XML read
     */
    NeuronPtr readNeuron( const std::string& fileName );

    /**
     * Creates a NeuronMorphology and loads info described in EspINA XML file
     *
     * @param fileName path to XML file to read
     * @return pointer to the NeuronMorphology created; nullptr if failure on XML read
     */
    NeuronMorphologyPtr readMorphology( const std::string& fileName );


    protected:

    //! initId not necessary because we have only one neurite.
    //! nodes_ and reposition_ not needed because there is not soma.
    //! For branch and bifurcation counting use Neurite::computeBranchBifurcations.
    void _ReadNeurite( NeuritePtr neurite,
    				   SkeletonPtr skeleton );

    bool _NodeFoundInNodeCollection( Nodes nodes, NodePtr node );

    NodePtr _EspINASkeletonNodeToNSOLNode( SkeletonNodePtr skeletonNode );

  }; // class EspINAXMLReaderTemplated


  typedef EspINAXMLReaderTemplated< Node,
    NeuronMorphologySection,
    Dendrite,
    Axon,
    Soma,
    NeuronMorphology,
    Neuron > EspINAXMLReader;

  /**
  typedef EspINAXMLReaderTemplated< Node,
    NeuronMorphologySectionStats,
    DendriteStats,
    AxonStats,
    SomaStats,
    NeuronMorphologyStats,
    Neuron > SwcReaderStats;

  typedef EspINAXMLReaderTemplated< NodeCached,
    NeuronMorphologySectionCachedStats,
    DendriteCachedStats,
    AxonCachedStats,
    SomaStats,
    NeuronMorphologyCachedStats,
    Neuron > SwcReaderCachedStats;
    **/

  //////////////////////////////////////////////////////////////////
  //
  // Implementation of methods for EspINAXMLTemplated
  //
  //////////////////////////////////////////////////////////////////

  template < ESPINAXML_READER_TEMPLATE_CLASSES >
  NeuronPtr
  EspINAXMLReaderTemplated< ESPINAXML_READER_TEMPLATE_CLASS_NAMES >::readNeuron(
    const std::string& fileName )
  {
    NeuronMorphologyPtr nm = this->readMorphology( fileName );

    if ( nm )
    {
      NeuronPtr neuron( new NEURON( nm ) );
      nm->addParentNeuron( neuron );
      return neuron;
    }
    else
      return nullptr;
  }

  template < ESPINAXML_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  EspINAXMLReaderTemplated< ESPINAXML_READER_TEMPLATE_CLASS_NAMES >::readMorphology(
    const std::string& fileName )
  {

	SegmentationPtr segmentation =
	  new Segmentation( );

	try
	{
      segmentation->loadFromXML( fileName );
	}
    catch( const std::runtime_error& e  )
	{
      Log::log( std::string( e.what() ), LOG_LEVEL_WARNING );
      return nullptr;
    }

    NeuronMorphologyPtr neuronMorphology( new NEURONMORPHOLOGY( new SOMA ) );

    SegmentationClassification classification =
      segmentation->getClassificationAsEnum();

    switch( classification )
    {
      case SegmentationClassification::AXON :
      {
	    AxonPtr axonP = new AXON();
        neuronMorphology->addNeurite( axonP );
        axonP->morphology( neuronMorphology );
        _ReadNeurite( axonP, segmentation->getSkeleton( ) );
      }
      break;

      case SegmentationClassification::DENDRITE :
      {
    	// Does EspINA distinguish between basal and apical dendrites?
	    DendritePtr basalP = new DENDRITE( Dendrite::BASAL );
	    neuronMorphology->addNeurite( basalP );
	    basalP->morphology( neuronMorphology );
	    _ReadNeurite( basalP, segmentation->getSkeleton( ) );
      }
      break;

      case SegmentationClassification::OTHER :
      {
        Log::log( std::string( "This segmentation is not an axon nor a dendrite." ),
        		  LOG_LEVEL_WARNING );
        return nullptr;
      }
      break;

      default :
      {
        Log::log( std::string( "The segmentation category is not well formed." ),
        		  LOG_LEVEL_WARNING );
        return nullptr;
      }
    }

    return neuronMorphology;
  }

  template < ESPINAXML_READER_TEMPLATE_CLASSES > void
  EspINAXMLReaderTemplated< ESPINAXML_READER_TEMPLATE_CLASS_NAMES >::_ReadNeurite(
    NeuritePtr neurite,
    SkeletonPtr skeleton )
  {
    NeuronMorphologySectionPtr firstSection =
	  NeuronMorphologySectionPtr( new NEURONMORPHOLOGYSECTION );

	unsigned int sectionId = 1;
	firstSection->id( sectionId );
	firstSection->neurite( neurite );
	firstSection->parent( nullptr );

	SkeletonNodeMap skeletonNodes = skeleton->getNodes( );
	SkeletonNodeMap::iterator skeletonNodeIt = skeletonNodes.begin( );
	SkeletonNodePtr firstNode = skeletonNodeIt->second;

	//! Creates first Node in first Section.
	NodePtr nsolFirstNode =
	  _EspINASkeletonNodeToNSOLNode( firstNode );
	firstSection->addNode( nsolFirstNode );

	neurite->firstSection( firstSection );

	//! Auxiliary structure.
	std::map< unsigned int, NeuronMorphologySectionPtr > lastNodeIds;
	lastNodeIds.insert( std::pair< unsigned int, NeuronMorphologySectionPtr >
						( firstNode->getId( ), firstSection ) );

	//! Iterating over skeleton nodes.
	while( lastNodeIds.size( ) > 0 )
	{
	  for( const auto& lastNodeId : lastNodeIds )
	  {
	    SkeletonNodePtr currentNode =
		  skeletonNodes.at( lastNodeId.first );
	    unsigned int currentNodeId =
		  currentNode->getId( );

	    //! We are only interested in nodes belonging to the neurite shaft
		std::map< unsigned int,
		     	  unsigned int > connections =
	      currentNode->getConnections( );

	    std::map< unsigned int,
		     	  unsigned int > filteredConnections;

		for( const auto& connection : connections )
		{
	      //! You can comment this and use all nodes (defined by neuroscientists).
		  /**/
		  unsigned int edgeId = connection.second;
		  SkeletonEdgePtr edge = skeleton->getEdges( ).at( edgeId );
		  unsigned int strokeId = edge->getStrokeId( );
		  SkeletonStrokePtr stroke = skeleton->getStrokes( ).at( strokeId );
		  if( stroke->getName( ).compare( "Shaft" ) == 0 )
		  {
            /**/
			filteredConnections.insert(
			  std::pair< unsigned int, unsigned int >
			  ( connection.first, connection.second ) );
		    //! You can comment this and use all nodes (defined by neuroscientists).
		    /**/
		  }
		  /**/
	    }

		unsigned int connectionCounter = filteredConnections.size( );

		NeuronMorphologySectionPtr currentSection =
		  lastNodeIds.at( currentNodeId );

		//! Node not belonging to neurite shaft
		if( connectionCounter == 0 )
		{
		  std::cerr << "Node not belonging to neurite shaft." << std::endl;
		  exit(-1);
	    }
		//! Initial or leaf node
		else if( connectionCounter == 1 )
		{
		  auto onlyConnection = filteredConnections.begin( );
		  unsigned int connectedNodeId = onlyConnection->first;
		  SkeletonNodePtr connectedNode =
		    skeleton->getNodes( ).at( connectedNodeId );

		  //! Initial node
		  if( currentNodeId == firstNode->getId( ) )
		  {
		    NodePtr nsolConnectedNode =
			  _EspINASkeletonNodeToNSOLNode( connectedNode );
		    currentSection->addNode( nsolConnectedNode );
			lastNodeIds.erase( currentNodeId );
			lastNodeIds.insert( std::pair< unsigned int, NeuronMorphologySectionPtr >
								( connectedNodeId, currentSection ) );
		  }
		  //! Leaf node
		  else
		  {
		    //! Actually erasing, no replacing.
			lastNodeIds.erase( currentNodeId );
	      }
		}
		//! Transition node
		else if( connectionCounter == 2 )
		{
		  for( const auto& connection : filteredConnections )
		  {
		    unsigned int connectedNodeId = connection.first;
			SkeletonNodePtr connectedNode =
			  skeleton->getNodes( ).at( connectedNodeId );

			NodePtr nsolConnectedNode =
			  _EspINASkeletonNodeToNSOLNode( connectedNode );

			Nodes sectionNodes = currentSection->nodes( );
			//! If not found.
			if( !_NodeFoundInNodeCollection( sectionNodes, nsolConnectedNode ) )
			{
			  currentSection->addNode( nsolConnectedNode );
			  lastNodeIds.erase( currentNodeId );
			  lastNodeIds.insert( std::pair< unsigned int, NeuronMorphologySectionPtr >
								  ( connectedNodeId, currentSection ) );
			}
		  }
		}
		//! Bifurcation node (n-ary tree).
		else
		{
		  NodePtr nsolCurrentNode =
		    _EspINASkeletonNodeToNSOLNode( currentNode );

		  for( const auto& connection : filteredConnections )
		  {
		    unsigned int connectedNodeId = connection.first;
			SkeletonNodePtr connectedNode =
			  skeleton->getNodes( ).at( connectedNodeId );

			NodePtr nsolConnectedNode =
			  _EspINASkeletonNodeToNSOLNode( connectedNode );

		    Nodes sectionNodes = currentSection->nodes( );
			//! If not found.
			if( !_NodeFoundInNodeCollection( sectionNodes, nsolConnectedNode ) )
			{
			  NeuronMorphologySectionPtr newSection =
			    NeuronMorphologySectionPtr( new NEURONMORPHOLOGYSECTION );

			  newSection->id( sectionId++ );
			  newSection->neurite( neurite );
			  //! A new section must include the bifurcation node.
			  newSection->addNode( nsolCurrentNode );
			  newSection->addNode( nsolConnectedNode );
			  newSection->addBackwardNeighbour( currentSection );

			  currentSection->addForwardNeighbour( newSection );

			  //! Creating an entry for the new section.
			  lastNodeIds.insert( std::pair< unsigned int, NeuronMorphologySectionPtr >
								  ( connectedNodeId, newSection ) );
			}
		  }
		  //! Actually erasing, no replacing.
		  lastNodeIds.erase( currentNodeId );
		}
	  } // for lastNodeIds
	} // while lastNodeIds not empty
  }

  template < ESPINAXML_READER_TEMPLATE_CLASSES > bool
  EspINAXMLReaderTemplated< ESPINAXML_READER_TEMPLATE_CLASS_NAMES >::_NodeFoundInNodeCollection(
    Nodes nodes,
    NodePtr node )
  {
    for( auto nodeElem : nodes )
    {
      //! Ignoring position and radius.
      if( nodeElem->id( ) == node->id( ) )
      {
        return true;
      }
    }
	return false;
  }

  template < ESPINAXML_READER_TEMPLATE_CLASSES > NodePtr
  EspINAXMLReaderTemplated< ESPINAXML_READER_TEMPLATE_CLASS_NAMES >::_EspINASkeletonNodeToNSOLNode(
    SkeletonNodePtr skeletonNode )
  {
    NodePtr nsolNode;
    Vec3f nsolNodePoint(
	  skeletonNode->getPosition( ).at( 0 ),
	  skeletonNode->getPosition( ).at( 1 ),
	  skeletonNode->getPosition( ).at( 2 ) );
    unsigned int nsolNodeId = skeletonNode->getId( );
    //! This attribute does not exist on EspINA.
    unsigned int nsolNodeRadius = 1.0f;
    nsolNode = new NODE( nsolNodePoint,
    		             nsolNodeId,
						 nsolNodeRadius );
    return nsolNode;
  }

} // namespace nsol

#endif
