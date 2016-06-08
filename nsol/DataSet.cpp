#include <set>
#include "DataSet.h"
#include "error.h"


namespace nsol
{

  DataSet::DataSet( void )
    : _blueConfig( nullptr )
    , _target( std::string(""))
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
    _neurons.clear( );
    _morphologies.clear( );

    if ( _blueConfig )
      delete _blueConfig;

    return;
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
