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
#ifndef __NSOL_SKELETON_NODE__
#define __NSOL_SKELETON_NODE__

#include <nsol/api.h>
#include "../../NsolTypes.h"

// std.
#include <map>
#include <string>
#include <vector>

namespace nsol
{

class SkeletonNode
{

public:

  NSOL_API
  SkeletonNode( void );

  NSOL_API
  virtual ~SkeletonNode( void );

  NSOL_API
  const std::map< unsigned int, unsigned int >& getConnections( void ) const;

  NSOL_API
  void setConnections( const std::map< unsigned int, unsigned int >& connections );

  NSOL_API
  void addConnection( const unsigned int& nodeId, const unsigned int& edgeId );

  NSOL_API
  unsigned int getId( void ) const;

  NSOL_API
  void setId( unsigned int id );

  NSOL_API
  const std::vector< double >& getPosition( void ) const;

  NSOL_API
  void setPosition( const std::vector< double >& position );

protected:

  unsigned int _id;
  std::vector< double > _position;
  // key: neighbour node (id). value: common edge (id).
  std::map< unsigned int, unsigned int > _connections;

};

typedef SkeletonNode* SkeletonNodePtr;
typedef std::vector< SkeletonNodePtr > SkeletonNodes;
typedef std::map< unsigned int, SkeletonNodePtr > SkeletonNodeMap;

} // namespace nsol

#endif
