/**
 * @file    Neurite.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "Neurite.h"

#include <stack>


namespace nsol 
{

  //! Default constructor
  Neurite::Neurite( TNeuriteType neuriteType ) 
    : _neuriteType( neuriteType )
    , _firstSection( nullptr)
    , _morphology( nullptr )
    , _numBranches( 0 )
    , _numBifurcations( 0 )
  {
  }
  

  Neurite::~Neurite( ) 
  {
    // if (_firstSection) 
    // {
    //   std::stack<SectionPtr> sPS;
    //   sPS.push(_firstSection);
      
    //   while (!sPS.empty( )) 
    //   {
    // 	SectionPtr lS = sPS.top( );
    // 	sPS.pop( );
	  
    // 	if (lS->childs( ).size( ) > 0) {
    // 	  for (unsigned int i = 0; i < lS->childs( ).size( ); ++i)
    // 	    sPS.push(lS->childs( )[i]);
    // 	}
	  
    // 	delete lS;
    //   }
    // }
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
  
  NeuronMorphologyPtr Neurite::morphology( NeuronMorphologyPtr morphology ) 
  {
    return _morphology = morphology;
  }

  bool Neurite::hasMorphology( ) 
  {
    return ( _morphology != nullptr );
  }

  SectionPtr Neurite::firstSection( ) {
    return _firstSection;
  }

  void Neurite::firstSection(SectionPtr section) {
    _firstSection = section;
  }

  void Neurite::computeBranchBifurcations( void )
  {
    unsigned int numBranchs = 0;
    unsigned int numBifur = 0;
    std::stack<SectionPtr> sPS;
    sPS.push(_firstSection);

    while (!sPS.empty( ))
    {
      SectionPtr lS = sPS.top( );
      sPS.pop( );
      for (Sections::iterator child = lS->childs( ).begin( );
	   child != lS->childs( ).end( ); child++)
      {
	numBranchs++;
	numBifur += lS->childs( ).size( );

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

  float Neurite::volume( void ) 
  {
    float volume = 0.0f;

    if (_firstSection) 
    {
      std::stack<SectionPtr> sPS;
      sPS.push(_firstSection);

      while (!sPS.empty( )) 
      {
	SectionPtr lS = sPS.top( );
	sPS.pop( );

	volume += lS->volume( );

	if (lS->childs( ).size( ) > 0)
	  for (unsigned int i = 0; i < lS->childs( ).size( ); ++i)
	    sPS.push(lS->childs( )[i]);
      }
    }
    return volume;
  }

  float Neurite::surface( void ) 
  {
    float surface = 0.0f;

    if (_firstSection) 
    {
      std::stack<SectionPtr> sPS;
      sPS.push(_firstSection);

      while (!sPS.empty( )) 
      {
	SectionPtr lS = sPS.top( );
	sPS.pop( );

	surface += lS->surface( );

	if (lS->childs( ).size( ) > 0)
	  for (unsigned int i = 0; i < lS->childs( ).size( ); ++i)
	    sPS.push(lS->childs( )[i]);
      }
    }

    return surface;
  }

  float Neurite::length( void ) 
  {
    float length = 0.0f;

    if (_firstSection) 
    {
      std::stack<SectionPtr> sPS;
      sPS.push(_firstSection);

      while (!sPS.empty( )) 
      {
	SectionPtr lS = sPS.top( );
	sPS.pop( );

	length += lS->length( );

	if (lS->childs( ).size( ) > 0)
	  for (unsigned int i = 0; i < lS->childs( ).size( ); ++i)
	    sPS.push(lS->childs( )[i]);
      }
    }
    return length;
  }

  // Casting virtual functions

  //! Return pointer to Dendrite objetc
  // Dendrite * Neurite::asDendrite( void ) 
  // {
  //   return 0;
  // }

  // //! Return pointer to Dendrite objetc
  // Axon * Neurite::asAxon( void ) 
  // {
  //   return 0;
  // }

  void Neurite::_addBifurcationCount( unsigned int numBifurcations ) 
  {
    _numBifurcations += numBifurcations;
  }

  void Neurite::_addBranchCount( unsigned int numBranches ) 
  {
    _numBranches += numBranches;
  }

} // namespace nsol

// EOF
