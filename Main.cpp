#include<iostream>
#include"Menu.h"
#include <ctime>
#include "TimeMeasure.h"
#include <sstream> 

/*TimeMeasure pomiary;
Genetic *gen = new Genetic();
std::vector<int> czasyAlgorytm;
std::vector<std::vector<int>> drogi;
std::vector<int> koszty;

void test(int popul, int times, double coef, int muation, double cross, int size)
{
	gen->setPopulatinCount(popul);
	gen->setTime(times);
	gen->setMutationCoefficient(coef);
	gen->setMutationChoice(muation);
	gen->setCrossCoefficient(cross);

	std::ostringstream ss, ss1, ss2, ss3, ss4;
	ss << muation;
	ss1 << size;
	ss2 << cross;
	ss3 << popul;
	ss4 << times;
	std::string nazwaPlikuAlgorytm = "Metoda " + ss.str() + " Wierzcholki-" + ss1.str() + "Krzyzowanie " + ss2.str() + "Populacja" + ss3.str() + "Wyniki-Czas = " + ss4.str() + ".txt";
	std::string nazwaPlikuDrogi = "Metoda " + ss.str() + " Wierzcholki-" + ss1.str() + "Krzyzowanie " + ss2.str() + "Populacja" + ss3.str() + "Drogi-Czas = " + ss4.str() + ".txt";

	for (int j = 0; j < 5; j++)
	{
		gen->GeneticAlgorithm();
		drogi.push_back(gen->getPath());
		czasyAlgorytm.push_back(gen->getTime());
		koszty.push_back(gen->getCost());
	}
	pomiary.savePath(koszty, nazwaPlikuAlgorytm);
	pomiary.saveToFile(drogi, nazwaPlikuDrogi);
	czasyAlgorytm.clear();
	drogi.clear();
	koszty.clear();
}*/

int main()
{
	srand(time(NULL));
	Menu menu;
	menu.MainMenu();
	
	/*gen->ReadAtspFile("ftv47.atsp", 48);

	test(50, 10, 0.01, 1, 0.8, 48);
	test(100, 15, 0.01, 1, 0.8, 48);
	test(500, 20, 0.01, 1, 0.8, 48);
	test(50, 10, 0.01, 2, 0.8, 48);
	test(100, 15, 0.01, 2, 0.8, 48);
	test(500, 20, 0.01, 2, 0.8, 48);
	
	gen->ReadAtspFile("ftv170.atsp", 171);
	
	test(50, 20, 0.01, 1, 0.8, 171);
	test(100, 25, 0.01, 1, 0.8, 171);
	test(500, 30, 0.01, 1, 0.8, 171);
	test(50, 20, 0.01, 2, 0.8, 171);
	test(100, 25, 0.01, 2, 0.8, 171);
	test(500, 30, 0.01, 2, 0.8, 171);
	
	gen->ReadAtspFile("rbg403.atsp", 403);

	test(50, 300, 0.01, 1, 0.8, 403);
	test(100, 350, 0.01, 1, 0.8, 403);
	test(500, 400, 0.01, 1, 0.8, 403);
	test(50, 300, 0.01, 2, 0.8, 403);
	test(100, 350, 0.01, 2, 0.8, 403);
	test(500, 400, 0.01, 2, 0.8, 403);*/

	return 0;
}

