/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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
#ifndef __NSOL_NODES__
#define __NSOL_NODES__

#include <nsol/NsolTypes.h>
#include <nsol/Node.h>

namespace nsol
{

  class Nodes : public NsolVector<NodePtr>
  {
  public:

    NsolVector< Vec3f > positions( void ) const
    {
      NsolVector< Vec3f > result;
      result.reserve( size( ));

      for( auto node : *this )
        result.emplace_back( node->point( ));

      return result;
    }

  protected:

  };

}


#endif
