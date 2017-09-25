/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
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
     * Method to get the min radius of the soma
     * @return min radius of the soma
     */
    NSOL_API
    const float & minRadius( void ) const;

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
    virtual SomaPtr clone( void ) const;

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

    //! Minimum radius of the soma
    float _minRadius;

    //! Mean radius of the soma
    float _meanRadius;

  private:


    void _recalculateParams( void );


  }; // class Soma

} // namespace nsol

#endif // __NSOL_SOMA__

// EOF
