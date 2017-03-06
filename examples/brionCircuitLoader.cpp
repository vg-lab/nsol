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

/** -- Computing synaptic-nodes -- **/
void calculateSynapticNodes( MorphologySynapsePtr synapse,
                               NeuronPtr preSynapticNeuron,
                               NeuronPtr postSynapticNeuron,
                               NodePtr& preSynNode,
                               NodePtr& postSynNode )
{
    if ( preSynapticNeuron == nullptr || postSynapticNeuron == nullptr ||
         synapse == nullptr )
    {
        return;
    }

    // To pre-synaptic node...
    preSynNode = nullptr;
    Nodes nodesPre = preSynapticNeuron->morphology()->soma()->nodes();

    SectionPtr preSynSection = synapse->preSynapticSection( );

    if( preSynSection != nullptr )
    {
        nodesPre = preSynSection->nodes();
        nodesPre.push_back(preSynSection->firstNode());
        nodesPre.push_back(preSynSection->lastNode());
    }

    const Matrix4_4f modelPre = preSynapticNeuron->transform();
    Vec3f p_ = synapse->preSynapticSurfacePosition( );
    float distance = 10000000;
    NSOL_FOREACH( nodeIt, nodesPre )
    {
        const NodePtr node = (*nodeIt);
        Vec3f posNode = node->point();

        Vec4f pt = modelPre * Vec4f(posNode.x(),
                                    posNode.y(),
                                    posNode.z(), 1.f);
        pt = pt/pt.w();

        float distActual = std::sqrt(pow((p_.x()-pt.x()), 2)+
                                     pow((p_.y()-pt.y()), 2)+
                                     pow((p_.z()-pt.z()), 2));
        if(distActual < distance)
        {
            distance = distActual;
            preSynNode = node;
        }
    }

    // To post-synaptic node...
    postSynNode = nullptr;
    Nodes nodesPost = postSynapticNeuron->morphology()->soma()->nodes();

    SectionPtr postSynSection = synapse->postSynapticSection();

    if(postSynSection != nullptr)
    {
        nodesPost = postSynSection->nodes();
        nodesPost.push_back(postSynSection->firstNode());
        nodesPost.push_back(postSynSection->lastNode());
    }

    const Matrix4_4f modelPost = postSynapticNeuron->transform();
    p_ = synapse->postSynapticSurfacePosition();
    distance = 10000000;
    NSOL_FOREACH( nodeIt, nodesPost )
    {
        const NodePtr node = (*nodeIt);
        Vec3f posNode = node->point();

        Vec4f pt = modelPost * Vec4f(posNode.x(),
                                     posNode.y(),
                                     posNode.z(), 1.f);
        pt = pt/pt.w();

        float distActual = std::sqrt(pow((p_.x()-pt.x()), 2)+
                                     pow((p_.y()-pt.y()), 2)+
                                     pow((p_.z()-pt.z()), 2));
        if(distActual < distance)
        {
            distance = distActual;
            postSynNode = node;
        }
    }
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

    dataSet.loadBlueConfigHierarchy( blueConfig, target );
    dataSet.loadAllMorphologies( );
    dataSet.loadBlueConfigConnectivity( );

    cout << " EXECUTING CircuitLoader... " << endl;
    cout << endl; cout << endl; cout << endl;

    Circuit circuit = dataSet.circuit();

    std::set<SynapsePtr> synapses = circuit.synapses( Circuit::ALL );

    if( !synapses.empty( ))
    {
        cout << "Synapses of the circuit: " << endl;
        cout << endl;

        NeuronsMap neurons = dataSet.neurons();

        int numberSynapse = 0;
//        for( unsigned int i = 0; i < synapses.size(); ++i )
//        {
        NSOL_FOREACH( synapseIt, synapses )
        {
            SynapsePtr synapse_ = (*synapseIt);
            MorphologySynapsePtr synapse = dynamic_cast
                                            <MorphologySynapsePtr>( synapse_ );
            NeuronPtr preSynapticNeuron  = nullptr;
            NeuronPtr postSynapticNeuron = nullptr;

            NeuronsMap::iterator neuronIt = neurons.
                                           find( synapse->preSynapticNeuron( ));
            if( neuronIt != neurons.end( ))
            {
                preSynapticNeuron = neuronIt->second;
            }
            NeuronsMap::iterator neuronIt_ = neurons.
                                          find( synapse->postSynapticNeuron( ));
            if( neuronIt_ != neurons.end( ))
            {
                postSynapticNeuron = neuronIt_->second;
            }

            SectionPtr preSynSection  = nullptr;
            SectionPtr postSynSection = nullptr;

            NodePtr preSynNode  = nullptr;
            NodePtr postSynNode = nullptr;

          Vec3f preSynPos  = synapse->preSynapticSurfacePosition();
            Vec3f postSynPos = synapse->postSynapticSurfacePosition();

            cout <<  "Synapse Nº " << numberSynapse <<" = "<< endl;

#if 1 TESTING_PRINT_LITERAL

            calculateSynapticNodes( synapse, preSynapticNeuron,
                                             postSynapticNeuron,
                                      preSynNode, postSynNode );

            MorphologySynapse::TSynapseType synapseType;
            synapseType = synapse->synapseType();

            switch( synapseType )
            {
                case MorphologySynapse::DENDRODENDRITIC:
                    cout << " - Type: DENDRODENDRITIC" << endl;

                    preSynSection = synapse->preSynapticSection();
                    postSynSection = synapse->postSynapticSection();

                    cout << " - [Presynaptic Section] id: "
                         << preSynSection->id() << endl;
                    cout << " nº middle nodes: "
                         << preSynSection->nodes().size()<< endl;
                    cout << " - [Postsynaptic Section] id: "
                         << postSynSection->id() << endl;
                    cout << " nº middle nodes: "
                         << postSynSection->nodes().size()<< endl;

                    cout << " - [Presynaptic Node] id: "
                         << preSynNode->id() << endl;
                    cout << " postion: [ "
                               << preSynNode->point().x()
                         <<" ,"<< preSynNode->point().y()
                         <<" ,"<< preSynNode->point().z()
                         << " ]" << endl;
                    cout << " - [Postsynaptic Node] id: "
                         << postSynNode->id() << endl;
                    cout << " postion: [ "
                               << postSynNode->point().x()
                         <<" ,"<< postSynNode->point().y()
                         <<" ,"<< postSynNode->point().z()
                         << " ]" << endl;

                    break;
                case MorphologySynapse::AXODENDRITIC:
                    cout << " - Type: AXODENDRITIC" << endl;

                    preSynSection = synapse->preSynapticSection();
                    postSynSection = synapse->postSynapticSection();

                    cout << " - [Presynaptic Section] id: "
                         << preSynSection->id() << endl;
                    cout << " nº middle nodes: "
                         << preSynSection->nodes().size()<< endl;
                    cout << " - [Postsynaptic Section] id: "
                         << postSynSection->id() << endl;
                    cout << " nº middle nodes: "
                         << postSynSection->nodes().size()<< endl;

                    cout << " - [Presynaptic Node] id: "
                         << preSynNode->id() << endl;
                    cout << " postion: [ "
                               << preSynNode->point().x()
                         <<" ,"<< preSynNode->point().y()
                         <<" ,"<< preSynNode->point().z()
                         << " ]" << endl;
                    cout << " - [Postsynaptic Node] id: "
                         << postSynNode->id() << endl;
                    cout << " postion: [ "
                               << postSynNode->point().x()
                         <<" ,"<< postSynNode->point().y()
                         <<" ,"<< postSynNode->point().z()
                         << " ]" << endl;

                    break;
                case MorphologySynapse::AXOAXONIC:
                    cout << " - Type: AXOAXONIC" << endl;

                    preSynSection = synapse->preSynapticSection();
                    postSynSection = synapse->postSynapticSection();

                    cout << " - [Presynaptic Section] id: "
                         << preSynSection->id() << endl;
                    cout << " nº middle nodes: "
                         << preSynSection->nodes().size()<< endl;
                    cout << " - [Postsynaptic Section] id: "
                         << postSynSection->id() << endl;
                    cout << " nº middle nodes: "
                         << postSynSection->nodes().size()<< endl;

                    cout << " - [Presynaptic Node] id: "
                         << preSynNode->id() << endl;
                    cout << " postion: [ "
                               << preSynNode->point().x()
                         <<" ,"<< preSynNode->point().y()
                         <<" ,"<< preSynNode->point().z()
                         << " ]" << endl;
                    cout << " - [Postsynaptic Node] id: "
                         << postSynNode->id() << endl;
                    cout << " postion: [ "
                               << postSynNode->point().x()
                         <<" ,"<< postSynNode->point().y()
                         <<" ,"<< postSynNode->point().z()
                         << " ]" << endl;

                    break;
                case MorphologySynapse::SOMATOSOMATIC:
                    cout << " - Type: SOMATOSOMATIC" << endl;

                    cout << " - [Presynaptic Node] id: "
                         << preSynNode->id() << endl;
                    cout << " postion: [ "
                               << preSynNode->point().x()
                         <<" ,"<< preSynNode->point().y()
                         <<" ,"<< preSynNode->point().z()
                         << " ]" << endl;
                    cout << " - [Postsynaptic Node] id: "
                         << postSynNode->id() << endl;
                    cout << " postion: [ "
                               << postSynNode->point().x()
                         <<" ,"<< postSynNode->point().y()
                         <<" ,"<< postSynNode->point().z()
                         << " ]" << endl;

                    break;
                case MorphologySynapse::AXOSOMATIC:
                    cout << " - Type: AXOSOMATIC" << endl;

                    preSynSection = synapse->preSynapticSection();

                    cout << " - [Presynaptic Section] id: "
                         << preSynSection->id() << endl;
                    cout << " nº middle nodes: "
                         << preSynSection->nodes().size()<< endl;

                    cout << " - [Presynaptic Node] id: "
                         << preSynNode->id() << endl;
                    cout << " postion: [ "
                               << preSynNode->point().x()
                         <<" ,"<< preSynNode->point().y()
                         <<" ,"<< preSynNode->point().z()
                         << " ]" << endl;
                    cout << " - [Postsynaptic Node] id: "
                         << postSynNode->id() << endl;
                    cout << " postion: [ "
                               << postSynNode->point().x()
                         <<" ,"<< postSynNode->point().y()
                         <<" ,"<< postSynNode->point().z()
                         << " ]" << endl;

                    break;
                case MorphologySynapse::DENDROSOMATIC:
                    cout << " - Type: DENDROSOMATIC" << endl;

                    preSynSection = synapse->preSynapticSection();

                    cout << " - [Presynaptic Section] id: "
                         << preSynSection->id() << endl;
                    cout << " nº middle nodes: "
                         << preSynSection->nodes().size()<< endl;

                    cout << " - [Presynaptic Node] id: "
                         << preSynNode->id() << endl;
                    cout << " postion: [ "
                               << preSynNode->point().x()
                         <<" ,"<< preSynNode->point().y()
                         <<" ,"<< preSynNode->point().z()
                         << " ]" << endl;
                    cout << " - [Postsynaptic Node] id: "
                         << postSynNode->id() << endl;
                    cout << " postion: [ "
                               << postSynNode->point().x()
                         <<" ,"<< postSynNode->point().y()
                         <<" ,"<< postSynNode->point().z()
                         << " ]" << endl;

                    break;
                default:
                    cout<< "synapse type not consistent"<< endl;
                    break;
            }
#else
             cout << " - Type : " <<  int(synapse->synapseType())<< endl;
#endif
             // Presynaptic neuron
             if( preSynapticNeuron != nullptr )
             {
                 Matrix4_4f modelPre = preSynapticNeuron->transform();
                 cout << " - [Presynaptic Neuron] id: "
                      << synapse->preSynapticNeuron()<< endl;
                 cout << " - [Presynaptic Neuron] transform:" << endl << "[ " <<
                         modelPre(0,0) << ", " <<
                         modelPre(0,1) << ", " <<
                         modelPre(0,2) << ", " <<
                         modelPre(0,3) << " ]" <<
                         endl;
                         cout << "[ " <<
                         modelPre(1,0) << ", " <<
                         modelPre(1,1) << ", " <<
                         modelPre(1,2) << ", " <<
                         modelPre(1,3) << " ]" <<
                         endl;
                         cout << "[ " <<
                         modelPre(2,0) << ", " <<
                         modelPre(2,1) << ", " <<
                         modelPre(2,2) << ", " <<
                         modelPre(2,3) << " ]" <<
                         endl;
                         cout << "[ " <<
                         modelPre(3,0) << ", " <<
                         modelPre(3,1) << ", " <<
                         modelPre(3,2) << ", " <<
                         modelPre(3,3) << " ]" <<
                         endl;

#if 1 TESTING_PRINT_LITERAL
                switch( preSynapticNeuron->morphologicalType( ))
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
                    case Neuron::STELLATE:
                          cout << " morphological type: STELLATE " << endl;
                          break;
                    case Neuron::GOLGI:
                          cout << " morphological type: GOLGI " << endl;
                          break;
                    case Neuron::GRANULE:
                          cout << " morphological type: GRANULE " << endl;
                          break;
                    case Neuron::LUGARO:
                          cout << " morphological type: LUGARO " << endl;
                          break;
                    case Neuron::UNIPOLAR_BRUSH:
                          cout << " morphological type: UNIPOLAR_BRUSH " << endl;
                          break;
                    case Neuron::PURKINJE:
                          cout << " morphological type: PURKINJE " << endl;
                          break;
                    case Neuron::CHANDELIER:
                          cout << " morphological type: CHANDELIER " << endl;
                          break;
                    case Neuron::INFERIOR_OLIVE:
                          cout << " morphological type: INFERIOR_OLIVE " << endl;
                          break;
                    case Neuron::DEEP_CEREBELLAR_NUCLEI:
                          cout << " morphological type: DEEP_CEREBELLAR_NUCLEI " << endl;
                          break;
                    default:
                          cout<< "neuron morphological type not consistent"<< endl;
                          break;
                 }
#else
      cout << " morphological type: " << int( preSynapticNeuron->morphologicalType( ))
           << endl;
#endif
             }//Presynaptic neuron

#if 1 TESTING_PRINT_LITERAL
    switch(preSynapticNeuron->functionalType( ))
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
      cout << " functional type: " << int(preSynapticNeuron->functionalType( ))
           << endl;
#endif

             //Postsynaptic neuron
             if( postSynapticNeuron != nullptr )
             {
                Matrix4_4f modelPost = postSynapticNeuron->transform();
                cout << " - [Postsynaptic Neuron] id: "
                     << synapse->postSynapticNeuron( )<< endl;
                cout << " - [Postsynaptic Neuron] transform:" << endl << "[ " <<
                        modelPost(0,0) << ", " <<
                        modelPost(0,1) << ", " <<
                        modelPost(0,2) << ", " <<
                        modelPost(0,3) << " ]" <<
                        endl;
                        cout << "[ " <<
                        modelPost(1,0) << ", " <<
                        modelPost(1,1) << ", " <<
                        modelPost(1,2) << ", " <<
                        modelPost(1,3) << " ]" <<
                        endl;
                        cout << "[ " <<
                        modelPost(2,0) << ", " <<
                        modelPost(2,1) << ", " <<
                        modelPost(2,2) << ", " <<
                        modelPost(2,3) << " ]" <<
                        endl;
                        cout << "[ " <<
                        modelPost(3,0) << ", " <<
                        modelPost(3,1) << ", " <<
                        modelPost(3,2) << ", " <<
                        modelPost(3,3) << " ]" <<
                        endl;

#if 1 TESTING_PRINT_LITERAL
                switch( postSynapticNeuron->morphologicalType( ))
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
                    case Neuron::STELLATE:
                          cout << " morphological type: STELLATE " << endl;
                          break;
                    case Neuron::GOLGI:
                          cout << " morphological type: GOLGI " << endl;
                          break;
                    case Neuron::GRANULE:
                          cout << " morphological type: GRANULE " << endl;
                          break;
                    case Neuron::LUGARO:
                          cout << " morphological type: LUGARO " << endl;
                          break;
                    case Neuron::UNIPOLAR_BRUSH:
                          cout << " morphological type: UNIPOLAR_BRUSH " << endl;
                          break;
                    case Neuron::PURKINJE:
                          cout << " morphological type: PURKINJE " << endl;
                          break;
                    case Neuron::CHANDELIER:
                          cout << " morphological type: CHANDELIER " << endl;
                          break;
                    case Neuron::INFERIOR_OLIVE:
                          cout << " morphological type: INFERIOR_OLIVE " << endl;
                          break;
                    case Neuron::DEEP_CEREBELLAR_NUCLEI:
                          cout << " morphological type: DEEP_CEREBELLAR_NUCLEI " << endl;
                          break;
                    default:
                          cout<< "neuron morphological type not consistent"<< endl;
                          break;
                 }
#else
      cout << " morphological type: " << int( postSynapticNeuron->morphologicalType( ))
           << endl;
#endif
             }//Postsynaptic neuron

#if 1 TESTING_PRINT_LITERAL
    switch(postSynapticNeuron->functionalType( ))
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
      cout << " functional type: " << int(postSynapticNeuron->functionalType( ))
           << endl;
#endif


             cout << " - [Presynaptic Surface Position]: [ "  << preSynPos.x()
                  << ", " << preSynPos.y() << ", " << preSynPos.z() << " ]"
                  << endl;
             cout << " - [Postsynaptic Surface Position]: [ "  << postSynPos.x()
                  << ", " << postSynPos.y() << ", " << postSynPos.z() << " ]"
                  << endl;
             cout << endl;

             numberSynapse++;

        }//All synapses

        cout << "Number of synapses: " << synapses.size() <<endl;
        cout << endl;

        // Free resources
        dataSet.close( );

        return 0;
    }

    cout << "Error: circuit is empty. " << endl;

    dataSet.close( );
    return -1;

}
