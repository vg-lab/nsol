/**
 * @file    BBPSDKReader.h
 * @brief
 * @author  Ricardo Suarez <ricardo.suarez@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_BBPSDK_READER__
#define __NSOL_BBPSDK_READER__

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <stack>
#include <map>
#include <dirent.h>
#include <NsolTypes.h>
#include <Dendrite.h>
#include <NeuronMorphology.h>
#include <BBP/bbp.h>
#include <Writer/SwcWriter.h>

using namespace std;

namespace nsol {

typedef struct {
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

class BBPSDKReader {

public:

	const std::map<unsigned int, ColumnPtr> &readExperiment(const char *toRead,
			unsigned int directory = 0) {
		if (directory)
			return this->readFromDirectory(std::string(toRead));
		else
			return this->readFromBlueFile(std::string(toRead));
	}

	const std::map<unsigned int, ColumnPtr> &readExperiment(
			const std::string toRead, unsigned int directory = 0) {
		if (directory)
			return this->readFromDirectory(toRead);
		else
			return this->readFromBlueFile(toRead);
	}

private:

	/**
	 * Method to get a columns for BBPSDK experiment allocated in memory
	 * @param toRead blue config file to read
	 * @return map with columns
	 */
	std::map<unsigned int, ColumnPtr> &readFromBlueFile(
			const std::string toRead) {

		// Types of SWC nodes
		typedef enum {
			SWC_SOMA = 1, SWC_AXON = 2, SWC_DENDRITE = 3, SWC_APICAL = 4
		} TSwcNodeType;

		// A bbpsdk experiment is opened
		bbp::Experiment experiment;
		std::cout << toRead << ": Opening experiment " << std::endl;
		experiment.open(toRead);
		std::cout << toRead << ": DONE " << std::endl;

		if (!experiment.is_open()) {
			std::cerr << toRead << ": Experiment could not be opened"
					<< std::endl;
		}

		std::vector<NeuronPtr> nVector;
		std::map<string, NeuronMorphologyPtr> nMorphoMap;
		std::map<unsigned int, MiniColumnPtr> miniColumnMap;

		// The microcircuit of the experiment loads the data
		bbp::Microcircuit & mcp = experiment.microcircuit();
		bbp::Cell_Target target;
		mcp.load(target,
				bbp::MICROCIRCUIT | bbp::AFFERENT_SYNAPSES
						| bbp::EFFERENT_SYNAPSES);

		const bbp::Neurons &neuronsExpe = experiment.microcircuit().neurons();
		std::cerr << toRead << ": Exporting " << neuronsExpe.size()
				<< " neurons. " << std::endl;

		for (bbp::Neurons::const_iterator it = neuronsExpe.begin();
				it != neuronsExpe.end(); ++it) {
			cout << "Neuron " << it->label() << " with morphology "
					<< it->morphology().label() << std::endl;

			nsol::NeuronPtr n = new nsol::Neuron(false);		//New neuron
			nVector.push_back(n);

			bool miniColumnExist;

			//MiniColumn control
			if (miniColumnMap.find(it->minicolumn()) != miniColumnMap.end())//MiniColumn exist
					{
				n->miniColumn(miniColumnMap[it->minicolumn()]);

				miniColumnExist = true;
			} else						//MiniColumn not exist
			{
				miniColumnExist = false;
				miniColumnMap[it->minicolumn()] = new MiniColumn(
						it->minicolumn());
				n->miniColumn(miniColumnMap[it->minicolumn()]);
			}

			//Column control
			if (columnMap.find(it->column()) != columnMap.end())//Column exist
				n->miniColumn()->column(columnMap[it->column()]);
			else							//Column not exist
			{
				columnMap[it->column()] = new Column(it->column());
				n->miniColumn()->column(columnMap[it->column()]);
			}

			miniColumnMap[it->minicolumn()]->addNeuron(n);//Add neuron to minicolumn
			if (!miniColumnExist)
				columnMap[it->column()]->addMiniColumn(
						miniColumnMap[it->minicolumn()]);//Add minicolumn to column

			//Morphology previously loaded
			if (nMorphoMap.find(it->morphology().label()) != nMorphoMap.end()) {
				cout << "Morphology previously loaded" << endl;

				n->morphology(
						nMorphoMap.find(it->morphology().label())->second);
				n->layer() = it->layer();
				n->transforM(it->global_transform());
				n->gid() = it->gid();
			} else
			{
				cout << "Loading morphology " << it->morphology().label()
						<< endl;

				nsol::NeuronMorphologyPtr m = new nsol::NeuronMorphology;

				nMorphoMap[it->morphology().label()] = m;
				n->morphology(m);
				n->layer() = it->layer();
				n->transforM(it->global_transform());
				n->gid() = it->gid();

				unsigned int id = 1;

				//Getting morphology of the neuron
				const bbp::Morphology &morphology = it->morphology();
				//Getting soma of the morphology
				const bbp::Soma &soma = morphology.soma();
				//Writing soma
				for (bbp::Soma::const_iterator it = soma.begin();
						it != soma.end(); ++it) {
					NodePtr node = new Node(Vec3f((*it)[0], (*it)[1], (*it)[2]),
							id, soma.mean_radius());
					m->soma().addNode(node);

					id++;
				}

				const bbp::Sections &somas = morphology.somas();
				//Writing neurites
				for (bbp::Sections::const_iterator it = somas.begin();
						it != somas.end(); it++) {
					bbp::Sections children = (*it).children();
					for (bbp::Sections::iterator cit = children.begin();
							cit != children.end(); cit++) {
						DendritePtr
						d = nullptr;
						NeuritePtr
						n = nullptr;
						if ((*cit).type() == bbp::SECTION_AXON)
							n = m->addNeurite(Neurite::AXON);
						else if ((*cit).type() == bbp::SECTION_DENDRITE)
							d = m->addDendrite(Dendrite::BASAL);
						else if ((*cit).type() == bbp::SECTION_APICAL_DENDRITE)
							d = m->addDendrite(Dendrite::APICAL);

						const bbp::Section *section = &(*cit);
						std::stack<const bbp::Section *> sPS;
						sPS.push(section);
						std::stack<SectionPtr> parents;
						parents.push(nullptr);
						bool first = true;

						while (!sPS.empty())
						{
							const bbp::Section *lS = sPS.top();
							sPS.pop();

							SectionPtr parentSection = parents.top();
							parents.pop();

							SectionPtr s = new Section;
							if (d)
							{
								if (!d->firstSection())
									d->firstSection(s);

								s->neurite(d);
							}
							else
							{
								if (!n->firstSection())
									n->firstSection(s);

								s->neurite(n);
							}

							s->parent(parentSection);
							SegmentPtr segment = s->addSegment();

							const bbp::Segments &segments = lS->segments();
							bbp::Segments::const_iterator it = segments.begin();
							//Add first segment
							if (first)
							{
								segment->begin(
										new Node(
												Vec3f(it->begin().center()[0],
														it->begin().center()[1],
														it->begin().center()[2]),
												id, it->begin().radius()));

								++id;

								first = false;
							}
							else
								segment->begin(s->parent()->_lastSegment->end());

							segment->end(
									new Node(
											Vec3f(it->end().center()[0],
													it->end().center()[1],
													it->end().center()[2]), id,
											it->end().radius()));

							++id;

					        if (parentSection)
					          parentSection->addChild(s);

							NodePtr nPre = segment->end();
							it++;

							//While same section add more segments
							for (bbp::Segments::const_iterator itL = it;
									itL != segments.end(); ++itL) {
								segment = s->addSegment();
								segment->parentSection(s);

								segment->begin(nPre);
								segment->end(
										new Node(
												Vec3f(itL->end().center()[0],
														itL->end().center()[1],
														itL->end().center()[2]),
												id, itL->end().radius()));

								++id;

								nPre = segment->end();

							}

							//Childs?
							for (bbp::Sections::const_iterator child =
									lS->children().begin();
									child != lS->children().end(); ++child) {
								if (d) {
//									//Plus new branch
//									d->addBranchCount(lS->children().size());
									//Plus new bifurcation
//									d->addBifurcationCount(1);
								} else {
//									//Plus new branch
//									n->addBranchCount(lS->children().size());
									//Plus new bifurcation
//									n->addBifurcationCount(1);
								}

								sPS.push(&(*child));
								parents.push(s);
							}
						}
					}
				}

				SwcWriter w;

				w.writeFile(it->morphology().label(), m);
			}
		}

		return columnMap;

	}

	/**
	 * Method to get the columns for BBPSDK experiment allocated in files
	 * @param directory where the files are allocated
	 * @return map with columns
	 */
	std::map<unsigned int, ColumnPtr> &readFromDirectory(
			const std::string toRead) {
		SwcReader r;
		bool findCsv = false;

		std::vector<NeuronPtr> nVector;
		std::map<string, NeuronMorphologyPtr> nMorphoMap;
		std::map<unsigned int, MiniColumnPtr> miniColumnMap;

		DIR *pDIR;
		struct dirent *entry;
		if ((pDIR = opendir(toRead.c_str()))) {
			std::string dir(toRead.c_str());

			while ((entry = readdir(pDIR))) {
				std::string str(entry->d_name);
				unsigned found = str.find_last_of(".");

				//Load neuron file
				if (strcmp(entry->d_name, ".") != 0
						&& strcmp(entry->d_name, "..") != 0
						&& str.substr(found + 1) == "csv") {

					findCsv = true;
					cout << "\nLoading neuron file " << entry->d_name << endl;

					std::ifstream inFile;
					inFile.open(dir + entry->d_name, std::ios::in);

					//Opening file checking
					if ((inFile.rdstate() & std::ifstream::failbit) != 0) {
						std::cerr << "Error opening file " << entry->d_name
								<< std::endl;
						inFile.close();

						continue;
					}

					std::string line;
					std::getline(inFile, line);

					//Reading csv file with each neuron
					while (std::getline(inFile, line)) {

						// TODO: this does not cover the case the # char is not the first char
						if (line[0] != '#') {
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

							//TODO:column order, why?
							iss >> csvLine.globalTrans[0][0];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[1][0];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[2][0];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[3][0];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[0][1];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[1][1];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[2][1];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[3][1];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[0][2];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[1][2];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[2][2];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[3][2];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[0][3];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[1][3];
							getline(iss, comma, ',');
							iss >> csvLine.globalTrans[2][3];
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

							cout << "Neuron " << csvLine.label
									<< " with morphology "
									<< csvLine.morphoLabel << std::endl;

							NeuronPtr n = new Neuron(false);		//New neuron
							nVector.push_back(n);

							bool miniColumnExist;

							//MiniColumn control
							if (miniColumnMap.find(csvLine.miniColumn)
									!= miniColumnMap.end())	//MiniColumn exist
									{
								n->miniColumn(
										miniColumnMap[csvLine.miniColumn]);

								miniColumnExist = true;
							} else						//MiniColumn not exist
							{
								miniColumnExist = false;
								miniColumnMap[csvLine.miniColumn] =
										new MiniColumn(csvLine.miniColumn);
								n->miniColumn(
										miniColumnMap[csvLine.miniColumn]);
							}

							//Column control
							if (columnMap.find(csvLine.column)
									!= columnMap.end())	//Column exist
								n->miniColumn()->column(
										columnMap[csvLine.column]);
							else							//Column not exist
							{
								columnMap[csvLine.column] = new Column(
										csvLine.column);
								n->miniColumn()->column(
										columnMap[csvLine.column]);
							}

							miniColumnMap[csvLine.miniColumn]->addNeuron(n);//Add neuron to minicolumn
							if (!miniColumnExist)
								columnMap[csvLine.column]->addMiniColumn(
										miniColumnMap[csvLine.miniColumn]);	//Add minicolumn to column

							//Morphology previously loaded
							if (nMorphoMap.find(csvLine.morphoLabel)
									!= nMorphoMap.end()) {
								cout << "Morphology file previously loaded"
										<< endl;

								n->morphology(
										nMorphoMap.find(csvLine.morphoLabel)->second);
								n->layer() = csvLine.layer;
								n->transforM(csvLine.globalTrans);
								n->gid() = csvLine.id;
							} else {
								cout << "Loading morphology file "
										<< csvLine.morphoLabel << ".swc"
										<< endl;

								NeuronMorphologyPtr m = r.readFile(
										dir + csvLine.morphoLabel + ".swc");

								if (!m) {
									cout << "\nError opening morphology file "
											<< csvLine.morphoLabel << endl;
									continue;
								}

								nMorphoMap[csvLine.morphoLabel] = m;
								n->morphology(m);
								n->layer() = csvLine.layer;
								n->transforM(csvLine.globalTrans);
								n->gid() = csvLine.id;
							}
						}
					}

					inFile.close();
				}
			}

			closedir(pDIR);
		}

		if (!findCsv)
			cout << "Neuron file not found." << std::endl;

		return columnMap;
	}

protected:
	std::map<unsigned int, ColumnPtr> columnMap;
};
}

#endif
