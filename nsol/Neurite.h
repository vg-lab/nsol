/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
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
#ifndef __NSOL_NEURITE__
#define __NSOL_NEURITE__

#include <nsol/nsol_export.h>
#include "NsolTypes.h"
#include "NeuronMorphologySection.h"

#include <stack>

#include <iostream>


namespace nsol {

  class Dendrite;
  class Axon;
  class NeuriteStats;

  class NSOL_EXPORT Neurite
  {

    template< class NODE,
              class NEURONMORPHOLOGYSECTION,
              class DENDRITE,
              class AXON,
              class SOMA,
              class NEURONMORPHOLOGY,
              class NEURON > friend class SwcReaderTemplated;

    template< class NODE,
        class NEURONMORPHOLOGYSECTION,
        class DENDRITE,
        class AXON,
        class SOMA,
        class NEURONMORPHOLOGY,
        class NEURON > friend class AscReaderTemplated;
       
    template< class NODE,
              class NEURONMORPHOLOGYSECTION,
              class DENDRITE,
              class AXON,
              class SOMA,
              class NEURONMORPHOLOGY,
              class NEURON > friend class SnuddaSwcReaderTemplated;          

  public:

    //! Possible types of neurite
    typedef enum
    {
      DENDRITE = 0,
      AXON
    } TNeuriteType;

    friend std::ostream & operator<< ( std::ostream & os,
                                       const TNeuriteType & rhs)
    {
      switch ( rhs )
      {
      case DENDRITE:
        return os << "DENDRITE";
        break;
      case AXON:
        return os << "AXON";
        break;
      default:
        return os << "UNDEFINED";
      }
      return os;
    }

    //! Default constructor
    Neurite( TNeuriteType neuriteType = DENDRITE );

    virtual ~Neurite( void );

    //! Get the type of neurite
    TNeuriteType & neuriteType( void );

    NeuronMorphologyPtr morphology( void ) const;

    NeuronMorphologyPtr morphology( NeuronMorphologyPtr morphology );

    bool hasMorphology( void ) const;

    NeuronMorphologySectionPtr firstSection( void ) const ;

    virtual void firstSection( NeuronMorphologySectionPtr section );

    Sections sections( void ) const;

    //TODO: this methods should disappear
    void computeBranchBifurcations( void );

    unsigned int numBranches( void );

    unsigned int numBifurcations( void );

    /**
     * Returns object as NeuriteStats
     * @return pointer to NeuriteStats object
     */
    virtual NeuriteStats * stats( void );

    virtual NeuritePtr clone( void ) const;

    bool operator == ( Neurite & other );

    bool operator != ( Neurite & other );

  protected:

    void _addBifurcationCount( unsigned int numBifurcations );

    void _addBranchCount( unsigned int numBranches );
  
    void _clone( NeuritePtr neurite ) const;

    TNeuriteType _neuriteType;

    NeuronMorphologySectionPtr _firstSection;

    NeuronMorphologyPtr _morphology;

    unsigned int _numBranches;

    unsigned int _numBifurcations;
  };

}

#endif
