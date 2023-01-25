#include <iostream>
#include "CGeneticAlgorithm.h"
#include <algorithm>
using namespace std;

// constructor & destructor
CGeneticAlgorithm::CGeneticAlgorithm(CKnapsackProblem& knapsackProblem, int popSize, float crossProb, float mutProb, int iterationAmount)
	: bestIndividual(vector<bool>()), knapsackProblem(knapsackProblem)
{
	if (popSize < 2) {
		throw invalid_argument("popSize must be greater than 1");
	}
	if (crossProb < 0 || crossProb > 1) {
		throw invalid_argument("Cross probability must be between 0 and 1");
	}
	if (mutProb < 0 || mutProb > 1) {
		throw invalid_argument("mutProb must be between 0 and 1 inclusive");
	}
	if (iterationAmount < 1) {
		throw invalid_argument("iterationAmount must be greater than 0");
	}
	this-> popSize = popSize;
	this-> crossProb = crossProb;
	this-> mutProb = mutProb;
	this-> iterationAmount = iterationAmount;
	bestIteration = 1;
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
	
}

// methods
void CGeneticAlgorithm::execute()
{
	generatePopulation();
	
	for (int i = 0; i < iterationAmount; i++)
	{
		cout << "\niteration " << i + 1 << endl;
		recalcFitness();
		
		sort(population.rbegin(), population.rend(), [](CMySmartPointer<CIndividual>& a, CMySmartPointer<CIndividual>& b) {return a->getFitness() < b->getFitness(); });
		if (bestIndividual.getFitness() < population.front()->getFitness())
		{
			bestIndividual = *population.front();
			bestIteration = i + 1;
		}
		
		cross();
		mutate();
		printBestResult();
	}
	cout << "\n\n";
}

void CGeneticAlgorithm::generatePopulation()
{
	for (int i = 0; i < popSize; i++)
		population.push_back(CMySmartPointer<CIndividual>(new CIndividual(knapsackProblem)));
}

void CGeneticAlgorithm::cross()
{
	vector<CMySmartPointer<CIndividual>> newPopulation;
	
	while (newPopulation.size() < popSize)
	{
		int cnd1Pos = rand() % popSize;
		int cnd2Pos = rand() % popSize;
		int p1pos = 0, p2pos = 0;
		
		while (cnd1Pos == cnd2Pos)
			cnd2Pos = rand() % popSize;
		if (population[cnd1Pos]->getFitness() > population[cnd2Pos]->getFitness())
			p1pos = cnd1Pos;
		else
			p1pos = cnd2Pos;

		cnd1Pos = rand() % popSize;
		cnd2Pos = rand() % popSize;
		
		while (cnd1Pos == cnd2Pos)
			cnd2Pos = rand() % popSize;
		if (population[cnd1Pos]->getFitness() > population[cnd2Pos]->getFitness())
			p2pos = cnd1Pos;
		else
			p2pos = cnd2Pos;


		// (optional) make sure that parents are different
		if (p1pos == p2pos)
		{
			if (p2pos == cnd1Pos)
				p2pos = cnd2Pos;
			else
				p2pos = cnd1Pos;
		}
		
		pair<CIndividual*, CIndividual*> children = population[p1pos]->crossover(*population[p2pos], crossProb);
		
		if (children.first == nullptr && children.second == nullptr)
		{
			newPopulation.push_back(population[p1pos]);
			if (newPopulation.size() < popSize)
				newPopulation.push_back(population[p2pos]);
		}
		else {
			newPopulation.push_back(children.first);
			if (newPopulation.size() < popSize)
				newPopulation.push_back(children.second);
		}
	}
	population = newPopulation;
}

void CGeneticAlgorithm::mutate()
{
	for (int i = 0; i < popSize; i++)
		population.at(i)->mutate(mutProb);
}

void CGeneticAlgorithm::recalcFitness()
{
	for (int i = 0; i < popSize; i++)
		population.at(i)->calculateFitness(knapsackProblem);
}

CIndividual CGeneticAlgorithm::getBestIndividual()
{
	return bestIndividual;
}

void CGeneticAlgorithm::printPopulationFitness()
{
	for (int i = 0; i < popSize; i++)
		cout << population.at(i)->getFitness() << " ";
	cout << endl;
}

void CGeneticAlgorithm::printBestResult()
{
	cout << "best result: ";
	bestIndividual.printGenotype();
	cout << " fitness: " << bestIndividual.getFitness() << " iteration: " << bestIteration << endl;
}

void CGeneticAlgorithm::printPopulation()
{
	for (int i = 0; i < popSize; i++)
	{
		population.at(i)->printGenotype();
		cout << " fitness: " << population.at(i)->getFitness() << endl;
	}
	cout << endl;
}