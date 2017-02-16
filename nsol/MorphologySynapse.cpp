/**
 * @file    CompartmentSynapse.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include "MorphologySynapse.h"

namespace nsol
{

  MorphologySynapse::MorphologySynapse( void )
  : Synapse( )
  , _preSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
  , _postSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
  , _preSynapticSection( nullptr )
  , _postSynapticSection( nullptr )
  {
  }

  MorphologySynapse::MorphologySynapse( const MorphologySynapse& other_ )
  : Synapse( )
  , _preSynapticSurfacePosition( other_.preSynapticSurfacePosition( ))
  , _postSynapticSurfacePosition( other_.postSynapticSurfacePosition( ))
  , _preSynapticSection( other_.preSynapticSection( ))
  , _postSynapticSection( other_.postSynapticSection( ))
  {
  }

  MorphologySynapse::~MorphologySynapse( void )
  {
  }

  MorphologySynapse::TSynapseType MorphologySynapse::synapseType( void ) const
  {
    // -- Treatment of synapse type -- //
    MorphologySynapse::TSynapseType synapseType_ =
                                                  MorphologySynapse::UNDEFINED;

    if( _preSynapticSection == nullptr && _postSynapticSection == nullptr )
    {
      return MorphologySynapse::SOMATOSOMATIC;
    }
    if( _preSynapticSection == nullptr )
    {
      return synapseType_;
    }

    Neurite::TNeuriteType neuritePresynaptic, neuritePostsynaptic;
    neuritePresynaptic  = Neurite::DENDRITE;
    neuritePostsynaptic = Neurite::DENDRITE;

    this->_calculateSynapticSection( neuritePresynaptic,
                                     MorphologySynapse::PRESYNAPTICSECTION );
    this->_calculateSynapticSection( neuritePostsynaptic,
                                     MorphologySynapse::POSTSYNAPTICSECTION );

    // Checking type of synapse...
    if( neuritePresynaptic == Neurite::DENDRITE ) // 1st Checkup
    {
      if( _postSynapticSection == nullptr )
      {
        return MorphologySynapse::DENDROSOMATIC;
      }
      if( neuritePostsynaptic == Neurite::DENDRITE )
      {
        return MorphologySynapse::DENDRODENDRITIC;
      }
    }

    if( neuritePresynaptic == Neurite::AXON ) // 2nd Checkup
    {
      if( _postSynapticSection == nullptr )
      {
        return MorphologySynapse::AXOSOMATIC;
      }
      if( neuritePostsynaptic == Neurite::DENDRITE )
      {
        return MorphologySynapse::AXODENDRITIC;
      }
      if( neuritePostsynaptic == Neurite::AXON )
      {
        return MorphologySynapse::AXOAXONIC;
      }
    }

    return synapseType_;
  }

  void MorphologySynapse::preSynapticSurfacePosition
                                  ( const Vec3f& presynaptic_surface_position_ )
  {
    _preSynapticSurfacePosition = presynaptic_surface_position_;
  }

  Vec3f MorphologySynapse::preSynapticSurfacePosition( void ) const
  {
    return _preSynapticSurfacePosition;
  }

  void MorphologySynapse::postSynapticSurfacePosition( const Vec3f& position_ )
  {
    _postSynapticSurfacePosition = position_;
  }

  Vec3f MorphologySynapse::postSynapticSurfacePosition( void ) const
  {
    return _postSynapticSurfacePosition;
  }

  void
  MorphologySynapse::preSynapticSection( const SectionPtr preSynapticSection_ )
  {
    _preSynapticSection = preSynapticSection_;
  }

  SectionPtr MorphologySynapse::preSynapticSection( void ) const
  {
    return _preSynapticSection;
  }

  void MorphologySynapse::postSynapticSection( const SectionPtr section_ )
  {
    _postSynapticSection = section_;
  }

  SectionPtr MorphologySynapse::postSynapticSection( void ) const
  {
    return _postSynapticSection;
  }

  MorphologySynapse&
  MorphologySynapse::operator = ( const MorphologySynapse& other_ )
  {
    if (this != &other_)
    {
      this->preSynapticNeuron( other_.preSynapticNeuron( ));
      this->postSynapticNeuron( other_.postSynapticNeuron( ));
      this->weight( other_.weight( ));

      this->preSynapticSurfacePosition( other_.preSynapticSurfacePosition( ));
      this->postSynapticSurfacePosition( other_.postSynapticSurfacePosition( ));
      this->preSynapticSection( other_.preSynapticSection( ));
      this->postSynapticSection( other_.postSynapticSection( ));
    }

    return *this;
  }

  bool MorphologySynapse::operator == ( const MorphologySynapse& other_ )
  {
    return (( this->preSynapticNeuron( ) == other_.preSynapticNeuron( )) &&
            ( this->postSynapticNeuron( ) == other_.postSynapticNeuron( )) &&
            ( this->weight( ) == other_.weight( )) &&
            ( this->preSynapticSection( ) == other_.preSynapticSection( )) &&
            ( this->postSynapticSection( ) == other_.postSynapticSection( )) &&
            ( this->preSynapticSurfacePosition( ) ==
              other_.preSynapticSurfacePosition( )) &&
            ( this->postSynapticSurfacePosition( ) ==
              other_.postSynapticSurfacePosition( )));
  }

  bool MorphologySynapse::operator != ( const MorphologySynapse& other_ )
  {
    return !( *this == other_ );
  }


} // namespace nsol

// EOF
