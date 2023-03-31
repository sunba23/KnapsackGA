#pragma once
#include <iostream>
#include <random>
using namespace std;

class RandomDevice {
public:
	float randomFloat(float min, float max)
	{
		static default_random_engine e;
		static uniform_real_distribution<> dis(min, max);
		return dis(e);
	}
	bool randomBool()
	{
		static default_random_engine e;
		static uniform_int_distribution<> dis(0, 1);
		return dis(e);
	}
	int randomInt(int a, int b)
	{
		static default_random_engine e;
		static uniform_int_distribution<> dis(a, b);
		return dis(e);
	}
private:
};
