/**
 * @file    Types.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_TYPES__
#define __NSOL_TYPES__

#include <memory>


#include <list>
#include <vector>

#include <iostream>

#include <vmmlib/vector.hpp>
#include <vmmlib/matrix.hpp>

#include <nsol/defines.h>

/* #include <boost/geometry/geometries/point.hpp> */

namespace nsol
{

#if __GNUC__ == 4
#if  __GNUC_MINOR__ > 6
  //! Vector container template alias (gcc 4.7 min required)
  template<typename T>
  using Vector = std::vector<T>;

  //! List container template alias (gcc 4.7 min required)
  template<typename T>
  using List = std::list<T>;
#else
  //! Vector container redefinition for gcc 4.6 and previous
#define Vector std::vector
  //! List container redefinition for gcc 4.6 and previous
#define List std::list

#endif
#endif

#ifdef _WINDOWS
	
#define Vector std::vector  
//#define List std::list

#endif  


  typedef vmml::vector<3, float> Vec3f;
  typedef vmml::matrix<4, 4, float> Matrix4_4f;
  typedef vmml::vector<4, float> Vec4f;

  class Axon;
  class Column;
  class Dendrite;
  class MiniColumn;
  class Neurite;
  class Neuron;
  class NeuronMorphology;
  class Node;
  class Section;
  class Segment;

  class CachedSection;


#if (NSOL_WITH_SHARED_PTR == 1)
  typedef std::shared_ptr<Axon> AxonPtr;
  typedef std::shared_ptr<Column> ColumnPtr;
  typedef std::shared_ptr<Dendrite> DendritePtr;
  typedef std::shared_ptr<MiniColumn> MiniColumnPtr;
  typedef std::shared_ptr<Neurite> NeuritePtr;
  typedef std::shared_ptr<Neuron> NeuronPtr;
  typedef std::shared_ptr<NeuronMorphology> NeuronMorphologyPtr;
  typedef std::shared_ptr<Node> NodePtr;
  typedef std::shared_ptr<Section> SectionPtr;
  typedef std::shared_ptr<Segment> SegmentPtr;

  typedef std::shared_ptr<CachedSection> CachedSectionPtr;


#define NSOL_DYNAMIC_CAST(__TYPE__, __SOURCE__)\
  std::dynamic_pointer_cast< __TYPE__ >( __SOURCE__ )

#define NSOL_DELETE_PTR( __PTR_TO_NSOL_OBJ__ ) \
  ( void ) __PTR_TO_NSOL_OBJ__


  
#else
  typedef Axon * AxonPtr;
  typedef Column * ColumnPtr;
  typedef Dendrite * DendritePtr;
  typedef MiniColumn * MiniColumnPtr;
  typedef Neurite * NeuritePtr;
  typedef Neuron * NeuronPtr;
  typedef NeuronMorphology * NeuronMorphologyPtr;
  typedef Node * NodePtr;
  typedef Section * SectionPtr;
  typedef Segment * SegmentPtr;

  typedef CachedSection * CachedSectionPtr;

#define NSOL_DYNAMIC_CAST(__TYPE__, __SOURCE__)\
  dynamic_cast< __TYPE__ * >( __SOURCE__ )

#define NSOL_DELETE_PTR( __PTR_TO_NSOL_OBJ__ ) \
  {                                            \
  delete __PTR_TO_NSOL_OBJ__;		       \
  }


#endif

}


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


#endif //__NSOL_TYPES__
