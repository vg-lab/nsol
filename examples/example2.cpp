
#include <nsol/nsol.h>
#include <assert.h>
#include <iostream>


using namespace nsol;
using namespace std;

int main ( void ) 
{

  ColumnPtr c ( new Column );
  c->id( ) = 0;

  std::cout << "Testing empty column" << std::endl;

  //<<<<<
  std::cout << " " << std::endl;
  std::cout << "Volume of Soma: "<<  c->meanSomaVolume( ) << " == 0"<< std::endl;//
  std::cout << "Surface of Soma: "<<  c->meanSomaSurface( ) << " == 0.0f"<<std::endl;//
  std::cout << "Volume of Dendrita: "<<  c->meanDendriteVolume( ) << " == 0.0f"<< std::endl;//
  std::cout << "Surface of Dendrita: "<<  c->meanDendriteSurface( ) << " == 0.0f"<< std::endl;//
  std::cout << "Max. Volume of Soma: "<<  c->maxSomaVolume( ) << " == 0.0f"<< std::endl;//
  std::cout << "Max. surface of Soma: "<<  c->maxSomaSurface( ) << " == 0.0f"<< std::endl;//
  std::cout << "Max. Volume of Dendrita: "<<  c->maxDendriteVolume( ) << " == 0.0f"<< std::endl;//
  std::cout << "Max. Surface of Dendrita: "<<  c->maxDendriteSurface( ) << " == 0.0f"<< std::endl;//
  std::cout << "Number of neurons: "<<  c->numberOfNeurons() << " == 0"<< std::endl;//
  std::cout << " " << std::endl;

  //>>>>>

  assert( c->meanSomaVolume( ) == 0 );
  assert( c->meanSomaSurface( ) == 0.0f );
  assert( c->meanDendriteVolume( ) == 0.0f );
  assert( c->meanDendriteSurface( ) == 0.0f );
  assert( c->maxSomaVolume( ) == 0.0f );
  assert( c->maxSomaSurface( ) == 0.0f );
  assert( c->maxDendriteVolume( ) == 0.0f );
  assert( c->maxDendriteSurface( ) == 0.0f );
  assert( c->numberOfNeurons() == 0 );
  assert( c->numberOfNeurons( false ) == 0 );
  assert( c->numberOfNeurons( true, NeuronMorphology::PYRAMIDAL ) == 0 );
  assert( c->numberOfNeurons( false, NeuronMorphology::PYRAMIDAL ) == 0 );
  assert( c->numberOfNeurons( true, NeuronMorphology::INTER ) == 0 );
  assert( c->numberOfNeurons( false, NeuronMorphology::INTER ) == 0 );


  std::cout << "Add mini column" << std::endl;
  MiniColumnPtr mc ( new MiniColumn ( c, 1 ));
  assert( mc->id( ) == 1 );
  assert( mc->column( )  == c );

  mc->id( ) = 0;
  assert( mc->id( ) == 0 );

  c->addMiniColumn( mc );

  //<<<<<
    std::cout << " " << std::endl;
    std::cout << "Mini columns size: "<<  c->miniColumns( ).size( ) << "== 1 " << std::endl;
    std::cout << "Number of minicolumns: "<<  c->numberOfMiniColumns( ) << " == "<< "Mini columns size: "<<
				c->miniColumns( ).size( ) <<std::endl;
    std::cout << " " << std::endl;

    //>>>>>

  assert( c->miniColumns( ).size( ) == 1);
  assert( c->miniColumns( ).size( ) == c->numberOfMiniColumns( ));

  assert( c->meanSomaVolume( ) == 0 );
  assert( c->meanSomaSurface( ) == 0.0f );
  assert( c->meanDendriteVolume( ) == 0.0f );
  assert( c->meanDendriteSurface( ) == 0.0f );
  assert( c->maxSomaVolume( ) == 0.0f );
  assert( c->maxSomaSurface( ) == 0.0f );
  assert( c->maxDendriteVolume( ) == 0.0f );
  assert( c->maxDendriteSurface( ) == 0.0f );
  assert( c->numberOfNeurons() == 0 );
  assert( c->numberOfNeurons( false ) == 0 );
  assert( c->numberOfNeurons( true, NeuronMorphology::PYRAMIDAL ) == 0 );
  assert( c->numberOfNeurons( false, NeuronMorphology::PYRAMIDAL ) == 0 );
  assert( c->numberOfNeurons( true, NeuronMorphology::INTER ) == 0 );
  assert( c->numberOfNeurons( false, NeuronMorphology::INTER ) == 0 );

  {
    MiniColumnPtr mc2 ( new MiniColumn );
    
    // needed in release mode to avoid warning in MSVC
#ifdef WIN32
    mc2;
#endif

    assert( c->removeMiniColumn( mc2 ) == false );

    //<<<<
    std::cout << " " << std::endl;
	std::cout << "Mini columns size: "<<  c->miniColumns( ).size( ) << " == 1"<< std::endl;
	std::cout << "Number of minicolumns: "<<  c->numberOfMiniColumns( ) << " == "
			  << "Mini columns size: "<<  c->miniColumns( ).size( ) << std::endl;
	std::cout << " " << std::endl;
    //>>>>

    assert( c->miniColumns( ).size( ) == 1);
    assert( c->miniColumns( ).size( ) == c->numberOfMiniColumns( ));
  }

  assert( c->removeMiniColumn( mc ) == true );

  //<<<<
    std::cout << " " << std::endl;
	std::cout << "Mini columns size: "<<  c->miniColumns( ).size( ) << " == 0"<< std::endl;
	std::cout << "Number of minicolumns: "<<  c->numberOfMiniColumns( ) << " == "
			  << "Mini columns size: "<<  c->miniColumns( ).size( ) << std::endl;
	std::cout << " " << std::endl;
 //>>>>

  assert( c->miniColumns( ).size( ) == 0);
  assert( c->miniColumns( ).size( ) == c->numberOfMiniColumns( ));


  #define NUM_MINICOLS 20
  #define NUM_NEURONS_PYR_PER_LAYER 10
  #define NUM_NEURONS_INT_PER_LAYER 8
  unsigned int gid = 0;
  for ( unsigned short i = 0 ; i < NUM_MINICOLS ; i++ )
  {
    c->addMiniColumn( MiniColumnPtr( new MiniColumn ( c, i )));
  }


  //<<<<
      std::cout << " " << std::endl;
  	std::cout << "Mini columns size: "<<  c->miniColumns( ).size( ) << std::endl;
  	std::cout << " " << std::endl;
   //>>>>

  MiniColumns miniCols = c->miniColumns( );
  
  for ( MiniColumns::iterator mcIt = miniCols.begin( );
	mcIt != miniCols.end( ); mcIt++ )
  {
    for ( unsigned short l = 1 ; l < 7 ; l++ )
    {
      for ( unsigned short j = 0 ; j < NUM_NEURONS_PYR_PER_LAYER ; j++ )
      {
	( *mcIt )->addNeuron( NeuronPtr( new Neuron( true, l, gid++, 
						     Matrix4_4f::IDENTITY, 
						     *mcIt)));//, NeuronMorphology::PYRAMIDAL )));
      }
      for ( unsigned short j = 0 ; j < NUM_NEURONS_INT_PER_LAYER ; j++ )
      {
	( *mcIt )->addNeuron( NeuronPtr( new Neuron( true, l, gid++, 
						     Matrix4_4f::IDENTITY, 
						     *mcIt)));//, NeuronMorphology::INTER )));
      }
    }
  }

  assert( c->numberOfNeurons( ) == gid );
  assert( c->numberOfNeurons( ) == 
	  NUM_MINICOLS * 6 * ( NUM_NEURONS_PYR_PER_LAYER + 
			       NUM_NEURONS_INT_PER_LAYER ) );
  assert( c->numberOfNeurons( false, NeuronMorphology::PYRAMIDAL ) ==
	  NUM_MINICOLS * 6 * NUM_NEURONS_PYR_PER_LAYER );
  assert( c->numberOfNeurons( false, NeuronMorphology::INTER ) ==
	  NUM_MINICOLS * 6 * NUM_NEURONS_INT_PER_LAYER );
  assert( c->numberOfNeurons( false, NeuronMorphology::PYRAMIDAL, 2 ) ==
	  NUM_MINICOLS * NUM_NEURONS_PYR_PER_LAYER );
  assert( c->numberOfNeurons( false, NeuronMorphology::INTER , 2 ) ==
	  NUM_MINICOLS * NUM_NEURONS_INT_PER_LAYER );


  assert( c->meanSomaVolume( ) == 0 );
  assert( c->meanSomaSurface( ) == 0.0f );
  assert( c->meanDendriteVolume( ) == 0.0f );
  assert( c->meanDendriteSurface( ) == 0.0f );
  assert( c->maxSomaVolume( ) == 0.0f );
  assert( c->maxSomaSurface( ) == 0.0f );
  assert( c->maxDendriteVolume( ) == 0.0f );
  assert( c->maxDendriteSurface( ) == 0.0f );


}
