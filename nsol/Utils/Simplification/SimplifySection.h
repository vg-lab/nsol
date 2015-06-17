/**
 * @file    SimplifySection.h
 * @brief
 * @author  Daniel Mancebo <d.mancebo@alumnos.urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 * Do not distribute without further notice.
 */
#ifndef __NSOL_SIMPLIFYSECTION__
#define __NSOL_SIMPLIFYSECTION__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Node.h>
#include <nsol/Section.h>
#include <nsol/Utils/Simplification/ScalarLabeledNode.h>
#include <nsol/Container/Neurites.h>
#include <nsol/NeuronMorphology.h>
#include <nsol/Neurite.h>

namespace nsol
{
  class SimplifySection
  {

  public:     

    NSOL_API
    static NeuronMorphologyPtr simplifyNeuron( NeuronMorphologyPtr neuron
                                  , const int algorithm
                                  , const float tolerance );

  private:    

    static NsolVector<NodePtr> _vectorize ( SectionPtr polyline
                              , NodePtr begin
                              , NodePtr end );
    
    static SectionPtr _simplifyRW ( NsolVector<NodePtr> polyline
                          , float tolerance
                          , unsigned int begin
                          , unsigned int end );

    static SectionPtr _simplifyRadial ( NsolVector<NodePtr> polyline
                          , float tolerance
                          , unsigned int begin
                          , unsigned int end );

    static SectionPtr _simplifyDP ( NsolVector<NodePtr> polyline
                          , float tolerance
                          , unsigned int begin
                          , unsigned int end );

    static float _average ( NsolVector<ScalarLabeledNodePtr> polyline
                     , unsigned int begin
                     , unsigned int end );

    static Vec3f _crossProduct( Vec3f a, Vec3f b );

    static Vec3f _subtract( Vec3f a, Vec3f b );

    static float _length( Vec3f v );

    static float _perpDistance ( NodePtr p1
             , NodePtr p2
             , NodePtr point );    

    static float _distance ( NodePtr p1, NodePtr p2);

  };

} // namespace nsol

#endif

// EOF
