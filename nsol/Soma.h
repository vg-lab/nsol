/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
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

#include <nsol/nsol_export.h>
#include "Container/Nodes.h"

namespace nsol
{

  class SomaStats;

  //!  Class to represent the soma of neurons
  /*!
    This class represents the soma and holds a container of the nodes
    that have been traced of its contour
  */
  class NSOL_EXPORT Soma
  {

  public:

    /**
     * Default constructor
     */
    Soma( void );

    /**
     * Destructor
     */
    virtual ~Soma( void );

    /**
     * Method to get the center of the soma
     * @return center of the soma
     */
    Vec3f center( void ) const;

    /**
     * Method to get the container of nodes
     * @return container with all the nodes of the soma
     */
    Nodes & nodes( void );

    /**
     * Method to get the max radius of the soma
     * @return max radius of the soma
     */
    const float & maxRadius( void ) const;

    /**
     * Method to get the min radius of the soma
     * @return min radius of the soma
     */
    const float & minRadius( void ) const;

    /**
     * Method to get the mean radius of the soma
     * @return mean radius of the soma
     */
    const float & meanRadius( void ) const;

    /**
     * Method to set the center of the soma
     * @param center_ New center of the soma
     */
    void center( const Vec3f & center_ );

    /**
     * Method to add a node to the soma
     * @param node pointer to the node to add
     */
    void addNode( NodePtr node );

    /**
     * Method to force the compute of the soma parameters (center and radii)
     */
    void computeParams( void );

    virtual const SomaStats * stats( void ) const
    {
      return nullptr;
    }

    virtual SomaPtr clone( void ) const;

    bool operator == ( Soma & other );

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
