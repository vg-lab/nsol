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

#include "Neurite.h"
#include "NeuronMorphology.h"
#include <stack>


namespace nsol
{

  //! Default constructor
  Neurite::Neurite( TNeuriteType initNeuriteType )
    : _neuriteType( initNeuriteType )
    , _firstSection( nullptr)
    , _morphology( nullptr )
    , _numBranches( 0 )
    , _numBifurcations( 0 )
  {
    // std::cout << "Neurite constructor " << _neuriteType << std::endl;
  }


  Neurite::~Neurite( )
  {
    delete _firstSection->firstNode( );

    if ( _morphology )
    {
      Neurites neurites = _morphology->neurites( );

      for ( unsigned int i = 0; i < neurites.size( ); i++ )
      {
        if ( neurites[i] == this ){
          neurites.erase( neurites.begin( ) + i );
          i--;
        }
      }
    }

    for ( SectionPtr section: this->sections( ))
      delete section;
  }

  //! Get the type of neurite
  Neurite::TNeuriteType & Neurite::neuriteType( void )
  {
    return _neuriteType;
  }


  NeuronMorphologyPtr Neurite::morphology( void ) const
  {
    return _morphology;
  }

  NeuronMorphologyPtr Neurite::morphology(
    NeuronMorphologyPtr newMorphology )
  {
    return _morphology = newMorphology;
  }

  bool Neurite::hasMorphology( ) const
  {
    return ( _morphology != nullptr );
  }

  NeuronMorphologySectionPtr Neurite::firstSection( void ) const
  {
    return _firstSection;
  }

  void Neurite::firstSection( NeuronMorphologySectionPtr section)
  {
    _firstSection = section;
  }

  Sections Neurite::sections( void ) const
  {
    Sections sections_; // = new Sections;
    std::stack<SectionPtr> sectionsToProcess;
    sectionsToProcess.push( _firstSection );

    while ( ! sectionsToProcess.empty( ))
    {
      NeuronMorphologySectionPtr section  =
        dynamic_cast< NeuronMorphologySectionPtr >( sectionsToProcess.top( ));
      sectionsToProcess.pop( );
      sections_.push_back( section );

      for ( auto childrenIt = section->children( ).begin( );
           childrenIt != section->children( ).end( ); childrenIt++ )
        sectionsToProcess.push( * childrenIt );
    }

    return sections_;
  }

  void Neurite::computeBranchBifurcations( void )
  {
    unsigned int numBranchs = 0;
    unsigned int numBifur = 0;
    std::stack<SectionPtr> sPS;

    if( _firstSection )
      sPS.push(_firstSection);

    while (!sPS.empty( ))
    {
      NeuronMorphologySectionPtr lS =
        dynamic_cast< NeuronMorphologySectionPtr >( sPS.top( ));
      sPS.pop( );
      for (Sections::iterator child = lS->children( ).begin( );
           child != lS->children( ).end( ); child++)
      {
        numBranchs++;
        numBifur += ( unsigned int ) lS->children( ).size( );

        sPS.push(*child);
      }
    }

    _numBranches = numBranchs;
    _numBifurcations = numBifur;
  }

  unsigned int Neurite::numBranches( void )
  {
    computeBranchBifurcations( );
    return _numBranches;
  }

  unsigned int Neurite::numBifurcations( void )
  {
    computeBranchBifurcations( );
    return _numBifurcations;
  }

  NeuriteStats * Neurite::stats( void )
  {
    return nullptr;
  }

  NeuritePtr Neurite::clone( void ) const
  {
    NeuritePtr neurite = new Neurite( _neuriteType );
    _clone( neurite );
    return neurite;
  }

  void Neurite::_clone( NeuritePtr neurite ) const
  {
    NeuronMorphologySectionPtr firstSec =
      dynamic_cast< NeuronMorphologySectionPtr >( _firstSection->clone( ));

    firstSec->neurite( neurite );
    firstSec->firstNode( _firstSection->firstNode( )->clone( ));
    neurite->firstSection( firstSec );

    std::stack< SectionPtr > originalSections;
    std::stack< SectionPtr > newSections;

    originalSections.push( _firstSection );
    newSections.push( firstSec );

    while( ! originalSections.empty( ))
    {
      NeuronMorphologySectionPtr originalSec =
        dynamic_cast< NeuronMorphologySectionPtr >( originalSections.top( ));
      NeuronMorphologySectionPtr newSec =
        dynamic_cast< NeuronMorphologySectionPtr >( newSections.top( ));
      originalSections.pop( );
      newSections.pop( );

      for ( SectionPtr childSec: originalSec->children( ))
      {
        NeuronMorphologySectionPtr newChildSec =
          dynamic_cast< NeuronMorphologySectionPtr >(
          dynamic_cast< NeuronMorphologySectionPtr >( childSec )->clone( ));
        newChildSec->parent( newSec );
        newChildSec->neurite( neurite );
        newSec->addChild( newChildSec );

        originalSections.push( childSec );
        newSections.push( newChildSec );
      }
    }
  }

  bool Neurite::operator == ( Neurite & other )
  {
    if ( _neuriteType != other.neuriteType( ) ||
         sections( ).size( ) != other.sections( ).size( ) ||
         numBranches( ) != other.numBranches( ) ||
         numBifurcations( ) != other.numBifurcations( ))
      return false;

    for ( unsigned int i = 0; i < sections( ).size( ); i++ )
      if ( sections( )[i] != other.sections( )[i] )
        return false;

    return true;
  }

  bool Neurite::operator != ( Neurite & other )
  {
    return ! ( *this == other );
  }

  void Neurite::_addBifurcationCount( unsigned int newNumBifurcations )
  {
    _numBifurcations += newNumBifurcations;
  }

  void Neurite::_addBranchCount( unsigned int newNumBranches )
  {
    _numBranches += newNumBranches;
  }

} // namespace nsol

// EOF
