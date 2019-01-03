#include "Genetic.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <ctime>
#include <random>


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

	for (int i = 0; i < population.size(); i++)
	{
		for (int j = 0; j < population[i].population.size(); j++)
		{
			if (j == population[i].population.size() - 1)
			{
				std::cout << population[i].population[j];
			}
			else
				std::cout << population[i].population[j] << "->";
		}

		std::cout << std::endl;
		std::cout << population[i].populationCost << std::endl;
	}

 	return population;
}

std::priority_queue<Population> Genetic::MutateSwap(double number)
{
	clock_t start, end;
	Population pop;
	std::priority_queue<Population> pq = Crossover(getCrossCoefficient());
	Population newPop;

	int x, y;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	start = clock();

	do
	{
		do
		{
			x = rand() % this->vertex;
			y = rand() % this->vertex;

		} while (x == y);

		pop = pq.top();
		pq.pop();

		pop.populationCost = 0;

		if (dis(gen) < number)
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

		pq.push(newPop);

		pop.populationCost = 0;
		newPop.populationCost = 0;

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

		end = clock();

	} while (getStopTime(end, start) <= getTime()/2);

	return pq;
}

std::priority_queue<Population> Genetic::MutateScramble(double number)
{
	clock_t start, end;
	Population pop;
	std::priority_queue<Population> pq = Crossover(getCrossCoefficient());
	Population newPop;

	int firstIndex;
	int lastIndex;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	start = clock();

	do
	{
		do
		{
			firstIndex = rand() % static_cast<int>(this->vertex / 2);
			lastIndex = rand() % static_cast<int>(this->vertex / 2);

		} while (firstIndex == lastIndex || firstIndex > lastIndex);

		pop = pq.top();
		pq.pop();

		pop.populationCost = 0;

		if(dis(gen) < number)
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

		pq.push(newPop);

		pop.populationCost = 0;
		newPop.populationCost = 0;

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

		end = clock();
	}
	while (getStopTime(end, start) <= getTime()/2);

	return pq;
}

std::priority_queue<Population> Genetic::Crossover(double number)
{
	clock_t start, end;
	std::priority_queue<Population> pq;
	Population parent1, parent2;
	Population child;
	std::priority_queue<Population> temp = pq;
	std::vector<bool> visited;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	visited.resize(this->vertex);

	start = clock();

	do
	{
		if (dis(gen) < number)
		{
			parent1 = temp.top();
			temp.pop();
			parent2 = temp.top();
			temp.pop();

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

			temp.push(parent1);
			//temp.push(parent2);
		}

		for (int j = 0; j < child.population.size() - 1; j++)
		{
			child.populationCost += graphData[child.population.at(j)][child.population.at(j + 1)];
		}
		child.populationCost += graphData[child.population.at(child.population.size() - 1)][child.population.at(0)];

		pq.push(child);

		child.population.clear();
		child.populationCost = 0;
		
		//temp.push(child);
			
		end = clock();

	} while (getStopTime(end, start) <= getTime() / 2 || !temp.empty());
	
	//for(auto i: child.population)
	//{
		//std::cout << i << " ";
	//}

	return pq;
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

	bestPath = pop.population;
	bestCost = pop.populationCost;

	std::cout << std::endl;
	std::cout << "Sciezka przejscia: " << std::endl;

	for(int i = 0; i < bestPath.size(); i++)
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
