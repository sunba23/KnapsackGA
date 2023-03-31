#pragma once
#include <iostream>
#include <vector>
#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include "CMySmartPointer.h"

using namespace std;

class CGeneticAlgorithm {
public:
	// constructor & destructor
	CGeneticAlgorithm(CKnapsackProblem& knapsackProblem, int popSize, float crossProb, float mutProb, int iterationAmount);
	~CGeneticAlgorithm();

	// methods
	void execute();
	CIndividual getBestIndividual();
	void printPopulationFitness();
	void printBestResult();
	void printPopulation();

private:
	void generatePopulation();
	void cross();
	void mutate();
	void recalcFitness();
	
	CKnapsackProblem knapsackProblem;
	vector<CMySmartPointer<CIndividual>> population;

	int iterationAmount;
	int popSize;
	float crossProb;
	float mutProb;
	
	CIndividual bestIndividual;
	int bestIteration;
};
