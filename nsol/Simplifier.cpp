#include "Simplifier.h"

#include "NeuronMorphology.h"
#include "Container/Nodes.h"

namespace nsol
{

  Simplifier* Simplifier::m_pInstance = NULL;

  Simplifier* Simplifier::Instance( void )
  {
    if ( !m_pInstance )
      m_pInstance = new Simplifier;

    return m_pInstance;
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
