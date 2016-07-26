#include "ObjectWithProperties.h"
#include "Log.h"

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
#ifdef NSOL_USE_FIRES
    return this;
#else
    Log::log( "No properties available. FiReS not supported.",
              LOG_LEVEL_WARNING );
    return nullptr;
#endif
  }


}
