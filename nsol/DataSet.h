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
#include "Container/Columns.h"
#include "Reader/BBPSDKReader.h"
#include "Reader/SwcReader.h"
#include "Reader/BrionReader.h"

#ifdef NSOL_USE_QT5CORE
#include <QStringList>
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <map>
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

      BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                            SOMA, NEURONMORPHOLOGY, NEURON, MINICOLUMN,
                            COLUMN > brionReader;

      _loadMorphology( neuronId_, morphologySource, morphologyLabel,
                       brionReader );
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
    void loadMorphologies( std::set< unsigned int >& neuronIds_ )
    {
      if( !_blueConfig )
        return;

      const brion::Circuit circuit( _blueConfig->getCircuitSource( ));
      const std::string morphologySource =
        _blueConfig->getMorphologySource( ).getPath( );

      const brion::NeuronMatrix& data = circuit.get(
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
    NeuronsMap& neurons( void );

    NSOL_API
    const NeuronsMap& neurons( void ) const;

    bool addNeuron( const NeuronPtr neuron )
    {
      if ( _neurons.find( neuron->gid( )) != _neurons.end( ))
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
      BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON, SOMA,
                            NEURONMORPHOLOGY, NEURON, MINICOLUMN, COLUMN  >
        brionReader;

      NEURON* neuron =  brionReader.loadNeuron( file_,
                                                gid_,
                                                layer_,
                                                transform_,
                                                type_ );

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
    void loadScene( const std::string& xmlSceneFile )
    {
#ifdef NSOL_USE_QT5CORE
      QFile qFile ( xmlSceneFile.c_str( ));
      if ( ! qFile.exists( ))
        NSOL_THROW( "Scene file not found" );

      qFile.open( QIODevice::ReadOnly | QIODevice::Text );

      if ( ! qFile.isOpen( ))
        NSOL_THROW( "Scene file not readable" );

      QXmlStreamReader xml( & qFile );

      if ( xml.hasError( ) )
        NSOL_THROW( "Scene XML file has errors" );

      xml.readNextStartElement( );

      std::string version;

      std::map< unsigned int, NeuronPtr > neuronsMap;


      if ( xml.name( ) == "scene" )
      {
        QXmlStreamAttributes attributes = xml.attributes( );

        if( attributes.hasAttribute( "version" ))
          version = attributes.value( "version" ).toString( ).toStdString( );
        else
          NSOL_THROW( "No version number present" );
      }
      else
        NSOL_THROW( "Expected <scene> root element" );

      while( !xml.atEnd( ) &&  !xml.hasError( ))
      {
        xml.readNext( );

        if ( xml.atEnd( ))
          continue;

        if ( xml.tokenType( ) != QXmlStreamReader::StartElement )
          continue;

        if ( xml.name( ) == "morphology" )
        {
          while( !xml.atEnd( ) &&  !xml.hasError( ))
          {
            xml.readNext( );

            if ( xml.atEnd( ) ||
               xml.tokenType( ) != QXmlStreamReader::StartElement )
            continue;

            if ( !xml.atEnd( ) && xml.name( ) == "column" )
            {
              QXmlStreamAttributes attributes = xml.attributes( );
              if( attributes.hasAttribute( "id" ))
              {
                //Creating column
                unsigned int colId = attributes.value( "id" ).toUInt( );
                ColumnPtr column = ( ColumnPtr )new COLUMN( colId );
                _columns.push_back( column );

                //Looking for minicolumns in column
                while( !xml.atEnd( ) && !xml.hasError( ) &&
                       !( xml.name( ) == "column" &&
                       xml.tokenType( ) == QXmlStreamReader::EndElement ))
                {
                  xml.readNext( );
                  if ( xml.atEnd( ) ||
                       xml.tokenType( ) != QXmlStreamReader::StartElement )
                    continue;

                  if ( !xml.atEnd( ) && xml.name( ) == "minicolumn" )
                  {
                    attributes = xml.attributes( );
                    if ( attributes.hasAttribute( "id" ) )
                    {
                      //Creating minicolumn
                      unsigned int miniColId = attributes.value( "id" ).toUInt( );
                      MiniColumnPtr miniColumn =
                          ( MiniColumnPtr )new MINICOLUMN( column, miniColId );
                      column->addMiniColumn( miniColumn );

                      //Looking for neuronos in minicolumn
                      while( !xml.atEnd( ) && !xml.hasError( ) &&
                             !( xml.name( ) == "minicolumn" &&
                             xml.tokenType( ) == QXmlStreamReader::EndElement ))
                      {
                        xml.readNext( );
                        if ( xml.atEnd( ) ||
                             xml.tokenType( ) != QXmlStreamReader::StartElement )
                          continue;

                        if ( !xml.atEnd( ) && xml.name( ) == "neuron" )
                        {
                          attributes = xml.attributes( );
                          if ( attributes.hasAttribute( "gid" ))
                          {
                            //Creating neuron
                            unsigned int gid =
                                attributes.value( "gid" ).toUInt( );
                            unsigned int layer = 1;
                            nsol::Neuron::TMorphologicalType morphologicalType =
                                nsol::Neuron::UNDEFINED;
                            nsol::Neuron::TFunctionalType functionalType =
                                nsol::Neuron::UNDEFINED_FUNCTIONAL_TYPE;
                            Matrix4_4f transform = Matrix4_4fIdentity;

                            //GET Layer
                            if ( attributes.hasAttribute( "layer" ))
                                layer = attributes.value( "layer" ).toUInt( );

                            //GET Mophological Type
                            if ( attributes.hasAttribute( "morphologicalType" ) )
                            {
                              std::string typeString(
                                  attributes.value( "morphologicalType" ).toString( ).toStdString( ));

                              if ( typeString == "INTERNEURON" )
                              {
                                morphologicalType = nsol::Neuron::INTERNEURON;
                              }
                              else if( typeString == "PYRAMIDAL" )
                              {
                                morphologicalType = nsol::Neuron::PYRAMIDAL;
                              }
                              else
                              {
                                NSOL_LOG( std::string( "Neuron " ) +
                                    std::to_string( gid ) +
                                    std::string( " undefined morphological type." ));
                              }
                            }

                            //GET Functional Type
                            if ( attributes.hasAttribute( "functionalType" ) )
                            {
                              std::string typeString(
                                  attributes.value( "functionalType" ).toString( ).toStdString( ));

                              if ( typeString == "EXCITATORY" )
                              {
                                functionalType = nsol::Neuron::EXCITATORY;
                              }
                              else if( typeString == "INHIBITORY" )
                              {
                                functionalType = nsol::Neuron::INHIBITORY;
                              }
                              else
                              {
                                NSOL_LOG( std::string( "Neuron " ) +
                                    std::to_string( gid ) +
                                    std::string( " undefined functional type." ));
                              }
                            }

                            // Looking for transform in neuron
                            while( !xml.atEnd( ) && !xml.hasError( ) &&
                                   !( xml.name( ) == "neuron" &&
                                   xml.tokenType( ) ==
                                       QXmlStreamReader::EndElement ))
                            {
                              xml.readNext( );
                              if ( xml.atEnd( ) ||
                                   xml.tokenType( ) !=
                                       QXmlStreamReader::StartElement )
                                continue;

                              if ( !xml.atEnd( ) && xml.name( ) == "transform" )
                              {
                                QStringList mL =
                                    xml.readElementText( ).remove(' ').
                                    remove('\n').remove('\t').split(",");
                                if ( mL.size( ) == 16 )
                                {
                                  for ( unsigned int i = 0; i < 4; i ++ )
                                    for ( unsigned int j = 0; j < 4; j ++ )
                                      transform( i, j ) =
                                        mL[ i * 4 + j].toFloat( );
                                }
                              }
                            }
                            NeuronPtr neuron = ( NeuronPtr )
                                new NEURON( nullptr, layer, gid,
                                            transform, miniColumn,
                                            morphologicalType,
                                            functionalType );
                            if ( neuron )
                            {
                              if ( addNeuron( neuron ))
                              {
                                miniColumn->addNeuron( neuron );
                                neuronsMap.insert(
                                  std::pair< unsigned int, NeuronPtr >(
                                    gid, neuron ));
                              }
                              else
                                delete neuron;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }

            if ( !xml.atEnd( ) && xml.name( ) == "neuronmorphologies" )
            {
              while( !xml.atEnd( ) &&  !xml.hasError( ))
              {
                xml.readNext( );
                if ( xml.atEnd( ) ||
                    xml.tokenType( ) != QXmlStreamReader::StartElement )
                  continue;

                if ( !xml.atEnd( ) && xml.name( ) == "neuronmorphology" )
                {
                  QXmlStreamAttributes attributes = xml.attributes( );
                  if( attributes.hasAttribute( "neurons" ) &&
                      attributes.hasAttribute( "swc" ) )
                  {
                    std::string swc =
                        attributes.value( "swc" ).toString( ).toStdString( );

                    BrionReaderTemplated< NODE, SECTION, DENDRITE, AXON,
                                          SOMA, NEURONMORPHOLOGY, NEURON,
                                          MINICOLUMN, COLUMN > brionReader;
                     NeuronMorphologyPtr neuronMorphology =
                         brionReader.loadMorphology( swc );
                     if ( neuronMorphology )
                     {
                       QStringList neurons_ =
                           attributes.value("neurons").toString( ).split(',');
                       NSOL_FOREACH( n, neurons_ )
                       {
                         std::map<unsigned int, NeuronPtr>::iterator neuronFind =
                             neuronsMap.find(( *n ).toUInt( ));
                         if( neuronFind != neuronsMap.end( ))
                         {
                           NeuronPtr neuron = neuronFind->second;
                           neuron->morphology( neuronMorphology );
                         }
                       }
                     }

                  }
                }
              }
            }
          }
        }
        else if ( xml.name( ) == "ciruit" )
        {
          //TODO
        }
        else
          NSOL_THROW ( std::string( "Element <" ) +
              xml.name( ).toString( ).toStdString( ) +
              std::string( "> not expected" ) );
      }
#else
      NSOL_THROW( std::string("Can't load ") + xmlSceneFile +
                  std::string( ". QT5CORE not supported" ));
#endif

    }

  private:

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
        return;

      std::map< std::string, NeuronMorphologyPtr >::iterator morphoIt =
        _morphologies.find( morphologyLabel_ );

      if( morphoIt != _morphologies.end( ))
      {
        neuron->morphology( morphoIt->second );
        return;
      }

      NeuronMorphologyPtr morpho = brionReader_.loadMorphology(
        morphologySource_ + "/" + morphologyLabel_ + ".h5" );

      neuron->morphology( morpho );
      _morphologies[ morphologyLabel_ ] = morpho;
    }


  protected:

    Columns _columns;

    //! Container of neurons by its gid
    NeuronsMap _neurons;

    std::map< std::string, NeuronMorphologyPtr > _morphologies;

    brion::BlueConfig* _blueConfig;

    std::string _target;


  }; // class DataSet

} // namespace nsol

#endif // __NSOL_DATASET__
