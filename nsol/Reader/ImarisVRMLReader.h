#ifndef __NSOL__IMARIS_VRML_READER__
#define __NSOL__IMARIS_VRML_READER__

#include "../Neuron.h"
#include "../Stats/NodeCached.h"
#include "../Stats/SectionCachedStats.h"
#include "../Stats/DendriteCachedStats.h"
#include "../Stats/AxonCachedStats.h"
#include "../Stats/NeuronMorphologyCachedStats.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <cctype>

#include <map>
#include <stack>
#include <queue>



//#include <boost/regex.hpp>
#include <regex>



/*
#define rexIdPattern "\\s*(?P<id>(?:col[0-9]+)?\\s*(?:origen|Origen|[a-zA-Z0-9]*-[0-9]?))\\s*(?:INC|bif)?\\s*"
#define rexPointName "\\s*(?P<point>[ABC]{1})"
#define rexFiletype "\\s*(?P<filetype>fil|Puntos|puntos)\\s*"
#define rexColFullID rexCollection ## rexIdPattern
#define rexFullName rexCollection ## rexIdPattern ## rexFiletype
#define rexColId "(?:" + rexCollection + ")*" ## rexIdPattern + rexPointName
#define rexMatrix '"?\\s*(?P<name>[a-zA-Z]+)\\-(?P<row>[0-9]){1}(?P<col>[0-9]){1}\\s*"?'
#define rexMeshHeader "DEF\\s*FilamentSegment((?:6|7)[0-9]+)"
*/

#define rexCollection "\\s*(?P<collection>(?:soma|apical|bas|basal)[0-9]*)\\s*"
#define rexCoordinates "\\s*(?:[a-zA-Z]+\\s*\\[)?\\s*"  \
                 "([\\-0-9]+\\.[0-9]+)\\s*"             \
                 "([\\-0-9]+\\.[0-9e\\-]+)\\s*"         \
                 "([\\-0-9]+\\.[0-9e\\-]+)\\s*[,\\]]"



namespace nsol
{

#define IMARIS_VRML_READER_TEMPLATE_CLASSES              \
    class NODE,                                  \
    class SECTION,                               \
    class DENDRITE,                              \
    class AXON,                                  \
    class SOMA,                                  \
    class NEURONMORPHOLOGY,                      \
    class NEURON

#define IMARIS_VRML_READER_TEMPLATE_CLASS_NAMES         \
    NODE,                                       \
    SECTION,                                    \
    DENDRITE,                                   \
    AXON,                                       \
    SOMA,                                       \
    NEURONMORPHOLOGY,                           \
    NEURON


  template < IMARIS_VRML_READER_TEMPLATE_CLASSES >
  class ImarisVRMLReaderTemplated
  {
  public:
    NeuronPtr readNeuron( const char* fileName, 
      bool reposition = true );
    NeuronPtr readNeuron( const std::string fileName, 
      bool reposition = true );
    NeuronMorphologyPtr readMorphology( const char *fileName,
        bool reposition_ = true );
    NeuronMorphologyPtr readMorphology( const std::string fileName,
        bool reposition_ = true );
  };



  typedef ImarisVRMLReaderTemplated<  Node,
                                      Section,
                                      Dendrite,
                                      Axon,
                                      Soma,
                                      NeuronMorphology,
                                      Neuron > ImarisVRMLReader;

  typedef ImarisVRMLReaderTemplated<  Node,
                                      SectionStats,
                                      DendriteStats,
                                      AxonStats,
                                      SomaStats,
                                      NeuronMorphologyStats,
                                      Neuron > ImarisVRMLReaderStats;

  typedef ImarisVRMLReaderTemplated<  NodeCached,
                                      SectionCachedStats,
                                      DendriteCachedStats,
                                      AxonCachedStats,
                                      SomaStats,
                                      NeuronMorphologyCachedStats,
                                      Neuron > ImarisVRMLReaderCachedStats;

  template < IMARIS_VRML_READER_TEMPLATE_CLASSES >
  NeuronPtr
  ImarisVRMLReaderTemplated< IMARIS_VRML_READER_TEMPLATE_CLASS_NAMES >::readNeuron(
    const char *fileName, bool reposition_ )
  {
    return this->readNeuron( std::string( fileName ), reposition_ );
  }

  template < IMARIS_VRML_READER_TEMPLATE_CLASSES >
  NeuronPtr
  ImarisVRMLReaderTemplated< IMARIS_VRML_READER_TEMPLATE_CLASS_NAMES >::readNeuron(
    const std::string fileName, bool reposition_ )
  {
    NeuronMorphologyPtr nm = this->readMorphology( std::string( fileName ),
        reposition_ );

    if ( nm )
    {
      NeuronPtr neuron( new NEURON( nm ));
      nm->addParentNeuron( neuron );
      return neuron;
    }
    else
      return nullptr;
  }

