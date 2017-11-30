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
#include "SkeletonEdge.h"

namespace nsol
{

SkeletonEdge::SkeletonEdge( void )
: _id( 0 )
, _strokeId( 0 )
, _strokeNumber( 0 )
{
}

SkeletonEdge::~SkeletonEdge( void )
{
}

unsigned int SkeletonEdge::getId( void ) const
{
  return _id;
}

void SkeletonEdge::setId( unsigned int id )
{
  _id = id;
}

unsigned int SkeletonEdge::getStrokeId( void ) const
{
  return _strokeId;
}

void SkeletonEdge::setStrokeId( unsigned int strokeId )
{
  _strokeId = strokeId;
}

unsigned int SkeletonEdge::getStrokeNumber( void ) const
{
  return _strokeNumber;
}

void SkeletonEdge::setStrokeNumber( unsigned int strokeNumber )
{
  _strokeNumber = strokeNumber;
}

} // namespace nsol
