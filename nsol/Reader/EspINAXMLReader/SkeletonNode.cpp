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
#include "SkeletonNode.h"

namespace nsol
{

SkeletonNode::SkeletonNode( void )
: _id( 0 )
{
}

SkeletonNode::~SkeletonNode( void )
{
}

const std::map< unsigned int, unsigned int >& SkeletonNode::getConnections( void ) const
{
  return _connections;
}

void SkeletonNode::setConnections(
    const std::map< unsigned int, unsigned int >& connections )
{
  _connections = connections;
}

void SkeletonNode::addConnection( const unsigned int& nodeId, const unsigned int& edgeId )
{
  _connections.insert( std::pair< unsigned int, unsigned int >
                       ( nodeId, edgeId ) );
}

unsigned int SkeletonNode::getId( void ) const
{
  return _id;
}

void SkeletonNode::setId( unsigned int id )
{
  _id = id;
}

const std::vector< double >& SkeletonNode::getPosition( void ) const
{
  return _position;
}

void SkeletonNode::setPosition( const std::vector< double >& position )
{
  _position = position;
}

} // namespace nsol
