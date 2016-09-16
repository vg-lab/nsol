/**
 * @file    DataSet.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_DATASET__
#define __NSOL_DATASET__

#include <nsol/api.h>
#include "error.h"
#include "Log.h"
#include "NsolTypes.h"
#include "Neuron.h"
#include "NeuronMorphology.h"
#include "Neurite.h"
#include "Axon.h"
#include "Section.h"
#include "Circuit.h"
#include "Synapse.h"
#include "SynapseNeuriteToNeurite.h"
#include "SynapseNeuriteToSoma.h"
#include "SynapseSomaToSoma.h"
#include "Container/Columns.h"
#include "Container/Sections.h"
#include "Reader/BBPSDKReader.h"
#include "Reader/XmlSceneReader.h"
#include "Reader/SwcReader.h"

#ifdef NSOL_USE_BRION
#include "Reader/BrionReader.h"
#else
#include <set>
#endif




namespace nsol
{


  class DataSet
  {
  public:

    NSOL_API
    DataSet( void );


    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
#ifdef NSOL_USE_BRION
    void loadBlueConfigHierarchy( const std::string& blueConfig_,
                                  const std::string& target_ )
    {
      close( );
      BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                            SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                            COLUMN > brionReader;

      _blueConfig = new brion::BlueConfig( blueConfig_ );
      _target = target_;

      brionReader. loadBlueConfigHierarchy( _columns,
                                            _neurons,
                                            *_blueConfig,
                                            _target );

#else
    void loadBlueConfigHierarchy( const std::string& /*blueConfig_*/,
                                    const std::string& /*target_*/ )
    {
      NSOL_THROW( std::string( "Brion not supported" ));
#endif
    }


    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
