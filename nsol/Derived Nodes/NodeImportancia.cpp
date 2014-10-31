/**
 * @file    NodeImportancia.cpp
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include "NodeImportancia.h"

namespace nsol
{

  NodeImportancia::NodeImportancia( const Vec3f &point, 
	      const int &id, 
	      const float &radius,
				const float &importancia )
    : Node ( point, id, radius )
    , _importancia( importancia )
  {
  }
  
  float & NodeImportancia::importancia(void)
  {
    return _importancia;
  }
  
  float NodeImportancia::importancia(void) const
  {
    return _importancia;
  }

  bool NodeImportancia::operator == ( NodeImportancia & other ) const
  {
    return ( ( this->id( ) == other.id( ) ) &&
	     ( this->radius( ) == other.radius( ) ) &&
	     ( this->point( ) == other.point( ) ) &&
			 ( this->importancia( ) == other.importancia( ) ) ); 
  }
  
  bool NodeImportancia::operator != ( NodeImportancia & other ) const
  {
    return ! ( *this == other );
  }
  
} // namespace nsol

// EOF
