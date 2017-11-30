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
#ifndef __NSOL_SKELETON_STROKE__
#define __NSOL_SKELETON_STROKE__

#include <nsol/api.h>
#include "../../NsolTypes.h"

// std.
#include <map>
#include <string>
#include <vector>

namespace nsol
{

enum class SkeletonStrokeType:
unsigned int
{
  SOLID = 0,
  DASHED
};

class SkeletonStroke
{

public:

  NSOL_API
  SkeletonStroke( void );

  NSOL_API
  virtual ~SkeletonStroke( void );

  NSOL_API
  unsigned int getColorHue( void ) const;

  NSOL_API
  void setColorHue( unsigned int colorHue );

  NSOL_API
  unsigned int getId( void ) const;

  NSOL_API
  void setId( unsigned int id );

  NSOL_API
  const std::string& getName( void ) const;

  NSOL_API
  void setName( const std::string& name );

  NSOL_API
  SkeletonStrokeType getType( void ) const;

  NSOL_API
  void setType( SkeletonStrokeType type );

  NSOL_API
  bool isUseMeasure( void ) const;

  NSOL_API
  void setUseMeasure( bool useMeasure );

protected:

  unsigned int _id;
  std::string _name;
  unsigned int _colorHue;
  SkeletonStrokeType _type;
  bool _useMeasure;

};

typedef SkeletonStroke* SkeletonStrokePtr;
typedef std::vector< SkeletonStrokePtr > SkeletonStrokes;
typedef std::map< unsigned int, SkeletonStrokePtr > SkeletonStrokeMap;

} // namespace nsol

#endif
