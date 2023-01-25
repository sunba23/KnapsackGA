#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "CKnapsackProblem.h"
#include "CMySmartPointer.h"
using namespace std;

class CIndividual {
public:
	CIndividual(CKnapsackProblem& CKnapsackProblem);
	CIndividual(const CIndividual& other);
	CIndividual(vector<bool> genotype);
	~CIndividual();

	void calculateFitness(CKnapsackProblem &knapsackProblem);
	pair<CIndividual*, CIndividual*> crossover(const CIndividual& partner, float crossProb);
	void mutate(float mutProb);
	void printGenotype();
	
	double getFitness();
	vector<bool>& getGenotype();

	//bool operator==(const CIndividual& other);

private:
	vector<bool> genotype;
	double fitness;
	void generateGenotype(CKnapsackProblem& knapsackProblem);
};
