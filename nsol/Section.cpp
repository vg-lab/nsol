/**
 * @file    Section.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Section.h"

namespace nsol
{

  Section::Section( void )
    : _neurite( nullptr )
    , _parent( nullptr )
    , _firstNode( nullptr )
    , _lastNode( nullptr )
  {
    _middleNodes.clear( );
  }

  Section::~Section( void )
  {
    // if (_firstSegment)
    // {
    //   SegmentPtr sP = _firstSegment;

    //   while (sP)
    //   {
    // 	SegmentPtr next = sP->_next;
    // 	delete sP;
    // 	sP = next;
    //   }
    // }
  }

  NeuritePtr Section::neurite( void )
  {
    return _neurite;
  }

  void Section::neurite( NeuritePtr newNeurite )
  {
    _neurite = newNeurite;
  }

  SectionPtr Section::parent( void )
  {
    return _parent;
  }

  void Section::parent( SectionPtr newParent )
  {
    if ( newParent )
    {
      _parent = newParent;
      if( _parent->lastNode() )
        _firstNode = _parent->lastNode( );
    }
  }

  void Section::addChild( SectionPtr section )
  {
    assert(section);
    _children.push_back(section);
  }

  Sections & Section::children( void )
  {
    return _children;
  }

  const Sections & Section::children( void ) const
  {
    return _children;
  }


  Nodes & Section::middleNodes( void )
  {
    return _middleNodes;
  }

  const Nodes & Section::middleNodes( void ) const
  {
    return _middleNodes;
  }


  void Section::addNode( NodePtr node )
  {
    if ( _lastNode )
      _middleNodes.push_back( _lastNode );
    _lastNode = node;
  }

  NodePtr Section::firstNode( void )
  {
    return _firstNode;
  }

  void Section::firstNode( NodePtr firstNode_ )
  {
    _firstNode = firstNode_;
  }

  NodePtr Section::lastNode( void )
  {
    return _lastNode;
  }

  SectionStats * Section::stats( void )
  {
    return nullptr;
  }

} // namespace nsol


// EOF
