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
     * an ASC file
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
     * @param fileName path to ASC file to be read
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true
     * @return pointer to the NeuronMorphology created; nullptr if failure on
     * ASC read
     */
    NeuronMorphologyPtr readMorphology( const std::string& fileName, 
      bool reposition_ = false );


    protected:

    //! Regular expressions that define data lines
    #define REGEX_DATA_LINE "\\s*\\(\\s*-?\\d+\\.?\\d*\\s+-?\\d+\\.?\\d*\\s+-?\\d+\\.?\\d*\\s+\\d+\\.?\\d*\\s*\\)\\s*"
    #define REGEX_SPINE_LINE "\\s*<\\s*\\(\\s*-?\\d+\\.?\\d*\\s+-?\\d+\\.?\\d*\\s+-?\\d+\\.?\\d*\\s+\\d+\\.?\\d*\\s*\\)\\s*>\\s*"

    unsigned int nodeId;
    std::ifstream inFile;

    /**
     * Reads a Neurite from an ASC file
     *
     * @param neuritePointer neuritePtr where info will be loaded
     * @param repositionNodes_ auxiliary vector for recalculation purposes
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true;
     * it will only serve to add all new nodes to repositionNodes_ for later
     * recalculation
     */
    void _ReadNeurite(
      NeuritePtr neuritePointer,
      NsolVector<NodePtr>* repositionNodes_,
      bool reposition_ );

    /**
    * Reads soma points from an ASC file
    *
    * @param neuronMorphology NeuronMorphologyPtr where soma nodes will be added
    * @param repositionNodes_ auxiliary vector for recalculation purposes
    * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true;
    * it will only serve to add all new nodes to repositionNodes_ for later
    * recalculation
    */
    void _ReadSoma( 
      NeuronMorphologyPtr neuronMorphology,
      NsolVector<NodePtr>* repositionNodes_,
      bool reposition_ );

    /**
     * Calculates the total amount of opening minus closing brackets
     *
     * @param line string to be analysed
     * @return total opening minus closing brackets count
     */
    int _countBrackets( const std::string& line );

    /**
     * Modifies a string by removing any comments there may be
     * (after ';' character)
     *
     * @param line reference to string to be modified
     */
    void _eraseComent( std::string& line );

    /**
     * Creates a new NodePtr using the information contained in a data line
     *
     * @param line string to be analysed
     * @return pointer to Node containing all info in received string
     */
    NodePtr _parseDataLine( const std::string& line );
    

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
    NeuronMorphologyPtr nm = this->readMorphology( fileName, reposition_ );

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
    if ( ( inFile.rdstate( ) & std::ifstream::failbit ) != 0 )
    {
      Log::log( std::string( "Error opening file: " ) + fileName,
        LOG_LEVEL_WARNING );
      return nullptr;

    }

    std::string lineString;

    NsolVector<NodePtr> repositionNodes;
    NeuronMorphologyPtr neuronMorphology( new NEURONMORPHOLOGY( new SOMA ) );

    nodeId = 0;

    //! Reads file, line by line
    while ( std::getline( inFile, lineString ) )
    {
      //! Removes commentaries
      _eraseComent( lineString );
      //! Puts line in lower letters to match the line types
      std::transform( lineString.begin( ), lineString.end( ),
        lineString.begin( ), ::tolower );

      //! Checks whether a new basal dendrite is being declared
      if ( std::regex_match( lineString,
        std::regex( ".*\\(\\s*dendrite\\s*\\).*" ) ) )
      {
        /**
         * Creates a pointer to a new basal dendrite and loads all corresponding
         * info from the ASC file
         */
        DendritePtr basalP = new DENDRITE( Dendrite::BASAL );
        neuronMorphology->addNeurite( basalP );
        basalP->morphology( neuronMorphology );
        _ReadNeurite( basalP, &repositionNodes, reposition_ );

      }
      //! Checks whether a new apical dendrite is being declared
      else if ( std::regex_match( lineString,
        std::regex( ".*\\(\\s*apical\\s*\\).*" ) ) )
      {
        /**
         * Creates a pointer to a new apical dendrite and loads all
         * corresponding info from the ASC file
         */
        DendritePtr apicalP = new DENDRITE( Dendrite::APICAL );
        neuronMorphology->addNeurite( apicalP );
        apicalP->morphology( neuronMorphology );
        _ReadNeurite( apicalP, &repositionNodes, reposition_ );

      }
      /**
       * Checks whether a new soma has been declared
       * If multiple soma contours are present, their points will be loaded
       * into a single soma
       */
      else if ( std::regex_match( lineString,
        std::regex( ".*\\(\\s*cellbody\\s*\\).*" ) ) )
      {
        _ReadSoma( neuronMorphology, &repositionNodes, reposition_ );

      }
      //! Checks whether a new axon has been declared
      else if ( std::regex_match( lineString,
        std::regex( ".*\\(\\s*axon\\s*\\).*" ) ) )
      {
        /**
         * Creates a pointer to a new axon and loads all
         * corresponding info from the ASC file
         */
        AxonPtr axon = new AXON( );
        neuronMorphology->addNeurite( axon );
        axon->morphology( neuronMorphology );
        _ReadNeurite( axon, &repositionNodes, reposition_ );
      }
      //! All other bracketed directives are ignored

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
    NsolVector<NodePtr>* repositionNodes_,
    bool reposition_ )
  {
    std::stack<NeuronMorphologySectionPtr> parentSections;
    NeuronMorphologySectionPtr currentSection = nullptr;
    std::string lineString;
    int level = 1;

    currentSection = NeuronMorphologySectionPtr( new NEURONMORPHOLOGYSECTION );
    neuritePointer->firstSection( currentSection );


    NeuronMorphologySectionPtr parentSection = nullptr;
    bool firstNode = true;


    //! Reads file, line by line, until end of current neurite is reached
    while ( level > 0 && std::getline( inFile, lineString ) )
    {
      //! Removes comment
      _eraseComent( lineString );

      //! Checks whether the line contains node info
      if( std::regex_match( lineString, std::regex( REGEX_DATA_LINE ) ) )
      {
        //! Parses the line and creates a new node
        NodePtr node = _parseDataLine( lineString );

        /**
         * Adds nodes for later recalculation of position
         * if reposition_ is active
         */
        if( reposition_ )
        {
          repositionNodes_->push_back( node );
        }

        //! Adds first node to the first section of the neurite
        if ( firstNode )
        {
          currentSection->firstNode( node );
          firstNode = false;
        }
        //! Adds new node to the current section
        else
        {
          currentSection->addNode( node );
        }
      }

      /**
       * Lines with character '|' mark the beginning of a new section at the
       * same level in the hierarchy.
       */
      else if ( std::regex_match( lineString, std::regex( "\\s*\\|\\s*" ) ) )
      {

        /**
         * Creates a new section, updates the parent section stack, and
         * increments branch count by one
         */
        currentSection =
          NeuronMorphologySectionPtr( new NEURONMORPHOLOGYSECTION );
        currentSection->neurite( neuritePointer );
        currentSection->parent( parentSection );
        parentSection->addChild( currentSection );
        neuritePointer->_addBranchCount( 1 );

      }
      //! Checks whether the line contains spine data (not implemented)
      else if ( std::regex_match( lineString, std::regex( REGEX_SPINE_LINE ) ) )
      {
        Log::log( std::string( "Spines still not implemented: " ) +
          lineString, LOG_LEVEL_VERBOSE );

      }
      else
      {
        int bracketCount = _countBrackets( lineString );
        level += bracketCount;

        //! Updates parent section stack whenever hierarchy level is changed
        if( bracketCount < 0 && level > 1 )
        {
          parentSections.pop( );
          parentSection = parentSections.top( );

        }
        else if( bracketCount > 0 )
        {
          std::transform( lineString.begin( ), lineString.end( ),
            lineString.begin( ), ::tolower );
          //! Skips markers (not implemented)
          if ( std::regex_match( lineString,
            std::regex( "\\s*\\(\\s*dot\\s*" ) ) )
          {
            bracketCount = 0;

            while ( bracketCount == 0 && std::getline( inFile, lineString ) )
            {
              _eraseComent( lineString );
              bracketCount = _countBrackets( lineString );

            }
            level += bracketCount;

          }
          else
          {
            /**
             * If end of hierarchy level is reached, updates parent Section
             * stack, branch and bifurcation counters, and creates the new
             * section to be worked on
             */
            parentSections.push( currentSection );
            neuritePointer->_addBifurcationCount( 1 );
            neuritePointer->_addBranchCount( 1 );

            parentSection = currentSection;
            currentSection = new NEURONMORPHOLOGYSECTION( );
            currentSection->neurite( neuritePointer );
            currentSection->parent( parentSection );
            parentSection->addChild( currentSection );

          }
        }
      }
    }
  }


  template < ASC_READER_TEMPLATE_CLASSES > void
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::_ReadSoma( 
    NeuronMorphologyPtr neuronMorphology,
    NsolVector<NodePtr>* repositionNodes_,
    bool reposition_ )
  {

    std::string lineString;
    int level = 1;

    //! Reads file, line by line, until end of current Soma contour is reached

    while ( level > 0 && std::getline( inFile, lineString ) )
    {

      //! Removes comment
      _eraseComent( lineString );

      //! Updates current hierarchy level
      level += _countBrackets( lineString );

      //! Detection of data lines
      if ( std::regex_match( lineString, std::regex( REGEX_DATA_LINE ) ) )
      {
        //! Parses line to a new node
        NodePtr node = _parseDataLine( lineString );

        /**
         * Adds nodes for later recalculation of position
         * if reposition_ is active
         */
        if ( reposition_ )
          repositionNodes_->push_back( node );

        //! Adds the new node to the soma
        neuronMorphology->soma( )->addNode( node );

      }
    }
  }


  template < ASC_READER_TEMPLATE_CLASSES > NodePtr
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::_parseDataLine( 
    const std::string& line )
  {
    std::istringstream iss( line );
    Vec3f xyz;
    float diametre;
    char tmp;

    //! Pareses data line into auxiliary variables
    iss >> tmp; //! Removes opening bracket
    iss >> xyz[0]
        >> xyz[1]
        >> xyz[2];
    iss >> diametre;

    //! Creates a new node with the info that was gathered
    NodePtr node = new NODE( xyz, ++nodeId, diametre/2.0f );

    return node;
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
  AscReaderTemplated< ASC_READER_TEMPLATE_CLASS_NAMES >::_eraseComent( 
    std::string &line )
  {
    //! Erases all characters from the first instance of ';' onwards
    unsigned long comment = line.find_first_of( ';' );
    if( comment != std::string::npos )
      line.erase( comment );

  }

} // namespace nsol

#endif

