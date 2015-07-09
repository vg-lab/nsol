/**
 * @file    ScalarWriter.h
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 * Do not distribute without further notice.
 */
#ifndef __NSOL_SCALAR_WRITER__
#define __NSOL_SCALAR_WRITER__

#include <nsol/NeuronMorphology.h>
#include <nsol/NsolTypes.h>

#include <deque>

namespace nsol
{

  class ScalarWriter
  {

  public:

    typedef struct
    {
      unsigned int id;
      float tolerance; 
    } TSwcLine;
  
    void writeFile( const char *fileName, NeuronMorphologyPtr morphology )
    {
      return this->writeFile( std::string( fileName ), morphology );
    }

    /*
     * Method which writes a .tol file with every tolerance correspoding to every node of 
     * the Neuronmorphology received as parameter
     */
    void writeFile( const std::string& fileName, NeuronMorphologyPtr morphology )
    {
      if ( !morphology )
      {
        std::cerr << "Error: No NeuronMorphology found" << std::endl;
      }

      std::ofstream outFile;
      outFile.open( fileName, std::ios::out );

      // Opening file checking
      if ( ( outFile.rdstate() & std::ofstream::failbit ) != 0 )
      {
        std::cerr << "Error opening file " << fileName << std::endl;
      }

      // Writing soma
      for ( NsolVector<NodePtr>::iterator it =
             morphology->soma()->nodes().begin();
             it != morphology->soma()->nodes().end(); ++it)
      {
        ScalarLabeledNodePtr sNode = NSOL_DYNAMIC_CAST( ScalarLabeledNode, *it );

        outFile << " "
                << sNode->id()
                << " "
                << sNode->relevance()
                << std::endl;
      }

      Neurites neurites = morphology->neurites();

      // Writing neurites
      for ( Neurites::iterator it = neurites.begin();
           it != neurites.end(); ++it )
      {
        SectionPtr fSection = ( *it )->firstSection();

        std::deque<SectionPtr> sPS;
        sPS.push_back( fSection );

        std::map<unsigned int, NodePtr> nodePtrMap;

        while ( !sPS.empty( ) )
        {
          SectionPtr lS = sPS.front();
          sPS.pop_front();

          SegmentPtr segment = lS->firstSegment();
          while( segment )
          {
            ScalarLabeledNodePtr sAux = NSOL_DYNAMIC_CAST( ScalarLabeledNode
                                                  , segment->end() );

            nodePtrMap[ segment->end()->id() ] = sAux;

            segment = segment->next();
          }

          if ( lS->children().size() > 0 )
            for ( unsigned int i = 0; i < lS->children().size(); ++i )
              sPS.push_back( lS->children()[ i ] );
        }

        for (std::map<unsigned int, NodePtr>::iterator nodeIt =
               nodePtrMap.begin(); nodeIt != nodePtrMap.end(); ++nodeIt)
        {
          ScalarLabeledNodePtr sNode = NSOL_DYNAMIC_CAST( ScalarLabeledNode
                                                , (*nodeIt).second );

          outFile << " "
                  << sNode->id()
                  << " "
                  << sNode->relevance()
                  << std::endl;
        }

      }

     outFile.close();

    } // writeFile

  };
}

#endif

// EOF