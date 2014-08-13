/**
 * @file    Neuron.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_NEURON_MORPHOLOGY__
#define __NSOL_NEURON_MORPHOLOGY__

#include <NsolTypes.h>
#include <NeuronMorphology.h>
#include <Soma.h>
#include <Neurite.h>
#include <Dendrite.h>
#include <Container/Dendrites.h>
#include <Container/Neurites.h>

namespace nsol
{

  /*! \class Neuron
   \brief A class to represent neurons.

   TODO: extend long description
   */
  class Neuron
  {

  public:

   /**
     * Default Neuron class constructor.
     * TODO: construct protected objects
     */
    Neuron(bool createMorphology = true)
    {
      _morphology = nullptr;
      _column = nullptr;
      _miniColumn = nullptr;
      _layer = 0;
      _transforM.zero();

      if (createMorphology)
    	  _morphology = new NeuronMorphology;
    }

    Neuron(const NeuronMorphologyPtr neuronMorphology, const unsigned short layer,
    	   const Matrix4_4f transForm, const ColumnPtr column, const MiniColumnPtr miniColumn)
    {
      _morphology = neuronMorphology;
      _layer = layer;
      _transforM = transForm;
      _column = column;
      _miniColumn = miniColumn;
    }


    ~Neuron()
    {
    }

    bool hasMorphology() const
    {
      return (_morphology != NULL);
    }

    NeuronMorphologyPtr createMorphology()
    {
    	if (!_morphology)
    		_morphology = new NeuronMorphology;

      return _morphology;
    }

    NeuronMorphologyPtr morphology() const
    {
      return _morphology;
    }

    void morphology(NeuronMorphologyPtr morphology)
    {
      _morphology = morphology;
    }


    /**
     * Method to add a new neurite to the neuron.
     * @param neuriteType type of Neurite.
     * @see Neurite::TNeuriteType
     * @return pointer to the added neurite
     */
    NeuritePtr addNeurite(Neurite::TNeuriteType neuriteType = Neurite::DENDRITE)
    {
      if (!this->hasMorphology()) return 0; 
      return _morphology->addNeurite(neuriteType);
    }
    

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType type of Dendrite
     * @see ndsl::Dendrite::TDendriteType
     * @return pointer to the added dendrite
     */
    Dendrite *addDendrite(
        Dendrite::TDendriteType dendriteType = Dendrite::BASAL)
    {
      if (!this->hasMorphology()) return 0; 
      return _morphology->addDendrite(dendriteType);
    }

    /**
     * Method to add a new axon to the neuron.
     * @return pointer to the added axon
     */
    Axon *addAxon()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->addAxon();
    }

    unsigned int numNeurites(void)
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->numNeurites();
    }

    unsigned int numDendrites(void)
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->numDendrites();
    }

    unsigned int numNeuriteBranches()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->numNeuriteBranches();
    }

    unsigned int numDendriteBranches()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->numDendriteBranches();
    }

    unsigned int numAxonBranches()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->numAxonBranches();
    }

    unsigned int numNeuriteBifurcations()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->numNeuriteBifurcations();
    }

    unsigned int numDendriteBifurcations()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->numDendriteBifurcations();
    }

    unsigned int numAxonBifurcations()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->numAxonBifurcations();
    }

    float volume()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->volume();
    }

    float neuritesVolume()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->neuritesVolume();
    }

    float dendritesVolume()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->dendritesVolume();
    }

    float axonVolume()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->axonVolume();
    }

    float surface()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->surface();
    }

    float neuritesSurface()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->neuritesSurface();
    }

    float dendritesSurface()
    { 
      if (!this->hasMorphology()) return 0; 
      return  _morphology->dendritesSurface();
    }

    float axonSurface()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->axonSurface();
    }

    float length()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->length();
    }

    float neuritesLength()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->neuritesLength();
    }

    float dendritesLength()
    {
      if (!this->hasMorphology()) return 0; 
      return  _morphology->dendritesLength();
    }

    float axonLength()
    {    
      if (!this->hasMorphology()) return 0; 
      return  _morphology->axonLength();
    }

    /**
     * Method to get all the dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites *dendrites(void)
    {
      if (!this->hasMorphology()) return 0; 
      return _morphology->dendrites();
    }

    /**
     * Method to get all the basal dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites *basalDendrites(void)
    {
      if (!this->hasMorphology()) return 0; 
      return _morphology->basalDendrites();
    }

    /**
     * Method to get all the apical dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites *apicalDendrites(void)
    {
      if (!this->hasMorphology()) return 0;
      return _morphology->apicalDendrites();
    }

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType  .
     * @see Neurite::TNeuriteType
     * @return pointer to the added dendrite
     */
    Dendrite *apicalDendrite(void)
    {
      if (!this->hasMorphology()) return 0; 
      return _morphology->apicalDendrite();
    }

    Neurites & neurites(void)
    {
      //TODO: handle error if (!this->hasMorphology()) return Neurites();
      assert(this->hasMorphology());
      return _morphology->neurites();
    }

    Soma & soma(void)
    {
      //TODO: handle error if (!this->hasMorphology()) return 0;
      assert(this->hasMorphology());
      return _morphology->soma();
    }

    /**
     * Method to set the transformation matrix of the neuron.
     */
    void transforM(Matrix4_4f transforM)
    {
    	_transforM = transforM;
    }

    /**
     * Method to get the transformation matrix of the neuron.
     * @return transformation matrix
     */
    Matrix4_4f & transforM(void)
    {
    	return _transforM;
    }

    /**
     * Method to get the layer of the neuron.
     * @return layer
     */
    unsigned short & layer(void)
    {
    	return _layer;
    }

    /**
     * Method to set the layer of the neuron.
     */
    void layer(const unsigned short layer)
    {
    	_layer = layer;
    }

    void column(ColumnPtr colummn)
    {
      _column = colummn;
    }

    ColumnPtr &column(void)
    {
      return _column;
    }

    void miniColumn(MiniColumnPtr miniColumn)
    {
    	_miniColumn = miniColumn;
    }

    MiniColumnPtr &miniColumn(void)
    {
    	return _miniColumn;
    }


  protected:

    /* Soma _soma; */
    /* //    Vector<Neurite *> _neurites; */
    /* Neurites _neurites; */

    NeuronMorphologyPtr _morphology;	//Morphology
    ColumnPtr _column;					//Column
    MiniColumnPtr _miniColumn;			//Minicolumn
    Matrix4_4f _transforM;				//Matrix of global transformation
    unsigned short _layer;				//Layer

  };

/*   //! Definition of pointer to Dendrite */
/* #if !BOOST */
/*   typedef  Neuron * NeuronPtr; */
/* #else */
/*   typedef  boost::shared_ptr<Neuron> * NeuronPtr; */
/* #endif */

}

#endif
