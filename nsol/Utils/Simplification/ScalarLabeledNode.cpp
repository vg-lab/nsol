/**
 * @file    ScalarLabeledNode.cpp
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */

#include "ScalarLabeledNode.h"

namespace nsol
{

  ScalarLabeledNode::ScalarLabeledNode( const Vec3f &initPoint 
	      , const int &initId
	      , const float &initRadius
				, const float &initRelevance )
    : Node ( initPoint, initId, initRadius )
    , _relevance( initRelevance )
  {
  }

  ScalarLabeledNode::~ScalarLabeledNode( void )
  {    
  }
  
  float & ScalarLabeledNode::relevance( void )
  {
    return _relevance;
  }
  
  float ScalarLabeledNode::relevance( void ) const
  {
    return _relevance;
  }

  bool ScalarLabeledNode::operator == ( ScalarLabeledNode & other ) const
  {
    return ( ( this->id( ) == other.id( ) ) &&
	     ( this->radius( ) == other.radius( ) ) &&
	     ( this->point( ) == other.point( ) ) &&
			 ( this->relevance( ) == other.relevance( ) ) ); 
  }
  
  bool ScalarLabeledNode::operator != ( ScalarLabeledNode & other ) const
  {
    return ! ( *this == other );
  }
  
} // namespace nsol

// EOF
