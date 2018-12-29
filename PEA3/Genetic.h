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
	std::vector<int> bestPath;
	int bestCost;
	int mutationChoice;

public:
	Genetic();
	~Genetic();
	std::priority_queue<Population> CreatePopulation(int number);
	std::priority_queue<Population> MutateSwap(double number);
	std::priority_queue<Population> MutateScramble(double number);
	void GeneticAlgorithm();
	//void Crossover();

	int getTime();
	void setTime(int number);
	int getPopulationCount();
	void setPopulatinCount(int number);
	double getMutationCoefficient();
	void setMutationCoefficient(double number);
	int getMutationChoice();
	void setMutationChoice(int number);
	double getStopTime(double a, double b);
};
