#include<iostream>
#include"Menu.h"
#include <ctime>
#include "TimeMeasure.h"

TimeMeasure pomiary;
Genetic *gen = new Genetic();
std::vector<double> czasyAlgorytm;
std::vector<int> drogi;
std::vector<double> koszty;

void test(int popul, double times, double coef, int i, int muation)
{
	gen->setPopulatinCount(popul);
	gen->setTime(times);
	gen->setMutationCoefficient(coef);
	gen->setMutationChoice(muation);

	for (int j = 0; j < 10; j++)
	{
		gen->GeneticAlgorithm();
		drogi = gen->getPath();
		czasyAlgorytm.push_back(gen->getTime());
		koszty.push_back(gen->getCost());
	}
	pomiary.saveToFile(czasyAlgorytm, "czasy.txt" + i + gen->getMutationChoice());
	pomiary.savePath(drogi, "drogi.txt" +i + gen->getMutationChoice());
	pomiary.saveToFile(koszty, "koszty.txt"+i + gen->getMutationChoice());
	czasyAlgorytm.clear();
	drogi.clear();
	czasyAlgorytm.clear();
}

int main()
{
	srand(time(NULL));
	Menu menu;
	menu.MainMenu();
	//Graph *graph;
	
	/*gen->ReadAtspFile("ftv47.atsp", 48);
	for(int i = 0; i < 5; i++)
	{
		test(10, 60, 0.01,i,1);
		test(20, 240, 0.01,i,1);
		test(30, 360, 0.01,i,1);
		test(10, 60, 0.01, i, 2);
		test(20, 240, 0.01, i, 2);
		test(30, 360, 0.01, i, 2);
	}

	gen->ReadAtspFile("ftv170.atsp", 171);
	for (int i = 0; i < 5; i++)
	{
		test(10, 120, 0.01, i, 1);
		test(20, 300, 0.01, i, 1);
		test(30, 480, 0.01, i, 1);
		test(10, 120, 0.01, i, 2);
		test(20, 300, 0.01, i, 2);
		test(30, 480, 0.01, i, 2);
	}

	gen->ReadAtspFile("rbg403.atsp", 403);
	for (int i = 0; i < 5; i++)
	{
		test(10, 240, 0.01, i, 1);
		test(20, 360, 0.01, i, 1);
		test(30, 720, 0.01, i, 1);
		test(10, 240, 0.01, i, 2);
		test(20, 360, 0.01, i, 2);
		test(30, 720, 0.01, i, 2);
	}*/
	return 0;
}

