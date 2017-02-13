/**
 * @file    CompartmentSynapse.cpp
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include "CompartmentSynapse.h"

namespace nsol
{

  CompartmentSynapse::CompartmentSynapse( void )
  : Synapse( )
  , _preSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
  , _postSynapticSurfacePosition( Vec3f( 0.0f, 0.0f, 0.0f ))
  , _preSynapticSection( nullptr )
  , _postSynapticSection( nullptr )
  {
  }

  CompartmentSynapse::CompartmentSynapse( const CompartmentSynapse& other )
  : Synapse( )
  , _preSynapticSurfacePosition( other.preSynapticSurfacePosition( ))
  , _postSynapticSurfacePosition( other.postSynapticSurfacePosition( ))
  , _preSynapticSection( other.preSynapticSection( ))
  , _postSynapticSection( other.postSynapticSection( ))
  {
  }

  CompartmentSynapse::~CompartmentSynapse( void )
  {
  }

  CompartmentSynapse::TSynapseType CompartmentSynapse::synapseType( void ) const
  {
    // -- Treatment of synapse type: -- //
    CompartmentSynapse::TSynapseType synapseType_ =
                                                  CompartmentSynapse::UNDEFINED;

    if( _preSynapticSection == nullptr && _postSynapticSection == nullptr )
    {
      return CompartmentSynapse::SOMATOSOMATIC;
    }

    Neurite::TNeuriteType neuritePresynaptic, neuritePostsynaptic;
    neuritePresynaptic  = Neurite::UNDEFINED;
    neuritePostsynaptic = Neurite::UNDEFINED;

    this->_calculateSynapticSection( neuritePresynaptic,
                                     CompartmentSynapse::PRESYNAPTICSECTION );
    int isSoma = this->_calculateSynapticSection( neuritePostsynaptic,
                                     CompartmentSynapse::POSTSYNAPTICSECTION );

    // Checking type of synapse...
    if( neuritePresynaptic == Neurite::DENDRITE ) // 1º Checkup
    {
      if( neuritePostsynaptic == Neurite::DENDRITE )
      {
        return CompartmentSynapse::DENDRODENDRITIC;
      }
      if( isSoma == -1 )
      {
        return CompartmentSynapse::DENDROSOMATIC;
      }
    }

    if( neuritePresynaptic == Neurite::AXON ) // 2º Checkup
    {
      if( neuritePostsynaptic == Neurite::DENDRITE )
      {
        return CompartmentSynapse::AXODENDRITIC;
      }
      if( neuritePostsynaptic == Neurite::AXON )
      {
        return CompartmentSynapse::AXOAXONIC;
      }
      if( isSoma == -1 )
      {
        return CompartmentSynapse::AXOSOMATIC;
      }
    }

    return synapseType_;
  }

  void CompartmentSynapse::preSynapticSurfacePosition( const Vec3f& position )
  {
    _preSynapticSurfacePosition = position;
  }

  Vec3f CompartmentSynapse::preSynapticSurfacePosition( void ) const
  {
    return _preSynapticSurfacePosition;
  }

  void CompartmentSynapse::postSynapticSurfacePosition( const Vec3f& position )
  {
    _postSynapticSurfacePosition = position;
  }

  Vec3f CompartmentSynapse::postSynapticSurfacePosition( void ) const
  {
    return _postSynapticSurfacePosition;
  }

  void CompartmentSynapse::preSynapticSection( const SectionPtr section )
  {
    _preSynapticSection = section;
  }

  SectionPtr CompartmentSynapse::preSynapticSection( void ) const
  {
    return _preSynapticSection;
  }

  void CompartmentSynapse::postSynapticSection( const SectionPtr section )
  {
    _postSynapticSection = section;
  }

  SectionPtr CompartmentSynapse::postSynapticSection( void ) const
  {
    return _postSynapticSection;
  }

  CompartmentSynapse& CompartmentSynapse::operator = (
                                             const CompartmentSynapse& other )
  {
    if (this != &other)
    {
      this->preSynapticNeuron( other.preSynapticNeuron( ));
      this->postSynapticNeuron( other.postSynapticNeuron( ));
      this->weight( other.weight( ));

      this->preSynapticSurfacePosition( other.preSynapticSurfacePosition( ));
      this->postSynapticSurfacePosition( other.postSynapticSurfacePosition( ));
      this->preSynapticSection( other.preSynapticSection( ));
      this->postSynapticSection( other.postSynapticSection( ));
    }

    return *this;
  }

  bool CompartmentSynapse::operator == ( const CompartmentSynapse& other )
  {
    return (( this->preSynapticNeuron( ) == other.preSynapticNeuron( )) &&
            ( this->postSynapticNeuron( ) == other.postSynapticNeuron( )) &&
            ( this->weight( ) == other.weight( )) &&
            ( this->preSynapticSection( ) == other.preSynapticSection( )) &&
            ( this->postSynapticSection( ) == other.postSynapticSection( )) &&
            ( this->preSynapticSurfacePosition( ) ==
              other.preSynapticSurfacePosition( )) &&
            ( this->postSynapticSurfacePosition( ) ==
              other.postSynapticSurfacePosition( )));
  }

  bool CompartmentSynapse::operator != ( const CompartmentSynapse& other )
  {
    return !( *this == other );
  }


} // namespace nsol

// EOF
