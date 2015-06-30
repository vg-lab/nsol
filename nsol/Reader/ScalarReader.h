/**
 * @file    ScalarReader.h
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 * Do not distribute without further notice.
 */
#ifndef __NSOL_SCALAR_READER__
#define __NSOL_SCALAR_READER__

#include <nsol/NeuronMorphology.h>
#include <nsol/NsolTypes.h>

#include <map>

namespace nsol
{
  class ScalarReader
  {
  
  public:

    void readScalarFile( const char *fileName, NeuronMorphologyPtr morphology )
    {
      return this->readScalarFile( std::string( fileName ), morphology );
    }

    void readScalarFile( std::string fileName, NeuronMorphologyPtr morphology )
    {
      if ( !morphology )
      {
        std::cerr << "Error: No NeuronMorphology found" << std::endl;
      }

      std::map<unsigned int, NodePtr> neuronMap;
      std::map<unsigned int, float> fileMap;

      std::ifstream is;
      is.open( fileName, std::ios::in );

      // Opening file checking
      if ( ( is.rdstate() & std::ifstream::failbit ) != 0)
      {
        std::cerr << "Error opening file " << is << std::endl;

        return;
      }

      // Store in fileMap every node in the file
      unsigned int id;
      float relevance;
      while( !is.eof() )
      {
        is >> id >> relevance;

        fileMap[ id ] = relevance;
      } // while

      is.close();

      // Store in neuronMap every node in morphology
      for ( NsolVector<NodePtr>::iterator it =
             morphology->soma()->nodes().begin();
             it != morphology->soma()->nodes().end(); ++it)
      {
        ScalarLabeledNodePtr sNode = NSOL_DYNAMIC_CAST( ScalarLabeledNode, *it );

        neuronMap[ sNode->id() ] = sNode;
      }

      Neurites neurites = morphology->neurites();

      // Iterate over the neurites
      for ( Neurites::iterator it = neurites.begin();
           it != neurites.end(); ++it )
      {
        SectionPtr fSection = ( *it )->firstSection();

        std::deque<SectionPtr> sPS;
        sPS.push_back( fSection );

        while ( !sPS.empty( ) )
        {
          SectionPtr lS = sPS.front();
          sPS.pop_front();

          SegmentPtr segment = lS->firstSegment();
          while( segment )
          {
            ScalarLabeledNodePtr sAux = NSOL_DYNAMIC_CAST( ScalarLabeledNode
                                                , segment->end() );

            neuronMap[ segment->end()->id() ] = sAux;

            segment = segment->next();
          }

          if ( lS->children().size() > 0 )
            for ( unsigned int i = 0; i < lS->children().size(); ++i )
              sPS.push_back( lS->children()[ i ] );

        } // while 
      } // for

      if ( neuronMap.size() != fileMap.size() )
      {
        NSOL_THROW( "Warning: '" 
          + fileName 
          + "' does not correspond to the morphology received" );

        return;

      } else {

        // Iterate over the fileMap in order to initialize the relevance of each node of neuronMap
        for ( std::map<unsigned int, float>::const_iterator it = fileMap.begin();
              it != fileMap.end(); ++it )
        {        
          ScalarLabeledNodePtr sNode = NSOL_DYNAMIC_CAST( ScalarLabeledNode
                                            , neuronMap[ (*it).first ] );

          sNode->relevance( (*it).second );
        }
      } // else

    } // readScalarFile

  };
}

#endif

// EOF
