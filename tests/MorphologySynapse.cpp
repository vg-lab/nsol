/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
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

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( morphologySynapse_constructors )
{
  {
     MorphologySynapse synapse;

     BOOST_CHECK_EQUAL( synapse.preSynapticSurfacePosition( ),
                        Vec3f( 0.0f, 0.0f, 0.0f ));
     BOOST_CHECK_EQUAL( synapse.postSynapticSurfacePosition( ),
                        Vec3f( 0.0f, 0.0f, 0.0f ));

     BOOST_CHECK_EQUAL( synapse.preSynapticSection( ) == nullptr, true );
     BOOST_CHECK_EQUAL( synapse.postSynapticSection( ) == nullptr, true );

     MorphologySynapse synapse2;
     synapse2 = synapse;
     BOOST_CHECK_EQUAL( synapse2.postSynapticSurfacePosition( ),
                        Vec3f( 0.0f, 0.0f, 0.0f ));

  }
  {
     SectionPtr sectionPre( new Section );
     SectionPtr sectionPost( new Section );
     sectionPre->id( 1 );
     sectionPost->id( 2 );

     Vec3f positionPre( 1.f, 1.f, 1.f );
     Vec3f positionPost( 2.f, 2.f, 2.f );

     MorphologySynapse synapse1;
     synapse1.preSynapticSection( sectionPre );
     synapse1.postSynapticSection( sectionPost );
     synapse1.preSynapticSurfacePosition( positionPre );
     synapse1.postSynapticSurfacePosition( positionPost );

     BOOST_CHECK_EQUAL( synapse1.preSynapticSurfacePosition( ),
                        Vec3f( 1.f, 1.f, 1.f ));
     BOOST_CHECK_EQUAL( synapse1.postSynapticSurfacePosition( ),
                        Vec3f( 2.f, 2.f, 2.f  ));
     BOOST_CHECK_EQUAL( synapse1.preSynapticSection( )->id( ), 1 );
     BOOST_CHECK_EQUAL( synapse1.postSynapticSection( )->id( ), 2 );

     MorphologySynapse synapse2( synapse1 );
     BOOST_CHECK_EQUAL( synapse1.preSynapticSection( ),
                        synapse2.preSynapticSection( ));
     BOOST_CHECK_EQUAL( synapse1.postSynapticSection( ),
                        synapse2.postSynapticSection( ));

     BOOST_CHECK_EQUAL( synapse1.preSynapticSurfacePosition( ),
                        synapse2.preSynapticSurfacePosition( ));
     BOOST_CHECK_EQUAL( synapse1.postSynapticSurfacePosition( ),
                        synapse2.postSynapticSurfacePosition( ));
    }
}


BOOST_AUTO_TEST_CASE( morphologySynapse_synapseType )
{
   MorphologySynapse* synapse = new MorphologySynapse( );

   // Dendrodendritic synapse
   DendritePtr dendritePre( new Dendrite );
   DendritePtr dendritePost( new Dendrite );

   SectionPtr sectionPre( new Section );
   SectionPtr sectionPost( new Section );
   sectionPre->neurite( dendritePre );
   sectionPost->neurite( dendritePost );

   synapse->preSynapticSection( sectionPre );
   synapse->postSynapticSection( sectionPost );

   BOOST_CHECK_EQUAL( synapse->synapseType(),
                      MorphologySynapse::DENDRODENDRITIC );

   // Axodendritic synapse
   AxonPtr axonPre( new Axon );
   sectionPre->neurite( axonPre );

   BOOST_CHECK_EQUAL( synapse->synapseType(),
                      MorphologySynapse::AXODENDRITIC );

   // Axoaxonic synapse
   AxonPtr axonPost( new Axon );
   sectionPost->neurite( axonPost );

   BOOST_CHECK_EQUAL( synapse->synapseType(),
                      MorphologySynapse::AXOAXONIC );

   // Axosomatic synapse
   synapse->postSynapticSection( nullptr );

   BOOST_CHECK_EQUAL( synapse->synapseType(),
                      MorphologySynapse::AXOSOMATIC );

   // Dendrosomatic synapse
   sectionPre->neurite( dendritePre );

   BOOST_CHECK_EQUAL( synapse->synapseType(),
                      MorphologySynapse::DENDROSOMATIC );

   // Somatosomatic synapse
   synapse->preSynapticSection( nullptr );

   BOOST_CHECK_EQUAL( synapse->synapseType(),
                      MorphologySynapse::SOMATOSOMATIC );

   NSOL_DELETE_PTR( synapse );

}

BOOST_AUTO_TEST_CASE( morphologySynapse_operator )
{
   MorphologySynapse synapse1;

   SectionPtr sectionPre( new Section );
   SectionPtr sectionPost( new Section );
   sectionPre->id( 1 );
   sectionPost->id( 2 );

   Vec3f positionPre( 1.f, 1.f, 1.f );
   Vec3f positionPost( 2.f, 2.f, 2.f );

   synapse1.preSynapticSection( sectionPre );
   synapse1.postSynapticSection( sectionPost );
   synapse1.preSynapticSurfacePosition( positionPre );
   synapse1.postSynapticSurfacePosition( positionPost );

   MorphologySynapse synapse2 = synapse1;

   BOOST_CHECK_EQUAL( synapse2.preSynapticSection( )->id( ), 1 );
   BOOST_CHECK_EQUAL( synapse2.postSynapticSection( )->id( ), 2 );
   BOOST_CHECK_EQUAL( synapse2.preSynapticSurfacePosition( ),
                      Vec3f( 1.f, 1.f, 1.f ));
   BOOST_CHECK_EQUAL( synapse2.postSynapticSurfacePosition( ),
                      Vec3f( 2.f, 2.f, 2.f ));
}


