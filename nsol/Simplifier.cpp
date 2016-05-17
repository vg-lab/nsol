#include "Simplifier.h"

#include "NeuronMorphology.h"
#include "Container/Nodes.h"
#include "ImportanceNode.h"

#include <stack>

namespace nsol
{

  Simplifier* Simplifier::_mpInstance = NULL;

  Simplifier* Simplifier::Instance( void )
  {
    if ( !_mpInstance )
      _mpInstance = new Simplifier;

    return _mpInstance;
  }

  NeuronMorphologyPtr Simplifier::simplify( NeuronMorphologyPtr morpho_,
                                            TSimplificationMethod simplMethod_,
                                            float tolerance_,
                                            bool clone )
  {
    NeuronMorphologyPtr morpho = morpho_;

    if ( clone )
      morpho = morpho->clone( );

    typedef void (*func)( SectionPtr, float ) ;

    func function = nullptr;

    switch( simplMethod_ )
    {
    case 0:
      function = Simplifier::_simplSecDeleteAll;
      break;
    case 1:
      function = Simplifier::_simplSecDistNodes;
      break;
    default:
      function = Simplifier::_simplSecDeleteAll;
      break;
    }

    if ( !function )
      return morpho;

    for ( auto neurite: morpho->neurites( ))
      for ( auto section: neurite->sections( ))
      {
        function( section, tolerance_ );
      }
    return morpho;
  }

  NeuronMorphologyPtr Simplifier::adaptSoma( NeuronMorphologyPtr morpho_,
                                             bool clone )
  {
    NeuronMorphologyPtr morpho = morpho_;

    if ( clone )
      morpho = morpho->clone( );

    Vec3f somaCenter = morpho->soma( )->center( );
    float radius = morpho->soma( )->minRadius( );

    for ( auto neurite: morpho->neurites( ))
    {
      SectionPtr sec = neurite->firstSection( );
      Nodes* nodes = &sec->nodes( );

      // Deleting the nodes inside the initial sphere
      for ( unsigned int i = 0; i < nodes->size( )-1; i++ )
      {
        NodePtr node = (*nodes)[i];
        if ( (node->point( ) - somaCenter).norm( ) < radius )
        {
          delete (*nodes)[i];
          nodes->erase( nodes->begin( ) + i );
          i--;
        }
      }

      // Deleting the nodes
      float dist = ((*nodes)[0]->point( ) - somaCenter).norm( );
      for ( unsigned int i = 1; i < nodes->size( )-1; i++ )
      {
        NodePtr node = (*nodes)[i];
        if ( (node->point( ) - somaCenter).norm( ) < dist )
        {
          delete (*nodes)[i];
          nodes->erase( nodes->begin( ) + i );
          i--;
        }
      }
    }

    return morpho;
  }

  NeuronMorphologyPtr Simplifier::cutout( NeuronMorphologyPtr morpho_,
                                          bool clone )
  {
    NeuronMorphologyPtr morpho = morpho_;

    if ( morpho->neurites( ).size( ) < 1 )
    {
      std::cerr << "This morphology doesn't containes neurites" << std::endl;
      return morpho;
    }

    if ( ! dynamic_cast<ImportanceNodePtr>(
           morpho->neurites( )[0]->firstSection( )->firstNode( )))
    {
      std::cerr << "This morphology doesn't containes ImportanceNodes"
                << std::endl;
      return morpho;
    }

    if ( clone )
      morpho = morpho->clone( );

    for ( NeuritePtr neurite: morpho->neurites( ))
    {
      for( SectionPtr section: neurite->sections( ))
      {
        _cutoutAnalizeSection( section );
      }
    }

    return morpho;
  }

  void Simplifier::_cutoutAnalizeSection( SectionPtr /*section_*/ )
  {
  }

  void Simplifier::_cutoutSection( SectionPtr section_ )
  {
    std::stack< SectionPtr > sectionStack;

    sectionStack.push( section_ );

    while( ! sectionStack.empty( ))
    {
      SectionPtr section = sectionStack.top( );
      sectionStack.pop( );

      for ( SectionPtr child: section->children( ))
        sectionStack.push( child );

      delete section;
    }
  }

  void Simplifier::_simplSecDeleteAll( SectionPtr section_,
                                       float /*tolerance_*/ )
  {
    Nodes* nodes = &section_->nodes( );

    for ( unsigned int i = 1; i < nodes->size( )-1; i++ )
    {
      delete (*nodes)[i];
      nodes->erase( nodes->begin( ) + i );
      i--;
    }
    // nodes->erase( nodes->begin( )+1, nodes->end( ) - 1);
  }

  void Simplifier::_simplSecDistNodes( SectionPtr section_,
                                       float tolerance_ )
  {
    Nodes* nodes = &section_->nodes( );
    for ( unsigned int i = 1; i < nodes->size( )-1; i++ )
    {
      float distance =
        ((*nodes)[i-1]->point( ) - (*nodes)[i]->point( )).length( );
      if ( distance < tolerance_ )
      {
        delete (*nodes)[i];
        nodes->erase( nodes->begin( ) + i );
        i--;
      }
    }
  }
} // namespace nsol
