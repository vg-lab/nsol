/**
 * @file    SimplifySection.h
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 * Do not distribute without further notice.
 */
#ifndef __NSOL_SIMPLIFYSECTION__
#define __NSOL_SIMPLIFYSECTION__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Node.h>
#include <nsol/Section.h>
#include <nsol/Utils/Simplification/ScalarLabeledNode.h>

namespace nsol
{
  class SimplifySection
  {

  public:

    NSOL_API
    SectionPtr simplify ( SectionPtr polyline 
				          , float tolerance
                  , int range
                  , float threshold );

    NSOL_API
    SectionPtr simplifyRadialv1 ( Vector<NodePtr> polyline
                  , float tolerance
                  , unsigned int begin
                  , unsigned int end );

    NSOL_API  
    SectionPtr simplifyRadialv2 ( SectionPtr polyline
                  , float tolerance
                  , NodePtr begin
                  , NodePtr end );

    NSOL_API
    SectionPtr simplifyRWv1 ( Vector<NodePtr> polyline
                  , float tolerance
                  , unsigned int begin
                  , unsigned int end );

    NSOL_API
    SectionPtr simplifyRWv2 ( SectionPtr polyline
                  , float tolerance
                  , NodePtr begin
                  , NodePtr end );

    NSOL_API
    SectionPtr simplifyDP ( Vector<NodePtr> polyline
                  , float tolerance
                  , unsigned int begin
                  , unsigned int end );

  //private:    

    NSOL_API
    Vector<NodePtr> _vectorize ( SectionPtr polyline
                        , NodePtr begin
                        , NodePtr end );
    
    private:

    NSOL_API
    float _average ( Vector<ScalarLabeledNodePtr> polyline
             , unsigned int begin
             , unsigned int end );

    NSOL_API
    Vec3f _crossProduct( Vec3f a, Vec3f b );

    NSOL_API
    Vec3f _subtract( Vec3f a, Vec3f b );

    NSOL_API
    float _length( Vec3f v );

    NSOL_API
    float _perpDistance ( NodePtr p1
             , NodePtr p2
             , NodePtr point );    

    NSOL_API
    float _distance ( NodePtr p1, NodePtr p2);

  };

} // namespace nsol

#endif

// EOF
