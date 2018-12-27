#pragma once
#include "Graph.h"
#include <queue>

struct Population
{
	std::vector<int> population;
	int populationCost;

	friend bool operator <(const Population& other, const Population& second)
	{
		return other.populationCost > second.populationCost;
	}
};

class Genetic: public Graph
{
private:
	int stopTime;
	int populationCount;
	double mutationCoefficient;
	double crossCoefficient;
public:
	Genetic();
	~Genetic();
	std::priority_queue<Population> CreatePopulation(int number);
	std::priority_queue<Population> Mutate(int number);
	void Crossover();

	int getTime();
	void setTime(int number);
	int getPopulationCount();
	void setPopulatinCount(int number);
	double getMutationCoefficient();
	void setMutationCoefficient(double number);
	double getCrossCoefficient();
	void setCrossCoefficient(double number);
	//Population getPopulaton();
};
