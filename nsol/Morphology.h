/*
 * Copyright (c) 2014-2017 VG-Lab/URJC.
 *
 * Authors: Juan Jose Garcia Cantero <juanjose.garcia@urjc.es>
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
#ifndef __NSOL_MORPHOLOGY__
#define __NSOL_MORPHOLOGY__

#include <nsol/api.h>

#include "NsolTypes.h"
#include "Section.h"
#include "Container/Sections.h"

namespace nsol
{

  /*! \class Morphology */
  class Morphology
    : public virtual Object
  {

  public:

    /*
     * Default Morphology class constructor
     */
    NSOL_API
    Morphology( void ) { }

    /*
     * Default Morphology class destructor
     */
    NSOL_API
    virtual ~Morphology( void ) { }

    /*
     * Method that returns the morphology sections
     * @return the morphology sections
     */
    Sections& sections( void ) { return _sections; }

  protected:

    //! Morphology sections
    Sections _sections;

  };

} // end namespace nsol

#endif
