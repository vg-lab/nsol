#include <nsol.h>
#include <assert.h>
#include <iostream>
#include <stack>
#include <map>
#include <dirent.h>

using namespace nsol;
using namespace std;

typedef struct
{
  unsigned int id;
  std::string label;
  unsigned int column;
  unsigned int miniColumn;
  unsigned int layer;
  Vec3f position;
  Matrix4_4f globalTrans;
  Vec4f orientation;
  std::string morphoLabel;
} TcsvFileLine;


int main(int argc, char *argv[])
{

  SwcReader r;
  bool findCsv = false;

  DIR *pDIR;
  struct dirent *entry;
  if ( (pDIR=opendir(argv[1])) )
  {
	  std::string dir(argv[1]);

	  std::vector<NeuronPtr> nVector;
	  std::map<string, NeuronMorphologyPtr> nMorphoMap;
	  std::map<unsigned int, ColumnPtr> columnMap;
	  std::map<unsigned int, MiniColumnPtr> miniColumnMap;


	  while((entry = readdir(pDIR)))
	  {
		  std::string str(entry->d_name);
			unsigned found = str.find_last_of(".");

			//Load neuron file
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && str.substr(found+1) == "csv")
			{

				findCsv = true;
				  cout << "\nLoading neuron file " << entry->d_name << endl;

				  std::ifstream inFile;
				  inFile.open(dir + entry->d_name, std::ios::in);

				  //Opening file checking
				  if ((inFile.rdstate() & std::ifstream::failbit) != 0)
				  {
					std::cerr << "Error opening file " << entry->d_name << std::endl;

					continue;
				  }

				  std::map<string, TcsvFileLine> neurons;

				  std::string line;
				  std::getline(inFile, line);

				  /* // Padding for skkiping line 0 */
				  /* TSwcLine padding; */
				  /* linespush_back(padding); */

				  while (std::getline(inFile, line))
				  {

					// TODO: this does not cover the case the # char is not the first char
					if (line[0] != '#')
					{
					  std::istringstream iss(line);
					  std::string comma;
					  TcsvFileLine csvLine;

					  iss >> csvLine.id;
					  getline(iss, comma, ',');
//				          iss >> csvLine.label;
					  getline(iss, csvLine.label, ',');
					  iss >> csvLine.column;
					  getline(iss, comma, ',');
					  iss >> csvLine.miniColumn;
					  getline(iss, comma, ',');
					  iss >> csvLine.layer;
					  getline(iss, comma, ',');
					  iss >> csvLine.position[0];
					  getline(iss, comma, ',');
					  iss >> csvLine.position[1];
					  getline(iss, comma, ',');
					  iss >> csvLine.position[2];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[0][0];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[0][1];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[0][2];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[0][3];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[1][0];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[1][1];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[1][2];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[1][3];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[2][0];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[2][1];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[2][2];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[2][3];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[3][0];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[3][1];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[3][2];
					  getline(iss, comma, ',');
					  iss >> csvLine.globalTrans[3][3];
					  getline(iss, comma, ',');
					  iss >> csvLine.orientation[0];
					  getline(iss, comma, ',');
					  iss >> csvLine.orientation[1];
					  getline(iss, comma, ',');
					  iss >> csvLine.orientation[2];
					  getline(iss, comma, ',');
					  iss >> csvLine.orientation[3];
					  getline(iss, comma, ',');
//				          iss >> csvLine.morphoLabel;
					  getline(iss, csvLine.morphoLabel, ',');


					  cout << "Neuron " << csvLine.label  << " with morphology " << csvLine.morphoLabel << std::endl;

					  NeuronPtr n = new Neuron(false);		//New neuron
					  nVector.push_back(n);

					  //Column control
					  if (columnMap.find(csvLine.column) != columnMap.end())	//Column exist
						  n->column(columnMap[csvLine.column]);
					  else														//Column not exist
					  {
						  columnMap[csvLine.column] = new Column(csvLine.column);
						  n->column(columnMap[csvLine.column]);
					  }

					  //MiniColumn control
					  if (miniColumnMap.find(csvLine.miniColumn) != miniColumnMap.end())	//MiniColumn exist
						  n->miniColumn(miniColumnMap[csvLine.miniColumn]);
					  else																	//MiniColumn not exist
					  {
						  miniColumnMap[csvLine.miniColumn] = new MiniColumn(csvLine.miniColumn);
						  n->miniColumn(miniColumnMap[csvLine.miniColumn]);
					  }

					  miniColumnMap[csvLine.miniColumn]->addNeuron(n);									//Add neuron to minicolumn
					  columnMap[csvLine.column]->addMiniColumn(miniColumnMap[csvLine.miniColumn]);		//Add minicolumn to column

					  //Morphology previously loaded
					  if (neurons.find(csvLine.morphoLabel)  != neurons.end())
					  {
						  cout << "Morphology file previously loaded" << endl;

						  n->morphology(nMorphoMap.find(csvLine.morphoLabel)->second);
						  n->layer(csvLine.layer);
						  n->transforM(csvLine.globalTrans);
					  }
					  else
					  {
						  neurons[csvLine.morphoLabel] = csvLine;	//Add neuron

						  cout << "Loading morphology file " << csvLine.morphoLabel << ".swc" << endl;

						  NeuronMorphologyPtr m = r.readFile(dir+csvLine.morphoLabel+".swc");

						  nMorphoMap[csvLine.morphoLabel] = m;

						  n->morphology(m);
						  n->layer(csvLine.layer);
						  n->transforM(csvLine.globalTrans);

						  if (!m)
						  {
							  cout << "\nError opening morphology file " << entry->d_name << endl;
							  continue;
						  }

						  Neurites neurites = m->neurites();

						  for (Neurites::iterator it = neurites.begin(); it != neurites.end(); it++)
						  {
							NeuritePtr neurite = (*it);

							if (!neurite->firstSection())
							{
							  continue;
							}

							stack<SectionPtr> stack;
							stack.push(neurite->firstSection());

							while (!stack.empty())
							{

							  SectionPtr section = stack.top();

							  assert(section);
							  stack.pop();

							  for (Sections::iterator itSect = section->childs().begin();
								  itSect != section->childs().end(); itSect++)
							  {
								SectionPtr child = (*itSect);
								stack.push(child);
							  };

							  SegmentPtr segment = section->firstSegment();
							  while (segment)
							  {
								segment = segment->next();
							  }
							}
						  }
					  }
					}
				  }

				  inFile.close();
			}
	  }

	  closedir(pDIR);


//	  for (std::vector<NeuronPtr>::iterator it =
//    		  nVector.begin(); it != nVector.end(); it++)
//    	  cout << (*it)->column()->id() << " " <<  (*it)->miniColumn()->id() << " " << (*it)->layer() << " " << (*it)->transforM()[0][0] <<  endl;
//
//	  vector<NeuronPtr>::iterator it1 = nVector.end()-1;
//
//	  SwcWriter w;
//
//	  w.writeFile("salida_prueba", (*it1)->morphology());


  }

  if (!findCsv)
	  cout << "Neuron file not found." << std::endl;

}
