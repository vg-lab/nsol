/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
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

#include "ImportanceNode.h"
#include "error.h"

namespace nsol
{

  ImportanceNode::ImportanceNode( const Vec3f & initPoint,
                                  const int & initId,
                                  const float & initRadius )
    : Node( initPoint, initId, initRadius )
    , _importance( 0 )
  {
  }

  unsigned int & ImportanceNode::importance( void )
  {
    return _importance;
  }

  unsigned int ImportanceNode::importance( void ) const
  {
    return _importance;
  }

  NodePtr ImportanceNode::clone( void ) const
  {
    ImportanceNode* newNode = new ImportanceNode( _point, _id, _radius );
    newNode->importance( ) = _importance;
    return ( NodePtr ) newNode;
  }
}
