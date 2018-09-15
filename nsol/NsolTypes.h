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
#ifndef __NSOL_TYPES__
#define __NSOL_TYPES__

#include <memory>


#include <list>
#include <vector>
#include <iostream>
#include <Eigen/Core>
#include <nsol/defines.h>

// Visual Studio Warning disable.
#pragma warning( disable : 4250 )

#ifdef __APPLE__
// This pragma should be removed. Added to macosx clang building
#pragma clang diagnostic ignored "-Woverloaded-virtual"
#endif

namespace nsol
{

#if ( __GNUC__ == 4 && __GNUC_MINOR__ > 6 ) || __GNUC__ == 5
  //! NsolVector container template alias (gcc 4.7 min required)
  template<typename T>
  using NsolVector = std::vector<T>;

  //! NsolList container template alias (gcc 4.7 min required)
  template<typename T>
  using NsolList = std::list<T>;
#else
  //! NsolVector container redefinition for gcc 4.6 and previous
#define NsolVector std::vector
  //! NsolList container redefinition for gcc 4.6 and previous
#define NsolList std::list

#endif

#ifdef _WINDOWS

#define NsolVector std::vector
#define NsolList std::list

#endif

  typedef ::Eigen::Vector3i Vec3i;
  typedef ::Eigen::Vector3f Vec3f;
  typedef ::Eigen::Matrix4f Matrix4_4f;
  typedef std::vector< Vec3i > Vec3is;
  typedef std::vector< Vec3f > Vec3fs;
  typedef ::Eigen::Vector4f Vec4f;
  typedef Vec3is* Vec3isPtr;
  typedef std::vector< Vec4f > Vec4fs;
  typedef Vec4fs* Vec4fsPtr;
  #define Matrix4_4fIdentity Matrix4_4f::Identity()

  static const nsol::Matrix4_4f __VISUAL_STATIC_CONST_MATRIX4_4f__;

  class Axon;
  class Column;
  class Dendrite;
  class ImportanceNode;
  class MiniColumn;
  class Morphology;
  class Neurite;
  class Neuron;
  class NeuronMorphology;
  class NeuronMorphologySection;
  class Node;
  class Object;
  class ObjectWithProperties;
  class Properties;
  class Section;
  class Soma;
  class Circuit;
  class Synapse;
  class MorphologySynapse;

