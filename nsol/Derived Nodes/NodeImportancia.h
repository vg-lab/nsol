/**
 * @file    NodeImportancia.h
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_NODEIMPORTANCIA__
#define __NSOL_NODEIMPORTANCIA__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Node.h>

namespace nsol
{

  class NodeImportancia : public Node
  {

  public:

    NSOL_API
    NodeImportancia( const Vec3f & point = Vec3f(0,0,0), 
	  			const int &id = 0, 
	  			const float &radius = 0.0f,
					const float &importancia = 0.0f );

    NSOL_API
    float & importancia( void );

    NSOL_API
    float importancia( void ) const;

    NSOL_API
    bool operator == ( NodeImportancia & other ) const;
    
    NSOL_API
    bool operator != ( NodeImportancia & other ) const;

  private:

    float _importancia;

  };

} // namespace nsol

#endif

// EOF
