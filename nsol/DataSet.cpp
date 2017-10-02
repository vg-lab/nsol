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

#include <set>
#include "DataSet.h"
#include "error.h"
#include "Writer/XmlSceneWriter.h"


namespace nsol
{

  DataSet::DataSet( void )
#ifdef NSOL_USE_BRION
    : _blueConfig( nullptr )
    , _target( std::string(""))
#endif
  {

  }

  void DataSet::unloadMorphologies( void )
  {
    for( auto par: _morphologies )
    {
      delete par.second;
    }
    _morphologies.clear( );

    for( auto par: _neurons )
    {
      NeuronPtr neuron = par.second;
      neuron->morphology( nullptr );
    }
  }

  void DataSet::close( void )
  {
    std::set< NeuronMorphologyPtr > morphologies;

    NSOL_FOREACH( col, _columns )
    {
      NSOL_FOREACH( miniCol, ( *col )->miniColumns( ))
      {
        NSOL_FOREACH( neuron, ( *miniCol )->neurons( ))
        {
          if ( (*neuron )->morphology( ) )
            morphologies.insert(( *neuron )->morphology( ));
          delete *neuron;
        }
        delete *miniCol;
      }
      delete *col;
    }

    NSOL_FOREACH( morphology, morphologies )
    {
      delete *morphology;
    }

    _columns.clear( );
    _circuit.clear( );
    _neurons.clear( );
    _morphologies.clear( );

#ifdef NSOL_USE_BRION
    if ( _blueConfig )
      delete _blueConfig;
#endif

    return;
  }

  void DataSet::writeXmlScene( const std::string& xmlSceneFile )
  {
    XmlSceneWriter::writeToXml( xmlSceneFile, _columns, _morphologies );
  }

  Columns& DataSet::columns( void )
  {
    return _columns;
  }

  const Columns& DataSet::columns( void ) const
  {
    return _columns;
  }

  Circuit& DataSet::circuit( void )
  {
      return _circuit;
  }

  const Circuit& DataSet::circuit( void ) const
  {
      return _circuit;
  }

  NeuronsMap& DataSet::neurons( void )
  {
    return _neurons;
  }

  const NeuronsMap& DataSet::neurons( void ) const
  {
    return _neurons;
  }

} // namespace nsol
