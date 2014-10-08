/**
 * @file    Neurite.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NEURITE__
#define __NSOL_NEURITE__

#include "NsolTypes.h"
#include "Section.h"

namespace nsol {

  class Dendrite;
  class Axon;

  class Neurite 
  {

    friend class SwcReader;
    friend class BBPSDKreader;

  public:

    //! Possible types of neurite
    typedef enum 
    {
      DENDRITE = 0, 
      AXON
    } TNeuriteType;

    //! Default constructor
    Neurite(TNeuriteType neuriteType = DENDRITE);

    virtual ~Neurite();

    //! Get the type of neurite
    TNeuriteType & neuriteType( void );


    NeuronMorphologyPtr morphology( void ) const;

    NeuronMorphologyPtr morphology( NeuronMorphologyPtr morphology );

    bool hasMorphology( void );

    SectionPtr firstSection();

    void firstSection( SectionPtr section );

    void computeBranchBifurcations( void );

    unsigned int numBranches( void );

    unsigned int numBifurcations( void );

    float volume( void );

    float surface( void ); 

    float length( void );

    // Casting virtual functions

    //! Return pointer to Dendrite object
    virtual DendritePtr asDendrite( void ); 

    //! Return pointer to Axon object
    virtual AxonPtr asAxon( void ); 

  protected:

    void _addBifurcationCount( unsigned int numBifurcations ); 

    void _addBranchCount( unsigned int numBranches ); 

    TNeuriteType _neuriteType;

    SectionPtr _firstSection;

    NeuronMorphologyPtr _morphology;

    unsigned int _numBranches;

    unsigned int _numBifurcations;
  };

}

#endif
