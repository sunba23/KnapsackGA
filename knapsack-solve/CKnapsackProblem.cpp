#include <iostream>
#include <fstream>
#include "CKnapsackProblem.h"

// constructors & destructor
CKnapsackProblem::CKnapsackProblem(int itemCount, double capacity, vector<double>& values, vector<double>& weights)
{
	if (itemCount != values.size())
	{
		throw invalid_argument("the number of items in the file must be equal to the number of values.");
	}
	if (itemCount != weights.size())
	{
		throw invalid_argument("the number of items in the file must be equal to the number of weights.");
	}
	if (capacity < 0)
	{
		throw invalid_argument("the capacity cannot be negative.");
	}
	this-> itemCount = itemCount;
	this-> capacity = capacity;
	this-> values = values;
	this-> weights = weights;
}

CKnapsackProblem::CKnapsackProblem(string& fileName)
{
	ifstream file(fileName);
	if (!file.good())
	{
		throw invalid_argument("input file doesn't exist");
	}
	file.close();
	readFromFile(fileName);
}

CKnapsackProblem::~CKnapsackProblem()
{
	
}

// methods
double CKnapsackProblem::evaluate(const vector<bool>& genotype)
{
	double fitness = 0;
	double weight = 0;
	for (int i = 0; i < itemCount; i++)
	{
		if (genotype[i] == 1)
		{
			fitness += values[i];
			weight += weights[i];
		}
	}
	if (weight > capacity)
		fitness = 0;
	return fitness;
}

void CKnapsackProblem::readFromFile(string& fileName)
{
	ifstream myReadFile(fileName);
	if (myReadFile.peek() == ifstream::traits_type::eof())
		throw invalid_argument("the file must not be empty.");
	myReadFile.close();
	
	if (!onlyHasNumbers(fileName))
	{
		throw invalid_argument("the file must contain only numbers.");
	}
	
	myReadFile.open(fileName);
	if (myReadFile >> itemCount) {}
	else
	{
		throw invalid_argument("the number of items must be an integer.");
	}
	if (myReadFile >> capacity) {}
	else
	{
		throw invalid_argument("the capacity must be a double.");
	}
	
	double x = 0;
	while (myReadFile >> x)
	{
		values.push_back(x);
		if (myReadFile >> x)
		{
			weights.push_back(x);
		}
	}
	
	myReadFile.close();

	if (itemCount != values.size())
	{
		throw invalid_argument("there need to be as many values as items stated in the first line.");
	}
	if (itemCount != weights.size())
	{
		throw invalid_argument("there need to be as many weights as items stated in the first line.");
	}
	if (capacity < 0)
	{
		throw invalid_argument("the capacity cannot be negative.");
	}
}

bool CKnapsackProblem::onlyHasNumbers(string& fileName)
{
	ifstream myReadFile1(fileName);
	string smth = "";
	while (myReadFile1 >> smth) {
		if (smth.find_first_not_of("-0123456789") != string::npos)
		{
			return false;
		}
	}
	myReadFile1.close();
	return true;
}

// getters
double CKnapsackProblem::getCapacity()
{
	return capacity;
}
int CKnapsackProblem::getItemCount()
{
	return itemCount;
}
vector<double>& CKnapsackProblem::getValues()
{
	return values;
}
vector<double>& CKnapsackProblem::getWeights()
{
	return weights;
}