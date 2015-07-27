/**
 * @file    CircuitLoader.cpp
 * @brief   Test for class nsol::Circuit
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifdef NSOL_WITH_BBPSDK

#define TESTING_PRINT_LITERAL

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

			 cout <<  "Synapse Nº " << numberSynapse <<" = "<< endl;
#if 1 TESTING_PRINT_LITERAL
			  switch((*synapseIt)->synapseType())
			  {
			  	  case 	Synapse::DENDRODENDRITIC:
			  		    cout << " - Type: DENDRODENDRITIC" << endl;
			  		    break;
			  	  case	Synapse::AXODENDRITIC:
			  		    cout << " - Type: AXODENDRITIC" << endl;
			  		    break;
			  	  case	Synapse::AXOAXONIC:
			  		    cout << " - Type: AXOAXONIC" << endl;
			  		    break;
			  	  case	Synapse::SOMATOSOMAL:
			  		    cout << " - Type: SOMATOSOMAL" << endl;
			  		    break;
			  	  case	Synapse::AXOSOMATIC:
			  		    cout << " - Type: AXOSOMATIC" << endl;
			  		    break;
			  	  case	Synapse::DENDROSOMATIC:
			  		    cout << " - Type: DENDROSOMATIC" << endl;
			  		    break;
			  	  default:
			  		    cout<< "synapse type not consistent"<< endl;
			  		    break;
			  }
#else
			 cout << " - Type : " <<  int((*synapseIt)->synapseType())<< endl;
#endif

			 cout << " - [Presynaptic Neuron] id: " << preSynNeuron->gid();
#if 1 TESTING_PRINT_LITERAL
		switch(preSynNeuron->neuronType())
					  {
					  	  case 	Neuron::UNDEFINED:
					  		    cout << " type: UNDEFINED " << endl;
					  		    break;
					  	  case	Neuron::INTER:
					  		    cout << " type: INTER " << endl;
					  		    break;
					  	  case Neuron::PYRAMIDAL:
					  		    cout << " type: PYRAMIDAL " << endl;
								break;
					  	  default:
					  		    cout<< "neuron type not consistent"<< endl;
					  		    break;
					  }
#else
				   << " type: " << int(preSynNeuron->neuronType())<< endl;
#endif


			 cout << " - [Postsynaptic Neuron] id: " << postSynNeuron->gid();
#if 1 TESTING_PRINT_LITERAL
		switch(postSynNeuron->neuronType())
					  {
					  	  case 	Neuron::UNDEFINED:
					  		    cout << " type: UNDEFINED " << endl;
					  		    break;
					  	  case	Neuron::INTER:
					  		    cout << " type: INTER " << endl;
					  		    break;
					  	  case Neuron::PYRAMIDAL:
					  		    cout << " type: PYRAMIDAL " << endl;
								break;
					  	  default:
					  		    cout<< "neuron type not consistent"<< endl;
					  		    break;
					  }
#else
			    << " type: " << int(postSynNeuron->neuronType())<< endl;
#endif
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
