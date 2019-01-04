#include "Genetic.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <ctime>
#include <random>
#include <functional>


Genetic::Genetic()
{
	stopTime = 60;
	populationCount = 5;
	bestPath.resize(this->vertex);
	bestCost = 0;
	mutationCoefficient = 0.01;
	crossCoefficient = 0.8;
	mutationChoice = 1;
}


Genetic::~Genetic()
{
	bestPath.clear();
}

int Genetic::CalculateCost(std::vector<int> vector)
{
	int cost = 0;

	for (int k = 0; k < vector.size() - 1; k++)
	{
		cost += graphData[vector.at(k)][vector.at(k + 1)];
	}
	cost += graphData[vector.at(vector.size() - 1)][vector.at(0)];

	return cost;
}

bool CostCompare(const Population& x, const Population& y)
{
	return x.populationCost < y.populationCost;
}

std::vector<Population> Genetic::CreatePopulation(int number)
{
	Population pop;
	std::vector<Population> population;
	std::vector<int> path;
	int pathCost = 0;

	for(int i = 0; i < number; i++)
	{
		for (int j = 0; j < this->vertex; j++)
		{
			path.push_back(j);
		}
		std::random_shuffle(path.begin(), path.end());

		for(int k = 0; k < path.size() - 1; k++)
		{
			pathCost += graphData[path.at(k)][path.at(k + 1)];
		}
		pathCost += graphData[path.at(path.size() - 1)][path.at(0)];

		pop.population = path;
		pop.populationCost = pathCost;

		population.push_back(pop);

		path.clear();
		pathCost = 0;
	}

 	return population;
}

Population Genetic::MutateSwap(Population individual)
{
	int x, y;
	do
	{
		x = rand() % this->vertex;
		y = rand() % this->vertex;

	} while (x == y);

	std::swap(individual.population.at(x), individual.population.at(y));
		
	individual.populationCost = CalculateCost(individual.population);

	return individual;
}

Population Genetic::MutateScramble(Population individual)
{
	int firstIndex = 0;
	int lastIndex = 0;
	do
	{
		firstIndex = rand() % static_cast<int>(this->vertex / 2);
		lastIndex = rand() % static_cast<int>(this->vertex / 2);

	} while (firstIndex == lastIndex || firstIndex > lastIndex);

	std::random_shuffle(individual.population.begin() + firstIndex, individual.population.end() - lastIndex);
	
	individual.populationCost = CalculateCost(individual.population);

	return individual;
}

Population Genetic::Crossover(Population parent1, Population parent2)
{
	Population child;
	std::vector<bool> visited;

	visited.resize(this->vertex);
	for(int i = 0; i < visited.size(); i++)
	{
		visited[i] = false;
	}

	for (int i = 0; i < this->vertex / 2; i++)
	{
		child.population.push_back(parent1.population[i]);
		visited[parent1.population[i]] = true;
	}

	for (int i = this->vertex / 2; i < this->vertex; i++)
	{
		if (!visited[parent2.population[i]])
		{
			child.population.push_back(parent2.population[i]);
			visited[parent2.population[i]] = true;
		}
	}

	for (int i = 0; i < this->vertex; i++)
	{
		if (!visited[i])
		{
			child.population.push_back(i);
		}
	}

	visited.clear();

	child.populationCost = CalculateCost(child.population);
	
	return child;
}
	
void Genetic::GeneticAlgorithm()
{
	clock_t start, end;
	Population pop;
	std::vector<Population> p = CreatePopulation(getPopulationCount());
	//std::priority_queue<Population> pq;
	std::vector<int> vector;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	start = clock();

	do
	{
		int size = p.size();
		for(int i = 0; i < size; i++)
		{
			if (dis(gen) < getCrossCoefficient())
			{
				int parentIndex1;
				int parentIndex2;

				do
				{
					parentIndex1 = rand() % p.size();
					parentIndex2 = rand() % p.size();

				} while (parentIndex1 == parentIndex2);

				p.push_back(Crossover(p[parentIndex1], p[parentIndex2]));
			}
		}

		int index;
		for(int i = 0; i < p.size(); i++)
		{
			if (dis(gen) < getCrossCoefficient())
			{
				switch(getMutationChoice())
				{
				case 1:
					index = rand() % p.size();
					p[index] = MutateSwap(p[index]);
					break;
				case 2:
					index = rand() % p.size();
					p[index] = MutateScramble(p[index]);
					break;
				default:
					break;
				}
			}
		}

		std::sort(p.begin(), p.end(), CostCompare);

		while (p.size() > getPopulationCount())
		{
			p.pop_back();
		}

		end = clock();

	} while (getStopTime(end, start) <= getTime());

	pop = p.front();

	bestPath = pop.population;
	bestCost = pop.populationCost;
}

void Genetic::DisplayPopulation()
{
	std::cout << std::endl;
	std::cout << "Sciezka przejscia: " << std::endl;

	for (int i = 0; i < bestPath.size(); i++)
	{
		if (i == bestPath.size() - 1)
		{
			std::cout << bestPath[i];
		}
		else
			std::cout << bestPath[i] << "->";
	}

	std::cout << std::endl;
	std::cout << "Koszt: " << bestCost << std::endl;
}

int Genetic::getTime()
{
	return stopTime;
}

void Genetic::setTime(int number)
{
	stopTime = number;
}

int Genetic::getPopulationCount()
{
	return populationCount;
}

void Genetic::setPopulatinCount(int number)
{
	populationCount = number;
}

double Genetic::getMutationCoefficient()
{
	return mutationCoefficient;
}

void Genetic::setMutationCoefficient(double number)
{
	mutationCoefficient = number;
}

int Genetic::getMutationChoice()
{
	return mutationChoice;
}

void Genetic::setMutationChoice(int number)
{
	mutationChoice = number;
}

double Genetic::getCrossCoefficient()
{
	return crossCoefficient;
}

void Genetic::setCrossCoefficient(double number)
{
	crossCoefficient = number;
}

double Genetic::getStopTime(double a, double b)
{
	return (double(a - b) / CLOCKS_PER_SEC);
}

std::vector<int> Genetic::getPath()
{
	return bestPath;
}

int Genetic::getCost()
{
	return bestCost;
}
