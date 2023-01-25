#pragma once
#include <iostream>
#include <vector>
using namespace std;

class CKnapsackProblem {
public:
	// constructor & destructor
	CKnapsackProblem(int itemCount, double capacity, vector<double>& values, vector<double>& weights);
	CKnapsackProblem(string& fileName);
	~CKnapsackProblem();

	// methods
	double evaluate(const vector<bool>& genotype);
	
	// getters
	double getCapacity();
	int getItemCount();
	vector<double>& getValues();
	vector<double>& getWeights();
	
private:
	void readFromFile(string& fileName);
	bool onlyHasNumbers(string& fileName);
	vector<double> values;
	vector<double> weights;
	double capacity;
	int itemCount;
};
