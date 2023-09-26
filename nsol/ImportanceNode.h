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
#ifndef __NSOL_IMPORTANCENODE__
#define __NSOL_IMPORTANCENODE__

#include <nsol/api.h>
#include "Node.h"

namespace nsol
{

  class ImportanceNode
    : public Node
  {
  public:

    NSOL_API
    ImportanceNode( const Vec3f & point = Vec3f(0,0,0),
                    const int & id = 0,
                    const float & radius = 0.0f );


    NSOL_API
    unsigned int & importance( void );

    NSOL_API
    unsigned int importance( void ) const;

    NSOL_API
    virtual NodePtr clone( void ) const;

  protected:

    unsigned int _importance;

  };

} // namespace nsol

#endif

// EOF
