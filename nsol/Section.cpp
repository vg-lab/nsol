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
    : _id( 0 )
    , _neurite( nullptr )
    , _parent( nullptr )
  {
    _nodes.clear( );
  }

  Section::~Section( void )
  {
    for ( unsigned int i = 1; i < _nodes.size( ); i++ )
      delete _nodes[i];

    _nodes.clear( );
  }

  unsigned int Section::id( void )
  {
      return _id;
  }

  void Section::id ( unsigned int id_ )
  {
      _id = id_;
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

  SectionPtr Section::clone( void ) const
  {
    SectionPtr section = new Section( );
    for ( unsigned int i = 1; i < _nodes.size( ); i++ )
    {
      section->addNode( _nodes[i]->clone( ));
    }
    return section;
  }

  bool Section::operator == ( Section & other ) const
  {
    unsigned int size = ( unsigned int )this->nodes( ).size( );

    if( size != other.nodes( ).size( ))
      return false;

    for ( unsigned int i = 0; i < size; i++ )
      if ( this->nodes( )[i] != other.nodes( )[i] )
        return false;
    return true;
  }

  bool Section::operator != ( Section & other ) const
  {
    return ! ( *this == other );
  }

} // namespace nsol


// EOF
