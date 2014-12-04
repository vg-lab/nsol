/**
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_DENDRITE__
#define __NSOL_DENDRITE__

#include <nsol/api.h>
#include "Neurite.h"

namespace nsol
{

  class Dendrite : public virtual Neurite
  {

  public:

    //! Type of dendrite
    typedef enum TDendriteType
    {
      BASAL = 0,
      APICAL
    } TDendriteType;

    friend std::ostream & operator<< ( std::ostream & os,
                                       const TDendriteType & rhs)
    {
      switch ( rhs )
      {
      case BASAL:
        return os << "BASAL";
        break;
      case APICAL:
        return os << "APICAL";
        break;
      default:
        return os << "UNDEFINED";
      }
      return os;
    }

    NSOL_API
    Dendrite ( TDendriteType dendriteType = BASAL );

    //! Get the type of neurite
    NSOL_API
    TDendriteType & dendriteType( void );

  protected:

    //! Type of dendrite
    TDendriteType _dendriteType;

  }; // class Dendrite


} // namespace nsol


#endif

// EOF
