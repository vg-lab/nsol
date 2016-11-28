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

  Synapse::TSynapseType CompartmentSynapse::getType( void ) const
  {
      Synapse::TSynapseType synapseType = Synapse::UNDEFINED;

      if( _preSynapticSection == nullptr && _postSynapticSection == nullptr )
      {
          return Synapse::SOMATOSOMAL;
      }

      bool isPreDentrite, isPreAxon;
      isPreDentrite = isPreAxon = false;

      if( _preSynapticSection != nullptr )
      {
        NeuritePtr neurite = _preSynapticSection->neurite();

        switch(neurite->neuriteType())
        {
            case Neurite::DENDRITE:  isPreDentrite = true;
                                     break;
            case Neurite::AXON: isPreAxon = true;
                                break;
            default: break;
        }
      }

      bool isPostDentrite, isPostAxon, isPostSoma;
      isPostDentrite = isPostAxon = false;
      isPostSoma = true;

      if( _postSynapticSection != nullptr )
      {
          NeuritePtr neurite = _preSynapticSection->neurite();

          switch(neurite->neuriteType())
          {
              case Neurite::DENDRITE:  isPostDentrite = true;
                                       isPostSoma = false;
              break;
              case Neurite::AXON: isPostAxon = true;
                                  isPostSoma = false;
              break;
              default: break;
          }
      }

      if( isPreDentrite ) // 1º Checkup
      {
          if( isPostDentrite )
          {
              return Synapse::DENDRODENDRITIC;
          }
          if( isPostSoma )
          {
               return Synapse::DENDROSOMATIC;
           }
      }

      if( isPreAxon ) // 2º Checkup
      {
          if( isPostDentrite )
          {
              return Synapse::AXODENDRITIC;
          }
          if( isPostAxon )
          {
              return Synapse::AXOAXONIC;
          }
          if( isPostSoma )
          {
              return Synapse::AXOSOMATIC;
          }
      }

      return synapseType;
  }

  void CompartmentSynapse::preSynapticSurfacePosition( const Vec3f position )
  {
    _preSynapticSurfacePosition = position;
  }

  Vec3f CompartmentSynapse::preSynapticSurfacePosition( void ) const
  {
    return _preSynapticSurfacePosition;
  }

  void CompartmentSynapse::postSynapticSurfacePosition( const Vec3f position )
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
      this->preSynapticSurfacePosition( other.preSynapticSurfacePosition( ));
      this->postSynapticSurfacePosition( other.postSynapticSurfacePosition( ));
      this->preSynapticSection( other.preSynapticSection( ));
      this->postSynapticSection( other.postSynapticSection( ));
    }

    return *this;
  }

   bool CompartmentSynapse::operator == ( const CompartmentSynapse& other )
   {
     return (( this->preSynapticSection( ) == other.preSynapticSection( )) &&
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
