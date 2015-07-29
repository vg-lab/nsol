#include "Object.h"

namespace nsol
{

  Object::Object( void )
  {
  }

  Object::~Object( void )
  {
  }

  ColumnPtr Object::asColumn( void )
  {
    return nullptr;
  }

  MiniColumnPtr Object::asMiniColumn( void )
  {
    return nullptr;
  }

  NeuronPtr Object::asNeuron( void )
  {
    return nullptr;
  }

  NeuronMorphologyPtr Object::asNeuronMorphology( void )
  {
    return nullptr;
  }

  SectionPtr Object::asSection( void )
  {
    return nullptr;
  }

  SegmentPtr Object::asSegment( void )
  {
    return nullptr;
  }

  NodePtr Object::asNode( void )
  {
    return nullptr;
  }

  ObjectWithPropertiesPtr Object::properties( void)
  {
    return nullptr;
  }

  ObjectPtr Object::create( void ) const
  {
    return new Object;
  }

  ObjectPtr Object::clone( void ) const
  {
    return this->create( );
  }

}