  class NodeCached;

#if (NSOL_USE_SHARED_PTR == 1)
  typedef std::shared_ptr< Axon > AxonPtr;
  typedef std::shared_ptr< Column > ColumnPtr;
  typedef std::shared_ptr< Dendrite > DendritePtr;
  typedef std::shared_ptr< ImportanceNode > ImportanceNodePtr;
  typedef std::shared_ptr< MiniColumn > MiniColumnPtr;
  typedef std::shared_ptr< Morphology > MorphologyPtr;
  typedef std::shared_ptr< Neurite > NeuritePtr;
  typedef std::shared_ptr< Neuron > NeuronPtr;
  typedef std::shared_ptr< NeuronMorphology > NeuronMorphologyPtr;
  typedef std::shared_ptr< NeuronMorphologySection > NeuronMorphologySectionPtr;
  typedef std::shared_ptr< Node > NodePtr;
  typedef std::shared_ptr< Object > ObjectPtr;
  typedef std::shared_ptr< ObjectWithProperties > ObjectWithPropertiesPtr;
  typedef std::shared_ptr< Properties > PropertiesPtr;
  typedef std::shared_ptr< Section > SectionPtr;
  typedef std::shared_ptr< Soma > SomaPtr;
  typedef std::shared_ptr< Circuit > CircuitPtr;
  typedef std::shared_ptr< Synapse > SynapsePtr;
  typedef std::shared_ptr< MorphologySynapse > MorphologySynapsePtr;
  typedef std::shared_ptr< NodeCached > NodeCachedPtr;


#define NSOL_ENABLE_SHARED_FROM_THIS( __TYPE __ )   \
  std::enable_shared_from_this< __TYPE __>

#define NSOL_THIS_POINTER shared_from_this( )

#define NSOL_DYNAMIC_CAST(__TYPE__, __SOURCE__)\
  std::dynamic_pointer_cast< __TYPE__ >( __SOURCE__ )

#define NSOL_DELETE_PTR( __PTR_TO_NSOL_OBJ__ ) \
  ( void ) __PTR_TO_NSOL_OBJ__


#else
  typedef Axon* AxonPtr;
  typedef Column* ColumnPtr;
  typedef Dendrite* DendritePtr;
  typedef ImportanceNode* ImportanceNodePtr;
  typedef MiniColumn* MiniColumnPtr;
  typedef Morphology* MorphologyPtr;
  typedef Neurite* NeuritePtr;
  typedef Neuron* NeuronPtr;
  typedef NeuronMorphology* NeuronMorphologyPtr;
  typedef NeuronMorphologySection* NeuronMorphologySectionPtr;
  typedef Node* NodePtr;
  typedef Object* ObjectPtr;
  typedef Properties* PropertiesPtr;
  typedef ObjectWithProperties* ObjectWithPropertiesPtr;
  typedef Section* SectionPtr;
  typedef Soma* SomaPtr;
  typedef Circuit* CircuitPtr;
  typedef Synapse* SynapsePtr;
  typedef MorphologySynapse* MorphologySynapsePtr;
  typedef NodeCached* NodeCachedPtr;


#define NSOL_ENABLE_SHARED_FROM_THIS( __TYPE__ )

#define NSOL_THIS_POINTER this


#define NSOL_DYNAMIC_CAST(__TYPE__, __SOURCE__)\
  dynamic_cast< __TYPE__ * >( __SOURCE__ )

#define NSOL_DELETE_PTR( __PTR_TO_NSOL_OBJ__ ) \
  {                                            \
  delete __PTR_TO_NSOL_OBJ__;		       \
  }


#endif


#define NSOL_CONST_FOREACH( __ITERATOR__, __CONTAINER__ )         \
  for ( auto __ITERATOR__ = (__CONTAINER__).cbegin( );            \
        __ITERATOR__ != (__CONTAINER__).cend( );                  \
        __ITERATOR__++ )

#define NSOL_FOREACH( __ITERATOR__, __CONTAINER__ )               \
  for ( auto __ITERATOR__ = (__CONTAINER__).begin( );             \
        __ITERATOR__ != (__CONTAINER__).end( );                   \
        __ITERATOR__++ )

#define NSOL_CONST_REVERSE_FOREACH( __ITERATOR__, __CONTAINER__ ) \
  for ( auto __ITERATOR__ = (__CONTAINER__).crbegin( );           \
        __ITERATOR__ != (__CONTAINER__).crend( );                 \
        __ITERATOR__++ )

#define NSOL_REVERSE_FOREACH( __ITERATOR__, __CONTAINER__ )       \
  for ( auto __ITERATOR__ = (__CONTAINER__).rbegin( );            \
        __ITERATOR__ != (__CONTAINER__).rend( );                  \
        __ITERATOR__++ )


  typedef enum
  {
    TOTAL = 0,
    MEAN,
    VARIANCE,
    STD_DEV,
    MIN,
    MAX
  } TAggregation;

  static inline bool validAggregation( TAggregation agg )
  {
    switch( agg )
    {
    case /*TAggregation::*/TOTAL:
    case /*TAggregation::*/MEAN:
    case /*TAggregation::*/VARIANCE:
    case /*TAggregation::*/STD_DEV:
    case /*TAggregation::*/MIN:
    case /*TAggregation::*/MAX:
      return true;
      break;
    default:
      break;
    };
    return false;
  }


  enum LoadFlags
  {
    CORTICAL_HIERARCHY       = 0x00000001,
    MORPHOLOGY               = 0x00000002,
    CIRCUIT                  = 0x00000004,
    SIMULATION_DATA          = 0x00000008,
  };


} // namespace nsol



#ifndef M_2PI
#define M_2PI   6.283185307179586476925286766559  /* 2*pi */
#endif

#ifndef M_PI
#define M_PI    3.141592653589793238462643383280
#endif

#ifndef M_4PI
#define M_4PI    12.5663706144	//4*pi
#endif

#ifndef M_4PI_3
#define M_4PI_3   4.18879020479	//4*pi/3
#endif

#ifndef M_PI_3
#define M_PI_3   1.0471975512 //pi/3
#endif


#endif //__NSOL_TYPES__
