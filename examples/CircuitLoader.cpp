/**
 * @file    CircuitLoader.cpp
 * @brief   Test for class nsol::Circuit
 * @author  Raquel Jarillo Pellon <r.jarillo@alumnos.urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */
#ifdef NSOL_USE_BBPSDK

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

		 int numberSynapse = 0;
		 NSOL_FOREACH( synapseIt, synapses )
		 {
			 NeuronPtr preSynNeuron  = nullptr;
			 NeuronPtr postSynNeuron = nullptr;

			 preSynNeuron  = (*synapseIt)->preSynapticNeuron();
			 postSynNeuron = (*synapseIt)->postSynapticNeuron();

			 Vec3f preSynPos  =(*synapseIt)->preSynapticSurfacePosition();
			 Vec3f postSynPos =(*synapseIt)->postSynapticSurfacePosition();

			 cout <<  "Synapse Nº " << numberSynapse <<" = "<< endl;
			 cout << " - ID : " <<  (*synapseIt)->id()<< endl;
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

			 cout << " - [Presynaptic Neuron] id: " << preSynNeuron->gid()<< endl;
#if 1 TESTING_PRINT_LITERAL
		switch(preSynNeuron->morphologicalType( ))
					  {
					  	  case 	Neuron::UNDEFINED:
					  		    cout << " morphological type: UNDEFINED " << endl;
					  		    break;
					  	  case	Neuron::INTERNEURON:
					  		    cout << " morphological type: INTERNEURON " << endl;
					  		    break;
					  	  case Neuron::PYRAMIDAL:
					  		    cout << " morphological type: PYRAMIDAL " << endl;
								break;
					  	  default:
					  		    cout<< "neuron morphological type not consistent"<< endl;
					  		    break;
					  }
#else
				   << " morphological type: " << int(preSynNeuron->morphologicalType( ))
           << endl;
#endif

#if 1 TESTING_PRINT_LITERAL
    switch(preSynNeuron->functionalType( ))
            {
                case  Neuron::UNDEFINED_FUNCTIONAL_TYPE:
                    cout << " functional type: UNDEFINED_FUNCTIONAL_TYPE "
                         << endl;
                    break;
                case Neuron::INHIBITORY:
                    cout << " functional type: INHIBITORY " << endl;
                break;
                case Neuron::EXCITATORY:
                    cout << " functional type: EXCITATORY " << endl;
                break;
                default:
                    cout<< "neuron functional type not consistent"<< endl;
                    break;
            }
#else
           << " functional type: " << int(preSynNeuron->functionalType( ))
           << endl;
#endif


			 cout << " - [Postsynaptic Neuron] id: " << postSynNeuron->gid()<< endl;
#if 1 TESTING_PRINT_LITERAL
    switch(postSynNeuron->morphologicalType( ))
            {
                case  Neuron::UNDEFINED:
                    cout << " morphological type: UNDEFINED " << endl;
                    break;
                case  Neuron::INTERNEURON:
                    cout << " morphological type: INTERNEURON " << endl;
                    break;
                case Neuron::PYRAMIDAL:
                    cout << " morphological type: PYRAMIDAL " << endl;
                break;
                default:
                    cout<< "neuron morphological type not consistent"<< endl;
                    break;
            }
#else
           << " morphological type: " << int(postSynNeuron->morphologicalType( ))
           << endl;
#endif

#if 1 TESTING_PRINT_LITERAL
    switch(postSynNeuron->functionalType( ))
            {
                case  Neuron::UNDEFINED_FUNCTIONAL_TYPE:
                    cout << " functional type: UNDEFINED_FUNCTIONAL_TYPE "
                         << endl;
                    break;
                case Neuron::INHIBITORY:
                    cout << " functional type: INHIBITORY " << endl;
                break;
                case Neuron::EXCITATORY:
                    cout << " functional type: EXCITATORY " << endl;
                break;
                default:
                    cout<< "neuron functional type not consistent"<< endl;
                    break;
            }
#else
           << " functional type: " << int(postSynNeuron->functionalType( ))
           << endl;
#endif
			    cout << " - [Presynaptic Surface Position]: "  << preSynPos<< endl;
			    cout << " - [Postsynaptic Surface Position]: " << postSynPos<< endl;
			    cout << endl;

			 numberSynapse++;
		 }

     cout << "Number of synapses: " << synapses.size() <<endl;
     cout << endl;

     cout << "Synapses of the circuit: " << endl;
     cout << endl;

		 // Free resources
		 bbpReader.deleteAll(columns);

		 return 0;
	 }

	 cout << "Error: columns is empty. " << endl;
	 return -1;
} // namespace nsol

#endif // NSOL_USE_BBPSDK
