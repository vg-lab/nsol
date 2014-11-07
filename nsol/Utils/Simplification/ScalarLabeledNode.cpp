/**
 * @file    NodeRelevance.cpp
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include "NodeRelevance.h"

namespace nsol
{

  NodeRelevance::NodeRelevance( const Vec3f &point, 
	      const int &id, 
	      const float &radius,
				const float &relevance )
    : Node ( point, id, radius )
    , _relevance( relevance )
  {
  }
  
  float & NodeRelevance::relevance(void)
  {
    return _relevance;
  }
  
  float NodeRelevance::relevance(void) const
  {
    return _relevance;
  }

  bool NodeRelevance::operator == ( NodeRelevance & other ) const
  {
    return ( ( this->id( ) == other.id( ) ) &&
	     ( this->radius( ) == other.radius( ) ) &&
	     ( this->point( ) == other.point( ) ) &&
			 ( this->relevance( ) == other.relevance( ) ) ); 
  }
  
  bool NodeRelevance::operator != ( NodeRelevance & other ) const
  {
    return ! ( *this == other );
  }
  
} // namespace nsol

// EOF
