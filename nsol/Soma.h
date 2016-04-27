/**
 * @file    Soma.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SOMA__
#define __NSOL_SOMA__

#include <nsol/api.h>
#include "Container/Nodes.h"

namespace nsol
{

  class SomaStats;

  //!  Class to represent the soma of neurons
  /*!
    This class represents the soma and holds a container of the nodes
    that have been traced of its contour
  */
  class Soma
  {

  public:

    /**
     * Default constructor
     */
    NSOL_API
    Soma( );

    /**
     * Destructor
     */
    NSOL_API
    virtual ~Soma( );

    /**
     * Method to get the center of the soma
     * @return center of the soma
     */
    NSOL_API
    Vec3f center( void ) const;

    /**
     * Method to get the container of nodes
     * @return container with all the nodes of the soma
     */
    NSOL_API
    Nodes & nodes( void );

    /**
     * Method to get the max radius of the soma
     * @return max radius of the soma
     */
    NSOL_API
    const float & maxRadius( void ) const;

    /**
     * Method to get the mean radius of the soma
     * @return mean radius of the soma
     */
    NSOL_API
    const float & meanRadius( void ) const;

    /**
     * Method to set the center of the soma
     * @param center of the soma
     */
    NSOL_API
    void center( Vec3f center_ );

    /**
     * Method to add a node to the soma
     * @param node pointer to the node to add
     */
    NSOL_API
    void addNode( NodePtr node );

    NSOL_API
    virtual const SomaStats * stats( void ) const
    {
      return nullptr;
    }

    NSOL_API
    SomaPtr clone( void ) const;

    NSOL_API
    bool operator == ( Soma & other );

    NSOL_API
    bool operator != ( Soma & other );

  protected:

    //! Center of the soma
    Vec3f _center;

    //! Container of nodes of the soma
    Nodes _nodes;

    //! Maximum radius of the soma
    float _maxRadius;

    //! Mean radius of the soma
    float _meanRadius;

  private:


    void _recalculateParams( void );


  }; // class Soma

} // namespace nsol

#endif // __NSOL_SOMA__

// EOF
