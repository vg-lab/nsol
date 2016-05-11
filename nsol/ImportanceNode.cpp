/**
 * @file ImportanceNode.cpp
 * @brief
 * @author Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remark Copyright (c) GMRV/URJC. All rights reserved.
           Do not distribute without further notice.
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
