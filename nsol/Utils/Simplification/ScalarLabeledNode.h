/**
 * @file    NodeRelevance.h
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_NODERELEVANCE__
#define __NSOL_NODERELEVANCE__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Node.h>

namespace nsol
{

  class NodeRelevance : public Node
  {

  public:

    NSOL_API
    NodeRelevance( const Vec3f & point = Vec3f(0,0,0), 
	  			const int &id = 0, 
	  			const float &radius = 0.0f,
					const float &importancia = 0.0f );

    NSOL_API
    float & relevance( void );

    NSOL_API
    float relevance( void ) const;

    NSOL_API
    bool operator == ( NodeRelevance & other ) const;
    
    NSOL_API
    bool operator != ( NodeRelevance & other ) const;

  private:

    float _relevance;

  };

} // namespace nsol

#endif

// EOF
