/**
 * @file    CompartmentSynapse.h
 * @brief
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_COMPARTMENTSYNAPSE__
#define __NSOL_COMPARTMENTSYNAPSE__

#include <nsol/api.h>
#include <nsol/NsolTypes.h>
#include <nsol/Neuron.h>
#include <nsol/Synapse.h>


namespace nsol
{

  class CompartmentSynapse : public virtual Synapse
  {

  public:

    //! Possible types of synapse
    typedef enum
    {
      UNDEFINED = 0,
      DENDRODENDRITIC,
      AXODENDRITIC,
      AXOAXONIC,
      SOMATOSOMATIC,
      AXOSOMATIC,
      DENDROSOMATIC
    }TSynapseType;

    //! Possible types of synaptic section
    typedef enum
    {
      PRESYNAPTICSECTION = 0,
      POSTSYNAPTICSECTION
    } TSynapticSectionType;

    /** @name Constructors and destructors  */
    ///@{

    /**
     * Default CompartmentSynapse constructor
     */
    NSOL_API
    CompartmentSynapse( void );

    /**
     * Copy constructor
     * @param other comparment synapse to be copied
     */
    NSOL_API
    CompartmentSynapse( const CompartmentSynapse& other );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~CompartmentSynapse( void );

    ///@}

    /** @name getters and setters methods */
    ///@{

    /**
     * Method to get the type of the synapse.
     */
    NSOL_API
    TSynapseType synapseType( void ) const;

    /**
     * Method to get the presynaptic surface position.
     * @return presynaptic surface position.
     */
    NSOL_API
    Vec3f preSynapticSurfacePosition( void ) const;

    /**
     * Method to set presynaptic surface position to the synapse.
     * @param presynaptic surface position.
     */
    NSOL_API
    void
    preSynapticSurfacePosition( const Vec3f& presynaptic_surface_position );

    /**
     * Method to get the postsynaptic surface position.
     * @return postsynaptic surface position.
     */
    NSOL_API
    Vec3f postSynapticSurfacePosition( void ) const;

    /**
     * Method to set postsynaptic surface position to the synapse.
     * @param postsynaptic surface position.
     */
    NSOL_API
    void
    postSynapticSurfacePosition( const Vec3f& postsynaptic_surface_position );

    /**
     * Method to add a presynaptic section to the synapse.
     * @param presynaptic section.
     * @see Synapse
     * @return pointer to the presynaptic section added
     */
    NSOL_API
    void preSynapticSection( const SectionPtr preSynapticSection);

    /**
     * Method to get the presynaptic section.
     * @return pointer to the presynaptic section.
     */
    NSOL_API
    SectionPtr preSynapticSection( void ) const;

    /**
     * Method to add a postsynaptic section to the synapse.
     * @param postsynaptic section.
     * @see Synapse
     * @return pointer to the postsynaptic section added
     */
    NSOL_API
    void postSynapticSection( const SectionPtr postSynapticSection);

    /**
     * Method to get the postsynaptic section.
     * @return pointer to the postsynaptic section.
     */
    NSOL_API
    SectionPtr postSynapticSection( void ) const;

    ///@}

    /** @name Operators */
    ///@{

    NSOL_API
    virtual CompartmentSynapse& operator =
    ( const CompartmentSynapse& other );

    NSOL_API
    virtual bool operator == ( const CompartmentSynapse& other );

    NSOL_API
    virtual bool operator != ( const CompartmentSynapse& other );

    ///@}


  private:

    int
    _calculateSynapticSection( Neurite::TNeuriteType& neuriteType,
                               TSynapticSectionType synapticSectionType ) const
    {
      NeuritePtr neurite = nullptr;

      switch( synapticSectionType )
      {
        case CompartmentSynapse::PRESYNAPTICSECTION:
         {
          if( _preSynapticSection == nullptr )
           return -1;
          neurite = _preSynapticSection->neurite( );
         }
         break;
        case CompartmentSynapse::POSTSYNAPTICSECTION:
         {
          if( _postSynapticSection == nullptr )
           return -1;
          neurite = _postSynapticSection->neurite( );
         }
         break;
        default:
         return -1;
      }

      neuriteType = neurite->neuriteType();

      return 0;
    }



  protected:

    //! Presynaptic surface position
    Vec3f _preSynapticSurfacePosition;

    //! Postsynaptic surface position
    Vec3f _postSynapticSurfacePosition;

    //! Section of a presynaptic neuron (neurite)
    SectionPtr _preSynapticSection;

    //! Section of a postsynaptic neuron (neurite)
    SectionPtr _postSynapticSection;

  };

} // namespace nsol

#endif // __NSOL_COMPARTMENTSYNAPSE__
