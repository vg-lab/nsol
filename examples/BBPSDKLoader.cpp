#include <nsol/nsol.h>
#include <assert.h>
#include <iostream>
#include <map>

using namespace nsol;
using namespace std;

int main( int argc, char *argv[] )
{

  BBPSDKReader r;

  if ( argc < 2 )
    std::cerr << "Error: blueconfig file parameter needed." << std::endl;

  std::map<unsigned int, ColumnPtr> columns =
    r.readExperiment(argv[1], 0);

  if (!columns.empty())
  {

    cout << "Number of mini columns: "
	 << columns[0]->numberOfMiniColumns()
	 << " id column: " << columns[0]->id()
	 << " Columns size: " << columns.size() << endl;

    MiniColumns miniColumns = columns[0]->miniColumns();

    cout << "Number of neuron: "
	 << miniColumns[9]->numberOfNeurons(false, Neuron::INTER)
	 << endl;

    NeuronPtr neuron = miniColumns[0]->neurons()[0];

    cout << "soma surface: " << neuron->soma().surface() << endl;

    for (vmml::matrix<4,4,float>::const_iterator it =
	   neuron->transform().begin();
	 it != neuron->transform().end(); it++)
      cout << *it << endl;


    NeuritePtr n = neuron->morphology()->neurites()[0];

    std::cout << "soma center: "
	      << neuron->transform() *
      Vec4f(neuron->morphology()->soma().center(),1)
	      << std::endl;

    std::cout << "soma first point: "
	      << neuron->morphology()->soma().nodes()[0]->point()
	      << std::endl;

    std::cout << "first segment point: "
	      << n->firstSection()->firstSegment()->begin()->point()
	      << std::endl;

    std::cout << "Soma radius: "
	      << neuron->morphology()->soma().maxRadius()
	      << std::endl;

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

    std::cout << "Neuron type: "
	      << int( neuron->neuronType( ))
	      << std::endl;

    return 0;
  }

  cout << "Error" << endl;

  return -1;
}
