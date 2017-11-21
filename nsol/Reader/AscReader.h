/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *          Iago Calvo Lista
 *          Fernando Lucas Pérez
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
#ifndef __NSOL_ASC_READER__
#define __NSOL_ASC_READER__


#include "../Neuron.h"
#include "../Stats/NodeCached.h"
#include "../Stats/NeuronMorphologySectionCachedStats.h"
#include "../Stats/DendriteCachedStats.h"
#include "../Stats/AxonCachedStats.h"
#include "../Stats/NeuronMorphologyCachedStats.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <regex>

#include <stack>

namespace nsol
{

#define ASC_READER_TEMPLATE_CLASSES            \
  class NODE,                                  \
  class NEURONMORPHOLOGYSECTION,               \
  class DENDRITE,                              \
  class AXON,                                  \
  class SOMA,                                  \
  class NEURONMORPHOLOGY,                      \
  class NEURON

#define ASC_READER_TEMPLATE_CLASS_NAMES       \
  NODE,                                       \
  NEURONMORPHOLOGYSECTION,                    \
  DENDRITE,                                   \
  AXON,                                       \
  SOMA,                                       \
  NEURONMORPHOLOGY,                           \
  NEURON


  template < ASC_READER_TEMPLATE_CLASSES >
  class AscReaderTemplated
  {

    public:

    /**
     * Creates a new Neuron that contains the NeuronMorphology described in
     * ASC file
     * Calls readMorphology( 2 )
     *
     * @param fileName path to ASC file to read
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true
     * @return pointer to the Neuron created; nullptr if failure on ASC read
     */
    NeuronPtr readNeuron( const std::string& fileName,
                          bool reposition_ = false );

    /**
     * Creates a NeuronMorphology and loads info described in ASC file
     *
     * @param fileName path to ASC file to read
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true
     * @return pointer to the NeuronMorphology created; nullptr if failure on ASC read
     */
    NeuronMorphologyPtr readMorphology( const std::string& fileName,
                                        bool reposition_ = false );


    protected:

  }; // class AscReaderTemplated


  typedef AscReaderTemplated< Node,
      NeuronMorphologySection,
      Dendrite,
      Axon,
      Soma,
      NeuronMorphology,
      Neuron > AscReader;

  typedef AscReaderTemplated< Node,
      NeuronMorphologySectionStats,
      DendriteStats,
      AxonStats,
      SomaStats,
      NeuronMorphologyStats,
      Neuron > AscReaderStats;

  typedef AscReaderTemplated< NodeCached,
      NeuronMorphologySectionCachedStats,
      DendriteCachedStats,
      AxonCachedStats,
      SomaStats,
      NeuronMorphologyCachedStats,
      Neuron > AscReaderCachedStats;


  //////////////////////////////////////////////////////////////////
  //
  // Implementation of methods for AscTemplated
  //
  //////////////////////////////////////////////////////////////////

  template < ASC_READER_TEMPLATE_CLASSES >
  NeuronPtr
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::readNeuron(
      const std::string& fileName, bool reposition_ )
  {
    NeuronMorphologyPtr nm = this->readMorphology( fileName,
                                                   reposition_ );

    if ( nm )
    {
      NeuronPtr neuron( new NEURON( nm ) );
      nm->addParentNeuron( neuron );
      return neuron;
    }
    else
      return nullptr;
  }


