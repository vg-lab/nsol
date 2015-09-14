/**
 * @file    BBPSDKReader.h
 * @brief
 * @author  Ricardo Suarez <ricardo.suarez@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifdef NSOL_USE_BBPSDK

#ifndef __NSOL_BBPSDK_READER__
#define __NSOL_BBPSDK_READER__

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <stack>
#include <map>
#include <dirent.h>

#include "../NsolTypes.h"
#include "../Dendrite.h"
#include "../NeuronMorphology.h"
#include "SwcReader.h"

#include <BBP/BBP.h>

namespace nsol
{

  typedef struct
  {
    unsigned int id;
    std::string label;
    unsigned int column;
    unsigned int miniColumn;
    unsigned int layer;
    Vec3f position;
    Matrix4_4f globalTrans;
    Vec4f orientation;
    std::string morphoLabel;
  } TcsvFileLine;


#define BBPSDK_LOADER_TEMPLATE_CLASSES          \
    class NODE,                                 \
    class SECTION,                              \
    class DENDRITE,                             \
    class AXON,                                 \
    class SOMA,                                 \
    class NEURONMORPHOLOGY,                     \
    class NEURON,                               \
    class MINICOLUMN,                           \
    class COLUMN

#define BBPSDK_LOADER_TEMPLATE_CLASS_NAMES      \
    NODE,                                       \
    SECTION,                                    \
    DENDRITE,                                   \
    AXON,                                       \
    SOMA,                                       \
    NEURONMORPHOLOGY,                           \
    NEURON,                                     \
    MINICOLUMN,                                 \
    COLUMN

  template < BBPSDK_LOADER_TEMPLATE_CLASSES >
  class BBPSDKReaderTemplated
  {

  public:

    // const std::map<unsigned int, ColumnPtr> &
    // readExperiment(const char *inputFile,
    //                unsigned int directory = 0)
    // {
    //   if (directory)
    //     return this->readFromDirectory(std::string(inputFile));
    //   else
    //     return this->readFromBlueConfig(std::string(inputFile));
    // }

    // const std::map<unsigned int, ColumnPtr> &
    // readExperiment( const std::string inputFile,
    //                 unsigned int directory = 0)
    // {
    //   if (directory)
    //     return this->readFromDirectory(inputFile);
    //   else
    //     return this->readFromBlueConfig(inputFile);
    // }


    /**
     * Method to get the columns for BBPSDK experiment allocated in files
     * @param directory where the files are allocated
     * @return map with columns
     */
    void readFromDirectory( Columns& columns,
                            const std::string inputFile );

    /**
     * Method to get a columns for BBPSDK experiment allocated in memory
     * @param columns output morphology
     * @param inputFile blue config file to read
     * @param bbpTarget BBPSDK target to be used.
     *                  By default a new one is created
     * @param loadFlags Structures to be loaded. By default
     *                     nsol::MORPHOLOGY
     */
    void
    readFromBlueConfig( Columns& columns,
                        const std::string inputFile,
                        const int loadFlags = MORPHOLOGY | HIERARCHY,
                        const std::string& targetLabel = std::string( "" ));

    void deleteAll( Columns& columns )
    {
      std::set< NeuronMorphologyPtr > morphologies;

      NSOL_FOREACH( col, columns )
      {
        NSOL_FOREACH( miniCol, ( *col )->miniColumns( ))
        {
          NSOL_FOREACH( neuron, ( *miniCol )->neurons( ))
          {
            morphologies.insert(( *neuron )->morphology( ));
            delete *neuron;
          }
          delete *miniCol;
        }
        delete *col;
      }

      std::set< NodePtr > nodes;

      NSOL_FOREACH( morphology, morphologies )
      {
        NSOL_FOREACH( neurite, ( *morphology )->neurites( ))
        {
          Sections sections = ( *neurite )->sections( );
          NSOL_FOREACH( section, sections )
          {
            delete ( *section )->lastNode( );
            NSOL_FOREACH( node, (*section)->middleNodes( ))
            {
              delete *node;
            }
            delete *section;
          }
//          delete sections;
          delete *neurite;
        }
        delete ( *morphology )->soma( );
        delete *morphology;
      }
      return;
    }


  private:

    // Types of SWC nodes
    typedef enum
    {
      SWC_SOMA = 1,
      SWC_AXON = 2,
      SWC_DENDRITE = 3,
      SWC_APICAL = 4
    } TSwcNodeType;

    // protected:
    //   std::map<unsigned int, ColumnPtr> columnMap;


  };


  typedef BBPSDKReaderTemplated< Node,
                                 Section,
                                 Dendrite,
                                 Axon,
                                 Soma,
                                 NeuronMorphology,
                                 Neuron,
                                 MiniColumn,
                                 Column > BBPSDKReader;

