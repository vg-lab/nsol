/**
 * @file    Neuron.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NOL_NEURON_
#define __NOL_NEURON_

#include <Types.h>
#include <Soma.h>
#include <Neurite.h>
#include <Dendrite.h>
#include <Container/Dendrites.h>
#include <Container/Neurites.h>

namespace nol
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
    Neuron()
    {
    }

    /**
     * Method to add a new neurite to the neuron.
     * @param neuriteType type of Neurite.
     * @see Neurite::TNeuriteType
     * @return pointer to the added neurite
     */
    NeuritePtr addNeurite(Neurite::TNeuriteType neuriteType = Neurite::DENDRITE)
    {
      if (neuriteType == Neurite::DENDRITE)
        _neurites.push_back(new Dendrite());
      else if (neuriteType == Neurite::AXON)
        _neurites.push_back(new Axon());
      else
        return NULL;

      return _neurites.back();
    }
    ;

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType type of Dendrite
     * @see ndsl::Dendrite::TDendriteType
     * @return pointer to the added dendrite
     */
    Dendrite *addDendrite(
        Dendrite::TDendriteType dendriteType = Dendrite::BASAL)
    {
      _neurites.push_back(new Dendrite(dendriteType));
      return _neurites.back()->asDendrite();
    }

    /**
     * Method to add a new axon to the neuron.
     * @return pointer to the added axon
     */
    Axon *addAxon()
    {
      _neurites.push_back(new Axon());
      return _neurites.back()->asAxon();
    }


    unsigned int numNeurites(void)
    {
      return _neurites.size();
    }

    unsigned int numDendrites(void)
    {
      unsigned int nd = 0;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asDendrite()) nd++;

      return nd;
    }

    unsigned int numNeuriteBranches()
    {
      unsigned int nb = 0;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        nb += (*it)->numBranches();

      return nb;
    }

    unsigned int numDendriteBranches()
    {
      unsigned int nb = 0;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asDendrite())
          nb += (*it)->numBranches();

      return nb;
    }

    unsigned int numAxonBranches()
    {
      unsigned int nb = 0;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if  ((*it)->asAxon())
          nb += (*it)->numBranches();

      return nb;
    }

    unsigned int numNeuriteBifurcations()
    {
      unsigned int nb = 0;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        nb += (*it)->numBifurcations();

      return nb;
    }

    unsigned int numDendriteBifurcations()
    {
      unsigned int nb = 0;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asDendrite())
          nb += (*it)->numBifurcations();

      return nb;
    }

    unsigned int numAxonBifurcations()
    {
      unsigned int nb = 0;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if  ((*it)->asAxon())
          nb += (*it)->numBifurcations();

      return nb;
    }

    float volume()
    {
      return this->neuritesVolume() + _soma.volume();
    }

    float neuritesVolume()
    {
      return this->dendritesVolume() + this->axonVolume();
    }

    float dendritesVolume()
    {
      float volume = 0.0f;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asDendrite())
          volume += (*it)->volume();

      return volume;
    }

    float axonVolume()
    {
      float volume = 0.0f;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asAxon())
          volume += (*it)->volume();

      return volume;
    }

    float surface()
    {
      return this->neuritesSurface() + _soma.surface();
    }

    float neuritesSurface()
    {
      return this->dendritesSurface() + this->axonSurface();
    }

    float dendritesSurface()
    {
      float surface = 0.0f;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asDendrite())
          surface += (*it)->surface();

      return surface;
    }

    float axonSurface()
    {
      float surface = 0.0f;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asAxon())
          surface += (*it)->surface();

      return surface;
    }

    float length()
    {
      return this->neuritesLength();
    }

    float neuritesLength()
    {
      return this->dendritesLength() + this->axonLength();
    }

    float dendritesLength()
    {
      float length = 0;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asDendrite())
          length += (*it)->length();

      return length;
    }

    float axonLength()
    {
      float length = 0.0f;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
        if ((*it)->asAxon())
          length += (*it)->length();

      return length;
    }

    /**
     * Method to get all the dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites *dendrites(void)
    {
      Dendrites *dendrites = new Dendrites;

      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
      if ((*it)->asDendrite())
      dendrites->push_back((*it)->asDendrite());

      return dendrites;
    }

    /**
     * Method to get all the basal dendrites in a container.
     * Memory for the container is allocated.
     * @return pointer to the container of Dendrites
     */
    Dendrites *basalDendrites(void)
    {
      // TODO: create a list of all basal dendrites
      return new Dendrites;
    }

    /**
     * Method to add a new dendrite to the neuron.
     * @param dendriteType  .
     * @see Neurite::TNeuriteType
     * @return pointer to the added dendrite
     */
    Dendrite *apicalDendrite(void)
    {
      for (Vector<Neurite *>::iterator it = _neurites.begin();
      it != _neurites.end(); ++it)
      {
        if ((*it)->asDendrite() &&
        ((*it)->asDendrite()->dendriteType() == Dendrite::APICAL))
        return (*it)->asDendrite();
      }

      return NULL;
    }

    Neurites &neurites(void)
    {
      return _neurites;
    }

    Soma &soma(void)
    {
      return _soma;
    }

  protected:

    Soma _soma;
    //    Vector<Neurite *> _neurites;
    Neurites _neurites;

  };

/*   //! Definition of pointer to Dendrite */
/* #if !BOOST */
/*   typedef  Neuron * NeuronPtr; */
/* #else */
/*   typedef  boost::shared_ptr<Neuron> * NeuronPtr; */
/* #endif */

}

#endif
