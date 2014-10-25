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

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Section.h>

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
    NSOL_API
    Neurite(TNeuriteType neuriteType = DENDRITE);

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
    bool hasMorphology( void );

    NSOL_API
    SectionPtr firstSection();

    NSOL_API
    void firstSection( SectionPtr section );

    NSOL_API
    void computeBranchBifurcations( void );

    NSOL_API
    unsigned int numBranches( void );

    NSOL_API
    unsigned int numBifurcations( void );

    NSOL_API
    float volume( void );

    NSOL_API
    float surface( void ); 

    NSOL_API
    float length( void );

    // Casting virtual functions

    //! Return pointer to Dendrite object
    // virtual Dendrite * asDendrite( void ); 

    // //! Return pointer to Axon object
    // virtual Axon * asAxon( void ); 

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
