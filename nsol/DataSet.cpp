#include <set>
#include "DataSet.h"
#include "error.h"
#include "Writer/XmlSceneWriter.h"


namespace nsol
{

  DataSet::DataSet( void )
#ifdef NSOL_USE_BRION
    : _blueConfig( nullptr )
    , _target( std::string(""))
#endif
  {

  }

  void DataSet::unloadMorphologies( void )
  {
    for( auto par: _morphologies )
    {
      delete par.second;
    }
    _morphologies.clear( );

    for( auto par: _neurons )
    {
      NeuronPtr neuron = par.second;
      neuron->morphology( nullptr );
    }
  }

  void DataSet::close( void )
  {
    std::set< NeuronMorphologyPtr > morphologies;

    NSOL_FOREACH( col, _columns )
    {
      NSOL_FOREACH( miniCol, ( *col )->miniColumns( ))
      {
        NSOL_FOREACH( neuron, ( *miniCol )->neurons( ))
        {
          if ( (*neuron )->morphology( ) )
            morphologies.insert(( *neuron )->morphology( ));
          delete *neuron;
        }
        delete *miniCol;
      }
      delete *col;
    }

    NSOL_FOREACH( morphology, morphologies )
    {
      delete *morphology;
    }

    _columns.clear( );
    _circuit.clear();
    _neurons.clear( );
    _morphologies.clear( );

#ifdef NSOL_USE_BRION
    if ( _blueConfig )
      delete _blueConfig;
#endif

    return;
  }

  void DataSet::writeXmlScene( const std::string& xmlSceneFile )
  {
    XmlSceneWriter::writeToXml( xmlSceneFile, _columns, _morphologies );
  }

  Columns& DataSet::columns( void )
  {
    return _columns;
  }

  const Columns& DataSet::columns( void ) const
  {
    return _columns;
  }

  NeuronsMap& DataSet::neurons( void )
  {
    return _neurons;
  }

  const NeuronsMap& DataSet::neurons( void ) const
  {
    return _neurons;
  }

} // namespace nsol
