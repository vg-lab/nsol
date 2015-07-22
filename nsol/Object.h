/**
 * @brief   General object class
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_OBJECT__
#define __NSOL_OBJECT__

#include <nsol/api.h>
#include "NsolTypes.h"

namespace nsol
{

  class Object
  {
  public:

    NSOL_API
    Object( void );

    NSOL_API
    virtual ~Object( void );

    NSOL_API
    virtual ColumnPtr asColumn( void );

    NSOL_API
    virtual MiniColumnPtr asMiniColumn( void );

    NSOL_API
    virtual
    NeuronPtr asNeuron( void );

    NSOL_API
    virtual
    NeuronMorphologyPtr asNeuronMorphology( void );

    NSOL_API
    virtual
    SectionPtr asSection( void );

    NSOL_API
    virtual
    SegmentPtr asSegment( void );

    NSOL_API
    virtual
    NodePtr asNode( void );

    NSOL_API
    virtual ObjectWithProperties* properties( void );

  };


} // namespace nsol


#endif
