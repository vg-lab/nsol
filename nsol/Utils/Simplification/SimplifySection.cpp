/**
 * @file    Section_Simplify.cpp
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "Section_Simplify.h"

#include <math.h>

namespace nsol
{

  /*
   *  Método que divide en grupos la Section, 
   *  si la importancia supera un umbral simplifica
   *  con Reumann-Witkam, si no, simplifica con
   *  un algoritmo radial y luego con Douglas-Peucker
   */
  SectionPtr Section_Simplify::simplify ( SectionPtr polyline
                               , float tolerance
                               , int range
                               , float threshold )
  {
    NodePtr begin = polyline->firstSegment( )->begin( );
    NodePtr naux = polyline->firstSegment( )->begin( );
    NodePtr end = nullptr;
    SegmentPtr saux = polyline->firstSegment( );
    SectionPtr simple = new Section( );
    SectionPtr sectaux = new Section( );
    bool highestQuality;

    float reference = begin->relevance( );
    while ( naux != polyline->lastSegment( )->end( ) )
    {
      while ( ( naux.relevance( ) <= reference + range ) && 
              ( naux.relevance( ) >= reference - range))
      {
        end = naux;

        if ( aux != polyline->lastSegment->end( ) )
        {
          saux = saux->next( );
          naux = saux->begin( );
        }

        if ( naux == nullptr )
          break;
      } // while #2

      highestQuality = ( _average( polyline, begin, end ) > threshold );

      if ( ! highestQuality ) 
      {
        sectaux = simplifyRadial ( polyline, tolerance,
                                   begin, end );
        //sectaux = simplifyDP ( polyline, tolerance,
        //                       begin, end );
      } else 
      {
        //sectaux = simplifyRW ( polyline, tolerance, 
        //                       begin, end );
      }
    } // while #1

    return simple;
  }


  /*
   *	Método que simplifica una Section dada una tolerancia utilizando un algoritmo radial.
   *	Utiliza un vector como estructura auxiliar para recorrer la polilinea, en lugar de usar 
   *  una Section.
   */
  SectionPtr Section_Simplify::simplifyRadial ( SectionPtr polyline
                                    , float tolerance
                                    , NodePtr begin
                                    , NodePtr end ) 
  {
    unsigned int index = 0;
    Vector<NodePtr> vaux = Vector<NodePtr>( );
    NodePtr naux = nullptr;
    NodePtr pivot = nullptr;
    List<NodePtr> simple = List<NodePtr>( );
		
    _vectorize( polyline, vaux, begin, end );		
		
    pivot = vaux[ 0 ];
    while ( pivot != polyline->lastSegment( )->end( ) )
    {
      simple.push_back( pivot );
			
      naux = vaux[ index++ ];
	    while ( tolerance >= (( pivot->point( ) - naux->point( ) )
                            .length( ) ) )
	    {
  	    naux = vaux[ index++ ];
  		
  	    if ( index == ( vaux.size( ) - 1 ) )
  		    break;
  		} // while

	    pivot = naux;
	  }  // while

	  simple.push_back( polyline->lastSegment( )->end( ) );

	  SectionPtr s = ( SectionPtr ) ( new Section ( polyline->neurite( )
                                    			, polyline->parent( )
                                    			, polyline->childs( ,
                                          , simple ) );
	  simple.clear( );

	  return s;

	}	// simplifyRadial


  SectionPtr Section_Simplify::simplifyRW ( SectionPtr polyline 
                                  , float tolerance
                                  , NodePtr begin
                                  , NodePtr end )
  {
    SegmentPtr saux = polyline.firstSegment( );
    SegmentPtr straight = new Segment( );
    List<NodePtr> simple = List<NodePtr>( );

    while ( saux->begin( ) != begin )
    {
      saux = saux->next( );
    }

    simple.push_back( saux->begin( ) );
    straight = saux;
    saux = saux->next( );

    while ( saux != polyline->lastSegment( ))
    {
      while (( saux ) && 
             ( _perpDistance( straight, saux->begin( )) ))
      {
        saux = saux->next( );
      } // while #2

      saux = saux->prev( );
      simple.push_back( saux->end( ) );

      saux = saux->next( );
      straight = saux;
    } // while #1
  }


  /*
   *	Método que inicializa un vector de nodos utilizando una Section de origen.
   */ 
  void Section_Simplify::_vectorize ( SectionPtr polyline 
                              , Vector<NodePtr> & vaux
                              , NodePtr begin
                              , NodePtr end ) 
  {
	  SegmentPtr seg_aux = polyline->firstSegment( );

    if ( begin )
    {
      while ( seg_aux->begin( ) != begin )
      {
        seg_aux = seg_aux->next( );
      }
    }

	  while (( seg_aux != polyline->lastSegment( )) ||
           ( seg_aux->end( ) != end )) 
	  {
	    vaux.push_back( seg_aux->begin( ) );
	    seg_aux = seg_aux->next( );
	  }

	  vaux.push_back ( seg_aux->end( ) );
  } // _vectorize
} // class nsol

// EOF
