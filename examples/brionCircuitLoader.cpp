/**
* @file    brionCircuitLoader.cpp
* @brief Test for class nsol::Circuit
* @author   Raquel Jarillo Pellon <raquel.jarillo@urjc.es>
* @date
* @remarks Copyright (c) GMRV/URJC. All rights reserved.
*          Do not distribute without further notice.
*/

#define TESTING_PRINT_LITERAL

#include <nsol/nsol.h>
#include <nsol/DataSet.h>

#include <assert.h>

#include <iostream>

using namespace nsol;
using namespace std;

void usageMessage( char* programName )
{
  std::cerr << std::endl
            << "Usage: "
            << programName << "\t"
            << " -bc file_name -target target_name" << std::endl
            << std::endl << std::endl;
  exit(-1);
}

int main( int argc, char* argv[ ])
{
    std::string blueConfig;
    std::string target = std::string( "" );

  for( int i = 1; i < argc; i++ )
  {
    if( std::strcmp( argv[ i ], "-bc" ) == 0 )
    {
      if( ++i < argc )
      {
        blueConfig = std::string( argv[ i ]);
      }
      else
        usageMessage( argv[0] );
    }
    if( std::strcmp( argv[ i ], "-target" ) == 0 )
    {
      if( ++i < argc )
      {
        target = std::string( argv[ i ] );
      }
      else
        usageMessage( argv[0] );
    }
  }

  if ( blueConfig.empty( ) | target.empty( ))
  {
    usageMessage( argv[0] );
  }

  DataSet dataSet;

  cout << "Open BlueConfig ..." << endl;

  dataSet.loadBlueConfigConnectivity( blueConfig, target);

  cout << " EXECUTING CircuitLoader... " << endl;
  cout << endl; cout << endl; cout << endl;

  Circuit circuit = dataSet.circuit();

  if(!circuit.connections().empty())
  {
      cout << "Synapses of the circuit: " << endl;
      cout << endl;

      //cout << "Circuit with id" << circuit.id() << endl;
      set<SynapsePtr> synapses = circuit.connections();

      int numberSynapse = 0;
      NSOL_FOREACH( synapseIt, synapses )
      {
          SynapsePtr synapse = (*synapseIt);

          NeuronPtr preSynNeuron  = nullptr;
          NeuronPtr postSynNeuron = nullptr;

          preSynNeuron  = synapse->preSynapticNeuron();
          postSynNeuron = synapse->postSynapticNeuron();

          SectionPtr preSynSection  = nullptr;
          SectionPtr postSynSection = nullptr;

          NodePtr preSynNode  = nullptr;
          NodePtr postSynNode = nullptr;

          Vec3f preSynPos  = synapse->preSynapticSurfacePosition();
          Vec3f postSynPos = synapse->postSynapticSurfacePosition();

          cout <<  "Synapse Nº " << numberSynapse <<" = "<< endl;
          cout << " - ID : " <<  synapse->id()<< endl;

#if 1 TESTING_PRINT_LITERAL
             SynapseNeuriteToNeuritePtr syn1 = nullptr;
             SynapseNeuriteToSomaPtr    syn2 = nullptr;
             SynapseSomaToSomaPtr       syn3 = nullptr;
              switch(synapse->synapseType())
              {
                  case 	Synapse::DENDRODENDRITIC:
                        cout << " - Type: DENDRODENDRITIC" << endl;
                        syn1 = dynamic_cast<SynapseNeuriteToNeuritePtr>(synapse);
                        preSynSection = syn1->preSynapticSection();
                        postSynSection = syn1->postSynapticSection();

                        preSynNode = syn1->preSynapticNode();
                        postSynNode = syn1->postSynapticNode();

                        cout << " - [Presynaptic Section] id: "
                             << preSynSection->_id << endl;
                        cout << " nº middle nodes: "
                             << preSynSection->nodes().size()<< endl;
                        cout << " - [Postsynaptic Section] id: "
                             << postSynSection->_id << endl;
                        cout << " nº middle nodes: "
                             << postSynSection->nodes().size()<< endl;

                        cout << " - [Presynaptic Node] id: "
                             << preSynNode->id() << endl;
                        cout << " postion: "
                             << preSynNode->point() << endl;
                        cout << " - [Postsynaptic Node] id: "
                             << postSynNode->id() << endl;
                        cout << " postion: "
                             << "[ " << postSynNode->point() << endl;

                        break;
                  case	Synapse::AXODENDRITIC:
                        cout << " - Type: AXODENDRITIC" << endl;
                        syn1 = dynamic_cast<SynapseNeuriteToNeuritePtr>(synapse);
                        preSynSection = syn1->preSynapticSection();
                        postSynSection = syn1->postSynapticSection();

                        preSynNode = syn1->preSynapticNode();
                        postSynNode = syn1->postSynapticNode();

                        cout << " - [Presynaptic Section] id: "
                             << preSynSection->_id << endl;
                        cout << " nº middle nodes: "
                             << preSynSection->nodes().size()<< endl;
                        cout << " - [Postsynaptic Section] id: "
                             << postSynSection->_id << endl;
                        cout << " nº middle nodes: "
                             << postSynSection->nodes().size()<< endl;

                        cout << " - [Presynaptic Node] id: "
                             << preSynNode->id() << endl;
                        cout << " postion: "
                             << preSynNode->point() << endl;
                        cout << " - [Postsynaptic Node] id: "
                             << postSynNode->id() << endl;
                        cout << " postion: "
                             << postSynNode->point() << endl;

                        break;
                  case	Synapse::AXOAXONIC:
                        cout << " - Type: AXOAXONIC" << endl;
                        syn1= dynamic_cast<SynapseNeuriteToNeuritePtr>(synapse);
                        preSynSection = syn1->preSynapticSection();
                        postSynSection = syn1->postSynapticSection();

                        preSynNode = syn1->preSynapticNode();
                        postSynNode = syn1->postSynapticNode();

                        cout << " - [Presynaptic Section] id: "
                             << preSynSection->_id << endl;
                        cout << " nº middle nodes: "
                             << preSynSection->nodes().size()<< endl;
                        cout << " - [Postsynaptic Section] id: "
                             << postSynSection->_id << endl;
                        cout << " nº middle nodes: "
                             << postSynSection->nodes().size()<< endl;

                        cout << " - [Presynaptic Node] id: "
                             << preSynNode->id() << endl;
                        cout << " postion: "
                             << preSynNode->point() << endl;
                        cout << " - [Postsynaptic Node] id: "
                             << postSynNode->id() << endl;
                        cout << " postion: "
                             << postSynNode->point() << endl;

                        break;
                  case	Synapse::SOMATOSOMAL:
                        cout << " - Type: SOMATOSOMAL" << endl;
                        syn3 = dynamic_cast<SynapseSomaToSomaPtr>(synapse);
                        preSynNode = syn3->preSynapticNode();
                        postSynNode = syn3->postSynapticNode();

                        cout << " - [Presynaptic Node] id: "
                             << preSynNode->id() << endl;
                        cout << " postion: "
                             << preSynNode->point() << endl;
                        cout << " - [Postsynaptic Node] id: "
                             << postSynNode->id() << endl;
                        cout << " postion: "
                             << postSynNode->point() << endl;

                        break;
                  case	Synapse::AXOSOMATIC:
                        cout << " - Type: AXOSOMATIC" << endl;
                        syn2 = dynamic_cast<SynapseNeuriteToSomaPtr>(synapse);
                        preSynSection = syn2->preSynapticSection();

                        preSynNode = syn2->preSynapticNode();
                        postSynNode = syn2->postSynapticNode();

                        cout << " - [Presynaptic Section] id: "
                             << preSynSection->_id << endl;
                        cout << " nº middle nodes: "
                             << preSynSection->nodes().size()<< endl;

                        cout << " - [Presynaptic Node] id: "
                             << preSynNode->id() << endl;
                        cout << " postion: "
                             << preSynNode->point() << endl;
                        cout << " - [Postsynaptic Node] id: "
                             << postSynNode->id() << endl;
                        cout << " postion: "
                             << postSynNode->point() << endl;

                        break;
                  case	Synapse::DENDROSOMATIC:
                        cout << " - Type: DENDROSOMATIC" << endl;
                        syn2 = dynamic_cast<SynapseNeuriteToSomaPtr>(synapse);
                        preSynSection = syn2->preSynapticSection();

                        preSynNode = syn2->preSynapticNode();
                        postSynNode = syn2->postSynapticNode();

                        cout << " - [Presynaptic Section] id: "
                             << preSynSection->_id << endl;
                        cout << " nº middle nodes: "
                             << preSynSection->nodes().size()<< endl;

                        cout << " - [Presynaptic Node] id: "
                             << preSynNode->id() << endl;
                        cout << " postion: "
                             << preSynNode->point() << endl;
                        cout << " - [Postsynaptic Node] id: "
                             << postSynNode->id() << endl;
                        cout << " postion: "
                             << postSynNode->point() << endl;

                        break;
                  default:
                        cout<< "synapse type not consistent"<< endl;
                        break;
              }
#else
             cout << " - Type : " <<  int(synapse->synapseType())<< endl;
#endif

             cout << " - [Presynaptic Neuron] id: " << preSynNeuron->gid()<< endl;
#if 1 TESTING_PRINT_LITERAL
        switch(preSynNeuron->morphologicalType( ))
        {
            case Neuron::UNDEFINED:
                  cout << " morphological type: UNDEFINED " << endl;
                  break;
            case Neuron::INTERNEURON:
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
      cout << " morphological type: " << int(preSynNeuron->morphologicalType( ))
           << endl;
#endif

#if 1 TESTING_PRINT_LITERAL
    switch(preSynNeuron->functionalType( ))
    {
        case Neuron::UNDEFINED_FUNCTIONAL_TYPE:
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
      cout << " functional type: " << int(preSynNeuron->functionalType( ))
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
cout << " morphological type: " << int(postSynNeuron->morphologicalType( ))
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
      cout << " functional type: " << int(postSynNeuron->functionalType( ))
           << endl;
#endif

      cout << " - [Presynaptic Surface Position]: [ "  << preSynPos[0]
           << ", " << preSynPos[1] << ", " << preSynPos[2] << "]" << endl;
      cout << " - [Postsynaptic Surface Position]: " << postSynPos<< endl;
      cout << endl;

       numberSynapse++;
   }

cout << "Number of synapses: " << synapses.size() <<endl;
cout << endl;

   // Free resources
   // TODO: brionReader.deleteAll( );

   return 0;
  }

  cout << "Error: circuit is empty. " << endl;
  return -1;

}
