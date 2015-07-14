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
          SegmentPtr segment = ( *section )->firstSegment( );
          while ( segment )
          {
            SegmentPtr tmpSegment = segment;
            segment = segment->next( );
            nodes.insert( tmpSegment->begin( ));
            nodes.insert( tmpSegment->end( ));
            delete tmpSegment;
          }
          delete *section;
        }
        delete *neurite;
      }
      delete ( *morphology )->soma( );
      delete *morphology;
    }


    NSOL_FOREACH( node, nodes )
      delete *node;

    _columns.clear( );

    return;
  }


  Columns& DataSet::columns( void )
  {
    return _columns;
  }


} // namespace nsol