//  typedef BBPSDKReaderTemplated< Node,
//                                 SectionStats,
//                                 DendriteStats,
//                                 AxonStats,
//                                 SomaStats,
//                                 NeuronMorphologyStats,
//                                 Neuron,
//                                 MiniColumnStats,
//                                 ColumnStats
//                                 > BBPSDKReaderStats;
//
//  typedef BBPSDKReaderTemplated< NodeCached,
//                                 SectionCachedStats,
//                                 DendriteCachedStats,
//                                 AxonCachedStats,
//                                 SomaStats,
//                                 NeuronMorphologyCachedStats,
//                                 Neuron,
//                                 MiniColumnStats,
//                                 ColumnStats
//                                 > BBPSDKReaderCachedStats;


  /**
   * Method to get a columns for BBPSDK experiment allocated in memory
   * @param inputFile blue config file to read
   * @return map with columns
   */
  template < BBPSDK_LOADER_TEMPLATE_CLASSES >
  //  std::map<unsigned int, ColumnPtr> &
  void
  BBPSDKReaderTemplated
  < BBPSDK_LOADER_TEMPLATE_CLASS_NAMES >::readFromBlueConfig(
    Columns& columns,
    const std::string inputFile,
    const int loadFlags,
    const std::string& targetLabel )
  {
    if ( loadFlags == 0 )
      return;

    std::map<unsigned int, ColumnPtr> columnMap;

    // Detect which flags must be passed to the bbpsdk loader
    int bbpDataTypes = 0;

    if ( loadFlags & HIERARCHY )
      bbpDataTypes |= ( bbp::NEURONS );

    if ( loadFlags & MORPHOLOGY )
      bbpDataTypes |= ( bbp::MORPHOLOGIES | bbp::NEURONS );

    // A bbpsdk experiment is opened
    bbp::Experiment experiment;
    // std::cerr << inputFile << ": Opening experiment " << std::endl;
    experiment.open(inputFile);
    // std::cerr << inputFile << ": DONE " << std::endl;

    if (!experiment.is_open()) {
      std::cerr << inputFile << ": Experiment could not be opened"
                << std::endl;
    }

    std::vector< NeuronPtr > neuronVector;
    std::map< std::string, NeuronMorphologyPtr > neuronMorphoMap;
    std::map< unsigned int, MiniColumnPtr > miniColumnMap;

    // The microcircuit of the experiment loads the data
    const bbp::Cell_Target& target =
      ( targetLabel == "" ) ? bbp::Cell_Target( ) :
      experiment.cell_target( targetLabel );

    bbp::Microcircuit & mcp = experiment.microcircuit();
    //bbp::Cell_Target target;

//    mcp.load( bbpTarget, bbpDataTypes );
    mcp.load( target, bbpDataTypes );

// target,
//              bbp::MICROCIRCUIT |
//              bbp::AFFERENT_SYNAPSES |
//              bbp::EFFERENT_SYNAPSES);

    const bbp::Neurons &neuronsExpe =
      experiment.microcircuit().neurons();

    // std::cerr << inputFile << ": Exporting " << neuronsExpe.size()
    //           << " neurons. " << std::endl;

    // for (bbp::Neurons::const_iterator it = neuronsExpe.begin();
    //      it != neuronsExpe.end(); ++it)

    unsigned long neuronCounter = 0;
    unsigned int oldPerc = 0;

    std::cout << "nsol: Loading neurons" << std::endl;

    NSOL_FOREACH( it, neuronsExpe )
    {
      // std::cerr << "Neuron " << it->label() << " with morphology "
      //          << it->morphology().label() << std::endl;

      NeuronPtr neuron (new NEURON( )); //New neuron
      neuronVector.push_back( neuron );

      bool miniColumnExist;

      // MiniColumn control
      if (miniColumnMap.find(it->minicolumn()) != miniColumnMap.end())
      {
        //MiniColumn exist
        neuron->miniColumn(miniColumnMap[it->minicolumn()]);
        miniColumnExist = true;
      }
      else
      {
        // MiniColumn does not exist

        miniColumnExist = false;
        miniColumnMap[it->minicolumn()] =
          MiniColumnPtr( new MINICOLUMN( nullptr,
                                         it->minicolumn()) );
        neuron->miniColumn(miniColumnMap[it->minicolumn()]);
      }

      // Column control
      if (columnMap.find(it->column()) != columnMap.end())
        // Column exist
        neuron->miniColumn()->column(columnMap[it->column()]);
      else
      {
        //Column does not exist
        columnMap[it->column()] = ColumnPtr(new COLUMN(it->column()));
        neuron->miniColumn()->column(columnMap[it->column()]);
      }

      //Add neuron to minicolumn
      miniColumnMap[it->minicolumn()]->addNeuron( neuron );

      //Add minicolumn to column
      if (!miniColumnExist)
        columnMap[it->column()]->addMiniColumn(
          miniColumnMap[it->minicolumn()]);

      neuron->layer() = it->layer();
      neuron->transform() = it->global_transform();
      neuron->gid() = it->gid();


      if( it->morphology_type( ).is_interneuron( ))
        neuron->neuronType( ) = Neuron::INTER;
      else if( it->morphology_type( ).is_pyramidal( ))
        neuron->neuronType( ) = Neuron::PYRAMIDAL;
      else
        neuron->neuronType( ) = Neuron::UNDEFINED;

      if ( loadFlags & MORPHOLOGY )
      {
        //Morphology previously loaded
        if (neuronMorphoMap.find(it->morphology().label()) !=
            neuronMorphoMap.end())
        {

          NeuronMorphologyPtr m =
            neuronMorphoMap.find(it->morphology().label())->second;

          neuron->morphology( m );
          m->addParentNeuron( neuron );

        }
        else
        {
          // std::cerr << "Loading morphology " << it->morphology().label()
          //           << std::endl;

          NeuronMorphologyPtr m ( new NEURONMORPHOLOGY ( new SOMA ));

          neuronMorphoMap[it->morphology().label()] = m;

          neuron->morphology(m);
          m->addParentNeuron( neuron );

          unsigned int id = 1;

          //Getting morphology of the neuron
          const bbp::Morphology &morphology = it->morphology();
          //Getting soma of the morphology
          const bbp::Soma &soma = morphology.soma();
          //Writing soma
          // for (bbp::Soma::const_iterator nodeIt = soma.begin();
          //      nodeIt != soma.end(); ++nodeIt)
          NSOL_FOREACH( nodeIt, soma )
          {

            m->soma()->addNode(NodePtr(
                                 new NODE( Vec3f( ( * nodeIt)[0],
                                                  ( * nodeIt)[1],
                                                  ( * nodeIt)[2] ),
                                           id, soma.mean_radius( ))));

            id++;
          }

          const bbp::Sections &somas = morphology.somas();
          //Writing neurites
          // for (bbp::Sections::const_iterator sectionIt = somas.begin();
          //      sectionIt != somas.end(); sectionIt++)
          NSOL_FOREACH( sectionIt, somas )
          {

            bbp::Sections children = ( * sectionIt ).children();

            // for ( bbp::Sections::iterator cit = children.begin( );
            //       cit != children.end( ); cit++)
            NSOL_FOREACH( cit, children )
            {
              DendritePtr dendrite = nullptr;
              NeuritePtr neurite = nullptr;

              if ((*cit).type() == bbp::SECTION_AXON)
              {
                neurite = new AXON( );
                m->addNeurite( neurite );
              }
              else if ((*cit).type() == bbp::SECTION_DENDRITE)
              {
                dendrite = new DENDRITE( Dendrite::BASAL );
                m->addNeurite( dendrite);
              }
              else if ((*cit).type() == bbp::SECTION_APICAL_DENDRITE)
              {
                dendrite = new DENDRITE( Dendrite::APICAL );
                m->addNeurite( dendrite );
              }

              const bbp::Section * bbpSection = &(*cit);
              std::stack<const bbp::Section *> sPS;
              sPS.push(bbpSection);
              std::stack<SectionPtr> parents;
              parents.push(nullptr);
              bool first = true;

              while (!sPS.empty())
              {
                const bbp::Section *lS = sPS.top();
                sPS.pop();
                SectionPtr parentSection = parents.top();
                parents.pop();

                SectionPtr section ( new SECTION );
                if ( dendrite )
                {
                  if ( ! dendrite->firstSection( ))
                    dendrite->firstSection( section );

                  section->neurite( dendrite);
                }
                else
                {
                  if ( ! neurite->firstSection( ))
                    neurite->firstSection( section );

                  section->neurite( neurite );
                }

                section->parent( parentSection );
//                SegmentPtr segment = section->addSegment( new SEGMENT );
//                segment->parentSection( section );

                const bbp::Cross_Sections & cross_Sections =
                  lS->cross_sections();

                bbp::Cross_Sections::const_iterator crossSectionIt =
                  cross_Sections.begin();

                if (first)
                {
                  //TODO: select correct initial soma point
                  section->firstNode( new NODE(
                             Vec3f( crossSectionIt->center()[0],
                                    crossSectionIt->center()[1],
                                    crossSectionIt->center()[2] ),
                             id, crossSectionIt->radius( )));
                  first = false;
                }

                if (parentSection)
                  parentSection->addChild( section );

                crossSectionIt++;

                for ( bbp::Cross_Sections::const_iterator itL =
                        crossSectionIt; itL != cross_Sections.end();
                      ++itL )
                {
                  section->addNode( new NODE( Vec3f( itL->center()[0],
                                                     itL->center()[1],
                                                     itL->center()[2]),
                                              id, itL->radius( )));
                }
                // for (bbp::Sections::const_iterator child =
                //        lS->children().begin();
                //      child != lS->children().end(); ++child)
                NSOL_FOREACH( child, lS->children( ))
                {
                  sPS.push( & ( * child ) );
                  parents.push( section );
                }
              } // while not stack empty
            } // for all soma section childs
          } // for all soma sections
        } // morphology not previously loaded
      } // loadFlags & MORPHOLOGY

      unsigned int perc = 100 * ( neuronCounter + 1 ) / neuronsExpe.size( );


      if ( perc > oldPerc )
      {
        std::cout << "\r" "nsol::BBPSDKReader("
                  << perc
                  << "%) Loading Neuron " << neuronCounter;
      }
      oldPerc = perc;

      neuronCounter++;

    }

    // close experiment and free its resources
    experiment.close( );

    NSOL_FOREACH( column, columnMap )
      columns.push_back( column->second );


    std::cout << std::endl;

    return;

  }

  template < BBPSDK_LOADER_TEMPLATE_CLASSES >
  void
  BBPSDKReaderTemplated
  < BBPSDK_LOADER_TEMPLATE_CLASS_NAMES >::readFromDirectory(
    Columns& columns,
    const std::string inputFile)
  {

    std::map<unsigned int, ColumnPtr> columnMap;

    SwcReader r;
    bool findCsv = false;

    std::vector<NeuronPtr> neuronVector;
    std::map<std::string, NeuronMorphologyPtr> neuronMorphoMap;
    std::map<unsigned int, MiniColumnPtr> miniColumnMap;

    DIR *pDIR;
    struct dirent *entry;
    if ((pDIR = opendir(inputFile.c_str()))) {
      std::string dir(inputFile.c_str());

      while ((entry = readdir(pDIR))) {
        std::string str(entry->d_name);
        unsigned found = str.find_last_of(".");

        //Load neuron file
        if (strcmp(entry->d_name, ".") != 0
            && strcmp(entry->d_name, "..") != 0
            && str.substr(found + 1) == "csv") {

          findCsv = true;
          // std::cerr << "\nLoading neuron file " << entry->d_name << std::endl;

          std::ifstream inFile;
          inFile.open(dir + entry->d_name, std::ios::in);

          //Opening file checking
          if ((inFile.rdstate() & std::ifstream::failbit) != 0) {
            std::cerr << "Error opening file " << entry->d_name
                      << std::endl;
            inFile.close();

            continue;
          }

          std::string line;
          std::getline(inFile, line);

          //Reading csv file with each neuron
          while (std::getline(inFile, line)) {

            // TODO: this does not cover the case the # char is not the first char
            if (line[0] != '#') {
              std::istringstream iss(line);
              std::string comma;
              TcsvFileLine csvLine;

              iss >> csvLine.id;
              getline(iss, comma, ',');
//          iss >> csvLine.label;
              getline(iss, csvLine.label, ',');
              iss >> csvLine.column;
              getline(iss, comma, ',');
              iss >> csvLine.miniColumn;
              getline(iss, comma, ',');
              iss >> csvLine.layer;
              getline(iss, comma, ',');
              iss >> csvLine.position[0];
              getline(iss, comma, ',');
              iss >> csvLine.position[1];
              getline(iss, comma, ',');
              iss >> csvLine.position[2];
              getline(iss, comma, ',');

//TODO:column order, why?
              iss >> csvLine.globalTrans[0][0];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[1][0];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[2][0];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[3][0];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[0][1];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[1][1];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[2][1];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[3][1];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[0][2];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[1][2];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[2][2];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[3][2];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[0][3];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[1][3];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[2][3];
              getline(iss, comma, ',');
              iss >> csvLine.globalTrans[3][3];
              getline(iss, comma, ',');
              iss >> csvLine.orientation[0];
              getline(iss, comma, ',');
              iss >> csvLine.orientation[1];
              getline(iss, comma, ',');
              iss >> csvLine.orientation[2];
              getline(iss, comma, ',');
              iss >> csvLine.orientation[3];
              getline(iss, comma, ',');
//          iss >> csvLine.morphoLabel;
              getline(iss, csvLine.morphoLabel, ',');

              std::cerr << "Neuron " << csvLine.label
                        << " with morphology "
                        << csvLine.morphoLabel << std::endl;

              NeuronPtr neuron ( new NEURON( ));//New neuron
              neuronVector.push_back( neuron );

              bool miniColumnExist;

//MiniColumn control
              if (miniColumnMap.find(csvLine.miniColumn)
                  != miniColumnMap.end())//MiniColumn exist
              {
                neuron->miniColumn(
                  miniColumnMap[csvLine.miniColumn]);
                miniColumnExist = true;
              }
              else
                //MiniColumn not exist
              {
                miniColumnExist = false;
                miniColumnMap[csvLine.miniColumn] =
                  MiniColumnPtr( new MINICOLUMN( nullptr,
                                                 csvLine.miniColumn ));
                neuron->miniColumn(
                  miniColumnMap[csvLine.miniColumn]);
              }

//Column control
              if (columnMap.find(csvLine.column)
                  != columnMap.end())
                //Column exist
                neuron->miniColumn()->column(
                  columnMap[csvLine.column]);
              else
                //Column not exist
              {
                columnMap[csvLine.column] =
                  ColumnPtr ( new COLUMN( csvLine.column ));
                neuron->miniColumn()->column(
                  columnMap[csvLine.column]);
              }

              //Add neuron to minicolumn
              miniColumnMap[csvLine.miniColumn]->addNeuron(neuron);

              if (!miniColumnExist)
                //Add minicolumn to column
                columnMap[csvLine.column]->addMiniColumn(
                  miniColumnMap[csvLine.miniColumn]);

              //Morphology previously loaded
              if (neuronMorphoMap.find(csvLine.morphoLabel)
                  != neuronMorphoMap.end()) {
                std::cerr << "Morphology file previously loaded"
                          << std::endl;
                neuron->morphology(
                  neuronMorphoMap.find(csvLine.morphoLabel)->second);
                neuron->layer() = csvLine.layer;
                neuron->transform() = csvLine.globalTrans;
                neuron->gid() = csvLine.id;
              } else
              {
                std::cerr << "Loading morphology file "
                          << csvLine.morphoLabel << ".swc"
                          << std::endl;
                NeuronMorphologyPtr m = r.readMorphology(
                  dir + csvLine.morphoLabel + ".swc");

                if (!m)
                {
                  std::cerr << "\nError opening morphology file "
                            << csvLine.morphoLabel << std::endl;
                  continue;
                }

                neuronMorphoMap[csvLine.morphoLabel] = m;
                neuron->morphology(m);
                neuron->layer() = csvLine.layer;
                neuron->transform() = csvLine.globalTrans;
                neuron->gid() = csvLine.id;
              }
            }
          }

          inFile.close();
        }
      }

      closedir(pDIR);
    }

    if (!findCsv)
      std::cerr << "Neuron file not found." << std::endl;

    NSOL_FOREACH( column, columnMap )
      columns.push_back( column->second );

    return;
  }



} // namespace nsol

#endif // NSOL_USE_BBPSDK
#endif // __NSOL_BBPSDK_READER__
