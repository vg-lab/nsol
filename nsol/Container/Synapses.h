/**
 * @file    Synapses.h
 * @brief   Container for class nsol::SynapsePtr
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifndef __NSOL_SYNAPSES__
#define __NSOL_SYNAPSES__

#include <nsol/NsolTypes.h>
#include <nsol/Synapse.h>
#include <map>

namespace nsol
{

  typedef NsolVector< SynapsePtr > Synapses;

  class SynapsesMap : public std::unordered_multimap< unsigned int, SynapsePtr >
  {
  public:

    template<class Iter>
    struct iter_pair_range : std::pair<Iter,Iter>
    {
      iter_pair_range(std::pair<Iter,Iter> const& pair_)
      : std::pair<Iter,Iter>( pair_ )
      {
      }

      Iter begin( void ) const
      {
        return this->first;
      }
      Iter end( void ) const
      {
        return this->second;
      }
    };

    template<class Iter>
    inline iter_pair_range<Iter>
    as_range( std::pair<Iter,Iter> const& pair_ ) const
    {
      return iter_pair_range<Iter>( pair_ );
    }   

    NSOL_API
    void addSynapse( unsigned int neuronGID_, SynapsePtr synapse_ );

  private:

    bool _checkSynapseRepeated( unsigned int neuronGID_, Synapse* synapse_ );

  };
}

#endif // __NSOL_SYNAPSES_H_

