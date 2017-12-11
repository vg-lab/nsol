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
#ifndef __NSOL_SEGMENTATION__
#define __NSOL_SEGMENTATION__

#include <nsol/api.h>
#include "../../NsolTypes.h"

// std.
#include <fstream>
#include <string>

// Qt.
#include <QFile>
#include <QXmlStreamReader>

#include "Skeleton.h"

namespace nsol
{

enum class SegmentationClassification:
unsigned int
{
  AXON = 0,
  DENDRITE,
  OTHER
};

class Segmentation
{

public:

  NSOL_API
  Segmentation( void );

  NSOL_API
  virtual ~Segmentation( void );

  NSOL_API
  const std::string& getUuid( void ) const;

  NSOL_API
  void setUuid( const std::string& uuid );

  NSOL_API
  const std::string& getName( void ) const;

  NSOL_API
  void setName( const std::string& name );

  NSOL_API
  const std::string& getClassification( void ) const;

  NSOL_API
  SegmentationClassification getClassificationAsEnum( void ) const;

  NSOL_API
  void setClassification( const std::string& classification );

  NSOL_API
  SkeletonPtr getSkeleton( void ) const;

  NSOL_API
  void setSkeleton( SkeletonPtr skeleton );

  NSOL_API
  void loadFromXML( const std::string& filename_ );

  NSOL_API
  void saveAsXML( const std::string& filename_ );

protected:
  std::vector< std::string > split( const std::string& str, const std::string& delimiter );
  QString boolToQString( bool inputBool );
  bool qStringToBool( QString inputQString );

  std::string _uuid;
  std::string _name;
  std::string _classification;
  // MeshPtr     _mesh;
  SkeletonPtr _skeleton;
  // Here there would be some volumetric data.

};

typedef Segmentation* SegmentationPtr;
typedef std::vector< SegmentationPtr > Segmentations;

} // namespace nsol

#endif
