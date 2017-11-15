/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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
#include "NeuronMorphologySection.h"
#include "Circuit.h"
#include "Synapse.h"
#include "MorphologySynapse.h"
#include "Container/Columns.h"
#include "Container/Sections.h"
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
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
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
      BrionReaderTemplated< NODE, NEURONMORPHOLOGYSECTION, DENDRITE, AXON,
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
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
#ifdef NSOL_USE_BRION
    void loadBlueConfigConnectivity( void )
    {
      if( !_blueConfig || _target.empty( ))
      {
        Log::log("BlueConfig not open or target empty", LOG_LEVEL_WARNING );
        return;
      }

       BrionReaderTemplated< NODE, NEURONMORPHOLOGYSECTION, DENDRITE, AXON,
                             SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                             COLUMN > brionReader;

       brionReader.loadBlueConfigConnectivity( _neurons,
                                                    _circuit,
                                                   *_blueConfig, _target );
#else
    void loadBlueConfigConnectivity( )
    {
      NSOL_THROW( std::string( "Brion not supported" ));
#endif
    }

    template < class NODE = Node,
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
               class DENDRITE = Dendrite,
               class AXON = Axon,
               class SOMA = Soma,
               class NEURONMORPHOLOGY = NeuronMorphology,
               class NEURON = Neuron,
               class MINICOLUMN = MiniColumn,
               class COLUMN = Column >
#ifdef NSOL_USE_BRION
    void loadBlueConfigConnectivityWithMorphologies( )
    {
      if( !_blueConfig || _target.empty())
      {
        Log::log("BlueConfig not open or target empty", LOG_LEVEL_WARNING );
        return;
      }

      this->loadBlueConfigConnectivity< nsol::Node,
                                             nsol::NeuronMorphologySection,
                                             nsol::Dendrite,
                                             nsol::Axon,
                                             nsol::Soma,
                                             nsol::NeuronMorphology,
                                             nsol::Neuron,
                                             nsol::MiniColumn,
                                             nsol::Column >( );

      brain::Circuit brainCircuit( *_blueConfig );
      brion::GIDSet gidSetBrain = brainCircuit.getGIDs( _target );
      const brain::Synapses& brainSynapses = brainCircuit.
                                        getAfferentSynapses( gidSetBrain,
                                              brain::SynapsePrefetch::all );

      if( _circuit.synapses().size() != brainSynapses.size() )
      {
        Log::log("Not exist correspondence of the neurons data "
                 "between NSOL and BRION", LOG_LEVEL_WARNING );
        return;
      }

      for( unsigned int i = 0; i < _circuit.synapses().size(); ++i )
      {
        const brain::Synapse& brainSynapse = brainSynapses[ i ];
        MorphologySynapsePtr synapse = dynamic_cast<MorphologySynapsePtr>
                                       ( _circuit.synapses()[i] );

        if( synapse == nullptr )
        {
          Log::log("Inconsistent type of synapse.", LOG_LEVEL_WARNING );
          return;
        }

        vmml::Vector3f brainPreSynPos  = brainSynapse.
                                              getPresynapticSurfacePosition();
        vmml::Vector3f brainPostSynPos = brainSynapse.
                                              getPostsynapticSurfacePosition();

        synapse->preSynapticSurfacePosition( Vec3f( brainPreSynPos.x(),
                                                        brainPreSynPos.y(),
                                                        brainPreSynPos.z()));

        synapse->postSynapticSurfacePosition( Vec3f( brainPostSynPos.x(),
                                                         brainPostSynPos.y(),
                                                         brainPostSynPos.z()));

        std::unordered_map< unsigned int, NeuronPtr >::const_iterator
                         nitPre = _neurons.find( synapse->preSynapticNeuron( ));
        std::unordered_map< unsigned int, NeuronPtr >::const_iterator
                        nitPost = _neurons.find( synapse->postSynapticNeuron( ));

        if (( nitPre  == _neurons.end( ))||
            ( nitPost == _neurons.end( )))
         continue;

        NeuronPtr preSynapticNeuron = nitPre->second;
        NeuronPtr postSynapticNeuron = nitPost->second;

        // Computing pre-synaptic section..
        bool found = false;
        NeuronMorphologySectionPtr preSynSection = nullptr;
        unsigned int brainIDSection = brainSynapse.getPresynapticSectionID();

        Neurites neuritesPre = preSynapticNeuron->morphology()->neurites();
        NSOL_FOREACH( neuriteIt, neuritesPre )
        {
          if( found ) break;

          const NeuritePtr neurite = (*neuriteIt);
          Sections sections = neurite->sections();

          NSOL_FOREACH( sectionIt, sections )
          {
            const NeuronMorphologySectionPtr section =
              dynamic_cast< NeuronMorphologySectionPtr>( *(sectionIt));
            if( section->id() == brainIDSection )
            {
              found = true;
              preSynSection = section;

              break;
            }
          }// for all sections of one neurite
        }// for all neurites


        // Computing post-synaptic section..
        found = false;

        NeuronMorphologySectionPtr postSynSection = nullptr;
        brainIDSection = brainSynapse.getPostsynapticSectionID();

        Neurites neuritesPost = postSynapticNeuron->morphology()->neurites();
        NSOL_FOREACH( neuriteIt, neuritesPost )
        {
          if( found ) break;

          const NeuritePtr neurite = (*neuriteIt);
          Sections sections = neurite->sections();

          NSOL_FOREACH( sectionIt, sections )
          {
            const NeuronMorphologySectionPtr section =
              dynamic_cast< NeuronMorphologySectionPtr >( *( sectionIt ));

            if( section->id() == brainIDSection )
            {
              found = true;
              postSynSection = section;

              break;
            }
          }// for all sections of one neurite
        }// for all neurites

        synapse->preSynapticSection( preSynSection );
        synapse->postSynapticSection( postSynSection );

      }// all synapses

#else
    void loadBlueConfigConnectivityWithMorphologies( )
    {
      NSOL_THROW( std::string( "Brion not supported" ));
#endif

    }


    template < class NODE = Node,
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
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

      const brion::Circuit circuit( _blueConfig->getCircuitSource( ));
      const std::string morphologySource =
        _blueConfig->getMorphologySource( ).getPath( );

      brion::GIDSet gidSet;
      gidSet.insert( neuronId_ );

      const brion::NeuronMatrix& data = circuit.get(
        gidSet, brion::NEURON_MORPHOLOGY_NAME );

      std::string morphologyLabel = data[0][0];

      BrionReaderTemplated< NODE, NEURONMORPHOLOGYSECTION, DENDRITE, AXON,
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
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
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

      const brion::Circuit circuit( _blueConfig->getCircuitSource( ));
      const std::string morphologySource =
        _blueConfig->getMorphologySource( ).getPath( );

      const brion::NeuronMatrix& data = circuit.get(
        neuronIds_, brion::NEURON_MORPHOLOGY_NAME );

      BrionReaderTemplated< NODE, NEURONMORPHOLOGYSECTION, DENDRITE, AXON,
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
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
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
      loadMorphologies< NODE, NEURONMORPHOLOGYSECTION, DENDRITE, AXON,
                        SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                        COLUMN >( neuronIds );
    }


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
    const Circuit& circuit( void ) const;

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
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
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
      BrionReaderTemplated< NODE, NEURONMORPHOLOGYSECTION, DENDRITE, AXON, SOMA,
                            NEURONMORPHOLOGY, NEURON, MINICOLUMN, COLUMN  >
        brionReader;

      neuron =  brionReader.loadNeuron( file_, gid_, layer_, transform_,
                                        type_ );
#else
      SwcReaderTemplated< NODE, NEURONMORPHOLOGYSECTION, DENDRITE, AXON, SOMA,
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
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
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
        loadNeuronFromFile< NODE, NEURONMORPHOLOGYSECTION, DENDRITE, AXON, SOMA,
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
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
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
        NODE, NEURONMORPHOLOGYSECTION, DENDRITE,
        AXON, SOMA, NEURONMORPHOLOGY,
        NEURON, MINICOLUMN, COLUMN >( xmlSceneFile, _columns,
                                      _neurons, _morphologies );
    }

    NSOL_API
    void writeXmlScene( const std::string& xmlSceneFile );

  private:

#ifdef NSOL_USE_BRION
    template < class NODE = Node,
               class NEURONMORPHOLOGYSECTION = NeuronMorphologySection,
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
                          BrionReaderTemplated< NODE, NEURONMORPHOLOGYSECTION,
                          DENDRITE, AXON, SOMA, NEURONMORPHOLOGY, NEURON,
                          MINICOLUMN, COLUMN >& brionReader_ )
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

    //! Entry for connections of the circuit.
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
