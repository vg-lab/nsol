/**
 * @brief   General object class
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_OBJECT_USE_PROPERTIES__
#define __NSOL_OBJECT_USE_PROPERTIES__

#include <nsol/api.h>
#include "Object.h"
#include "NsolTypes.h"

#ifdef NSOL_USE_FIRES
#include <fires/fires.h>
#endif

namespace nsol
{

  class ObjectWithProperties
    : public virtual Object
#ifdef NSOL_USE_FIRES
    , public fires::Object
#endif
  {
  public:

    NSOL_API
    ObjectWithProperties( void );

    NSOL_API
    virtual ~ObjectWithProperties( void );

    NSOL_API
    virtual ObjectWithPropertiesPtr properties( void );

    virtual ObjectPtr create( void )
    {
      return new ObjectWithProperties;
    }
  };


} // namespace nsol


#endif
