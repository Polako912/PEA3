#pragma once
#include "Graph.h"
#include <queue>

struct Population
{
	std::vector<int> population;
	int populationCost;
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
	int CalculateCost(std::vector<int> vector);
	std::vector<Population> CreatePopulation(int number);
	Population MutateSwap(Population individual);
	Population MutateScramble(Population individual);
	Population Crossover(Population parent1, Population parent2);
	void GeneticAlgorithm();
	void DisplayPopulation();

	int getTime();
	void setTime(int number);
	int getPopulationCount();
	void setPopulatinCount(int number);
	double getMutationCoefficient();
	void setMutationCoefficient(double number);
	int getMutationChoice();
	void setMutationChoice(int number);
	double getCrossCoefficient();
	void setCrossCoefficient(double number);
	double getStopTime(double a, double b);
	std::vector<int> getPath();
	int getCost();
};
