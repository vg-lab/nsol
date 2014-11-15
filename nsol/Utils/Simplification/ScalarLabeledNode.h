/**
 * @file    NodeRelevance.h
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_SCALARLABELEDNODE__
#define __NSOL_SCALARLABELEDNODE__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Node.h>

namespace nsol
{

  class ScalarLabeledNode : public Node
  {

  public:

    NSOL_API
    ScalarLabeledNode( const Vec3f & initPoint = Vec3f(0,0,0) 
	  			, const int &initId = 0 
	  			, const float &initRadius = 0.0f
					, const float &initRelevance = 0.0f );

    NSOL_API  
    virtual ~ScalarLabeledNode( void );

    NSOL_API
    float & relevance( void );

    NSOL_API
    float relevance( void ) const;

    NSOL_API
    bool operator == ( ScalarLabeledNode & other ) const;
    
    NSOL_API
    bool operator != ( ScalarLabeledNode & other ) const;

  private:

    float _relevance;

  };

} // namespace nsol

#endif

// EOF