  template < ASC_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::readMorphology(
      const std::string& fileName, bool reposition_ )
  {
    std::ifstream inFile;
    inFile.open( fileName, std::ios::in );

    //! Opening file check
    if ( ( inFile.rdstate( ) & std::ifstream::failbit ) != 0 )
    {
      Log::log( std::string( "Error opening file: " ) + fileName, LOG_LEVEL_WARNING );

      return nullptr;

    }

    std::string lineString;

    NsolVector< NodePtr > repositionNodes;
    NeuronMorphologyPtr neuronMorphology( new NEURONMORPHOLOGY( new SOMA ) );

    unsigned int lineCount = 0;
    unsigned int level = 0;
    unsigned int nodeIdCount = 0;
    std::stack<SectionPtr> parentSections;
    SectionPtr currentParentSection = nullptr;

    //! Reads file, line by line
    while ( std::getline( inFile, lineString ) )
    {
      ++lineCount;

      //! Removes comment
      lineString.erase( lineString.find_first_of( ';' ) );

      //! Skips empty lines
      if ( lineString.find_first_not_of( " \r\t" ) != std::string::npos )
      {
        //! Accounts for opening minus closing brackets
        int bracketCount = 0;
        for ( const auto& character : lineString )
        {
          if ( character == '(' )
          {
            ++bracketCount;

          }
          else if ( character == ')' )
          {
            --bracketCount;

          }

        }

        level += bracketCount;

        if ( bracketCount < 0 )
        {
          parentSections.pop( );

        }
        else if ( bracketCount > 0 && level != 1 )
        {
          parentSections.push( currentParentSection );

        }

        if ( level == 1 )
        {
          if (std::regex_match ( lineString, std::regex( ".*\".*\".*" ) ) )
          {

          }
          else if ( std::regex_match ( lineString, std::regex( ".*\( *[a|A]xon *\).*" ) ) )
          {

          }
          //TODO


        }

        //! Verifies there are 7 fields ( or more, if comments are present )
        unsigned int fields =
            1 + ( unsigned int )std::count_if( lineString.begin( ), lineString.end( ),
                                               []( unsigned char c )
                                               {
                                                 return std::isspace( c );
                                               }
            );

        if ( fields < 7 )
        {
          Log::log( std::string( "Skipping line " ) +
                    std::to_string( lineCount ) +
                    std::string( " in file " ) +
                    fileName + std::string( ": \"" ) + lineString +
                    std::string( "\" ( not enough fields found )" ),
                    LOG_LEVEL_WARNING );
        }
        else
        {
          //! Loads info in struct TAscLine
          std::istringstream iss( lineString );
          TAscLine ascLineString;

          bool failed = false;
          iss >> ascLineString.id;
          if ( iss.fail( ) )
            failed = true;
          iss >> ascLineString.type;
          if ( iss.fail( ) )
            failed = true;
          iss >> ascLineString.xyz[0]
              >> ascLineString.xyz[1]
              >> ascLineString.xyz[2];
          if ( iss.fail( ) )
            failed = true;
          iss >> ascLineString.radius;
          if ( iss.fail( ) )
            failed = true;
          iss >> ascLineString.parent;
          if ( iss.fail( ) )
            failed = true;

          if ( failed )
          {
            Log::log( std::string( "Skipping line " ) +
                      std::to_string( lineCount ) +
                      std::string( " in file " ) +
                      fileName + std::string( ": \"" ) + lineString +
                      std::string( "\" ( line format not recognised )" ),
                      LOG_LEVEL_WARNING );
          } else {
            lines[ascLineString.id] = ascLineString;
          }

        }
      }
    }

    inFile.close( );

    //! Adds children to TAscLine elements created
    for ( const auto& line : lines )
    {
      if ( line.second.parent != -1 )
        lines[line.second.parent].children.push_back( line.first );
    }

    std::vector<unsigned int> somaChildren;
    std::map<unsigned int, NodePtr > nodeSomaPtr;

    //! Adds soma nodes to neuronMorphology->Soma
    for ( const auto& line : lines )
    {
      if ( line.second.type == ASC_SOMA )
      {
        NodePtr node(
            new NODE( line.second.xyz, line.second.id, line.second.radius ) );

        /**
         * Adds nodes for later recalculation of position
         * if reposition_ is active
         */
        if ( reposition_ )
          repositionNodes.push_back( node );

        neuronMorphology->soma( )->addNode( node );

        nodeSomaPtr[line.second.id] = node;

        //! Adds non-soma childrens of soma nodes to vector for later use
        for ( const unsigned int child : line.second.children )
          if ( lines[child].type != ASC_SOMA )
            somaChildren.push_back( child );

      }
    }

    //! Initiates read process for each neurite, via first node
    for ( const unsigned int firstNodeId : somaChildren )
    {

      switch ( lines[firstNodeId].type ) {
        case ASC_BASAL:
        {
          DendritePtr basalP = new DENDRITE( Dendrite::BASAL );
          neuronMorphology->addNeurite( basalP );
          basalP->morphology( neuronMorphology );
          _ReadNeurite( basalP, lines, firstNodeId,
                        &repositionNodes, reposition_ );
        }
          break;

        case ASC_APICAL:
        {
          DendritePtr apicalP = new DENDRITE( Dendrite::APICAL );
          neuronMorphology->addNeurite( apicalP );
          apicalP->morphology( neuronMorphology );
          _ReadNeurite( apicalP, lines, firstNodeId,
                        &repositionNodes, reposition_ );
        }
          break;

        case ASC_AXON:
        {
          AxonPtr axonP = new AXON();
          neuronMorphology->addNeurite( axonP );
          axonP->morphology( neuronMorphology );
          _ReadNeurite( axonP, lines, firstNodeId,
                        &repositionNodes, reposition_ );
        }
          break;

        default:
          Log::log( std::string( "Unexpected line type value in line " ) +
                    std::to_string( firstNodeId ), LOG_LEVEL_WARNING);

      }
    }

    /**
     * Moves soma center to ( 0.0, 0.0, 0.0 ) if reposition_ is active,
     * accordingly recalculating position for all nodes
     */

    if ( reposition_ )
    {
      Vec3f center = neuronMorphology->soma( )->center( );

      for ( auto& node : repositionNodes )
      {
        node->point( node->point( ) - center );
      }

      neuronMorphology->soma( )->center( Vec3f( 0.0f, 0.0f, 0.0f ) );

    }

    return neuronMorphology;

  }