  template < IMARIS_VRML_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  ImarisVRMLReaderTemplated< IMARIS_VRML_READER_TEMPLATE_CLASS_NAMES >::readMorphology(
    const char * fileName, bool reposition_ )
  {
    return this->readMorphology(std::string(fileName), reposition_ );
  }

  typedef enum
  {
    Find = 0,
    Capt = 1,
    Coord = 2
    //CoordIdx = 3,
    //End = 4
  } TImarisVRMLState;

  static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
  }

  // trim from end
  static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
  }

  // trim from both ends
  static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
  }

  template < IMARIS_VRML_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  ImarisVRMLReaderTemplated< IMARIS_VRML_READER_TEMPLATE_CLASS_NAMES >::readMorphology(
    const std::string fileName, bool reposition_ )
  {
    std::cout << fileName << std::endl;
    std::ifstream inFile;
    inFile.open(fileName, std::ios::in);

    //Opening file checking
    if ((inFile.rdstate( ) & std::ifstream::failbit) != 0)
    {
      std::cerr << "Error opening file " << fileName << std::endl;

      return nullptr;
    }

    std::cout << rexMeshHeader << std::endl;

    std::string lineString;
    //std::getline( inFile, lineString );

    TImarisVRMLState state = TImarisVRMLState::Find;

    std::vector< std::string > sections;

    std::string relativeID;

    std::string aux;

    std::vector< std::vector

    //while ( inFile )
    while ( std::getline( inFile, aux ) )
    {
      if ( aux.length( ) == 0 )
        continue;
      //lineString += std::string("\n") + aux;

      //std::cout << aux << std::endl;
      if ( state == TImarisVRMLState::Find )
      {
        //std::cout << aux << std::endl;
        std::regex rgx( rexMeshHeader );
        std::smatch result;
        if (std::regex_search(aux, result, rgx))
        {
          std::string submatch(result[1].first, result[1].second);
          std::cout << submatch << std::endl;

          relativeID = submatch;

          state = TImarisVRMLState::Capt;
        }
      }
      else if ( state == TImarisVRMLState::Capt )
      {
        //std::cout << aux << std::endl;
        trim( aux );
        if ( aux.find( "Coordinate" ) == 0 )
        {
          //std::cout << aux << std::endl;
          state = TImarisVRMLState::Coord;
          //state = TImarisVRMLState::Find;
        }
        for( char& c : aux )
        {
          if ( c == '{' )
          {
            sections.push_back( std::string( "{" ) );
          }
          else if ( c == '[' )
          {
            sections.push_back( std::string( "[" ) );
          }
          else if ( ( ( c == '}')
                    && (sections.back( ) == std::string( "{" ))) ||
                  ( ( c == ']' )
                    && (sections.back( ) == std::string( "[" )))      
          )
          {
            sections.pop_back( );
          }
        }
        if ( sections.empty( ) )
        {
          if ( relativeID.find( std::string( "6" )) == 0 )
          {
            std::cout << "Is dendrite" << std::endl;
          }
          else if ( relativeID.find( std::string( "7" )) == 0 )
          {
            std::cout << "Is spine" << std::endl;
          }
          //std::cout << "Finish capt" << std::endl;
          state = TImarisVRMLState::Find;
        }
      }
      else if ( state == TImarisVRMLState::Coord )
      {
        if ( aux.find( std::string( "[" )) != std::string::npos )
        {
          sections.push_back( std::string( "[" ) );
        }
        std::regex rgx2( rexCoordinates );
        std::smatch result2;
        if (std::regex_search(aux, result2, rgx2))
        {
          std::string submatch(result2[1].first, result2[1].second);
          //std::cout << submatch << std::endl;

          std::string submatch2(result2[2].first, result2[2].second);
          //std::cout << submatch2 << std::endl;

          std::string submatch3(result2[3].first, result2[3].second);
          //std::cout << submatch3 << std::endl;
        }
        if ( ((aux.find( std::string( "}" )) != std::string::npos)
                    && (sections.back( ) == std::string( "{" ))) ||
              ((aux.find( std::string( "]" )) != std::string::npos)
                    && (sections.back( ) == std::string( "[" )))      
          )
        {
          sections.pop_back( );
          //std::cout << "Finish coords" << std::endl;
          state = TImarisVRMLState::Capt;
        }
      }
    }

    //std::cout << lineString << std::endl;

    //inFile.close( );
  }
}

#endif /* __NSOL__IMARIS_VRML_READER__ */