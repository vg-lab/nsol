/**
 * @file    Types.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_TYPES__
#define __NOL_TYPES__


#include <list>
#include <vector>

#include <iostream>

#include <vmmlib/vector.hpp>


/* #include <boost/geometry/geometries/point.hpp> */


namespace nol {

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
  
  
  typedef vmml::vector< 3, float > Vec3f;
  
  
  class Dendrite;
  class Neurite;
  class Neuron;
  class Node;
  class Section;
  class Segment;

  //! Definition of pointers to objects
#if !BOOST
  typedef  Dendrite * DendritePtr;
  typedef  Neurite * NeuritePtr;
  typedef  Neuron * NeuronPtr;
  typedef  Node * NodePtr;
  typedef  Section * SectionPtr;
  typedef  Segment * SegmentPtr;
#else
  typedef  boost::shared_ptr<Dendrite> * DendritePtr;
  typedef  boost::shared_ptr<Neurite> * NeuritePtr;
  typedef  boost::shared_ptr<Neuron> * NeuronPtr;
  typedef  boost::shared_ptr<Node> * NodePtr;
  typedef  boost::shared_ptr<Section> * SectionPtr;
  typedef  boost::shared_ptr<Segment> * SegmentPtr;
#endif
  







}


#endif
