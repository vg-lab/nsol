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
#ifndef __NSOL__XML_SCENE_WRITER__
#define __NSOL__XML_SCENE_WRITER__

#include <nsol/api.h>
#include "../Container/Columns.h"
#include <map>

namespace nsol
{

  /*!
    This class allows to write the structure and optionally
    morphologies of a given container of columns.
  */
  class XmlSceneWriter
  {
  public:

    /**
     * Write structure and optinally morphologies to xml file.
     * @param fileName name of file to write to
     * @param columns container of columns to be written
     * @param morphologies morphologies to be written to SWC
     *        files and linked in the Xml
     * @param relativeToXmlMorphologyPath if true morphology paths will be
     *                                    set to be relative to the xml
     * @return true if everything went ok
     */
    NSOL_API
    static bool writeToXml( const std::string& fileName,
                            const Columns& columns,
                            std::map< std::string, NeuronMorphologyPtr >
                            morphologies,
                            bool relativeToXmlMorphologyPath = false );
  }; // class XmlSceneWriter

}; // namespace nsol

#endif
