#include <iostream>
#include <utility>
#include "CIndividual.h"
#include "RandomDevice.h"
#include <random>
using namespace std;

CIndividual::CIndividual(CKnapsackProblem& knapsackProblem)
{
	fitness = -1;
	generateGenotype(knapsackProblem);
}

CIndividual::CIndividual(const CIndividual& other)
{
	genotype = other.genotype;
	fitness = other.fitness;
}

CIndividual::CIndividual(vector<bool> genotype)
{
	this->genotype = genotype;
	fitness = -1;
}

CIndividual::~CIndividual() {

}

void CIndividual::generateGenotype(CKnapsackProblem& knapsackProblem) {
	RandomDevice rd;
	for (int i = 0; i < knapsackProblem.getItemCount(); i++)
	{
		genotype.push_back(rd.randomBool());
	}
}

void CIndividual::calculateFitness(CKnapsackProblem& knapsackProblem) {
	fitness = knapsackProblem.evaluate(genotype);
}

pair<CIndividual*, CIndividual*> CIndividual::crossover(const CIndividual& partner, float crossProb) {
	RandomDevice rd;
	if (rd.randomFloat(0,1) < crossProb)
	{
		vector<bool> genotype1;
		vector<bool> genotype2;
		int genotypeLength = genotype.size();
		int crossPoint = rd.randomInt(0, genotypeLength) % genotypeLength;
		
		for (int i = 0; i < crossPoint; i++)
		{
			genotype1.push_back(genotype[i]);
			genotype2.push_back(partner.genotype[i]);
		}
		for (int i = crossPoint; i < genotypeLength; i++)
		{
			genotype1.push_back(partner.genotype[i]);
			genotype2.push_back(genotype[i]);
		}
		return make_pair(new CIndividual(genotype1), new CIndividual(genotype2));
	}
	else
	{
		return make_pair(nullptr, nullptr);
	}
}

void CIndividual::mutate(float mutProb) {
	int genotypeLength = genotype.size();
	RandomDevice rd;
	for (int i = 0; i < genotypeLength; i++)
	{
		if (rd.randomFloat(0, 1) < mutProb)
		{
			if (genotype[i] == 0)
			{
				genotype[i] = 1;
			}
			else
			{
				genotype[i] = 0;
			}
		}
	}
}

void CIndividual::printGenotype() {
	int length = genotype.size();
	for (int i = 0; i < length; i++)
	{
		cout << genotype[i];
	}
}

double CIndividual::getFitness() {
	return fitness;
}

vector<bool>& CIndividual::getGenotype() {
	return genotype;
}

//bool CIndividual::operator==(const CIndividual& other) {
//	return genotype == other.genotype;
//}