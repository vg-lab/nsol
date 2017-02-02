/**
 * @file    Section.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_SECTION__
#define __NSOL_SECTION__

#include <nsol/api.h>
#include "error.h"
#include "NsolTypes.h"
#include "Container/Sections.h"
#include "Container/Nodes.h"

namespace nsol
{

  class SectionStats;

  class Section
    : public virtual Object
  {

  public:

    /**
     * Default constructor
     */
    NSOL_API
    Section( void );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~Section( );

    /**
     * Method to get the gid of the section.
     * @return gid
     */
    NSOL_API
    unsigned int id( void );

    /**
     * Method to set the gid of the section.
     * @param gid
     */
    NSOL_API
    void id (unsigned int id_ );

    /**
     * Gets the parent Neurite of the Section
     * @return pointer to the parent Neurite
     */
    NSOL_API
    NeuritePtr neurite( void );

    /**
     * Sets the parent neurite of this Section
     * @param neurite pointer to parent neurite
     */
    NSOL_API
    void neurite( NeuritePtr neurite );

    /**
     * Gets the parent Section of this Section
     * @return pointer to the parent Section
     */
    NSOL_API
    SectionPtr parent( void );

    /**
     * Sets the parent Section of this Section
     * @param parent pointer to parent Section
     */
    NSOL_API
    void parent( SectionPtr parent );

    /**
     * Adds child Section to this Section
     * @param section pointer to the section to be added
     */
    NSOL_API
    void addChild( SectionPtr section );

    /**
     * Return the children sections
     * @return container of children sections
     */
    NSOL_API
    Sections & children( void );

    NSOL_API
    const Sections & children( void ) const;

    /**
     * Return the middle Nodes
     * @return container of middle Nodes
     */
    NSOL_API
    Nodes & nodes( void );

    NSOL_API
    const Nodes & nodes( void ) const;

    /**
     * Adds a Node at the end of Section
     * @param Node pointer to the Node to add.
     *        Precondition: pointer is not null.
     */
    NSOL_API
    virtual void addNode( NodePtr node );

    /**
     * Gets the first Node of the Section.
     * @return pointer to the first Node, null in case it doesn't have any
     */
    NSOL_API
    NodePtr firstNode( void );

    /**
     * Sets first Node of the Section. This method is virtual to allow
     * reimplementation for cached objects and dirty state propagation
     * @param firstNode pointer to the Node.
     */
    NSOL_API
    virtual void firstNode( NodePtr firstNode );

    /**
     * Gets the last Node of the Section.
     * @return pointer to the firts Node, null in case it doesn't have any
     */
    NSOL_API
    NodePtr lastNode( void );

    /**
     * Returns object as SectionStats
     * @return pointer to SectionStats object
     */
    NSOL_API
    virtual SectionStats * stats( void );

    NSOL_API
    virtual SectionPtr clone( void ) const;

    NSOL_API
    bool operator == ( Section & other ) const;

    NSOL_API
    bool operator != ( Section & other ) const;

    NSOL_API
    virtual SectionPtr asSection( void )
    {
      return this;
    }

  protected:

    //! Unique id
    unsigned int _id = 0;

    //! Parent neurite of the section
    NeuritePtr _neurite;

    //! Parent section of this section
    SectionPtr _parent;

    //! Container of the childrens sections of this section
    Sections _children;

    //! Container of the middle nodes of this section
    Nodes _nodes;


  }; // class Section

} // namespace nsol

#endif
