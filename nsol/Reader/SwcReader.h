 /**
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @author  Ricardo Suarez
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SWC_READER__
#define __NSOL_SWC_READER__


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

namespace nsol
{

#define SWC_READER_TEMPLATE_CLASSES              \
    class NODE,                                  \
    class SECTION,                               \
    class DENDRITE,                              \
    class AXON,                                  \
    class SOMA,                                  \
    class NEURONMORPHOLOGY,                      \
    class NEURON

#define SWC_READER_TEMPLATE_CLASS_NAMES         \
    NODE,                                       \
    SECTION,                                    \
    DENDRITE,                                   \
    AXON,                                       \
    SOMA,                                       \
    NEURONMORPHOLOGY,                           \
    NEURON


  template < SWC_READER_TEMPLATE_CLASSES >
  class SwcReaderTemplated
  {

  public:

    NeuronPtr readNeuron( const char *fileName,
        bool reposition_ = true );
    NeuronPtr readNeuron( const std::string fileName,
        bool reposition_ = true );
    NeuronMorphologyPtr readMorphology( const char *fileName,
        bool reposition_ = true );
    NeuronMorphologyPtr readMorphology( const std::string fileName,
        bool reposition_ = true );


  protected:

    typedef struct
    {
      unsigned int id;
      unsigned int type;
      Vec3f xyz;
      float radius;
      int parent;
      std::vector<unsigned int> children;
    } TSwcLine;

    typedef enum
    {
      SWC_SOMA = 1,
      SWC_AXON = 2,
      SWC_DENDRITE = 3,
      SWC_APICAL = 4
    } TSwcNodeType;

    typedef struct
    {
      unsigned int id;
      SectionPtr parent;
    } TReadDendritesStackElem;

    typedef struct
    {
      unsigned int id;
      SectionPtr parent;
    } TReadAxonStackElem;


    void _ReadDendrite( DendritePtr d,
                        std::map<unsigned int, TSwcLine> & lines,
                        unsigned int initId,
                        NsolVector<NodePtr>* nodes_ = nullptr,
                        bool reposition_ = false );

    void _ReadAxon(NeuritePtr d, std::map<unsigned int, TSwcLine> & lines,
                   unsigned int initId,
                   NsolVector<NodePtr>* nodes_ = nullptr,
                   bool reposition_ = false );


  }; // class SwcReaderTemplated


  typedef SwcReaderTemplated< Node,
                              Section,
                              Dendrite,
                              Axon,
                              Soma,
                              NeuronMorphology,
                              Neuron > SwcReader;

  typedef SwcReaderTemplated< Node,
                              SectionStats,
                              DendriteStats,
                              AxonStats,
                              SomaStats,
                              NeuronMorphologyStats,
                              Neuron > SwcReaderStats;

  typedef SwcReaderTemplated< NodeCached,
                              SectionCachedStats,
                              DendriteCachedStats,
                              AxonCachedStats,
                              SomaStats,
                              NeuronMorphologyCachedStats,
                              Neuron > SwcReaderCachedStats;



  //////////////////////////////////////////////////////////////////
  //
  // Implementation of methods for SwcTemplated
  //
  //////////////////////////////////////////////////////////////////

  template < SWC_READER_TEMPLATE_CLASSES >
  NeuronPtr
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::readNeuron(
    const char *fileName, bool reposition_ )
  {
    std::cerr << "SwcReader< >::readNeuron is deprecated. "
              << "Please use BrainReader< >::loadNeuron" << std::endl;
    return this->readNeuron(std::string(fileName), reposition_ );
  }



  template < SWC_READER_TEMPLATE_CLASSES >
  NeuronPtr
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::readNeuron(
    const std::string fileName, bool reposition_ )
  {
    std::cerr << "SwcReader< >::readNeuron is deprecated. "
              << "Please use BrainReader< >::loadNeuron" << std::endl;
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



  template < SWC_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::readMorphology(
    const char * fileName, bool reposition_ )
  {
    std::cerr << "SwcReader< >::readMorphology is deprecated. "
              << "Please use BrainReader< >::loadMorphology" << std::endl;
    return this->readMorphology(std::string(fileName), reposition_ );
  }



  template < SWC_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::readMorphology(
    const std::string fileName, bool reposition_ )
  {
    std::cerr << "SwcReader< >::readMorphology is deprecated. "
              << "Please use BrainReader< >::loadMorphology" << std::endl;
    std::ifstream inFile;
    inFile.open(fileName, std::ios::in);

    //Opening file checking
    if ((inFile.rdstate( ) & std::ifstream::failbit) != 0)
    {
      std::cerr << "Error opening file " << fileName << std::endl;

      return nullptr;
    }

    std::string lineString;
    std::getline( inFile, lineString );

    NsolVector< NodePtr > nodes;
    NeuronMorphologyPtr neuronMorphology( new NEURONMORPHOLOGY( new SOMA ));

    std::map<unsigned int, TSwcLine> lines;

    int lineCount = 0;

    while ( std::getline( inFile, lineString ))
    {
      lineCount++;

      // TODO: this does not cover the case the # char is not the first char
      if ( lineString[0] != '#' )
      {

        // Trim spaces
        lineString.erase( lineString.find_last_not_of( " \r\t") +1 );
        unsigned int fields =
          1 + std::count_if( lineString.begin( ), lineString.end( ),
                             []( unsigned char c )
                             {
                               return std::isspace( c );
                             });

        if ( fields < 7 )
        {
          Log::log( std::string( "Skipping lineString " ) +
                    std::to_string( lineCount ) +
                    std::string( ". Not enough fields found" ),
                    LOG_LEVEL_WARNING );
          continue;
        }


        std::istringstream iss(lineString);

        TSwcLine swcLineString;
        iss >> swcLineString.id;
        iss >> swcLineString.type;
        iss >> swcLineString.xyz[0]
            >> swcLineString.xyz[1]
            >> swcLineString.xyz[2];
        iss >> swcLineString.radius;
        iss >> swcLineString.parent;

        lines[swcLineString.id] = swcLineString;

      }
    }

    for ( const auto& line : lines )
    {
      if (line.second.parent != -1)
        lines[line.second.parent].children.push_back( line.first );
    }

    std::vector<unsigned int> somaChildren;
    std::map<unsigned int, NodePtr > nodeSomaPtr;

    for ( const auto& line : lines )
    {
      if (line.second.type == SWC_SOMA)
      {
        NodePtr node(
          new NODE(line.second.xyz, line.second.id, line.second.radius) );

        if ( reposition_ )
          nodes.push_back( node );

        neuronMorphology->soma( )->addNode(node);

        nodeSomaPtr[line.second.id] = node;

        for (unsigned int i = 0; i < line.second.children.size( ); i++)
          if (lines[line.second.children[i]].type != SWC_SOMA)
            somaChildren.push_back(line.second.children[i]);
      }
    }

    DendritePtr d;

    for (unsigned int i = 0; i < somaChildren.size( ); i++)
    {


      switch (lines[somaChildren[i]].type)
      {
      case SWC_SOMA:
        // TODO: handle error
        assert(false);

      case SWC_DENDRITE:
      {

        d = new DENDRITE( Dendrite::BASAL );
        neuronMorphology->addNeurite( d );
        d->morphology( neuronMorphology );
        _ReadDendrite(d, lines, somaChildren[i],
                      &nodes, reposition_ );

        break;
      }

      case SWC_APICAL:
        d = new DENDRITE( Dendrite::APICAL );
        neuronMorphology->addNeurite( d );
        d->morphology(neuronMorphology);
        _ReadDendrite(d, lines, somaChildren[i],
                      &nodes, reposition_ );

        break;

      case SWC_AXON:
      {
        AxonPtr nP = new AXON( );
        neuronMorphology->addNeurite( nP );
        nP->morphology(neuronMorphology);
        _ReadAxon(nP, lines, somaChildren[i],
                  &nodes, reposition_ );

        break;
      }

      default:
        break;
      }

    }


    inFile.close( );


    if ( reposition_ )
    {
      Vec3f center = neuronMorphology->soma( )->center( );

      NSOL_FOREACH( node, nodes )
      {
        (*node)->point( (*node)->point( ) - center );
      }

      neuronMorphology->soma( )->center( Vec3f( 0.0f, 0.0f, 0.0f ));

    }

    return neuronMorphology;

  }


  template < SWC_READER_TEMPLATE_CLASSES > void
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::_ReadDendrite(
    DendritePtr d,
    std::map<unsigned int, TSwcLine> & lines,
    unsigned int initId,
    NsolVector<NodePtr>* nodes_,
    bool reposition_ )
  {

    std::stack<TReadDendritesStackElem> ids;
    //ids.push(TReadDendritesStackElem { initId, NULL });
    TReadDendritesStackElem tmp = {initId, NULL};
    ids.push(tmp);


    SectionPtr s = nullptr, parentSection;
    bool first = true;

    while (!ids.empty( ))
    {

      unsigned int id = ids.top( ).id;
      parentSection = ids.top( ).parent;
      ids.pop( );

      /* parentSection = s; */
      s = SectionPtr( new SECTION );

      if (!d->firstSection( ))
        d->firstSection(s);  //->addSection( );

      s->neurite(d);
      s->parent( parentSection );

      NodePtr node;
      if (first)
      {
        node = new NODE(lines[id].xyz, id, lines[id].radius );
        s->firstNode( node );

        if ( reposition_ )
          nodes_->push_back( node );
        first = false;
      }
      else
      {
        node = new NODE(lines[id].xyz, id, lines[id].radius );
        s->addNode( node );

        if ( parentSection )
          parentSection->addChild( s );

        if ( reposition_ )
          nodes_->push_back( node );
      }

      // While same section create the segments
      while (lines[id].children.size( ) == 1)
      {
        id = lines[id].children[0];

        node  = new NODE( lines[id].xyz, id, lines[id].radius );
        if ( reposition_ )
          nodes_->push_back( node );

        s->addNode( node );
      }

      // New branching point
      if (lines[id].children.size( ) > 1)
      {
        //Plus new branch
        d->_addBranchCount( ( unsigned int ) lines[id].children.size( ) );
        //Plus new bifurcation
        d->_addBifurcationCount(1);

        NSOL_CONST_FOREACH( it, lines[ id ].children )
        {
          TReadDendritesStackElem tmpStackElem = { (*it), s };
          ids.push( tmpStackElem );
        }
      }

    }

  }

  template < SWC_READER_TEMPLATE_CLASSES > void
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::_ReadAxon(
    NeuritePtr d,
    std::map<unsigned int,
    TSwcLine> &lines,
    unsigned int initId,
    NsolVector<NodePtr>* nodes_,
    bool reposition_ )
  {

    std::stack<TReadAxonStackElem> ids;
    TReadAxonStackElem tmp = { initId, NULL };
    ids.push(tmp);

    SectionPtr s = NULL, parentSection;
    bool first = true;

    while (!ids.empty( ))
    {

      unsigned int id = ids.top( ).id;
      parentSection = ids.top( ).parent;
      ids.pop( );

      /* parentSection = s; */
      s = SectionPtr( new SECTION );

      if (!d->firstSection( ))
        d->firstSection(s);  //->addSection( );

      s->neurite(d);
      s->parent(parentSection);

      NodePtr node;
      if (first)
      {
        node = new NODE(lines[id].xyz, id, lines[id].radius );
        s->firstNode( node );

        if ( reposition_ )
          nodes_->push_back( node );
        first = false;
      }
      else
      {
        node = new NODE(lines[id].xyz, id, lines[id].radius );
        s->addNode( node );

        if ( parentSection )
          parentSection->addChild( s );

        if ( reposition_ )
          nodes_->push_back( node );
      }

      // While same section create the segments
      while (lines[id].children.size( ) == 1)
      {

        id = lines[id].children[0];

        node = new NODE(lines[id].xyz, id, lines[id].radius);
        if ( reposition_ )
          nodes_->push_back( node );

        s->addNode( node );

      }

      // New branching point
      if (lines[id].children.size( ) > 1)
      {
        //Plus new branch
        d->_addBranchCount( ( unsigned int ) lines[id].children.size( ));
        //Plus new bifurcation
        d->_addBifurcationCount(1);

        NSOL_CONST_FOREACH( it, lines[ id ].children )
        {
          TReadAxonStackElem tmpStackElem = { (*it), s };
          ids.push( tmpStackElem );
        }
      }

    }

  }


}

#endif
