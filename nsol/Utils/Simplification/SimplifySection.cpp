/**
 * @file    SimplifySection.cpp
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "SimplifySection.h"

#include <math.h>

namespace nsol
{

  /*
   *  Método que divide en grupos la Section, 
   *  si la importancia supera un umbral simplifica
   *  con Reumann-Witkam, si no, simplifica con
   *  un algoritmo radial y luego con Douglas-Peucker
   */
  SectionPtr SimplifySection::simplify ( SectionPtr polyline
                               , float tolerance
                               , int range
                               , float threshold )
  {
    Vector<ScalarLabeledNodePtr> vaux = _vectorize( polyline
                                            , nullptr
                                            , nullptr );
    SectionPtr simple, sectaux;
    bool highestQuality;
    unsigned int size = vaux.size( );
    unsigned int index, indBegin, indEnd = 0;    

    while ( index < size )
    {
      indBegin = index;
      float reference = vaux[ index ]->relevance( );

      while ( ( index < size ) &&
              ( vaux[ index ]->relevance( ) <= ( reference + range ) ) && 
              ( vaux[ index ]->relevance( ) >= ( reference - range ) ) )
      {
        indEnd = index++;
      } // while #2

      highestQuality = ( _average( vaux, indBegin, indEnd ) > threshold );

      if ( ( indEnd - indBegin ) > 2 )
      {        
        if ( ! highestQuality ) 
        {
          sectaux = simplifyRadialv1( vaux, tolerance,
                                      indBegin, indEnd );
          sectaux = simplifyDP ( vaux, tolerance,
                                 indBegin, indEnd );
        } else 
        {
          sectaux = simplifyRWv1( vaux, tolerance, 
                                  indBegin, indEnd );
        } // else 
      }  // if    

      // combinar las subsecciones en una

    } // while #1

    // copiar atributos de polyline a sectaux, falta childs
    sectaux->neurite( polyline->neurite( ) );
    sectaux->parent( polyline->parent( ) ); 

    vaux.clear( );

    simple = sectaux;

    return simple;
  }


  /*
   *  This method simplifies a Section previously vectorized
   *  using the Radial algorithm. Returns SectionPtr, the 
   *  attributes from the original Section are NOT copied,
   *  It must be done outside this function.
   */
  SectionPtr SimplifySection::simplifyRadialv1 ( 
                                      Vector<ScalarLabeledNodePtr> polyline
                                    , float tolerance
                                    , unsigned int begin
                                    , unsigned int end ) 
  {
    // This structure will store the simplified section
    Vector<ScalarLabeledNodePtr> vaux = Vector<ScalarLabeledNodePtr>( );
    SectionPtr simple = ( SectionPtr ) new Section;
    SegmentPtr segaux;
    unsigned int pivot = begin;
    unsigned next = pivot + 1;
    unsigned int i;

    // While there's section left
    while ( pivot <= end )
    {
      if ( pivot != end )
        vaux.push_back( polyline[ pivot ] ); 

      // While there's section left and the tolerance is
      // greater than the distance between the two nodes
      while ( ( next <= end ) &&
              ( ( _distance( polyline[ pivot ]
                           , polyline[ next ] ) <= tolerance ) ) ) 
      {
        next++;
      } // while #1

      pivot = next;
      next++;
    } // while #2

    // The last node is never simplified.
    vaux.push_back( polyline[ end ] );

    // Create a section using the auxiliar vector
    for ( i = 0; i < ( vaux.size( ) - 1 ); i++ )
    {
      segaux = simple->addSegment( nullptr );
      segaux->begin( vaux[ i ] );
      segaux->end( vaux[ i + 1 ] );
    }

	  return simple;

	}	// simplifyRadialv1

  /*
   *  As the previous method, this method simplifies a Section, but
   *  the Section has not to be previously vectorized. Returns a 
   *  SectionPtr, unlike the v1 method, this one copies the attributes
   *  from the original Section into the new one. 
   */
  SectionPtr SimplifySection::simplifyRadialv2 ( SectionPtr polyline
                                  , float tolerance
                                  , NodePtr begin
                                  , NodePtr end )
  {
    if ( polyline->firstSegment( ) != polyline->lastSegment( ) )
    {
      // This structure will store the simplified section
      List<NodePtr>* simple = new List<NodePtr>( );
      NodePtr next;
      NodePtr pivot = polyline->lastSegment( )->end( );
      SegmentPtr segaux = polyline->lastSegment( );
      SegmentPtr backup;    

      // We move back until the last node is reached
      while ( pivot != end ) 
      {
        segaux = segaux->prev( );
        pivot = segaux->end( );
      }

      // Backup will keep track of the next Segment
      backup = segaux->next( );
      segaux->next( nullptr );

      // We move to the first node
      pivot = polyline->firstSegment( )->begin( );
      segaux = polyline->firstSegment( );
      while ( pivot != begin )
      {
        segaux = segaux->next( );
        pivot = segaux->begin( );
      }

      segaux = segaux->next( );
      next = segaux->begin( );

      // While there's Section left
      while ( pivot != end )
      {
        simple->push_back( pivot );
        
        // While there's section left and the tolerance is
        // greater than the distance between the two nodes
        while ( ( next != end ) &&
                ( _distance( pivot, next ) <= tolerance ) )
        {
          // If there's another Segment remaining, we advance.
          // Else 'next' will be the end node of the current Segment
          if ( segaux->next( ) )
          {
            segaux = segaux->next( );
            next = segaux->begin( ); 
          } else {
            next = segaux->end( );
          }          
        } // while #2

        pivot = next;
        if ( segaux->next( ) )
        {
          segaux = segaux->next( );
          next = segaux->begin( );
        } else {
          next = segaux->end( );
        }
      } // while #1

      // The last node is never simplified.
      simple->push_back( end );

      // Create the simplified Section using the auxiliar list
      SectionPtr simplifed = ( SectionPtr ) new Section( 
                                    polyline->neurite( )
                                  , polyline->parent( )
                                  , polyline->children( )
                                  , simple );

      delete simple;

      // Undo the change made in the beginning.
      segaux->next( backup );

      return simplifed;
    } else {
      return polyline;
    }
  } // simplifyRadialv2

  /*
   *  This method simplifies a Section previously vectorized
   *  using the Reumann-Witkam algorithm. Returns SectionPtr,  
   *  the attributes from the original Section are NOT copied,
   *  It must be done outside this function.
   */
  SectionPtr SimplifySection::simplifyRWv1 ( Vector<ScalarLabeledNodePtr> polyline
                                  , float tolerance
                                  , unsigned int begin
                                  , unsigned int end ) 
  {
    // This structure will store the simplified section
    Vector<ScalarLabeledNodePtr> vaux = Vector<ScalarLabeledNodePtr> ( );
    SectionPtr simple = ( SectionPtr ) new Section;
    SegmentPtr segaux;
    unsigned int iniSeg, endSeg, aux, i;

    // The first node is never simplified.
    vaux.push_back( polyline[ begin ] );

    // Define the begin and the end of the segment.
    iniSeg = begin;
    endSeg = ( begin + 1 );

    // While there's Section left
    while ( iniSeg < ( end - 1 ) )
    {
      aux = ( endSeg + 1 );

      // While there's Section left and the tolerance is greater than
      // the distance between the segment and the node.
      while ( ( aux <= end ) &&
              ( _perpDistance( polyline[ iniSeg ], 
                               polyline[ endSeg ], 
                               polyline[ aux ] ) ) <= tolerance )
      {
        aux++;
      } // while #2

      // Add to the simplified section the last node
      // that falls within the tolerance.
      vaux.push_back( polyline[ --aux ] );

      // Update the nodes that form the segment.
      if ( aux == endSeg )
      {
        iniSeg++;
        endSeg++;
      } else {
        iniSeg = aux;
        endSeg = ( iniSeg + 1 );
      }
    } // while #1

    // The last node is never simplified.
    vaux.push_back( polyline[ end ] );

    // Create a section using the auxiliar vector
    for ( i = 0; i < ( vaux.size( ) - 1 ); i++ )
    {
      segaux = simple->addSegment( nullptr );
      segaux->begin( vaux[ i ] );
      segaux->end( vaux[ i + 1 ] );
    }

    return simple;

  } // simplifyRWv1

  /*
   *  As the previous method, this method simplifies a Section, but
   *  the Section has not to be previously vectorized. Returns a 
   *  SectionPtr, unlike the v1 method, this one copies the attributes
   *  from the original Section into the new one. 
   */
  SectionPtr SimplifySection::simplifyRWv2 ( SectionPtr polyline
                                    , float tolerance
                                    , NodePtr begin
                                    , NodePtr end )
  {
    if ( polyline->firstSegment( ) != polyline->lastSegment( ) )
    {
      // This structure will store the simplified section
      List<NodePtr>* simple = new List<NodePtr>( );
      NodePtr aux, endSeg;
      NodePtr iniSeg = polyline->lastSegment( )->end( );
      SegmentPtr segaux = polyline->lastSegment( );
      SegmentPtr backup;  
      // 'in' is true when the previous node to the last is simplified.  
      bool in = false;

      // We move back until the last node is reached
      while ( iniSeg != end ) 
      {
        segaux = segaux->prev( );
        iniSeg = segaux->end( );
      }

      // Backup will keep track of the next Segment
      backup = segaux->next( );
      segaux->next( nullptr );

      // We move to the first node
      iniSeg = polyline->firstSegment( )->begin( );
      segaux = polyline->firstSegment( );
      while ( iniSeg != begin )
      {
        segaux = segaux->next( );
        iniSeg = segaux->begin( );
      }

      segaux = segaux->next( );
      endSeg = segaux->begin( );

      // The first node is never simplified.
      simple->push_back( begin );

      // While there's Section left
      while ( endSeg != end )
      {
        if ( segaux->next( ) )
        {
          segaux = segaux->next( );
          aux = segaux->begin( );
        } else {
          aux = segaux->end( );
          in = ( _perpDistance( iniSeg, endSeg, aux ) <= tolerance );
        }

        // While there's Section left and the tolerance is greater than
        // the distance between the segment and the node.
        while ( ( _perpDistance( iniSeg, endSeg, aux ) <= tolerance ) &&
                ( aux != end ) )
        {
          if ( segaux->next( ) )
          {
            segaux = segaux->next( );
            aux = segaux->begin( ); 
          } else {
            aux = segaux->end( );
          }    
        } // while #2

        // Add to the simplified section the last node
        // that falls within the tolerance.
        endSeg = aux;
        if ( aux != end )
        {
          iniSeg = segaux->prev( )->begin( );
        } else {
          iniSeg = segaux->begin( );
        }      
          
        if ( !in )
        {
          simple->push_back( iniSeg );
        }          
      } // while #1

      // The last node is never simplified.
      simple->push_back( end );

      // Create the simplified Section using the auxiliar list
      SectionPtr simplifed = ( SectionPtr ) new Section( 
                                      polyline->neurite( )
                                    , polyline->parent( )
                                    , polyline->children( )
                                    , simple );

      delete simple;

      // Undo the change made in the beginning.
      segaux->next( backup );

      return simplifed;
    } else {
      return polyline;
    }
  } // simplifyRWv2

  /*
   *  This method simplifies a Section previously vectorized
   *  using the Douglas-Peucker algorithm. Returns SectionPtr,  
   *  the attributes from the original Section are NOT copied,
   *  It must be done outside this function. This is the 
   *  non-recursive algorithm version.
   */
  SectionPtr SimplifySection::simplifyDP ( Vector<ScalarLabeledNodePtr> polyline
                                  , float tolerance
                                  , unsigned int begin
                                  , unsigned int end )
  {
    SectionPtr simple = ( SectionPtr ) new Section;    
    SegmentPtr segaux;

    if ( tolerance > 0 )
    {
      // This structure will store the simplified section
      Vector<ScalarLabeledNodePtr> vaux = Vector<ScalarLabeledNodePtr>( );      

      unsigned int len = polyline.size( ) - 1;
      // Vector of boolean that indicates which nodes won't be simplified.
      Vector<bool> markers ( len, false ); 

      int first = begin;
      int index = begin;
      int last  = end;
      int i;

      float maxDist, dist;

      // Stacks in order to avoid recursion
      List<int>* firstStack  = new List<int> ( );
      List<int>* lastStack   = new List<int> ( );

      // Both first and last nodes are never simplified.
      markers[ begin ] = markers[ end ] = true;

      while ( last != -1 )
      {
        maxDist = 0;

        // Look for the node to the maximum distance.
        for ( i = ( first + 1 ); i < ( int ) last; i++ )
        {
          dist = _perpDistance ( polyline[ first ]
                      , polyline[ last ]
                      , polyline[ i ] );

          if ( maxDist < dist )
          {
            index = i;
            maxDist = dist;
          } 
        } // for

        // If tolerance is greater than the maximum distance found.
        if ( maxDist >= tolerance )
        {
          // Include that node
          markers[ index ] = true;

          // Update the stacks
          firstStack->push_back( first );
          lastStack->push_back( index );

          firstStack->push_back( index );
          lastStack->push_back( last );
        } // if

        // Continue if not empty
        if ( ! firstStack->empty( ) )
        {
          first = firstStack->back( );
          firstStack->pop_back( );
        } else
          first = -1;

        // Continue if not empty
        if ( ! lastStack->empty( ) )
        {
          last = lastStack->back( );
          lastStack->pop_back( );     
        } else
          last = -1;

      } // while 

      // Add to the vector the nodes that 
      // were not simplified.
      for ( i = begin; i <= (int)end; i++ )
      {
        if ( markers[ i ] )
          vaux.push_back( polyline[ i ] );
      }

      // Create a section using the auxiliar vector
      for ( i = 0; i < (int)( vaux.size( ) - 1 ); i++ )
      {
        segaux = simple->addSegment( nullptr );
        segaux->begin( vaux[ i ] );
        segaux->end( vaux[ i + 1 ] );
      }

      delete firstStack;
      delete lastStack;

    } else {

      for ( unsigned int i = begin; i < end ; i++ )
      {
        segaux = simple->addSegment( nullptr );
        segaux->begin( polyline[ i ] );
        segaux->end( polyline[ i + 1 ] );
      }
    } // else

    return simple;

  } // simplifyDP


  /*
   *  This method vectorizes a Section. In order to vectorize the entire
   *  Section, 'begin' and 'end' should point to null.
   */ 
  Vector<ScalarLabeledNodePtr> SimplifySection::_vectorize ( SectionPtr polyline 
                                        , ScalarLabeledNodePtr begin = nullptr
                                        , ScalarLabeledNodePtr end = nullptr ) 
  {
    SegmentPtr segment = polyline->firstSegment( );
    Vector<ScalarLabeledNodePtr> vaux = Vector<ScalarLabeledNodePtr>( );

    if ( begin )
    {
      while ( segment->begin( ) != begin )
      {
        segment = segment->next( );
      }
    }

    begin = end;

    vaux.push_back( dynamic_cast<ScalarLabeledNodePtr> ( segment->begin( ) ) );

	  while ( segment ) 
	  {
	    vaux.push_back( dynamic_cast<ScalarLabeledNodePtr> ( segment->end( ) ) );
	    segment = segment->next( );
	  }

    return vaux;
  } // _vectorize

  /*
   *  This method calculates the average relevance of the nodes between
   *  'begin' and 'end'
   */
  float SimplifySection::_average ( Vector<ScalarLabeledNodePtr> vaux
                            , unsigned int begin
                            , unsigned int end )
  {
    unsigned int i;
    float sum = 0;

    for ( i = begin; i <= end; i++)
    {
      sum += vaux[ i ]->relevance( );
    }

    return ( sum / ( float ) (( end - begin ) + 1 ) );
  } // _average

  /*
   *  This method returns the cross product of two 3D vectors.
   */ 
  Vec3f SimplifySection::_crossProduct( Vec3f a, Vec3f b )
  {
    float cx = ( ( a.y() * b.z() ) - ( a.z() * b.y() ) );
    float cy = ( ( a.z() * b.x() ) - ( a.x() * b.z() ) );
    float cz = ( ( a.x() * b.y() ) - ( a.y() * b.x() ) );  

    return Vec3f( cx, cy, cz );  
  } // _crossProduct

  /*
   *  This method returns the subtraction of two 3D vectors.
   */ 
  Vec3f SimplifySection::_subtract( Vec3f a, Vec3f b )
  {
    return Vec3f( a.x( ) - b.x( )
                , a.y( ) - b.y( )
                , a.z( ) - b.z( ) );
  } // _subtract

  /*
   *  This method returns the length of the 3D vector.
   */ 
  float SimplifySection::_length( Vec3f v )
  {
    return sqrtf( v.x( ) * v.x( ) 
                + v.y( ) * v.y( )
                + v.z( ) * v.z( ) );
  } // _length

  /*
   *  This method calculates the minimum distance between
   *  a segment defined by two nodes, and another node.
   */ 
  float SimplifySection::_perpDistance( NodePtr p1
					                   , NodePtr p2
					                   , NodePtr point )
  {
    Vec3f x0 = point->point( );
    Vec3f x1 = p1->point( );
    Vec3f x2 = p2->point( );

    return  ( _length( _crossProduct( _subtract( x2, x1 ), 
                                      _subtract( x1, x0 ) ) ) / 
              _length( _subtract( x2, x1 ) ) );
  
  } // _perpDistance

  /*
   *  This method calculates the distance between two nodes.
   */ 
  float SimplifySection::_distance( NodePtr p1, NodePtr p2 )
  {
    float xSqr = (double)(p1->point( ).x( ) - p2->point( ).x( )) * 
                 (p1->point( ).x( ) - p2->point( ).x( ));
    float ySqr = (double)(p1->point( ).y( ) - p2->point( ).y( )) *
                 (p1->point( ).y( ) - p2->point( ).y( ));
    float zSqr = (double)(p1->point( ).z( ) - p2->point( ).z( )) *
                 (p1->point( ).z( ) - p2->point( ).z( ));

    float mySqr = (double) xSqr + ySqr + zSqr;

    return sqrt(mySqr);

  } // _distance

} // class nsol

// EOF
