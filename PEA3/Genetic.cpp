#include "Genetic.h"
#include <iostream>
#include <algorithm>
#include <queue>


Genetic::Genetic()
{
	stopTime = 60;
	populationCount = 5;
	bestPath.resize(this->vertex);
	bestCost = 0;
	mutationCoefficient = 0.01;
	crossCoefficient = 0.01;
	mutationChoice = 1;
}


Genetic::~Genetic()
{
	bestPath.clear();
}

std::priority_queue<Population> Genetic::CreatePopulation(int number)
{
	Population pop;
	std::priority_queue<Population> pq;
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
			pathCost += graphData[path.at(i)][path.at(i + 1)];
		}
		pathCost += graphData[path.at(path.size() - 1)][path.at(0)];

		pop.population = path;
		pop.populationCost = pathCost;

		pq.push(pop);

		path.clear();
		pathCost = 0;
	}

	/*std::priority_queue<Population> pq1 = pq;

	do
	{
		Population pop1;
		pop1 = pq1.top();
		pq1.pop();
		for (int i = 0; i < pop1.population.size(); i++)
		{
			if (i == pop1.population.size() - 1)
			{
				std::cout << pop1.population[i];
			}
			else
				std::cout << pop1.population[i] << "->";
		}

		std::cout << std::endl;
		std::cout << pop1.populationCost << std::endl;

	} while (!pq1.empty());*/

 	return pq;
}

std::priority_queue<Population> Genetic::MutateSwap(double number)
{
	Population pop;
	std::priority_queue<Population> pq = CreatePopulation(getPopulationCount());
	Population newPop;
	std::priority_queue<Population> newQueue;

	int x, y;

	do
	{
		x = rand() % this->vertex;
		y = rand() % this->vertex;

	} while (x == y);

	do
	{
		pop = pq.top();
		pq.pop();

		if(static_cast<double>(rand() / RAND_MAX) < number)
		{
			std::swap(pop.population.at(x), pop.population.at(y));
		}

		for(int j = 0; j < pop.population.size() - 1; j++)
		{
			pop.populationCost += graphData[pop.population.at(j)][pop.population.at(j + 1)];		
		}
		pop.populationCost += graphData[pop.population.at(pop.population.size() - 1)][pop.population.at(0)];

		newPop.population = pop.population;
		newPop.populationCost = pop.populationCost;

		newQueue.push(newPop);

//		for (int i = 0; i < pop.population.size(); i++)
//		{
//			if (i == pop.population.size() - 1)
//			{
//				std::cout << pop.population[i];
//			}
//			else
//				std::cout << pop.population[i] << "->";
//		}
//		std::cout << std::endl;
//		std::cout << pop.populationCost << std::endl;

	} while (!pq.empty());

	return newQueue;
}

std::priority_queue<Population> Genetic::MutateScramble(double number)
{
	Population pop;
	std::priority_queue<Population> pq = CreatePopulation(getPopulationCount());
	Population newPop;
	std::priority_queue<Population> newQueue;

	int firstIndex;
	int lastIndex;

	do
	{
		firstIndex = rand() % static_cast<int>(this->vertex / 2);
		lastIndex = rand() % static_cast<int>(this->vertex / 2);
	}
	while (firstIndex == lastIndex || firstIndex > lastIndex);

	do
	{
		pop = pq.top();
		pq.pop();

		if(static_cast<double>(rand() / RAND_MAX) < number)
		{
			std::random_shuffle(pop.population.begin() + firstIndex, pop.population.end() - lastIndex);
		}

		for (int j = 0; j < pop.population.size() - 1; j++)
		{
			pop.populationCost += graphData[pop.population.at(j)][pop.population.at(j + 1)];
		}
		pop.populationCost += graphData[pop.population.at(pop.population.size() - 1)][pop.population.at(0)];

		newPop.population = pop.population;
		newPop.populationCost = pop.populationCost;

		newQueue.push(newPop);

//		for (int i = 0; i < pop.population.size(); i++)
//		{
//			if (i == pop.population.size() - 1)
//			{
//				std::cout << pop.population[i];
//			}
//			else
//				std::cout << pop.population[i] << "->";
//		}
//		std::cout << std::endl;
//		std::cout << pop.populationCost << std::endl;

	}
	while (!pq.empty());

	return newQueue;
}

void Genetic::GeneticAlgorithm()
{
	Population pop;
	std::priority_queue<Population> pq;

	if(getMutationChoice() == 1)
	{
		pq = MutateSwap(getMutationCoefficient());
	}

	if(getMutationChoice() == 2)
	{
		pq = MutateScramble(getMutationCoefficient());
	}

	pop = pq.top();

	std::cout << std::endl;
	std::cout << "Sciezka przejscia: " << std::endl;

	for(int i = 0; i < pop.population.size(); i++)
	{
		if (i == pop.population.size() - 1)
		{
			std::cout << pop.population[i];
		}
		else
			std::cout << pop.population[i] << "->";
	}

	std::cout << std::endl;
	std::cout << "Koszt: " << pop.populationCost << std::endl;
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
