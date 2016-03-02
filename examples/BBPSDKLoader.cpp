#include <nsol/nsol.h>
#include <assert.h>
#include <iostream>
#include <map>
#include <stack>

using namespace nsol;
using namespace std;

int main( int argc, char *argv[] )
{

  BBPSDKReader r;

  if ( argc < 2 )
    std::cerr << "Error: blueconfig file parameter needed." << std::endl;

  Columns columns;
  NeuronsMap neurons;
  r.readFromBlueConfig( columns, neurons, argv[1] );

  if (!columns.empty())
  {

    cout << "Number of mini columns: "
         << columns[0]->numberOfMiniColumns()
         << " id column: " << columns[0]->id()
         << " Columns size: " << columns.size() << endl;

    MiniColumns miniColumns = columns[0]->miniColumns();

    cout << "Number of neuron: "
         << miniColumns[9]->numberOfNeurons(false, Neuron::INTERNEURON)
         << endl;

    NeuronPtr neuron = miniColumns[0]->neurons()[0];

    // cout << "soma surface: " << neuron->morphology( )->soma().surface() << endl;

    for (vmml::matrix<4,4,float>::const_iterator it =
           neuron->transform().begin();
         it != neuron->transform().end(); ++it)
      cout << *it << endl;


    NeuritePtr n = neuron->morphology()->neurites()[0];

    std::cout << "soma center: "
              << neuron->transform() *
      Vec4f(neuron->morphology()->soma()->center(),1)
              << std::endl;

    std::cout << "soma first point: "
              << neuron->morphology()->soma()->nodes()[0]->point()
              << std::endl;

    std::cout << "first segment point: "
              << n->firstSection()->firstNode( )->point( )
              << std::endl;

    std::cout << "Soma radius: "
              << neuron->morphology()->soma()->maxRadius()
              << std::endl;

    //neuron morphology check

//    NSOL_FOREACH( neu, columns[0]->miniColumns( )[0]->neurons( ))
//    {
//      cout << "Neuron gid: " << ( *neu )->gid( ) << " type: "
//           << int(( *neu )->neuronType( ))<< endl;
      int j = 0;
      NSOL_FOREACH( neurite, columns[0]->miniColumns( )[0]->neurons( )[0]->morphology()->neurites() )
      {
        std::cout << "  Neurite " << j << endl;;
        j++;

        int numSections = 0;
        int numNodes = 1;
        std::stack< SectionPtr > sPS;
        sPS.push( (*neurite)->firstSection( ));


        while( ! sPS.empty( ))
        {
          SectionPtr section = sPS.top( );
          sPS.pop( );
          numSections ++;

          numNodes += section->nodes( ).size(  ) - 1;

          cout << "    Section-> number of nodes: "
               << section->nodes( ).size( ) << endl;
          cout << "      First Node: " << section->firstNode( )->id( )
               << " End Node: " << section->lastNode( )->id( ) << endl;

          if (section->children( ).size( ) > 0 )
            NSOL_FOREACH( sec, section->children( ))
            {
              if( section->lastNode( ) != (*sec)->firstNode( ))
                cout << "Inconherencia entre nodos" << endl;
              sPS.push( *sec );
            }
        }
        cout << " Number of sections " << numSections;
        cout << " number of nodes " << numNodes << endl;
      }
//    }

    // std::cout << "NumBranchs: "
    //           << neuron->numNeuriteBranches()
    //           << std::endl;

    // std::cout << "NumBifurcation: "
    //           << neuron->numNeuriteBifurcations()
    //           << std::endl;

    // std::cout << "Max soma volume mini column: "
    //           << neuron->miniColumn()->maxSomaVolume()
    //           << std::endl;

    // std::cout << "Max soma surface mini column: "
    //           << neuron->miniColumn()->maxSomaSurface()
    //           << std::endl;
    // std::cout << "Max soma volume column: "
    //           << neuron->miniColumn()->column()->maxSomaVolume()
    //           << std::endl;

    // std::cout << "Max soma surface column: "
    //           << neuron->miniColumn()->column()->maxSomaSurface()
    //           << std::endl;
    r.deleteAll( columns );

    return 0;
  }

  cout << "Error" << endl;

  return -1;
}
