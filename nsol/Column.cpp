#include "Column.h"

namespace nsol
{


  //
  // Constructors and destructors
  //

  Column::Column( const unsigned short identifier )
  {
    _id = identifier;
  }


  Column::Column( const Column & other )
    : _id( other.id( ))
    , _miniColumns( other.miniColumns( ))
  {}

  Column::~Column()
  {
/*    for (Vector<MiniColumnPtr>::iterator it = _miniColumns.begin();
      it != _miniColumns.end(); ++it)
      delete *it;
*/
    _miniColumns.clear();
  }

  void Column::addMiniColumn(MiniColumnPtr miniColumn)
  {
    _miniColumns.push_back(miniColumn);
  }

  bool Column::removeMiniColumn(MiniColumnPtr miniColumn)
  {
    MiniColumns::iterator mcIt =
      find (_miniColumns.begin( ), _miniColumns.end( ), miniColumn);

    if ( mcIt == _miniColumns.end( ))
      return false;

    _miniColumns.erase( mcIt );
    return true;
  }

  void Column::clearMiniColumns( void )
  {
    _miniColumns.clear( );
  }



  //
  // Operators
  //

  Column & Column::operator = (const Column & other)
  {
    if (this != &other)
    {
      this->id( ) = other.id( );
      this->miniColumns( ) = other.miniColumns( );
    }

    return *this;
  }

  bool Column::operator == (Column & other ) const
  {
    return ( ( this->id( ) == other.id( ) ) &&
             ( this->miniColumns( ) == other.miniColumns( )));
  }

  bool Column::operator != (Column & other ) const
  {
    return !( ( this->id( ) == other.id( ) ) &&
              ( this->miniColumns( ) == other.miniColumns( )));
  }


  //
  // Id related methods
  //

  unsigned short & Column::id(void)
  {
    return _id;
  }

  unsigned short Column::id(void) const
  {
    return _id;
  }

  //
  // Minicolumn related methods
  //

  MiniColumns & Column::miniColumns()
  {
    return _miniColumns;
  }

  MiniColumns Column::miniColumns() const
  {
    return _miniColumns;
  }

  unsigned int Column::numberOfMiniColumns(void) const
  {
    return ( unsigned int ) _miniColumns.size();
  }

  unsigned int Column::numberOfNeurons(bool all,
                                       Neuron::TNeuronType neuronType,
                                       unsigned int layer) const
  {
    unsigned int nNeurons = 0;

    NSOL_CONST_FOREACH( miniColumn, _miniColumns )
      nNeurons += ( * miniColumn )->numberOfNeurons(all, neuronType, layer);

    return nNeurons;

  }

} // namespace nsol
