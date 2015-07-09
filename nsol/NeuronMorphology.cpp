/**
 * @file    NeuronMorphology.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "NeuronMorphology.h"

#include <cstdlib>

namespace nsol
{

  NeuronMorphology::NeuronMorphology( SomaPtr soma_ )
    : _soma( soma_ )
  {
  }

  NeuronMorphology::~NeuronMorphology( void )
  {
  }

  NeuritePtr
  NeuronMorphology::addNeurite( NeuritePtr neurite_ )
  {
    NSOL_DEBUG_CHECK( neurite_, "neurite is null" );
    _neurites.push_back( neurite_ );
    return neurite_;
  }

  Dendrites * NeuronMorphology::dendrites( void ) const
  {
    Dendrites * tmpDendrites = new Dendrites;

    NSOL_CONST_FOREACH( it, _neurites )
    {

      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );

      if ( dend )
        tmpDendrites->push_back( dend );
    }
    return tmpDendrites;
  }

  Dendrites * NeuronMorphology::basalDendrites(void) const
  {

    Dendrites * tmpDendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::BASAL ))
        tmpDendrites->push_back( dend );
    }

    return tmpDendrites;
  }

  Dendrites * NeuronMorphology::apicalDendrites( void ) const
  {
    Dendrites * tmpDendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST ( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::APICAL ))
        tmpDendrites->push_back( dend );
    }

    return tmpDendrites;
  }

  DendritePtr NeuronMorphology::apicalDendrite( void ) const
  {
    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::APICAL ))
        return dend;
    }

    return NULL;
  }

  Neurites & NeuronMorphology::neurites( void )
  {
    return _neurites;
  }

  const Neurites & NeuronMorphology::neurites( void ) const
  {
    return _neurites;
  }

  Neurons & NeuronMorphology::parentNeurons( void )
  {
    return _parentNeurons;
  }

  const Neurons & NeuronMorphology::parentNeurons( void ) const
  {
    return _parentNeurons;
  }

  void NeuronMorphology::addParentNeuron( NeuronPtr neuron )
  {
    Neurons::iterator neuronIt =
      std::find ( _parentNeurons.begin( ),
                  _parentNeurons.end( ),
                  neuron );

    if ( neuronIt != _parentNeurons.end( ))
      _parentNeurons.push_back( neuron );
  }

  /*
   * Method that initializes every node with the relevance received
   */
  void NeuronMorphology::initRelevance( const float relevance )
  {
    // Iterate over the Soma
    for ( Nodes::iterator it =
             _soma->nodes( ).begin( );
             it != _soma->nodes( ).end( ); ++it)
    {
      ScalarLabeledNodePtr snode = NSOL_DYNAMIC_CAST( ScalarLabeledNode, *it );

      if ( snode == nullptr )
      {
        NSOL_THROW( "Warning: Unknown type of Node. Cannot cast" );
        return;
      }

      snode->relevance( relevance );
    } // for

    // Iterate over the neurites
    for ( Neurites::const_iterator it = _neurites.begin();
          it != _neurites.end(); ++it )
    {
      NeuritePtr naux = *it;
      Sections * saux = naux->sections();

      for ( Sections::const_iterator it2 = saux->begin();
            it2 != saux->end(); ++it2 )
      {
        SectionPtr section = *it2;
        SegmentPtr segment = section->firstSegment();

        while ( segment != nullptr )
        {
          ScalarLabeledNodePtr snode = NSOL_DYNAMIC_CAST( ScalarLabeledNode
                                                  , segment->begin() );

          if ( snode == nullptr )
          {
            NSOL_THROW( "Warning: Unknown type of Node. Cannot cast" );
            return;
          }

          snode->relevance( ( ( double )rand() / ( RAND_MAX ) ) );

          if ( segment->next() == nullptr )
          {
            snode = NSOL_DYNAMIC_CAST( ScalarLabeledNode, segment->end() );
            snode->relevance( ( ( double )rand() / ( RAND_MAX ) ) );
          }

          segment = segment->next();          
        } // while  
      } // for #2     
    } // for #1

  } // initRelevance

  SomaPtr NeuronMorphology::soma( void )
  {
    return _soma;
  }


} // namespace nsol

// EOF
