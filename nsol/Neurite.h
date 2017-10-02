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
#ifndef __NSOL_NEURITE__
#define __NSOL_NEURITE__

#include <nsol/api.h>
#include "NsolTypes.h"
#include "Section.h"

#include <stack>

#include <iostream>


namespace nsol {

  class Dendrite;
  class Axon;
  class NeuriteStats;

  class Neurite
  {

    template< class NODE,
              class SECTION,
              class DENDRITE,
              class AXON,
              class SOMA,
              class NEURONMORPHOLOGY,
              class NEURON > friend class SwcReaderTemplated;

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
    NSOL_API
    Neurite( TNeuriteType neuriteType = DENDRITE );

    NSOL_API
    virtual ~Neurite();

    //! Get the type of neurite
    NSOL_API
    TNeuriteType & neuriteType( void );

    NSOL_API
    NeuronMorphologyPtr morphology( void ) const;

    NSOL_API
    NeuronMorphologyPtr morphology( NeuronMorphologyPtr morphology );

    NSOL_API
    bool hasMorphology( void ) const;

    NSOL_API
    SectionPtr firstSection( void ) const ;

    NSOL_API
    virtual void firstSection( SectionPtr section );

    NSOL_API
    Sections sections( void ) const;

    //TODO: this methods should disappear
    NSOL_API
    void computeBranchBifurcations( void );

    NSOL_API
    unsigned int numBranches( void );

    NSOL_API
    unsigned int numBifurcations( void );

    /**
     * Returns object as NeuriteStats
     * @return pointer to NeuriteStats object
     */
    NSOL_API
    virtual NeuriteStats * stats( void );

    NSOL_API
    virtual NeuritePtr clone( void ) const;

    NSOL_API
    bool operator == ( Neurite & other );

    NSOL_API
    bool operator != ( Neurite & other );

  protected:

    NSOL_API
    void _addBifurcationCount( unsigned int numBifurcations );

    NSOL_API
    void _addBranchCount( unsigned int numBranches );

    TNeuriteType _neuriteType;

    SectionPtr _firstSection;

    NeuronMorphologyPtr _morphology;

    unsigned int _numBranches;

    unsigned int _numBifurcations;
  };

}

#endif
