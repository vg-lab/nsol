/**
 * @file    NodeWithProperties.cpp
 * @brief
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include "NodeWithProperties.h"

namespace nsol
{

  NodeWithProperties::NodeWithProperties( const Vec3f & point_,
      const int & id_,
      const float & radius_ )
    :Node( point_, id_, radius_ )
  {

  }

  NodeWithProperties::~NodeWithProperties( void )
  {
  }

  NodeWithPropertiesPtr NodeWithProperties::properties( void )
  {
#ifdef NSOL_WITH_FIRES
    return this;
#else
    return nullptr;
#endif
  }

  NodeWithPropertiesPtr NodeWithProperties::create( void ) const
  {
    return new NodeWithProperties;
  }

  NodeWithPropertiesPtr NodeWithProperties::clone( void )
  {
    NodeWithPropertiesPtr newNode = new NodeWithProperties( Vec3f( this->point( )),
        this->id( ), this->radius( ));

#ifdef NSOL_WITH_FIRES

    NSOL_FOREACH( feature, this->properties()->getFeatures( ))
    {
      newNode->properties()->registerFeature( (*feature).first,
          (*feature).second );
    }

#endif

    return newNode;
  }

} // namespace nsol

// EOF