  template < ASC_READER_TEMPLATE_CLASSES > void
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::_ReadNeurite(
      NeuritePtr neuritePointer,
      const std::map<unsigned int, TAscLine>& lines,
      unsigned int initId,
      NsolVector<NodePtr>* nodes_,
      bool reposition_ )
  {
    std::stack<TReadNeuriteStackElem> sectionFirstNodes;
    NeuronMorphologySectionPtr sectionPointer = nullptr;

    sectionPointer = NeuronMorphologySectionPtr( new NEURONMORPHOLOGYSECTION );

    sectionPointer->neurite( neuritePointer );
    sectionPointer->parent( nullptr );

    NodePtr node;
    //! Creates first Node in first Secion
    TAscLine lineElem = lines.at( initId );
    node = new NODE( lineElem.xyz, initId, lineElem.radius );
    sectionPointer->firstNode( node );
    //! Loads first Section in Neurite
    _ReadSection( neuritePointer, sectionPointer, node, &sectionFirstNodes, lines, nodes_, reposition_ );
    neuritePointer->firstSection( sectionPointer );

    //! Creates and loads all Sections in Neurite
    while ( !sectionFirstNodes.empty( ) )
    {
      unsigned int id = sectionFirstNodes.top( ).id;
      NeuronMorphologySectionPtr parentSection = sectionFirstNodes.top( ).parent;
      sectionPointer = NeuronMorphologySectionPtr( new NEURONMORPHOLOGYSECTION );
      sectionPointer->neurite( neuritePointer );
      sectionPointer->parent( parentSection );
      sectionFirstNodes.pop( );

      //! Creates first Node of new Section
      lineElem = lines.at( id );
      node = new NODE( lineElem.xyz, id, lineElem.radius );
      sectionPointer->addNode( node ); //

      parentSection->addChild( sectionPointer );

      //! Loads Section and stores first Nodes of other Sections to load
      _ReadSection( neuritePointer, sectionPointer, node, &sectionFirstNodes,
                    lines, nodes_, reposition_ );

    }
  }

  template < ASC_READER_TEMPLATE_CLASSES > void
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::_ReadSection(
      NeuritePtr neuritePointer,
      NeuronMorphologySectionPtr sectionPointer,
      NodePtr nodePointer,
      std::stack<TReadNeuriteStackElem>* sectionFirstNodes,
      const std::map<unsigned int, TAscLine>& lines,
      NsolVector<NodePtr>* nodes_,
      bool reposition_ )
  {
    unsigned int nodeId = ( unsigned int ) nodePointer->id();
    //! Stores first node for later position recalculation
    if ( reposition_ )
      nodes_->push_back( nodePointer );

    //! Loads all nodes in section
    TAscLine lineElem = lines.at( nodeId );
    while ( lineElem.children.size( ) == 1 )
    {
      nodeId = lineElem.children[0];
      lineElem = lines.at( nodeId );
      nodePointer = new NODE( lineElem.xyz, nodeId, lineElem.radius );

      //! Stores nodes for later position recalculation
      if ( reposition_ )
        nodes_->push_back( nodePointer );

      sectionPointer->addNode( nodePointer );
    }

    /**
     * End of section reached;
     * first nodes of branching sections will be added to stack
     */
    if ( lineElem.children.size( ) > 1 )
    {
      //! Branch count updated
      neuritePointer->_addBranchCount( ( unsigned int ) lineElem.children.size( ) );
      //! Plus new bifurcation
      neuritePointer->_addBifurcationCount( 1 );

      //! Adds first nodes of new branches to stack
      for ( const auto& it : lineElem.children )
      {
        TReadNeuriteStackElem tmpStackElem = { it, sectionPointer };
        sectionFirstNodes->push( tmpStackElem );
      }

    }
  }
} // namespace nsol

#endif

