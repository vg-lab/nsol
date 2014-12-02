/**
 * @file    SomaStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SOMASTATS__
#define __NSOL_SOMASTATS__

#include "../Soma.h"

namespace nsol
{


  class SomaStats : public Soma
  {

  public:

    typedef enum
    {
      SURFACE = 0,
      VOLUME,
      SOMA_NUM_STATS
    } TSomaStat;


    /**
     * Default constructor
     */
    NSOL_API
    SomaStats( );

    /**
     * Destructor
     */
    NSOL_API
    virtual ~SomaStats( );

    NSOL_API
    virtual const SomaStats * stats( void ) const;

    virtual float getStat( TSomaStat stat ) const;


  };

} // namespace nsol

#endif // __NSOL_SOMASTATS__
