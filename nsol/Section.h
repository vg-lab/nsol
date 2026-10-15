/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *
 * This file is part of nsol <https://github.com/vg-lab/nsol>
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
#ifndef __NSOL_SECTION__
#define __NSOL_SECTION__

#include <nsol/nsol_export.h>
#include "error.h"
#include "NsolTypes.h"
#include "Container/Sections.h"
#include "Container/Nodes.h"

namespace nsol
{

    class Section : public virtual Object
    {
      public:
        /**
         * Default constructor
         */
        NSOL_EXPORT
        Section(void);

        /**
         * Default destructor
         */
        NSOL_EXPORT
        virtual ~Section();

        /**
         * Gets the backward neighbour sections of this section
         * @return container of the backward neighbour sections
         */
        NSOL_EXPORT
        Sections& backwardNeighbors(void);

        NSOL_EXPORT
        const Sections& backwardNeighbors(void) const;

        /**
         * Gets the forward neighbour sections of this section
         * @return container of the forward neighbour sections
         */
        NSOL_EXPORT
        Sections& forwardNeighbors(void);

        NSOL_EXPORT
        const Sections& forwardNeighbors(void) const;

        /**
         * Adds backward neighbour section to this section
         * @param section pointer to the section to be added
         */
        NSOL_EXPORT
        void addBackwardNeighbour(SectionPtr section);

        /**
         * Adds forward neighbour section to this section
         * @param section pointer to the section to be added
         */
        NSOL_EXPORT
        void addForwardNeighbour(SectionPtr section);

        /**
         * Delete backward neighbour section from this section
         * @param section pointer to the section to be deleted
         * @return true if the given section is in the backward sections
         */
        NSOL_EXPORT
        bool deleteBackwardNeighbour(SectionPtr section_);

        /**
         * Delete forward neighbour section from this section
         * @param section pointer to the section to be deleted
         * @return true if the given section is in the forward sections
         */
        NSOL_EXPORT
        bool deleteForwardNeighbour(SectionPtr section_);

        /**
         * Check if the node connects with the backward or the fordward
         * neighbour sections and add the section to the correspondent sections
         * container
         * @param section pointer to the section to be added
         * @param node pointer to the node between sections
         */
        NSOL_EXPORT
        void addNeighbour(SectionPtr section, NodePtr node);

        /**
         * Return the middle Nodes
         * @return container of middle Nodes
         */
        NSOL_EXPORT
        Nodes& nodes(void);

        NSOL_EXPORT
        const Nodes& nodes(void) const;

        /**
         * Adds a node at the start of this section
         * @param node pointer to the Node to add.
         *        Precondition: pointer is not null.
         */
        NSOL_EXPORT
        virtual void addBackwardNode(NodePtr node);

        /**
         * Adds a node at the end of this section
         * @param node pointer to the Node to add.
         *        Precondition: pointer is not null.
         */
        NSOL_EXPORT
        virtual void addForwardNode(NodePtr node);

        /**
         * Gets the first Node of the Section.
         * @return pointer to the first Node, null in case it doesn't have any
         */
        NSOL_EXPORT
        NodePtr backwardNode(void);

        /**
         * Gets the last Node of the Section.
         * @return pointer to the first Node, null in case it doesn't have any
         */
        NSOL_EXPORT
        NodePtr forwardNode(void);

        NSOL_EXPORT
        virtual SectionPtr clone(void) const;

        NSOL_EXPORT
        bool operator==(Section& other) const;

        NSOL_EXPORT
        bool operator!=(Section& other) const;

        NSOL_EXPORT
        virtual SectionPtr asSection(void)
        {
            return this;
        }

      protected:
        //! Container of the middle nodes of this section
        Nodes _nodes;

        //! Container of the backward neighbour sections of this section
        Sections _backwardSections;

        //! Container of the forward neighbour sections of this section
        Sections _forwardSections;

    }; // class Section

} // namespace nsol

#endif
