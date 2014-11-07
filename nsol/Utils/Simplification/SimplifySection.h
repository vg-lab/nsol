/**
 * @file    Section_Simplify.h
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 * Do not distribute without further notice.
 */
#ifndef __NSOL_SECTION_SIMPLIFY__
#define __NSOL_SECTION_SIMPLIFY__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Node.h>
#include <nsol/Segment.h>
#include <nsol/Section.h>

namespace nsol
{
  class Section_Simplify
  {
  public:

    NSOL_API
    SectionPtr simplify ( SectionPtr polyline 
				          , float tolerance
                  , int range
                  , float threshold );

    NSOL_API
    SectionPtr simplifyRadial ( SectionPtr polyline
                  , float tolerance
                  , NodePtr begin
                  , NodePtr end );

    NSOL_API
    SectionPtr simplifyRW ( SectionPtr polyline
                    , float tolerance
                    , NodePtr begin
                    , NodePtr end );

  private:    

    NSOL_API
    void _vectorize ( SectionPtr polyline
			       , Vector<NodePtr> & vaux
             , NodePtr begin
             , NodePtr end );

    NSOL_API
    float _average ( SectionPtr polyline
             , NodePtr begin
             , NodePtr end );
  };

} // namespace nsol

#endif

// EOF
