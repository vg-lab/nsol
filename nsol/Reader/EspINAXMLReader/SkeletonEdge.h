/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Juan Guerrero Martín <juan.guerrero@urjc.es>
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
#ifndef __NSOL_SKELETON_EDGE__
#define __NSOL_SKELETON_EDGE__

#include <nsol/api.h>
#include "../../NsolTypes.h"

// std.
#include <map>
#include <vector>

namespace nsol
{

class SkeletonEdge
{

public:

  NSOL_API
  SkeletonEdge( void );

  NSOL_API
  virtual ~SkeletonEdge( void );

  NSOL_API
  unsigned int getId( void ) const;

  NSOL_API
  void setId( unsigned int id );

  NSOL_API
  unsigned int getStrokeId( void ) const;

  NSOL_API
  void setStrokeId( unsigned int strokeId );

  NSOL_API
  unsigned int getStrokeNumber( void ) const;

  NSOL_API
  void setStrokeNumber( unsigned int strokeNumber );

protected:

  unsigned int _id;
  unsigned int _strokeId;
  unsigned int _strokeNumber;

};

typedef SkeletonEdge* SkeletonEdgePtr;
typedef std::vector< SkeletonEdgePtr > SkeletonEdges;
typedef std::map< unsigned int, SkeletonEdgePtr > SkeletonEdgeMap;

} // namespace nsol

#endif
