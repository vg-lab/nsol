/**
 * @file    NGVSection.h
 * @brief
 * @author  Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NGV_SECTION__
#define __NSOL_NGV_SECTION__

#include <nsol/api.h>
#include "error.h"
#include "NsolTypes.h"
#include "Container/Nodes.h"

namespace nsol
{

  typedef NsolVector<NGVSectionPtr> NGVSections;
 /*! \class NGVSection
   \brief A class to represent Neuro-Glia-Vasculature Section.

   TODO: extend long description
   */
  class NGVSection
    : public virtual Object
  {

  public:

    /**
     * Default constructor
     */
    NSOL_API
    NGVSection( void );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~NGVSection( void );

    /**
     * Adds forward neighbour NGVSection to this NGVSection
     * @param ngvSection pointer to the ngvSection to be added
     */
    NSOL_API
    void addForwardNeighbour( NGVSectionPtr ngvSection_ );

    /**
     * Gets the forward neighbors NGVSections of this NGVSection
     * @return container of the forward neighbors NGVSection
     */
    NSOL_API
    NGVSections& forwardNeighbors( void );

    NSOL_API
    const NGVSections& forwardNeighbors( void ) const;

    /**
     * Adds backward neighbour NGVSection to this NGVSection
     * @param ngvSection pointer to the ngvSection to be added
     */
    NSOL_API
    void addBackwardNeighbour( NGVSectionPtr ngvSection_ );

    /**
     * Gets the backward neighbors NGVSections of this NGVSection
     * @return container of the backward neighbors NGVSection
     */
    NSOL_API
    NGVSections& backwardNeighbors( void );

    NSOL_API
    const NGVSections& backwardNeighbors( void ) const;

    /**
     * Check if the comnection node connects with the backward or the fordward
     * and add the NGVSection to the correspondent NGVSection list
     * @param ngvSection pointer to the ngvSection to be added
     * @param node pointer to the connection node between sections
     */
    NSOL_API
    void addNeighbour( NGVSectionPtr ngvSection_, NodePtr node_ );

    /**
     * Return the middle Nodes
     * @return container of middle Nodes
     */
    NSOL_API
    Nodes& nodes( void );

    NSOL_API
    const Nodes& nodes( void ) const;

    /**
     * Adds a Node at the end of Section
     * @param Node pointer to the Node to add.
     *        Precondition: pointer is nor null.
     */
    NSOL_API
    virtual void addFrontNode( NodePtr node_ );

    /**
     * Adds a Node at the start of Section
     * @param Node pointer to the Node to add.
     *        Precondition: pointer is nor null.
     */
    NSOL_API
    virtual void addBackNode( NodePtr node_ );

    NSOL_API
    virtual NGVSectionPtr asNGVSection( void )
    {
      return this;
    }

  protected:

    //! Container of the froward ngvSections of this ngvSection
    NGVSections _forwardNGVSections;

    //! Container of the backward ngvSections of this ngvSection
    NGVSections _backwardNGVSections;

    //! Container of the nodes of this ngvSection
    Nodes _nodes;

  };

}

#endif
