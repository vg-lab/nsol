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
#ifndef __NSOL_SKELETON__
#define __NSOL_SKELETON__

#include <nsol/api.h>
#include "../../NsolTypes.h"

// Qt.
#include <QString>

// std.
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "SkeletonStroke.h"
#include "SkeletonEdge.h"
#include "SkeletonNode.h"

namespace nsol
{

class Skeleton
{

public:

  NSOL_API
  Skeleton( void );

  NSOL_API
  virtual ~Skeleton( void );

  NSOL_API
  const SkeletonNodeMap& getNodes( void ) const;

  NSOL_API
  void setNodes( const SkeletonNodeMap& nodes );

  NSOL_API
  void addNode( const unsigned int& nodeId,
                SkeletonNodePtr nodePtr );

  NSOL_API
  const SkeletonEdgeMap& getEdges( void ) const;

  NSOL_API
  void setEdges( const SkeletonEdgeMap& edges );

  NSOL_API
  void addEdge( const unsigned int& edgeId,
                SkeletonEdgePtr edgePtr );

  NSOL_API
  const SkeletonStrokeMap& getStrokes( void ) const;

  NSOL_API
  void setStrokes( const SkeletonStrokeMap& strokes );

  NSOL_API
  void addStroke( const unsigned int& strokeId,
                  SkeletonStrokePtr strokePtr );

  NSOL_API
  void print( void );

protected:
  QString boolToQString( bool inputBool );

  SkeletonStrokeMap _strokes;
  SkeletonEdgeMap   _edges;
  SkeletonNodeMap   _nodes;

};

typedef Skeleton* SkeletonPtr;
typedef std::vector< SkeletonPtr > Skeletons;

} // namespace nsol

#endif