#ifdef NSOL_USE_BRION
    void loadBlueConfigBasicConnectivity( const std::string& blueConfig_,
                                          const std::string& target_ )
    {
        close( );
        BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                              SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                              COLUMN > brionReader;

        _blueConfig = new brion::BlueConfig( blueConfig_ );
        _target = target_;

        brionReader.loadBlueConfigBasicConnectivity( _columns,
                                                     _circuit,
                                                     _neurons,
                                                     *_blueConfig,
                                                     _target );
#else
    void loadBlueConfigBasicConnectivity( const std::string& /*blueConfig_*/,
                                          const std::string& /*target_*/ )
    {
      NSOL_THROW( std::string( "Brion not supported" ));
#endif
    }


    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
#ifdef NSOL_USE_BRION
    void loadBlueConfigConnectivity( const std::string& blueConfig_,
                                     const std::string& target_ )
    {
        close( );
        BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                              SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                              COLUMN > brionReader;

        _blueConfig = new brion::BlueConfig( blueConfig_ );
        _target = target_;

        std::map< unsigned short, SynapsePtr > synapseMap =
                      brionReader.loadBlueConfigBasicConnectivity( _columns,
                                                                   _circuit,
                                                                   _neurons,
                                                                   *_blueConfig,
                                                                    _target );
        for( int i=0; i < _neurons.size(); i++ )
//        NSOL_FOREACH( neuronIt, _neurons )
        {
            NeuronPtr neuron = _neurons[i];
            this->loadMorphology( neuron->gid() );
        }

        brain::Circuit brainCircuit( *_blueConfig );
        brion::GIDSet gidSetBrain = brainCircuit.getGIDs( target_ );
        const brain::Synapses& brainSynapses = brainCircuit.
                                          getAfferentSynapses( gidSetBrain );

//        for( brain::Synapses::const_iterator it = brainSynapses.begin();
//                                             it != brainSynapses.end(); ++it )
        for( int i = 0; i < brainSynapses.size(); i++)
        {
//            brain::Synapse* brainSynapse = &(*it);
            brain::Synapse brainSynapse = brainSynapses[i];
            SynapsePtr synapse = synapseMap.find(brainSynapse.getGID().second)->second;

            NeuronPtr preSynapticNeuron  = synapse->preSynapticNeuron();
            NeuronPtr postSynapticNeuron = synapse->postSynapticNeuron();

            if( preSynapticNeuron == nullptr || postSynapticNeuron == nullptr )
                continue;

            // -- Treatment of synapse type: -- //
            // Computing pre-synaptic section..
            SynapsePtr newSynapse = nullptr;

            bool isPreDentrite, isPreAxon, isPreSoma;
            isPreDentrite = isPreAxon = false;
            isPreSoma = true;

            bool found = false;
            SectionPtr preSynSection = nullptr;
            unsigned int brainIDSection = brainSynapse.getPresynapticSectionID();

            Neurites neuritesPre = preSynapticNeuron->morphology()->neurites();
            NSOL_FOREACH( neuriteIt, neuritesPre )
            {
                if( found ) break;

                const NeuritePtr neurite = (*neuriteIt);
                Sections sections = neurite->sections();

                NSOL_FOREACH( sectionIt, sections )
                {
                    const SectionPtr section = (*sectionIt);
                    if( section->_id == brainIDSection )
                    {
                        found = true;
                        preSynSection = section;

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

            // Computing post-synaptic section..
            bool isPostDentrite, isPostAxon, isPostSoma;
            isPostDentrite = isPostAxon = false;
            isPostSoma = true;

            found = false;

            SectionPtr postSynSection = nullptr;
            brainIDSection = brainSynapse.getPostsynapticSectionID();

            Neurites neuritesPost = postSynapticNeuron->morphology()->neurites();
            NSOL_FOREACH( neuriteIt, neuritesPost )
            {
                if( found ) break;

                const NeuritePtr neurite = (*neuriteIt);
                Sections sections = neurite->sections();

                NSOL_FOREACH( sectionIt, sections )
                {
                    const SectionPtr section = (*sectionIt);

                    if( section->_id == brainIDSection )
                    {
                        found = true;
                        postSynSection = section;

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

            // -- Computing synaptic-nodes --
            // To pre-synaptic node...

            NodePtr preSynNode = nullptr;
            Nodes nodesPre = preSynapticNeuron->morphology()->soma()->nodes();

            if(preSynSection != nullptr) nodesPre = preSynSection->nodes();

            const Matrix4_4f modelPre = preSynapticNeuron->transform();
            vmml::Vector3f p_ = brainSynapse.getPresynapticSurfacePosition();
            float distance = 10000000;
            NSOL_FOREACH( nodeIt, nodesPre )
            {
                const NodePtr node = (*nodeIt);
                Vec3f posNode = node->point();

                Vec4f pt = modelPre * Vec4f(posNode.x(),
                                            posNode.y(),
                                            posNode.z(), 1.f);
                pt = pt/pt.w();

                float distActual = std::sqrt(pow((p_.x()-pt.x()), 2)+
                                             pow((p_.y()-pt.y()), 2)+
                                             pow((p_.z()-pt.z()), 2));
                if(distActual < distance)
                {
                    distance = distActual;
                    preSynNode = node;
                }
            }

            // To post-synaptic node...
            NodePtr postSynNode = nullptr;
            Nodes nodesPost = postSynapticNeuron->morphology()->soma()->nodes();

            if(postSynSection != nullptr) nodesPost = postSynSection->nodes();

            const Matrix4_4f modelPost = postSynapticNeuron->transform();
            p_ = brainSynapse.getPostsynapticSurfacePosition();
            distance = 10000000;
            NSOL_FOREACH( nodeIt, nodesPost )
            {
                const NodePtr node = (*nodeIt);
                Vec3f posNode = node->point();

                Vec4f pt = modelPost * Vec4f(posNode.x(),
                                             posNode.y(),
                                             posNode.z(), 1.f);
                pt = pt/pt.w();

                float distActual = std::sqrt(pow((p_.x()-pt.x()), 2)+
                                             pow((p_.y()-pt.y()), 2)+
                                             pow((p_.z()-pt.z()), 2));
                if(distActual < distance)
                {
                    distance = distActual;
                    postSynNode = node;
                }
            }

            // Checking type of synapse...
            if( isPreDentrite ) // 1º Checkup
            {
                if( isPostDentrite )
                {
                    SynapseNeuriteToNeuritePtr _synapse =
                                                    new SynapseNeuriteToNeurite(
                                                        Synapse::DENDRODENDRITIC,
                                                                synapse->id() );
                    _synapse->preSynapticSection( preSynSection );
                    _synapse->postSynapticSection( postSynSection );

                    _synapse->preSynapticNode( preSynNode );
                    _synapse->postSynapticNode( postSynNode );

//                    std::cout <<" DENDRODENDRITIC \n";
                    newSynapse = _synapse;
                }else
                {
                    if( isPostSoma )
                    {
                        SynapseNeuriteToSomaPtr _synapse =
                                                       new SynapseNeuriteToSoma(
                                                       Synapse::DENDROSOMATIC,
                                                       synapse->id());
                        _synapse->preSynapticSection( preSynSection );

                        _synapse->preSynapticNode( preSynNode );
                        _synapse->postSynapticNode( postSynNode );

//                        std::cout <<" DENDROSOMATIC \n";
                        newSynapse = _synapse;
                    }
                }
            }
            if( isPreAxon ) // 2º Checkup
            {
                if( isPostDentrite )
                {
                    SynapseNeuriteToNeuritePtr _synapse =
                                                    new SynapseNeuriteToNeurite(
                                                    Synapse::AXODENDRITIC,
                                                    synapse->id());
                    _synapse->preSynapticSection( preSynSection );
                    _synapse->postSynapticSection( postSynSection );

                    _synapse->preSynapticNode( preSynNode );
                    _synapse->postSynapticNode( postSynNode );

//                    std::cout <<" AXODENDRITIC \n";
                    newSynapse = _synapse;
                }else
                {
                    if( isPostSoma )
                    {
                        SynapseNeuriteToSomaPtr _synapse =
                                                      new SynapseNeuriteToSoma (
                                                      Synapse::AXOSOMATIC,
                                                      synapse->id());
                        _synapse->preSynapticSection( preSynSection );

                        _synapse->preSynapticNode( preSynNode );
                        _synapse->postSynapticNode( postSynNode );

//                        std::cout <<" AXOSOMATIC \n";
                        newSynapse = _synapse;
                    }else
                    {
                        if( isPostAxon )
                        {
                            SynapseNeuriteToNeuritePtr _synapse =
                                                   new SynapseNeuriteToNeurite (
                                                   Synapse::AXOAXONIC,
                                                   synapse->id());
                            _synapse->preSynapticSection( preSynSection );
                            _synapse->postSynapticSection( postSynSection );

                            _synapse->preSynapticNode( preSynNode );
                            _synapse->postSynapticNode( postSynNode );

//                            std::cout <<" AXOAXONIC \n";
                            newSynapse = _synapse;
                        }
                    }
                }
            }
            if( isPreSoma ) // 3º Checkup
                if( isPostSoma )
                {
                    SynapseSomaToSomaPtr _synapse = new SynapseSomaToSoma
                                                            ( synapse->id() );
                    _synapse->preSynapticNode( preSynNode );
                    _synapse->postSynapticNode( postSynNode );

//                    std::cout <<" SOMATOSOMAL \n";
                    newSynapse = _synapse;
                }

            //new synapse with type
            newSynapse->preSynapticNeuron(synapse->preSynapticNeuron());
            newSynapse->postSynapticNeuron(synapse->postSynapticNeuron());
            newSynapse->preSynapticSurfacePosition(synapse->
                                                 preSynapticSurfacePosition());
            newSynapse->postSynapticSurfacePosition(synapse->
                                                 postSynapticSurfacePosition());
            _circuit.removeConnection( synapse );
//            delete( synapse );

            _circuit.addConnection( newSynapse );

        }// all synapses



#else
    void loadBlueConfigConnectivity( const std::string& /*blueConfig_*/,
                                     const std::string& /*target_*/ )
    {
      NSOL_THROW( std::string( "Brion not supported" ));
#endif
    }


    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
#ifdef NSOL_USE_BRION
    void loadMorphology( unsigned int neuronId_ )
    {
      if( !_blueConfig )
        return;

      const brion::Circuit brionCircuit( _blueConfig->getCircuitSource( ));
      const std::string morphologySource =
        _blueConfig->getMorphologySource( ).getPath( );

      brion::GIDSet gidSet;
      gidSet.insert( neuronId_ );

      const brion::NeuronMatrix& data = brionCircuit.get(
        gidSet, brion::NEURON_MORPHOLOGY_NAME );

      std::string morphologyLabel = data[0][0];

      BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                            SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                            COLUMN > brionReader;

      _loadMorphology( neuronId_, morphologySource, morphologyLabel,
                       brionReader );
#else
    void loadMorphology( unsigned int /*neuronId_*/ )
    {
      NSOL_THROW( std::string( "Brion not supported" ));
#endif
    }

    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
#ifdef NSOL_USE_BRION
    void loadMorphologies( std::set< unsigned int >& neuronIds_ )
    {
      if( !_blueConfig )
        return;

      const brion::Circuit brionCircuit( _blueConfig->getCircuitSource( ));
      const std::string morphologySource =
        _blueConfig->getMorphologySource( ).getPath( );

      const brion::NeuronMatrix& data = brionCircuit.get(
        neuronIds_, brion::NEURON_MORPHOLOGY_NAME );

      BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                            SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                            COLUMN > brionReader;

      int i = 0;
      for( auto id: neuronIds_ )
      {
        std::string morphologyLabel = data[i][0];
        i++;
        _loadMorphology( id, morphologySource, morphologyLabel,
                         brionReader );
      }
#else
    void loadMorphologies( std::set< unsigned int >& /*neuronIds_*/ )
    {
      NSOL_THROW( std::string( "Brion not supported" ));
#endif
    }

    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void loadAllMorphologies( void )
    {
      std::set< unsigned int > neuronIds;
      for ( auto par: _neurons )
      {
        neuronIds.insert( par.second->gid( ));
      }
      loadMorphologies< NODE, SECTION, DENDRITE, AXON,
                        SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                        COLUMN >( neuronIds );
    }

#ifdef NSOL_USE_BBPSDK

    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void loadFromBlueConfig(
      const std::string& blueconfig,
      const int loadFlags = MORPHOLOGY | CORTICAL_HIERARCHY,
      const std::string& targetLabel = std::string( "" ))
    {
      std::cerr << "DataSet< >::loadFromBlueConfig is deprecated.\n"
                << "Please use DataSet< >::loadBlueConfigHierarchy and\n"
                << "DataSet< >::loadMorphologies" << std::endl;
      BBPSDKReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                             SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                             COLUMN > reader;
      reader.readFromBlueConfig( _columns,
                                 _circuit,
                                 _neurons,
                                 blueconfig,
                                 loadFlags,
                                 targetLabel );
    }
#endif

    NSOL_API
    void unloadMorphologies( void );

    NSOL_API
    void close( void );

    NSOL_API
    Columns& columns( void );

    NSOL_API
    const Columns& columns( void ) const;

    NSOL_API
    Circuit& circuit( void );

    NSOL_API
    NeuronsMap& neurons( void );

    NSOL_API
    const NeuronsMap& neurons( void ) const;

    NSOL_API
    bool addNeuron( const NeuronPtr neuron )
    {
      if ( _neurons.find( (unsigned int)neuron->gid( )) != _neurons.end( ))
      {
        Log::log( std::string( "Warning: neuron with gid " ) +
                  std::to_string( neuron->gid( )) +
                  std::string( "already exists in the dataset" ),
                  LOG_LEVEL_WARNING );
        return false;
      }

      _neurons[ neuron->gid( ) ] = neuron;
      return true;

    }

    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    NeuronPtr loadNeuronFromFile(
      const std::string& file_,
      const unsigned int gid_,
      const unsigned int layer_ = 0,
      const Matrix4_4f transform_ = Matrix4_4fIdentity,
      const Neuron::TMorphologicalType type_ = Neuron::PYRAMIDAL )
    {
      NeuronPtr neuron;
#ifdef NSOL_USE_BRION
      BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON, SOMA,
                            NEURONMORPHOLOGY, NEURON, MINICOLUMN, COLUMN  >
        brionReader;

      neuron =  brionReader.loadNeuron( file_, gid_, layer_, transform_,
                                        type_ );
#else
      SwcReaderTemplated< NODE, SECTION, DENDRITE, AXON, SOMA,
                          NEURONMORPHOLOGY, NEURON > swcReader;
      neuron = swcReader.readNeuron( file_ );
      neuron->gid( ) = gid_;
      neuron->layer( ) = layer_;
      neuron->transform( ) = transform_;
      neuron->morphologicalType( ) = type_;

#endif
      if ( neuron && !addNeuron( neuron ))
      {
        delete neuron;
        return nullptr;
      }
      return neuron;
    }


    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void loadCorticalNeuronFromFile(
      const std::string& file_, const unsigned int gid_,
      const unsigned int columnId_ = 0, const unsigned int miniColumnId_ = 0,
      const unsigned int layer_ = 0,
      const Matrix4_4f transform_ = Matrix4_4fIdentity,
      const Neuron::TMorphologicalType type_ = Neuron::PYRAMIDAL )
    {
      NeuronPtr neuron =
        loadNeuronFromFile< NODE, SECTION, DENDRITE, AXON, SOMA,
                           NEURONMORPHOLOGY, NEURON, MINICOLUMN, COLUMN >
        ( file_, gid_, layer_, transform_, type_ );

      if( neuron && neuron->morphology( ) )
      {

        Column* column = nullptr;
        NSOL_FOREACH( col, _columns )
        {
          if (( *col )->id( ) == columnId_ )
          {
            column = *col;
          }
        }
        if( !column )
        {
          column = new COLUMN( columnId_ );
          _columns.push_back( column );
        }

        MINICOLUMN* miniColumn = nullptr;
        NSOL_FOREACH( miniCol, column->miniColumns() )
        {
          if(( *miniCol )->id( ) == miniColumnId_ )
          {
            miniColumn = *miniCol;
          }
        }
        if( !miniColumn )
        {
          miniColumn =
            ( MiniColumnPtr ) new MINICOLUMN( column, miniColumnId_ );
          column->addMiniColumn( miniColumn );
        }
        neuron->miniColumn( miniColumn );
        miniColumn->addNeuron( neuron );
      }

    }


    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void loadXmlScene( const std::string& xmlSceneFile )
    {
      XmlSceneReader::loadXml<
        NODE, SECTION, DENDRITE,
        AXON, SOMA, NEURONMORPHOLOGY,
        NEURON, MINICOLUMN, COLUMN >( xmlSceneFile, _columns,
                                      _neurons, _morphologies );
    }

    NSOL_API
    void writeXmlScene( const std::string& xmlSceneFile );

  private:

#ifdef NSOL_USE_BRION
    template < class NODE = Node,
               class SECTION = Section,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
    void _loadMorphology( unsigned int& neuronId_,
                          const std::string& morphologySource_,
                          const std::string& morphologyLabel_,
                          BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                          SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                          COLUMN >& brionReader_ )
  {
      NeuronsMap::iterator neuronIt = _neurons.find( neuronId_ );

      if( neuronIt == _neurons.end( ))
      {
        std::cerr << "Neuron " << neuronId_ << " doesn't exist in DataSet"
                  << std::endl;
        return;
      }
      NeuronPtr neuron = neuronIt->second;

      if ( neuron->morphology( ))
      {
        return;
      }

      std::map< std::string, NeuronMorphologyPtr >::iterator morphoIt =
        _morphologies.find( morphologyLabel_ );

      if( morphoIt != _morphologies.end( ))
      {
        morphoIt->second->parentNeurons( ).push_back( neuron );
        neuron->morphology( morphoIt->second );
        return;
      }

      NeuronMorphologyPtr morpho = brionReader_.loadMorphology(
        morphologySource_ + "/" + morphologyLabel_ + ".h5" );

      neuron->morphology( morpho );
      morpho->parentNeurons( ).push_back( neuron );
      _morphologies[ morphologyLabel_ ] = morpho;
    }
#endif

  protected:

    //! Entry for cortical hierarchy in form o a container of cortial columns
    Columns _columns;
    Circuit _circuit;

    //! Container of neurons by its gid
    NeuronsMap _neurons;

    //! Map of the paths of morphologies
    std::map< std::string, NeuronMorphologyPtr > _morphologies;

#ifdef NSOL_USE_BRION
    brion::BlueConfig* _blueConfig;

    std::string _target;
#endif


  }; // class DataSet

} // namespace nsol

#endif // __NSOL_DATASET__
