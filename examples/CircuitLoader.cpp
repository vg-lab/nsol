/**
 * @file    CircuitLoader.cpp
 * @brief   Test for class nsol::Circuit
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifdef NSOL_WITH_BBPSDK

#include <nsol/nsol.h>
#include <assert.h>
#include <iostream>
#include <set>

using namespace nsol;
using namespace std;

int main ( int argc, char *argv[] )
{

	if( argc < 2)
	{
		 std::cerr << " Error: blueconfig file"
				      " parameter needed." << std::endl;
		 return -1;
	}

	BBPSDKReader bbpReader;
	Columns      columns;
	Circuit      circuit;

	bbpReader.readFromBlueConfig( columns,
								  circuit,
								  argv[1],
								  LoadFlags::CIRCUIT );

	 cout << " EXECUTING CircuitLoader... " << endl;
	 cout << endl; cout << endl; cout << endl;

	 if( !columns.empty() )
	 {
		 //cout << "Circuit with id" << circuit.id() << endl;

		 set<SynapsePtr> synapses = circuit.connections();

		 cout << "Number of synapses: " << synapses.size() <<endl;
		 cout << endl;

		 cout << "Synapses of the circuit: " << endl;
		 cout << endl;

		 int numberSynapse = 0;

		 //for (set<SynapsePtr>::iterator synapseIt = synapses.begin();
		//		 synapseIt != synapses.end(); ++synapseIt)
		 NSOL_FOREACH( synapseIt, synapses )
		 {
			  NeuronPtr preSynNeuron  = nullptr;
			  NeuronPtr postSynNeuron = nullptr;

			  preSynNeuron  = (*synapseIt)->preSynapticNeuron();
			  postSynNeuron = (*synapseIt)->postSynapticNeuron();

			 cout << " Synapse " << numberSynapse << /*" - " <<
					   int(synapseIt->synapseType())<<*/ " = " << endl;
			 cout << " [Presynaptic Neuron] id: " << preSynNeuron->gid()
			      << " type: " << int(preSynNeuron->neuronType())<< endl;
			 cout << " [Postsynaptic Neuron] id: " << postSynNeuron->gid()
				  << " type: " << int(postSynNeuron->neuronType())<< endl;
			 cout << endl;

			 numberSynapse++;
		 }

		 // Free resources
		 bbpReader.deleteAll(columns);

		 return 0;
	 }

	 cout << "Error: columns is empty. " << endl;
	 return -1;
} // namespace nsol

#endif // NSOL_WITH_BBPSDK
