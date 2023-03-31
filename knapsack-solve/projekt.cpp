#include <iostream>
#include "CGeneticAlgorithm.h"
#include "CKnapsackProblem.h"
using namespace std;

int main()
{
	srand(time(NULL));
	string fileName = "f1_l-d_kp_10_269.txt";
	int popSize = 20;
	float crossProb = 0.6;
	float mutProb = 0.15;
	int iterationAmount = 100;
	
	try {
		CKnapsackProblem knapsackProblem(fileName);
		try
		{
			CGeneticAlgorithm geneticAlgorithm(knapsackProblem, popSize, crossProb, mutProb, iterationAmount);
			geneticAlgorithm.execute();
		}
		catch (invalid_argument& e)
		{
			cout << e.what() << endl;
			return 0;
		}
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}