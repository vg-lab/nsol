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
#include "SkeletonStroke.h"

namespace nsol
{

SkeletonStroke::SkeletonStroke( void )
: _id( 0 )
, _name( std::string( ) )
, _colorHue( 0 )
, _type( SkeletonStrokeType::SOLID )
, _useMeasure( true )
{
}

SkeletonStroke::~SkeletonStroke( void )
{
}

unsigned int SkeletonStroke::getColorHue( void ) const
{
  return _colorHue;
}

void SkeletonStroke::setColorHue( unsigned int colorHue )
{
  _colorHue = colorHue;
}

unsigned int SkeletonStroke::getId( void ) const
{
  return _id;
}

void SkeletonStroke::setId( unsigned int id )
{
  _id = id;
}

const std::string& SkeletonStroke::getName( void ) const
{
  return _name;
}

void SkeletonStroke::setName( const std::string& name )
{
  _name = name;
}

SkeletonStrokeType SkeletonStroke::getType( void ) const
{
  return _type;
}

void SkeletonStroke::setType( SkeletonStrokeType type )
{
  _type = type;
}

bool SkeletonStroke::isUseMeasure( void ) const
{
  return _useMeasure;
}

void SkeletonStroke::setUseMeasure( bool useMeasure )
{
  _useMeasure = useMeasure;
}

} // namespace nsol
