/**
 * @file    Object.h
 * @brief
 * @author  Juan Guerrero <j.guerrerom@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_OBJECT__
#define __NSOL_OBJECT__

namespace nsol
{

  /*! \class Object
    \brief A class to represent any NSOL object.

    TODO: extend long description
  */
  class Object
  {

  public:

    Object( void );

    virtual ~Object( void );

  };

  /**
   * @type ObjectPtr
   * @brief This type is a pointer to a nsol object.
   */
  //I don't know where I have to declare this
  typedef Object* ObjectPtr;

}

#endif /* OBJECT_H_ */
