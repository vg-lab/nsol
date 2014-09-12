/**
 * @file    Types.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_TYPES__
#define __NSOL_TYPES__

#include <list>
#include <vector>

#include <iostream>

#include <vmmlib/vector.hpp>
#include <vmmlib/matrix.hpp>

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

  class Dendrite;
  class Column;
  class MiniColumn;
  class Neurite;
  class Neuron;
  class NeuronMorphology;
  class Node;
  class Section;
  class Segment;

  //! Definition of pointers to objects
#if !BOOST
  typedef Dendrite * DendritePtr;
  typedef Column * ColumnPtr;
  typedef MiniColumn * MiniColumnPtr;
  typedef Neurite * NeuritePtr;
  typedef Neuron * NeuronPtr;
  typedef NeuronMorphology * NeuronMorphologyPtr;
  typedef Node * NodePtr;
  typedef Section * SectionPtr;
  typedef Segment * SegmentPtr;
#else
typedef boost::shared_ptr<Dendrite> * DendritePtr;
typedef boost::shared_ptr<Column> * ColumnPtr;
typedef boost::shared_ptr<MiniColumn> * MiniColumnPtr;
typedef boost::shared_ptr<Neurite> * NeuritePtr;
typedef boost::shared_ptr<Neuron> * NeuronPtr;
typedef boost::shared_ptr<NeuronMorphology> * NeuronMorphologyPtr;
typedef boost::shared_ptr<Node> * NodePtr;
typedef boost::shared_ptr<Section> * SectionPtr;
typedef boost::shared_ptr<Segment> * SegmentPtr;
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
