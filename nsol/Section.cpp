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
  {
    _nodes.clear( );
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
        firstNode( _parent->lastNode( ));
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


  Nodes & Section::nodes( void )
  {
    return _nodes;
  }

  const Nodes & Section::nodes( void ) const
  {
    return _nodes;
  }


  void Section::addNode( NodePtr node )
  {
    if ( node )
      _nodes.push_back( node );
  }

  NodePtr Section::firstNode( void )
  {
    if ( _nodes.size( ) > 0 )
      return _nodes[0];
    return nullptr;
  }

  void Section::firstNode( NodePtr firstNode_ )
  {
    if ( firstNode_ )
      _nodes.insert( _nodes.begin( ), firstNode_ );
  }

  NodePtr Section::lastNode( void )
  {
    if( _nodes.size( ) > 0 )
      return _nodes.back( );
    return nullptr;
  }

  SectionStats * Section::stats( void )
  {
    return nullptr;
  }

} // namespace nsol


// EOF
