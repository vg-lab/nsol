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
#include <queue>
#include <iostream>

namespace nsol
{
  /*
   *  This method simplifies a Section previously vectorized
   *  using the Radial algorithm. Returns SectionPtr, the 
   *  attributes from the original Section are NOT copied,
   *  It must be done outside this function.
   */
  SectionPtr SimplifySection::_simplifyRadial ( 
                                      Vector<NodePtr> polyline
                                    , float tolerance
                                    , unsigned int begin
                                    , unsigned int end ) 
  {
    // This structure will store the simplified section
    Vector<NodePtr> vaux = Vector<NodePtr>( );
    SectionPtr simple = ( SectionPtr ) new Section;
    SegmentPtr segaux;
    unsigned int pivot = begin;
    unsigned int next = pivot + 1;
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
      segaux = ( SegmentPtr ) new Segment( );
      segaux->begin( vaux[ i ] );
      segaux->end( vaux[ i + 1 ] );
      segaux->parentSection( simple );

      simple->addSegment( segaux );
    }

	  return simple;

	}	// simplifyRadial

  /*
   *  This method simplifies a Section previously vectorized
   *  using the Reumann-Witkam algorithm. Returns SectionPtr,  
   *  the attributes from the original Section are NOT copied,
   *  It must be done outside this function.
   */
  SectionPtr SimplifySection::_simplifyRW ( Vector<NodePtr> polyline
                                  , float tolerance
                                  , unsigned int begin
                                  , unsigned int end ) 
  {
    // This structure will store the simplified section
    Vector<NodePtr> vaux = Vector<NodePtr> ( );
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
      segaux = ( SegmentPtr ) new Segment( );
      segaux->begin( vaux[ i ] );
      segaux->end( vaux[ i + 1 ] );
      segaux->parentSection( simple );      

      simple->addSegment( segaux );
    }

    return simple;

  } // simplifyRW

  /*
   *  This method simplifies a Section previously vectorized
   *  using the Douglas-Peucker algorithm. Returns SectionPtr,  
   *  the attributes from the original Section are NOT copied,
   *  It must be done outside this function. This is the 
   *  non-recursive algorithm version.
   */
  SectionPtr SimplifySection::_simplifyDP ( Vector<NodePtr> polyline
                                  , float tolerance
                                  , unsigned int begin
                                  , unsigned int end )
  {
    SectionPtr simple = ( SectionPtr ) new Section;    
    SegmentPtr segaux;

    if ( tolerance > 0 )
    {
      // This structure will store the simplified section
      Vector<NodePtr> vaux = Vector<NodePtr>( );      

      unsigned int len = polyline.size( ) - 1;
      // Vector of boolean that indicates which nodes won't be simplified.
      Vector<bool> markers ( len, false ); 

      int first = begin;
      int index = begin;
      int last  = end;
      int i;

      float maxDist, dist;

      // Stacks used in order to avoid recursion
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
        segaux = ( SegmentPtr ) new Segment( );
        segaux->begin( vaux[ i ] );
        segaux->end( vaux[ i + 1 ] );  
        segaux->parentSection( simple );  

        simple->addSegment( segaux );
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
   * This method simplifies a neuron received as param and returns a new one.
   * Nodes are shared though. Algorithm must be a number between 1 and 3. 
   */
  NeuronMorphologyPtr SimplifySection::simplifyNeuron( NeuronMorphologyPtr neuron
                                              , int algorithm
                                              , float tolerance )
  {
    if ( neuron == nullptr ) 
    {
      NSOL_THROW( "Error: Neuron is empty" );
      return nullptr;
    }

    // Queue used in order to breadth traverse the neuron
    std::deque<SectionPtr> q_sections;
    // Vector used to store every simplified section
    nsol::Vector<SectionPtr> q_simples;
    // Vector used to store every section which is parent (has children)
    nsol::Vector<SectionPtr> q_parents;
    // Queue used to store the position of the parents in the q_parents queue
    std::deque<int> q_index;

    // Actual section simplified
    nsol::SectionPtr simple = nullptr;
    // Neuron simplified
    NeuronMorphologyPtr _simplifiedNeuron = 
            ( NeuronMorphologyPtr ) new NeuronMorphology( neuron->soma( ) );

    // Iterate over the neurites
    for ( Neurites::const_iterator it = neuron->neurites( ).begin( ); 
                                   it != neuron->neurites( ).end( );
                                   it++ )
    {
      // Create simplified neurite
      NeuritePtr naux = *it;

      nsol::SectionPtr section = naux->firstSection( );
      switch ( naux->neuriteType( ) )
      {
        case Neurite::DENDRITE:
        {
          DendritePtr dendrite = NSOL_DYNAMIC_CAST( Dendrite, naux );
          naux = ( NeuritePtr ) new Dendrite( dendrite->dendriteType( ));
          break;
        }
        case Neurite::AXON:
        {
          naux = new nsol::Axon( );
          break;
        }
        default:
        {
          NSOL_THROW( "Warning: Unknown neurite type, cannot cast" );
          return nullptr;
        }
      } // switch

      // Add it to the simplifed neuron
      naux->morphology( _simplifiedNeuron );
      _simplifiedNeuron->addNeurite( naux );

      // Iterate over the sections of the neurite
      q_sections.push_back( section );
      while ( ! q_sections.empty( ) )
      {
        section = q_sections.front( );
        q_sections.pop_front( );


        nsol::Vector<NodePtr> vaux = _vectorize( section
                                                , nullptr
                                                , nullptr );

        switch ( algorithm )
        {
          case 1:
          {
            simple = _simplifyRadial( vaux
                                , tolerance
                                , 0
                                , ( vaux.size( ) - 1 ) );
            break;
           }
          case 2:
          {
            simple = _simplifyRW( vaux
                            , tolerance
                            , 0
                            , ( vaux.size( ) - 1 ) );
            break;
          }
          case 3:
          {
            simple = _simplifyDP( vaux
                          , tolerance
                          , 0
                          , ( vaux.size( ) - 1 ) );
            break;
          }
          default:
          {
            NSOL_THROW( "Warning: No algorithm specified" );
            return nullptr;
          }
        } // switch

        // Check if I have children, if so, I add myself to parent's list
        // And add to q_index my position in parent's list, 
        // that way my children know where I am.
        if ( !section->children( ).empty( ) )
        {
          q_parents.push_back( simple );

          // Iterate over the children
          Sections childs = section->children( );
          for ( Sections::iterator it2 = childs.begin( ); 
                                  it2 != childs.end( ); it2++ )
          {
            q_sections.push_back( *it2 );
            q_index.push_back( ( q_parents.size( ) - 1 ) );
          } // 
        }

        // Store its neurite
        simple->neurite( naux );
          
        // If it has parent, look for it in the parent's list using q_index
        if ( section->parent( ) != nullptr )
        {
          simple->parent( q_parents[ q_index.front( ) ] );
          q_index.pop_front( );
          simple->parent( )->addChild( simple );
        } else
          simple->parent( nullptr );

        // Add the simplified section to the list
        q_simples.push_back( simple );

      } // while

      // This neurite is now simplified, so we store its first section
      naux->firstSection( q_simples.front( ) );

      // Delete every data structure.
      q_simples.clear( );
      q_parents.clear( );
      q_index.clear( );

    } // for

    return _simplifiedNeuron;

  } // simplifyNeuron

  /*
   *  This method vectorizes a Section. In order to vectorize the entire
   *  Section, 'begin' and 'end' should point to null.
   */ 
  Vector<NodePtr> SimplifySection::_vectorize ( SectionPtr polyline 
                                        , NodePtr begin = nullptr
                                        , NodePtr end = nullptr ) 
  {
    SegmentPtr segment = polyline->firstSegment( );
    Vector<NodePtr> vaux = Vector<NodePtr>( );

    if ( begin )
    {
      while ( segment->begin( ) != begin )
      {
        segment = segment->next( );
      }
    }

    begin = end;

    vaux.push_back( dynamic_cast<NodePtr> ( segment->begin( ) ) );

	  while ( segment ) 
	  {
	    vaux.push_back( dynamic_cast<NodePtr> ( segment->end( ) ) );
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
      sum += vaux[i]->relevance( );
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
