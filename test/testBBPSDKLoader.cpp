#include <nsol.h>
#include <assert.h>
#include <iostream>
#include <map>

using namespace nsol;
using namespace std;

int main(int argc, char *argv[])
{
	BBPSDKReader r;

	std::map<unsigned int, ColumnPtr> columns = r.readExperiment(argv[1], 0);

	if (!columns.empty())
	{
		cout << "Number of mini columns: " << columns[0]->numberOfMiniColumns()
		     << " id column: " << columns[0]->id() << " Columns size: " << columns.size() << endl;

		MiniColumns miniColumns = columns[0]->miniColumns();

		cout << "Number of neuron: " << miniColumns[9]->numberOfNeurons() << endl;

		NeuronPtr neuron = miniColumns[0]->neurons()[0];

		cout << "soma surface: " << neuron->soma().surface() << endl;

		for (vmml::matrix<4,4,float>::const_iterator it = neuron->transforM().begin();
				it != neuron->transforM().end(); it++)
			cout << *it << endl;



		return 0;
	}

	cout << "Error" << endl;

	return -1;
}
