#include <set>
#include "DataSet.h"
#include "error.h"


namespace nsol
{

  DataSet::DataSet( void )
  {

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
      NSOL_FOREACH( neurite, ( *morphology )->neurites( ))
      {
        Sections sections = ( *neurite )->sections( );
        delete ( *neurite )->firstSection( )->firstNode( );
        NSOL_FOREACH( section, sections )
        {
          Nodes nodes = ( *section )->middleNodes( );
          NSOL_FOREACH( node, nodes )
          {
            delete *node;
          }
          delete ( *section )->lastNode( );
          delete *section;
        }
        delete *neurite;
      }
      delete ( *morphology )->soma( );
      delete *morphology;
    }

    _columns.clear( );

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
