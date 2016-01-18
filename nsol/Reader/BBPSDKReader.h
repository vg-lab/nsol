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

#define TESTING_SYNAPSES
#define TESTING_PROPERTIES_SYNAPSE
#define CALCULATE_SYNAPSE_TYPE

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <stack>
#include <map>
#include <set>
#include <dirent.h>
#include <math.h>

#include "../NsolTypes.h"
#include "../Dendrite.h"
#include "../NeuronMorphology.h"
#include "../Synapse.h"
#include "../SynapseNeuriteToNeurite.h"
#include "../SynapseNeuriteToSoma.h"
#include "../SynapseSomaToSoma.h"
#include "../Circuit.h"

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
     * Method to get morphology, simulation and/or circuit data for BBPSDK
     * experiment allocated in memory
     * @param inputFile blue config file to read
     * @param loadFlags Structures to be loaded. By default
     *                     nsol::MORPHOLOGY
     * @param bbpTarget BBPSDK target to be used.
     *                  By default a new one is created
     * @param id_circuit to id of the circuit.
     */
    void
    readFromBlueConfig( Columns& columns, Circuit& circuit,
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

  typedef BBPSDKReaderTemplated< Node,
                                 SectionStats,
                                 DendriteStats,
                                 AxonStats,
                                 SomaStats,
                                 NeuronMorphologyStats,
                                 Neuron,
                                 MiniColumnStats,
                                 ColumnStats
                                 > BBPSDKReaderStats;

  typedef BBPSDKReaderTemplated< NodeCached,
                                 SectionCachedStats,
                                 DendriteCachedStats,
                                 AxonCachedStats,
                                 SomaStats,
                                 NeuronMorphologyCachedStats,
                                 Neuron,
                                 MiniColumnStats,
                                 ColumnStats
                                 > BBPSDKReaderCachedStats;

  /**
   * Method to get morphology, simulation and/or circuit data for BBPSDK
   * experiment allocated in memory
   * @param inputFile blue config file to read
   * @return map with columns
   */
  template < BBPSDK_LOADER_TEMPLATE_CLASSES >
  //  std::map<unsigned int, ColumnPtr> &
  void
  BBPSDKReaderTemplated
  < BBPSDK_LOADER_TEMPLATE_CLASS_NAMES >::readFromBlueConfig(
    Columns& columns, Circuit& circuit,
    const std::string inputFile,
    const int loadFlags,
    const std::string& targetLabel )
  {
    if ( loadFlags == 0 )
      return;

    // Detect which flags must be passed to the bbpsdk loader
    int bbpDataTypes = 0;
    if ( loadFlags & HIERARCHY )
      bbpDataTypes |= ( bbp::NEURONS );
    if ( loadFlags & MORPHOLOGY )
      bbpDataTypes |= ( bbp::MORPHOLOGIES | bbp::NEURONS );
    if( loadFlags | CIRCUIT)
      bbpDataTypes |= (bbp::MICROCIRCUIT      | bbp::SYNAPSES|
                       bbp::AFFERENT_SYNAPSES | bbp::EFFERENT_SYNAPSES);

    // A bbpsdk experiment is opened
    bbp::Experiment experiment;
    //std::cerr << inputFile << ": Opening experiment " << std::endl;
    experiment.open(inputFile);
    //std::cerr << inputFile << ": DONE " << std::endl;

    if (!experiment.is_open()) {
      std::cerr << inputFile << ": Experiment could not be opened"
                << std::endl;
      return;
    }

    // Morphology data structures
    //std::vector< NeuronPtr > neuronVector;
    std::map< unsigned int, ColumnPtr> columnMap;
    std::map< unsigned int, MiniColumnPtr > miniColumnMap;
    std::map< const bbp::Neuron*, NeuronPtr > neuronMap;
    std::map< std::string, NeuronMorphologyPtr > neuronMorphoMap;

    // The microcircuit of the experiment loads the data
    const bbp::Cell_Target& target =
      ( targetLabel == "" ) ? bbp::Cell_Target( ) :
      experiment.cell_target( targetLabel );

    bbp::Microcircuit & mcp = experiment.microcircuit();
    //bbp::Cell_Target target;

    //    mcp.load( bbpTarget, bbpDataTypes );
    mcp.load( target, bbpDataTypes );

    const bbp::Neurons &neuronsExpe = experiment.microcircuit().neurons();

    //std::cerr << inputFile << ": Exporting " << neuronsExpe.size()
    //                   << " neurons. " << std::endl;

    unsigned long neuronCounter = 0;
    unsigned int oldPerc = 0;

    std::cout << "nsol: Loading neurons" << std::endl;


    /**
     * In this case we have to use a constant iterator because
     * we create a map with a constant bbp::Neuron object pointer as
     * a key.
     */
    for (bbp::Neurons::const_iterator it = neuronsExpe.begin();
         it != neuronsExpe.end(); ++it)
      //NSOL_FOREACH( it, neuronsExpe )
    {
      //std::cerr << "Neuron " << it->label() << " with morphology "
      //           << it->morphology().label() << std::endl;

      NeuronPtr neuron (new NEURON( )); //New neuron
      const bbp::Neuron* bbpNeuron = &(*it);
      //neuronVector.push_back( neuron );
      neuronMap.insert        (std::pair<const bbp::Neuron*, NeuronPtr>
                               (bbpNeuron, neuron));

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

      if( it->type( ).is_interneuron( ))
        neuron->morphologicalType( ) = Neuron::INTERNEURON;
      else if( it->type( ).is_pyramidal( ))
        neuron->morphologicalType( ) = Neuron::PYRAMIDAL;
      else
        neuron->morphologicalType( ) = Neuron::UNDEFINED;

      if ( it->type( ).is_inhibitory( ))
        neuron->functionalType( ) = Neuron::INHIBITORY;
      else if ( it->type( ).is_excitatory( ))
        neuron->functionalType( ) = Neuron::EXCITATORY;
      else
        neuron->functionalType( ) = Neuron::UNDEFINED_FUNCTIONAL_TYPE;

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
          //                   << std::endl;

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

                SectionPtr section ( new SECTION ());
                section->_id = lS->id();
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
                  crossSectionIt ++;
                  id ++;
                }

                if (parentSection)
                  parentSection->addChild( section );


                for ( bbp::Cross_Sections::const_iterator itL =
                        crossSectionIt; itL != cross_Sections.end();
                      ++itL )
                {
                  section->addNode( new NODE( Vec3f( itL->center()[0],
                                                     itL->center()[1],
                                                     itL->center()[2]),
                                              id, itL->radius( )));
                  id ++;
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
      }

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

    NSOL_FOREACH( column, columnMap )
      columns.push_back( column->second );

    //              << Treatment Circuit Data >>                //
    if(loadFlags | CIRCUIT)
    {
      std::cout << ": Loading Circuit Data ... " << std::endl;

      unsigned short id = 1; // ID Synapse
      for (bbp::Neurons::const_iterator it = neuronsExpe.begin();
           it != neuronsExpe.end(); ++it)
      {
        const bbp::Neuron* bbpNeuron = &(*it);
        // number of neurons it is the same that afferent synapses
        const bbp::Synapses &synapsesExpe = bbpNeuron->afferent_synapses();

        for (bbp::Synapses::const_iterator synapseIt = synapsesExpe.begin();
             synapseIt != synapsesExpe.end(); ++synapseIt)
        {
          nsol::SynapsePtr afferent_synapse = new nsol::Synapse(
                                                    Synapse::UNDEFINED, id );

          const bbp::Synapse bbpSynapse = (*synapseIt);
          const bbp::Neuron* bbpPreSynNeuron =
            &(bbpSynapse.presynaptic_neuron());
          const bbp::Neuron* bbpPostSynNeuron =
            &(bbpSynapse.postsynaptic_neuron());

          Vec3f bbpPreSynPos  = bbpSynapse.preSynapticSurfacePosition();
          Vec3f bbpPostSynPos = bbpSynapse.postSynapticSurfacePosition();

#if 0 TESTING_PROPERTIES_SYNAPSE
          std::cout << "Synapse Index " <<
            bbpSynapse.index() << std::endl;
          std::cout << "PreSynaptic Neuron GID " <<
            bbpSynapse.presynaptic_neuron_gid() << std::endl;
          std::cout << "PostSynaptic Neuron GID " <<
            bbpSynapse.postsynaptic_neuron_gid() << std::endl;
          std::cout << std::endl;
          std::cout << std::endl;
#endif
#if 0 TESTING_PROPERTIES_SYNAPSE
          std::cout << "PreSynaptic Section ID " <<
            bbpSynapse.presynaptic_section_id()<< std::endl;
          std::cout << "PostSynaptic Section ID " <<
            bbpSynapse.postsynaptic_section_id()<< std::endl;
          std::cout << "PreSynaptic Segment ID " <<
            bbpSynapse.presynaptic_segment_id()<< std::endl;
          std::cout << "PostSynaptic Segment ID " <<
            bbpSynapse.postsynaptic_segment_id()<< std::endl;
          std::cout << "PreSynaptic Segment Distance " <<
            bbpSynapse.presynaptic_segment_distance() << std::endl;
          std::cout << "PostSynaptic Segment Distance " <<
            bbpSynapse.postsynaptic_segment_distance()<< std::endl;
          std::cout << std::endl;
          std::cout << std::endl;
#endif

          std::map< const bbp::Neuron*, NeuronPtr >::iterator nitPre =
            neuronMap.find( bbpPreSynNeuron );
          std::map< const bbp::Neuron*, NeuronPtr >::iterator nitPost=
            neuronMap.find( bbpPostSynNeuron );

          nsol::NeuronPtr nsolPreSynNeuron  = nullptr;
          nsol::NeuronPtr nsolPostSynNeuron = nullptr;

          if (( nitPre  != neuronMap.end( ))&&
              ( nitPost != neuronMap.end( )))
          {
            // New Synapse
            nsolPreSynNeuron  = nitPre->second;
            nsolPostSynNeuron = nitPost->second;

            // *** Treatment of synapse type:
            // Computing synaptic-sections:
            // To pre-synaptic section...
            bool isPreDentrite, isPreAxon, isPreSoma;
            isPreDentrite = isPreAxon = false;
            isPreSoma = true;

            bool found = false;

            nsol::SectionPtr nsolPreSynSection = nullptr;
            unsigned int bbp_id_section = bbpSynapse.presynaptic_section_id();
//            std::cout <<" [PRE SECTION]:"
//                      <<"\n bbp_id_section= "<< bbp_id_section << std::endl;

            nsol::Neurites neuritesPre = nsolPreSynNeuron->morphology()->neurites();
            NSOL_FOREACH( neuriteIt, neuritesPre )
            {
                // if bbp_id_section == 0 then is pre-soma and there are not pre-section
                if( found || (bbp_id_section == 0)) break;

                const nsol::NeuritePtr neurite = (*neuriteIt);
                nsol::Sections sections = neurite->sections();

                NSOL_FOREACH( sectionIt, sections )
                {
                    const nsol::SectionPtr section = (*sectionIt);

                    if( section->_id == bbp_id_section )
                    {
//                        std::cout <<" BBP ID= "<< bbp_id_section
//                                  <<"\n NSOL ID= "<< section->_id << std::endl;

                        found = true;
                        nsolPreSynSection = section;

                        switch(neurite->neuriteType())
                        {
                            case Neurite::DENDRITE:  isPreDentrite = true;
                                                     isPreSoma = false;
                            break;
                            case Neurite::AXON: isPreAxon = true;
                                                isPreSoma = false;
                            break;
                            default: break;
                        }
                        break;
                    }
                }// for all sections of one neurite
            }// for all neurites

            // To post-synaptic section...
            bool isPostDentrite, isPostAxon, isPostSoma;
            isPostDentrite = isPostAxon = false;
            isPostSoma = true;

            found = false;

            nsol::SectionPtr nsolPostSynSection = nullptr;
            bbp_id_section = bbpSynapse.postsynaptic_section_id();
//            std::cout <<" [POST SECTION]:"
//                      <<"\n bbp_id_section= "<< bbp_id_section << std::endl;

            nsol::Neurites neuritesPost = nsolPostSynNeuron->morphology()->neurites();
            NSOL_FOREACH( neuriteIt, neuritesPost )
            {
                // if bbp_id_section == 0 then is post-soma and there are not post-section
                if( found || (bbp_id_section == 0)) break;

                const nsol::NeuritePtr neurite = (*neuriteIt);
                nsol::Sections sections = neurite->sections();

                NSOL_FOREACH( sectionIt, sections )
                {
                    const nsol::SectionPtr section = (*sectionIt);

                    if( section->_id == bbp_id_section )
                    {
//                        std::cout <<" BBP ID= "<< bbp_id_section
//                                  <<"\n NSOL ID= "<< section->_id << std::endl;

                        found = true;
                        nsolPostSynSection = section;

                        switch(neurite->neuriteType())
                        {
                            case Neurite::DENDRITE:  isPostDentrite = true;
                                                     isPostSoma = false;
                            break;
                            case Neurite::AXON: isPostAxon = true;
                                                isPostSoma = false;
                            break;
                            default: break;
                        }
                        break;
                    }
                }// for all sections of one neurite
            }// for all neurites

            // Computing synaptic-nodes:
            // To pre-synaptic node...
            nsol::NodePtr nsolPreSynNode = nullptr;
            nsol::Nodes nodesPre = nsolPreSynNeuron->morphology()
                                                   ->soma()->nodes();
            if(nsolPreSynSection != nullptr)
            {
                nodesPre = nsolPreSynSection->middleNodes();
                nodesPre.push_back(nsolPreSynSection->firstNode());
                nodesPre.push_back(nsolPreSynSection->lastNode());
            }

            Vec3f bbpPreSynCenterPos  = bbpSynapse.presynaptic_position();
            float distance = 10000000;
            NSOL_FOREACH( nodeIt, nodesPre )
            {
                const nsol::NodePtr node = (*nodeIt);
                Vec3f posNode = node->point();
                Vec3f p_ = bbpPreSynCenterPos;
                float distActual = std::sqrt(pow((p_.x()-posNode.x()), 2)+
                                             pow((p_.y()-posNode.y()), 2)+
                                             pow((p_.z()-posNode.z()), 2));
                if(distActual < distance)
                {
                    distance = distActual;
                    nsolPreSynNode = node;
                }
            }

//            std::cout <<" [PRE NODE]:"<<
//                        "\n bbpPreSynCenterPos= "<< bbpPreSynCenterPos <<
//                        "\n Distance= "<< distance <<
//                        "\n Ref node= " << nsolPreSynNode <<
//                        "\n Pos node= " << nsolPreSynNode->point() << std::endl;

            // To post-synaptic node...
            nsol::NodePtr nsolPostSynNode = nullptr;
            nsol::Nodes nodesPost = nsolPostSynNeuron->morphology()
                                                     ->soma()->nodes();
            if(nsolPostSynSection != nullptr)
            {
                nodesPost = nsolPostSynSection->middleNodes();
                nodesPost.push_back(nsolPostSynSection->firstNode());
                nodesPost.push_back(nsolPostSynSection->lastNode());
            }

            Vec3f bbpPostSynCenterPos  = bbpSynapse.postsynaptic_position();
            distance = 10000000;
            NSOL_FOREACH( nodeIt, nodesPost )
            {
                const nsol::NodePtr node = (*nodeIt);
                Vec3f posNode = node->point();
                Vec3f p_ = bbpPostSynCenterPos;
                float distActual = std::sqrt(pow((p_.x()-posNode.x()), 2)+
                                             pow((p_.y()-posNode.y()), 2)+
                                             pow((p_.z()-posNode.z()), 2));
                if(distActual < distance)
                {
                    distance = distActual;
                    nsolPostSynNode = node;
                }
            }

//            std::cout <<" [POST NODE]:"<<
//                        "\n bbpPostSynCenterPos= "<< bbpPostSynCenterPos <<
//                        "\n Distance= "<< distance <<
//                        "\n Ref node= " << nsolPostSynNode <<
//                        "\n Pos node= " << nsolPostSynNode->point() << std::endl;

            // Checking type of synapse...
            if( isPreDentrite ) // 1º Checkup
            {
                if( isPostDentrite )
                {
                    nsol::SynapseNeuriteToNeuritePtr synapse =
                                            new nsol::SynapseNeuriteToNeurite
                                                (Synapse::DENDRODENDRITIC, id);
                    synapse->preSynapticSection( nsolPreSynSection );
                    synapse->postSynapticSection( nsolPostSynSection );

                    synapse->preSynapticNode( nsolPreSynNode );
                    synapse->postSynapticNode( nsolPostSynNode );

//                    std::cout <<" DENDRODENDRITIC \n";
                    afferent_synapse = synapse;
                }else
                {
                    if( isPostSoma )
                    {
                        nsol::SynapseNeuriteToSomaPtr synapse =
                                                new nsol::SynapseNeuriteToSoma
                                                    (Synapse::DENDROSOMATIC, id);
                        synapse->preSynapticSection( nsolPreSynSection );

                        synapse->preSynapticNode( nsolPreSynNode );
                        synapse->postSynapticNode( nsolPostSynNode );

//                        std::cout <<" DENDROSOMATIC \n";
                        afferent_synapse = synapse;
                    }
                }
            }
            if( isPreAxon ) // 2º Checkup
            {
                if( isPostDentrite )
                {
                    nsol::SynapseNeuriteToNeuritePtr synapse =
                                            new nsol::SynapseNeuriteToNeurite
                                                (Synapse::AXODENDRITIC, id);
                    synapse->preSynapticSection( nsolPreSynSection );
                    synapse->postSynapticSection( nsolPostSynSection );

                    synapse->preSynapticNode( nsolPreSynNode );
                    synapse->postSynapticNode( nsolPostSynNode );

//                    std::cout <<" AXODENDRITIC \n";
                    afferent_synapse = synapse;
                }else
                {
                    if( isPostSoma )
                    {
                        nsol::SynapseNeuriteToSomaPtr synapse =
                                                new nsol::SynapseNeuriteToSoma
                                                    (Synapse::AXOSOMATIC, id);
                        synapse->preSynapticSection( nsolPreSynSection );

                        synapse->preSynapticNode( nsolPreSynNode );
                        synapse->postSynapticNode( nsolPostSynNode );

//                        std::cout <<" AXOSOMATIC \n";
                        afferent_synapse = synapse;
                    }else
                    {
                        if( isPostAxon )
                        {
                            nsol::SynapseNeuriteToNeuritePtr synapse =
                                                    new nsol::SynapseNeuriteToNeurite
                                                        (Synapse::AXOAXONIC, id);
                            synapse->preSynapticSection( nsolPreSynSection );
                            synapse->postSynapticSection( nsolPostSynSection );

                            synapse->preSynapticNode( nsolPreSynNode );
                            synapse->postSynapticNode( nsolPostSynNode );

//                            std::cout <<" AXOAXONIC \n";
                            afferent_synapse = synapse;
                        }
                    }
                }
            }
            if( isPreSoma ) // 3º Checkup
                if( isPostSoma )
                {
                    nsol::SynapseSomaToSomaPtr synapse =
                                            new nsol::SynapseSomaToSoma( id );
                    synapse->preSynapticNode( nsolPreSynNode );
                    synapse->postSynapticNode( nsolPostSynNode );

//                    std::cout <<" SOMATOSOMAL \n";
                    afferent_synapse = synapse;
                }

//            std::cout << std::endl;

            // We have to build a nsol Neurons using a BBPSDK Neuron.
            afferent_synapse->preSynapticNeuron(nsolPreSynNeuron);
            afferent_synapse->postSynapticNeuron(nsolPostSynNeuron);
            afferent_synapse->preSynapticSurfacePosition(bbpPreSynPos);
            afferent_synapse->postSynapticSurfacePosition(bbpPostSynPos);

            circuit.addConnection(afferent_synapse);
          }
          id++;
        }// all synapses of a neuron
      }// all neurons
    }//circuit data

    // close experiment and free its resources
    experiment.close( );

    std::cout << std::endl;

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
