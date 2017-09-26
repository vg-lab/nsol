#include "Simplifier.h"

#include "NeuronMorphology.h"
#include "NGVMorphology.h"
#include "Container/Nodes.h"
#include "ImportanceNode.h"

#include <stack>

#define EPSILON 0.00001f

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
                                            bool clone_ )
  {
    NeuronMorphologyPtr morpho = morpho_;

    if ( clone_ )
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
    case 2:
      function = Simplifier::_simplSecDistNodesRadius;
      break;
    case 3:
      function = Simplifier::_simplSecMinAngle;
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


  NGVMorphologyPtr Simplifier::simplify( NGVMorphologyPtr ngvMorpho_,
                                         TSimplificationMethod simplMethod_,
                                         float tolerance_ )
  {
    NGVMorphologyPtr morpho = ngvMorpho_;

    typedef void (*func)( NGVSectionPtr, float ) ;

    func function = nullptr;

    switch( simplMethod_ )
    {
    case 1:
      function = Simplifier::_simplNGVSecDistNodes;
      break;
    case 2:
      function = Simplifier::_simplNGVSecDistNodesRadius;
      break;
    default:
      break;
    }

    if ( !function )
      return morpho;

    std::set< NGVSectionPtr > uniqueSections;
    for ( auto section: morpho->sections( ))
    {
      uniqueSections.insert( section );
      _groupSections( section, uniqueSections );
    }

    for ( auto section: uniqueSections)
    {
      function( section, tolerance_ );
    }
    return morpho;
  }

  NeuronMorphologyPtr Simplifier::adaptSoma( NeuronMorphologyPtr morpho_,
                                             bool clone_ )
  {
    NeuronMorphologyPtr morpho = morpho_;

    if ( clone_ )
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

  NeuronMorphologyPtr Simplifier::adaptBifurcations(
    NeuronMorphologyPtr morpho_,
    float tolerance_,
    bool clone_ )
  {
    NeuronMorphologyPtr morpho = morpho_;

    if ( clone_ )
      morpho = morpho->clone( );

    for ( auto neurite: morpho->neurites( ))
    {
      for ( auto section: neurite->sections( ))
      {
        if ( section->children( ).size( ) == 2 )
        {
          NodePtr bifurcation = section->lastNode( );
          NodePtr child0 = section->children( )[0]->nodes( )[1];
          NodePtr child1 = section->children( )[1]->nodes( )[1];

          Eigen::Vector3f v0 = child0->point( ) - bifurcation->point( );
          float v0Norm = v0.norm( );
          v0.normalize( );
          Eigen::Vector3f v1 = child1->point( ) - bifurcation->point( );
          float v1Norm = v1.norm( );
          v1.normalize( );
          Eigen::Vector3f tangent = ( v0 + v1 ).normalized( );
          Eigen::Vector3f previousTangent =
            ( bifurcation->point( ) - section->nodes( )[
              section->nodes( ).size( )-2 ]->point( )).normalized( );

          if ( tangent.norm( ) < EPSILON )
          {
            tangent = previousTangent - ( previousTangent.dot( v0 ) * v0 );
            tangent.normalized( );
          }

          if( tangent.norm( ) < EPSILON )
          {
            tangent = previousTangent;
          }

          float alpha2 = acos( v0.dot( tangent ));


          if ( alpha2 > M_PI * 0.5f * tolerance_ )
          {
            float correctionAngle = alpha2 - M_PI * 0.5f * tolerance_;
            Eigen::Vector3f exe = tangent.cross( v0 );
            Eigen::Quaternionf q ( Eigen::AngleAxisf( -correctionAngle, exe ));
            Eigen::Vector3f dir = q._transformVector( v0 );
            child0->point( bifurcation->point( ) + dir * v0Norm );

            q = Eigen::Quaternionf( Eigen::AngleAxisf( correctionAngle, exe ));
            dir = q._transformVector( v1 );
            child1->point( bifurcation->point( ) + dir * v1Norm );
          }
        }
      }
    }

    return morpho;
  }

  NeuronMorphologyPtr Simplifier::cutout( NeuronMorphologyPtr morpho_,
                                          bool clone_ )
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

    if ( clone_ )
      morpho = morpho->clone( );

    for ( unsigned int i = 0; morpho->neurites( ).size( ); i++ )
    {
      NeuritePtr neurite = morpho->neurites( )[i];
      ImportanceNodePtr inode = dynamic_cast<ImportanceNodePtr>(
        neurite->firstSection( )->firstNode( ));
      if( inode->importance( ) < 1 )
      {
        morpho->neurites( ).erase( morpho->neurites( ).begin( ) + i );
        delete neurite;
        i--;
      }
      else
      {
        _cutoutAnalizeSection( neurite->firstSection( ));
      }
    }

    return morpho;
  }

  void Simplifier::_cutoutAnalizeSection( SectionPtr section_ )
  {
    ImportanceNodePtr inode;

    bool deleteFromHere = false;

    std::stack< SectionPtr > sectionStack;

    sectionStack.push( section_ );

    while( ! sectionStack.empty( ))
    {
      SectionPtr section = sectionStack.top( );
      sectionStack.pop( );

      Nodes* nodes = &section->nodes( );

      for ( unsigned int i = 1; i < nodes->size( ); i++ )
      {
        if ( deleteFromHere )
        {
          delete (*nodes)[i];
          nodes->erase( nodes->begin( ) + i );
          i--;
        }
        else
        {
          inode = dynamic_cast<ImportanceNodePtr>( (*nodes)[i] );
          if ( inode->importance( ) < 1 )
          {
            deleteFromHere = true;
            i --;
          }
        }
      }
      for ( SectionPtr child: section->children( ))
      {
        if ( deleteFromHere )
        {
          section->children( ).clear( );
          _cutoutSection( child );
        }
        else
          sectionStack.push( child );
      }
    }
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

  void Simplifier::_groupSections( NGVSectionPtr section_,
                                   std::set< NGVSectionPtr >& uniqueSections_ )
  {
    for ( auto section : section_->backwardNeighbors( ))
    {
      if ( uniqueSections_.find( section ) == uniqueSections_.end( ))
      {
        uniqueSections_.insert( section );
        _groupSections( section, uniqueSections_ );
      }
    }
    for ( auto section : section_->forwardNeighbors( ))
    {
      if ( uniqueSections_.find( section ) == uniqueSections_.end( ))
      {
        uniqueSections_.insert( section );
        _groupSections( section, uniqueSections_ );
      }
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
        ((*nodes)[i-1]->point( ) - (*nodes)[i]->point( )).norm( );
      if ( distance < tolerance_ )
      {
        delete (*nodes)[i];
        nodes->erase( nodes->begin( ) + i );
        i--;
      }
    }
  }

  void Simplifier::_simplSecDistNodesRadius( SectionPtr section_,
                                             float /*tolerance_*/ )
  {
    Nodes* nodes = &section_->nodes( );
    float distancePre = ((*nodes)[0]->point( ) - (*nodes)[1]->point( )).norm( );
    float distancePost;
    float maxRadiusPre =
      std::max((*nodes)[0]->radius( ), (*nodes)[1]->radius( ));
    float maxRadiusPost;
    for ( unsigned int i = 1; i < nodes->size( )-1; i++ )
    {
      distancePost = ((*nodes)[i]->point( ) - (*nodes)[i+1]->point( )).norm( );
      maxRadiusPost =
        std::max((*nodes)[i]->radius( ), (*nodes)[i+1]->radius( ));

      if (( distancePre < maxRadiusPre ) || ( distancePost < maxRadiusPost ))
      {
        delete (*nodes)[i];
        nodes->erase( nodes->begin( ) + i );
        i--;
      }
      distancePre = distancePost;
      maxRadiusPre = maxRadiusPost;
    }
  }

  void Simplifier::_simplNGVSecDistNodes( NGVSectionPtr section_,
                                          float tolerance_ )
  {
    Nodes* nodes = &section_->nodes( );
    for ( unsigned int i = 1; i < nodes->size( )-1; i++ )
    {
      float distance =
        ((*nodes)[i-1]->point( ) - (*nodes)[i]->point( )).norm( );
      if ( distance < tolerance_ )
      {
        delete (*nodes)[i];
        nodes->erase( nodes->begin( ) + i );
        i--;
      }
    }
  }

  void Simplifier::_simplNGVSecDistNodesRadius( NGVSectionPtr section_,
                                                float /*tolerance_*/ )
  {
    Nodes* nodes = &section_->nodes( );
    if ( nodes->size(  ) < 3 )
      return;
    for ( unsigned int i = 1; i < nodes->size( ) - 1; i++ )
    {
      if ( nodes->size( ) < 3 )
        break;
      auto distPre = ((*nodes)[i]->point( ) - (*nodes)[i-1]->point( )).norm( );
      auto distPost = ((*nodes)[i]->point( ) - (*nodes)[i+1]->point( )).norm( );
      auto maxRadiusPre =
        std::max((*nodes)[i]->radius( ), (*nodes)[i - 1]->radius( ));
      auto maxRadiusPost =
        std::max((*nodes)[i]->radius( ), (*nodes)[i + 1]->radius( ));

      if ( i == 1 )
      {
        if ( distPre <= maxRadiusPre )
        {
          /* delete nodes->at(1); */
          nodes->erase( nodes->begin( ) + 1 );
          i--;
        }
        else if ( distPost <= maxRadiusPost )
        {
          nodes->erase( nodes->begin( ) + 2 );
          i--;
        }
      }
      else if ( i == ( nodes->size( ) - 2 ))
      {
        if ( distPost <= maxRadiusPost  )
        {
          /* delete nodes->at(i); */
          nodes->erase( nodes->begin( ) + i );
          i--;
        }
      }
      else if ( distPost <= maxRadiusPost )
      {
        /* delete nodes->at( i + 1 ); */
        nodes->erase( nodes->begin( ) + i + 1 );
        i--;
      }
    }
  }

  void Simplifier::_simplSecMinAngle( SectionPtr section_,
                                      float tolerance_ )
  {
    Nodes* nodes = &section_->nodes( );
    for ( unsigned int i = 1; i < nodes->size( )-1; i++ )
    {
      Vec3f exe0 =
        ((*nodes)[i-1]->point( ) - (*nodes)[i]->point( )).normalized( );
      Vec3f exe1 =
        ((*nodes)[i+1]->point( ) - (*nodes)[i]->point( )).normalized( );
      float angle = std::acos( exe0.dot( exe1 ));
      if ( angle <= tolerance_ )
      {
        delete (*nodes)[i];
        nodes->erase( nodes->begin( ) + i );
        i--;
      }
    }
  }
} // namespace nsol
