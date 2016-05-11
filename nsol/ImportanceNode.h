/**
 * @file ImportanceNode.h
 * @brief
 * @author Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remark Copyright (c) GMRV/URJC. All rights reserved.
           Do not distribute without further notice.
*/
#ifndef __NSOL_IMPORTANCENODE__
#define __NSOL_IMPORTANCENODE__

#include <nsol/api.h>
#include "Node.h"

namespace nsol
{

  class ImportanceNode
    : public Node
  {

    NSOL_API
    ImportanceNode( const Vec3f & point = Vec3f(0,0,0),
                    const int & id = 0,
                    const float & radius = 0.0f );


    NSOL_API
    unsigned int & importance( void );

    NSOL_API
    unsigned int importance( void ) const;

    NSOL_API
    virtual NodePtr clone( void ) const;

  protected:

    unsigned int _importance;

  };

} // namespace nsol

#endif

// EOF
