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
    unsigned int lineCount, nodeId;
    std::ifstream inFile;

    void _ReadNeurite(NeuronMorphologyPtr neuronMorphology);
    void _ReadSoma(
      NeuronMorphologyPtr neuronMorphology,
      NsolVector<NodePtr>* repositionNodes_,
      bool reposition_ );
    int _countBrackets( const std::string& line );

    void eraseComent( std::string& lineString );
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

    inFile.open( fileName, std::ios::in );

    //! Opening file check
    if ((inFile.rdstate() & std::ifstream::failbit) != 0)
    {
      Log::log( std::string( "Error opening file: " ) + fileName, LOG_LEVEL_WARNING );

      return nullptr;

    }

    std::string lineString;

    NsolVector<NodePtr> repositionNodes;
    NeuronMorphologyPtr neuronMorphology( new NEURONMORPHOLOGY( new SOMA ) );

    nodeId = 0;
    lineCount = 0;

    //! Reads file, line by line
    while (std::getline( inFile, lineString ) ) {
      ++lineCount;
      eraseComent( lineString );

      std::transform( lineString.begin(), lineString.end(), lineString.begin(), ::tolower );

      if (std::regex_match( lineString, std::regex( ".*\\( *dendrite *\\).*" ))) {
        DendritePtr dendrite = new DENDRITE();
        neuronMorphology->addNeurite( dendrite );
        dendrite->morphology( neuronMorphology );

        std::printf( "dendrita\n" );

        //_ReadNeurite( basalP, lines, firstNodeId,                        &repositionNodes, reposition_ );


      } else if (std::regex_match( lineString, std::regex( ".*\\( *cellbody *\\).*" ))) {
        _ReadSoma( neuronMorphology, &repositionNodes, reposition_ );

      } else if (std::regex_match( lineString, std::regex( ".*\\( *axon *\\).*" ))) {
        std::printf( "axon\n" );
      }//! else ignore
    }
    return neuronMorphology;

  }

  template < ASC_READER_TEMPLATE_CLASSES > void
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::eraseComent(
    std::string& lineString )
  {
    int comment = lineString.find_first_of( ';' );
    if(comment != std::string::npos)
        lineString.erase( comment );
  }


  template < ASC_READER_TEMPLATE_CLASSES > void
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::_ReadNeurite(NeuronMorphologyPtr neuronMorphology) {
    std::stack<SectionPtr> parentSections;
    SectionPtr currentParentSection = nullptr;
    std::string lineString;
    int level = 1;

    //! Reads file, line by line
    while ( std::getline( inFile, lineString ) && level > 0 ) {
      ++lineCount;

      eraseComent( lineString );

      //! Skips empty lines
      if ( lineString.find_first_not_of( " \r\t" ) != std::string::npos ) {
        //! Accounts for opening minus closing brackets
        int bracketCount = _countBrackets( lineString );
        level += bracketCount;

        if ( bracketCount < 0 ) {
          parentSections.pop( );

        } else if ( bracketCount > 0 && level != 1 ) {
          parentSections.push( currentParentSection );

        }
      }
    }
  }

  template < ASC_READER_TEMPLATE_CLASSES > int
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >:: _countBrackets(
      const std::string& line )
  {
    int bracketCount = 0;
    for ( const auto& character : line )
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
    return bracketCount;

  }

  template < ASC_READER_TEMPLATE_CLASSES > void
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::_ReadSoma(
      NeuronMorphologyPtr neuronMorphology,
      NsolVector<NodePtr>* repositionNodes_,
      bool reposition_ )
  {

    std::string lineString;
    int level = 1;

    //! Reads file, line by line
    while ( std::getline( inFile, lineString ) && level > 0 ) {

      eraseComent( lineString );

      level += _countBrackets( lineString );
      ++lineCount;

      if ( std::regex_match( lineString, std::regex( " *\\( *-*\\d+\\.*\\d* +-*\\d+\\.*\\d* +-*\\d+\\.*\\d* +\\d+\\.*\\d* *\\) *" ) ) )
      {
        //! Removes opening bracket
        lineString.erase( 0, lineString.find_first_of( '(' ) + 1);
        std::istringstream iss( lineString );
        Vec3f xyz;
        float diametre;

        iss >> xyz[0]
            >> xyz[1]
            >> xyz[2];
        iss >> diametre;

        NodePtr node(
            new NODE( xyz, ++nodeId, diametre/2.0f ) );

        /**
         * Adds nodes for later recalculation of position
         * if reposition_ is active
         */
        if ( reposition_ )
          repositionNodes_->push_back( node );

        neuronMorphology->soma( )->addNode( node );

      }
    }
  }

} // namespace nsol

#endif

