#include "ObjectWithProperties.h"
#include "../Log.h"

namespace nsol
{

  ObjectWithProperties::ObjectWithProperties( void )
  {
  }

  ObjectWithProperties::~ObjectWithProperties( void )
  {
  }

  ObjectWithPropertiesPtr ObjectWithProperties::properties( void )
  {
#ifdef NSOL_WITH_FIRES
    return this;
#else
    Log::log( "No properties available. FiReS not supported.",
              NSOL_LOG_WARNING );
    return nullptr;
#endif
  }

  ObjectWithPropertiesPtr ObjectWithProperties::create( void ) const
  {
    return new ObjectWithProperties;
  }

  ObjectWithPropertiesPtr ObjectWithProperties::clone( void )
  {
    ObjectWithPropertiesPtr newObject = create( );

#ifdef NSOL_WITH_FIRES

    NSOL_FOREACH( feature, this->properties()->getFeatures( ))
    {
      newObject->properties()->registerFeature( (*feature).first,
          (*feature).second );
    }

#endif

    return newObject;
  }


}
