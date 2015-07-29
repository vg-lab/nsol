/**
 * @brief   General object class
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NODE_WITH_PROPERTIES__
#define __NSOL_NODE_WITH_PROPERTIES__

#include <nsol/api.h>
#include "../NsolTypes.h"
#include "../Node.h"
#include "ObjectWithProperties.h"


namespace nsol
{
  class NodeWithProperties
    : public Node
    , public ObjectWithProperties
  {
  public:

    NSOL_API
    NodeWithProperties( const Vec3f & point_ = Vec3f(0,0,0),
        const int & id_ = 0,
        const float & radius_ = 0.0f );

    NSOL_API
    virtual
    ~NodeWithProperties( void );

    NSOL_API
    virtual
    NodeWithPropertiesPtr create( void ) const;

    NSOL_API
    virtual
    NodeWithPropertiesPtr clone( void );


  };


} // namespace nsol


#endif
