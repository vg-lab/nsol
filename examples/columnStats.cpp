/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
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


#include <nsol/nsol.h>
#include <../tests/testData.h>

using namespace nsol;

int main (  )
{
   DataSet ds;
   ds.loadXmlScene( NSOL_XML_SCENE_TEST_DATA );

   Columns columns = ds.columns();

   std::cout << "Num Columns = "<< columns.size() << std::endl;

   if( columns.size() == 0 )
   {
       std::cerr << "Columns data is empty" << std::endl;
       return -1;
   }

    std::vector<Column*> columnsStats;
   for( ColumnPtr col : columns )
   {
      ColumnStats* columnStat = new ColumnStats( col->id() );

      for( MiniColumnPtr miniCol : col->miniColumns() )
      {
         MiniColumnStats* miniColumnStat = new MiniColumnStats( col, miniCol->id() );

         for( NeuronPtr neuron : miniCol->neurons() )
         {
            NeuronMorphologyPtr nm = neuron->morphology();

            SomaPtr soma = nm->soma();
//            SomaStats* somaStats = new SomaStats( );

//            for(NodePtr node : soma->nodes() )
//            {
//               somaStats->addNode( node );
//            }

//            NeuronMorphologyStats* nmStats = new NeuronMorphologyStats( somaStats );
//            nmStats->soma( somaStats );

            NeuronMorphologyStats* nmStats = new NeuronMorphologyStats( soma );

            for( NeuritePtr neurite : nm->neurites() )
            {
               NeuriteStats* neuriteStat = neurite->stats();
               neuriteStat = new NeuriteStats( neurite->neuriteType());

               // << First section of the neurite
               SectionPtr    firstSection     = neurite->firstSection();
               SectionStats* firstSectionStat = firstSection->stats();

               firstSectionStat = new SectionStats();

               for( NodePtr node : firstSection->nodes())
               {
                  firstSectionStat->addNode( node );
               }

               neuriteStat->firstSection( firstSectionStat );

               // >>

               std::vector<SectionStats*> childrenSectionStats;
               Sections sections = firstSection->children();

               for( unsigned int i = 0; i < sections.size( ); ++i )
               {
                  SectionPtr    section     = sections.at(i);
                  SectionStats* sectionStat = section->stats();

                  sectionStat = new SectionStats();

                  for( NodePtr node : section->nodes())
                  {
                     sectionStat->addNode( node );
                  }

                  firstSectionStat->addChild( sectionStat );

                  childrenSectionStats.push_back( sectionStat );
               }

               for( unsigned int i = 0; i < childrenSectionStats.size(); ++i )
               {
                  SectionStats* parentSectionStat = childrenSectionStats.at(i);

                  for( unsigned int j = i+1; j < childrenSectionStats.size(); ++j )
                  {
                     SectionStats* childSectionStat = childrenSectionStats.at(j);

                     parentSectionStat->addChild( childSectionStat );
                  }
               }
               // Sections

               nmStats->addNeurite( neuriteStat );

            } // Neurites

            neuron->morphology( nmStats );

            miniColumnStat->addNeuron( neuron );

         } // Neurons

         columnStat->addMiniColumn( miniColumnStat );

      } // Minicolumns

      columnsStats.push_back( columnStat );
   } // Columns

   ColumnPtr column = columnsStats.at(0);
   std::cout << "IS NULL? = " << (column->stats() == nullptr) << std::endl;

   for( ColumnPtr col : columnsStats )
   {
      float maxVolume = col->stats()->getStat( ColumnStats::NEURITIC_VOLUME,
                                                  MAX, MAX );
      float maxSurface = col->stats()->getStat( ColumnStats::NEURITIC_SURFACE,
                                                  MAX, MAX );

      float minVolume = col->stats()->getStat( ColumnStats::NEURITIC_VOLUME,
                                                  MIN, MIN );
      float minSurface = col->stats()->getStat( ColumnStats::NEURITIC_SURFACE,
                                                  MIN, MIN );

      float maxVariance = col->stats()->getStat( ColumnStats::NEURITIC_SURFACE,
                                                  VARIANCE, MAX );
      float minVariance = col->stats()->getStat( ColumnStats::NEURITIC_SURFACE,
                                                  VARIANCE, MIN );

      std::cout << col->id() << ") Column" << std::endl;
      std::cout << "Neuritic Surface - Maximun Variance = "<< maxVariance << std::endl;
      std::cout << "Neuritic Surface - Minimun Variance = "<< minVariance << std::endl;

      std::cout << "Neuritic  Volume - Maximun = "<< maxVolume << std::endl;
      std::cout << "Neuritic Surface - Maximun = "<< maxSurface << std::endl;

      std::cout << "Neuritic  Volume - Minimun = "<< minVolume << std::endl;
      std::cout << "Neuritic Surface - Minimun = "<< minSurface << std::endl;

      std::cout << std::endl;
   }

   return 0;

}
