/**
 * @file    Neurite.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. Do not distribute without further notice.
 */
#ifndef __NSOL_NEURITE_
#define __NSOL_NEURITE_

#include <stack>
#include <NsolTypes.h>
#include <Section.h>

namespace nsol {

class Dendrite;
class Axon;

class Neurite {

	friend class SwcReader;
	friend class BBPSDKreader;

public:

	//! Possible types of neurite
	typedef enum {
		DENDRITE = 0, AXON
	} TNeuriteType;

	//! Default constructor
	Neurite(TNeuriteType neuriteType = DENDRITE) :
		_neuriteType(neuriteType),
		_firstSection(nullptr),
		_morphology(nullptr),
		_numBranches(0),
		_numBifurcations(0)
	{
	}
	;

	virtual ~Neurite() {
		if (_firstSection) {
			std::stack<SectionPtr> sPS;
			sPS.push(_firstSection);

			while (!sPS.empty()) {
				SectionPtr lS = sPS.top();
				sPS.pop();

				if (lS->childs().size() > 0) {
					for (unsigned int i = 0; i < lS->childs().size(); ++i)
						sPS.push(lS->childs()[i]);
				}

				delete lS;
			}
		}
	}

	//! Get the type of neurite
	TNeuriteType & neuriteType() {
		return _neuriteType;
	}


	NeuronMorphologyPtr morphology() const {
		return _morphology;
	}

	NeuronMorphologyPtr morphology(NeuronMorphologyPtr morphology) {
		return _morphology = morphology;
	}

	bool hasMorphology() {
		return _morphology;
	}

	/* SectionPtr addSection() { */
	/*   _sections.push_back(new Section); */
	/*   return _sections.back(); */
	/* }; */

	SectionPtr firstSection() {
		return _firstSection;
	}

	void firstSection(SectionPtr section) {
		_firstSection = section;
	}

	/* Sections sections() { */
	/*   return _sections; */
	/* } */

	void calculaBranchBifur(void)
	{
		unsigned int numBranchs = 0;
		unsigned int numBifur = 0;
		std::stack<SectionPtr> sPS;
		sPS.push(_firstSection);

		while (!sPS.empty())
		{
			SectionPtr lS = sPS.top();
			sPS.pop();
			for (Sections::iterator child = lS->childs().begin();
				 child != lS->childs().end(); child++)
			{
				numBranchs++;
				numBifur += lS->childs().size();

				sPS.push(*child);
			}
		}

		_numBranches = numBranchs;
		_numBifurcations = numBifur;
	}

	unsigned int numBranches()
	{
		calculaBranchBifur();
//		//Plus 1 branch for the first soma branch of each neurite
		return _numBranches;// + 1;
	}

	unsigned int numBifurcations()
	{
		calculaBranchBifur();
		return _numBifurcations;
	}

	float volume() {
		float volume = 0.0f;

		if (_firstSection) {
			std::stack<SectionPtr> sPS;
			sPS.push(_firstSection);

			while (!sPS.empty()) {
				SectionPtr lS = sPS.top();
				sPS.pop();

				volume += lS->volume();

				if (lS->childs().size() > 0)
					for (unsigned int i = 0; i < lS->childs().size(); ++i)
						sPS.push(lS->childs()[i]);
			}
		}

		return volume;
	}

	float surface() {
		float surface = 0.0f;

		if (_firstSection) {
			std::stack<SectionPtr> sPS;
			sPS.push(_firstSection);

			while (!sPS.empty()) {
				SectionPtr lS = sPS.top();
				sPS.pop();

				surface += lS->surface();

				if (lS->childs().size() > 0)
					for (unsigned int i = 0; i < lS->childs().size(); ++i)
						sPS.push(lS->childs()[i]);
			}
		}

		return surface;
	}

	float length() {
		float length = 0.0f;

		if (_firstSection) {
			std::stack<SectionPtr> sPS;
			sPS.push(_firstSection);

			while (!sPS.empty()) {
				SectionPtr lS = sPS.top();
				sPS.pop();

				length += lS->length();

				if (lS->childs().size() > 0)
					for (unsigned int i = 0; i < lS->childs().size(); ++i)
						sPS.push(lS->childs()[i]);
			}
		}

		return length;
	}

	// Casting virtual functions

	//! Return pointer to Dendrite objetc
	virtual Dendrite * asDendrite() {
		return 0;
	}

	//! Return pointer to Dendrite objetc
	virtual Axon * asAxon() {
		return 0;
	}

protected:

	void addBifurcationCount(unsigned int numBifurcations) {
		_numBifurcations += numBifurcations;
	}

	void addBranchCount(unsigned int numBranches) {
		_numBranches += numBranches;
	}

	TNeuriteType _neuriteType;

	//    Vector <Section>
	/* Sections _sections; */

	SectionPtr _firstSection;

	NeuronMorphologyPtr _morphology;

	unsigned int _numBranches;

	unsigned int _numBifurcations;
};

}

#endif
